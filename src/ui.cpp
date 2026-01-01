#include "ui.h"
#include "scale.h"
#include "perfiles.h"
#include "input.h"

// ================= VARIABLES =================
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Screen currentScreen = SPLASH;
unsigned long lastInteraction = 0;
static int currentPerfilOption = 0;

// Menú
MenuOption currentMenu = MENU_PESO;
const char* menuText[MENU_COUNT] = { "Peso", "Calibrar", "Perfiles", "Tara" };

// Opciones del submenú perfiles
const char* perfilesMenu[] = {"Cargar", "Crear", "Editar", "Eliminar"};
const int PERFILES_MENU_COUNT = 4;

//Crear perfil
enum PerfilCrearState {
    PERFIL_NOMBRE,
    PERFIL_PESO,
    PERFIL_GUARDAR
};

static PerfilCrearState perfilState = PERFIL_NOMBRE;
static String nombrePerfil = "";
static int pesoPerfil = 100;
static int letraPos = 0;

static const char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";

// ================= INICIALIZACION =================
void uiInit() {
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("Error pantalla");
        while(true); // detener para no seguir con fallos
    }
    display.clearDisplay();
    display.display();
    lastInteraction = millis();
    currentScreen = SPLASH;
}

// ================= LOOP PRINCIPAL =================
void uiLoop() {
    InputButton btn = readButton(); // <-- aquí btn recibe correctamente el valor
    Serial.print("btn = "); Serial.println((int)btn);
    Serial.print("SCREEN = "); Serial.println(currentScreen);

    switch(currentScreen) {

        case SPLASH:
            renderSplash();
            if (millis() - lastInteraction > 1000) {
                currentScreen = PRINCIPAL;
                lastInteraction = millis();
            }
            break;

        case PRINCIPAL:
            renderPrincipal();
            if (btn == BTN_SELECT) {
                currentScreen = MENU;
            }
            break;

        case MENU:
            if(btn == BTN_UP || btn == BTN_DOWN)
                menuNavigate((int&)currentMenu, MENU_COUNT, btn);

            if (btn == BTN_SELECT)
                handleMenuSelect(currentMenu);

            renderMenuGenerico("MENU", menuText, MENU_COUNT, currentMenu);
            break;

        case SUBMENU_PERFILES:
            if(btn == BTN_UP || btn == BTN_DOWN)
                menuNavigate(currentPerfilOption, PERFILES_MENU_COUNT, btn);

            if (btn == BTN_SELECT)
                perfilSelect();

            renderMenuGenerico("PERFILES", perfilesMenu, PERFILES_MENU_COUNT, currentPerfilOption);
            break;

        case CREAR_PERFIL:
        crearPerfilInteractivo(btn);
        break;
    }
}

// ================= PANTALLA SPLASH =================
void renderSplash() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    display.println("Inicializando");
    display.setCursor(0, 40);
    display.println("balanza ESP32");

    int barra = ((millis() / 200) % 6) + 1;
    for(int i=0; i<barra; i++) {
        display.fillRect(110 + i*3, 55, 2, 4, SSD1306_WHITE);
    }
    display.display();
}

// ================= PANTALLA PRINCIPAL =================
void renderPrincipal() {
    display.clearDisplay();

    int peso = leerPesoEstable();

    int16_t x, y;
    uint16_t w, h;
    String s = String(peso) + " g";

    display.setTextSize(2);
    display.getTextBounds(s, 0, 0, &x, &y, &w, &h);
    display.setCursor((SCREEN_WIDTH - w)/2, (SCREEN_HEIGHT - h)/2);
    display.setTextColor(SSD1306_WHITE);
    display.println(s);

    // Mostrar versión
    String ver = "DSH v0.3";
    display.setTextSize(1);
    display.getTextBounds(ver, 0, 0, &x, &y, &w, &h);
    display.setCursor(SCREEN_WIDTH - w - 1, SCREEN_HEIGHT - h - 1);
    display.println(ver);

    display.display();
}

// ================= RENDER GENÉRICO =================

void renderMenuGenerico(
    const char* titulo,
    const char** opciones,
    int count,
    int selected
) {
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(titulo);

    for (int i = 0; i < count; i++) {
        int y = 15 + i * 12;

        if (i == selected) {
            display.fillRoundRect(0, y - 1, SCREEN_WIDTH, 10, 2, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
        } else {
            display.setTextColor(SSD1306_WHITE);
        }

        display.setCursor(5, y);
        display.print(opciones[i]);
    }

    display.display();
}

// ================= NAVEGACIÓN =================

void menuNavigate(int &index, int count, InputButton btn) {
    if (btn == BTN_UP) {
        index = (index - 1 + count) % count;
    }
    else if (btn == BTN_DOWN) {
        index = (index + 1) % count;
    }
}

// ================= ACCIONES DEL MENÚ =================
void handleMenuSelect(MenuOption m) {
    switch(m) {
        case MENU_PESO: mostrarPeso(); break;
        case MENU_TARA: ejecutarTara(); break;
        case MENU_PERFILES: abrirSubMenuPerfiles(); break;
        case MENU_CALIBRAR: calibrar(); break;
    }
}

// ================= ACCIONESSUBMENÚ PERFILES =================

void perfilSelect() {
    switch (currentPerfilOption) {
        case 0: // Cargar
            break;
        case 1: // Crear
            perfilState = PERFIL_NOMBRE;
            nombrePerfil = "";
            pesoPerfil = 0;
            letraPos = 0;
            currentScreen = CREAR_PERFIL; // pantalla dedicada a crear perfil
            break;            
            break;
        case 2: // Editar
            break;
        case 3: // Eliminar
            break;
    }
}

// ================= FUNCIONES =================
void mostrarPeso() {
    currentScreen = PRINCIPAL;
}

void ejecutarTara() {
    aplicarTara();   // ✅ llamando a la función de scale
    Serial.println("[TARA] Tara aplicada");
    currentScreen = PRINCIPAL;
}

void calibrar() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,20);
    display.println("Flujo calibracion");
    display.display();
}

void crearPerfilInteractivo(InputButton b) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // -------------------- NOMBRE --------------------
    if (perfilState == PERFIL_NOMBRE) {
        display.setCursor(0, 0);
        display.println("Nombre perfil:");

        display.setCursor(0, 20);
        display.print(nombrePerfil);
        display.print(letras[letraPos]);
        display.print("_"); // cursor visual

        // Navegación de letras
        if (b == BTN_UP) {
            letraPos = (letraPos + 1) % (sizeof(letras) - 1); // ciclo circular
        } 
        else if (b == BTN_DOWN) {
            letraPos = (letraPos - 1 + (sizeof(letras) - 1)) % (sizeof(letras) - 1);
        } 
        else if (b == BTN_SELECT) {
            // Espacio (' ') significa terminar nombre
            if (letras[letraPos] == ' ') {
                perfilState = PERFIL_PESO;
            } else {
                nombrePerfil += letras[letraPos];
            }
        }
    }

    // -------------------- PESO --------------------
    else if (perfilState == PERFIL_PESO) {
        display.setCursor(0, 0);
        display.println("Peso perfil (g):");

        display.setCursor(0, 20);
        display.print(pesoPerfil);
        display.println(" g");

        // Ajuste de peso
        if (b == BTN_UP) pesoPerfil++;
        else if (b == BTN_DOWN && pesoPerfil > 0) pesoPerfil--;
        else if (b == BTN_SELECT) {
            perfilState = PERFIL_GUARDAR;
        }
    }

    // -------------------- GUARDAR --------------------
    else if (perfilState == PERFIL_GUARDAR) {
        crearPerfil(nombrePerfil, pesoPerfil); // función que guarda tu perfil
        // Reset de variables y regreso al submenú
        perfilState = PERFIL_NOMBRE;
        nombrePerfil = "";
        pesoPerfil = 0;
        letraPos = 0;
        currentScreen = SUBMENU_PERFILES;
        return; // importante salir antes de display.display()
    }

    display.display();
}

void abrirSubMenuPerfiles() {
    currentPerfilOption = 0;
    currentScreen = SUBMENU_PERFILES;
    lastInteraction = millis();
    readButton(); // limpia evento previo (SELECT)
}

