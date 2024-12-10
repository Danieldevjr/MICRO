#include <WiFi.h>
#include <ESP32WebServer.h>
#include <ArduinoJson.h>  // Para enviar e receber dados em formato JSON

// Credenciais Wi-Fi
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Configuração do servidor HTTP
ESP32WebServer server(80);

// Funções para sensores (simuladas, você pode substituir com leitura de sensores reais)
int readLuz() {
    return random(0, 100);  // Simula o nível de luz (0-100 lux)
}

int readTemperatura() {
    return random(20, 30);  // Simula a temperatura (20-30°C)
}

int readUmidade() {
    return random(50, 80);  // Simula a umidade (50-80%)
}

bool readPresenca() {
    return random(0, 2) == 0;  // Simula presença (true ou false)
}

bool readGases() {
    return random(0, 2) == 0;  // Simula presença de gases (true ou false)
}

// Funções para controlar atuadores (simuladas)
void controlLuz(bool action) {
    Serial.println(action ? "Luz ligada" : "Luz desligada");
}

void controlArCondicionado(bool action) {
    Serial.println(action ? "Ar-condicionado ligado" : "Ar-condicionado desligado");
}

// Rota para obter os dados dos sensores
void handleGetSensorsData() {
    StaticJsonDocument<200> doc;
    doc["luz"] = readLuz();
    doc["temperatura"] = readTemperatura();
    doc["umidade"] = readUmidade();
    doc["presenca"] = readPresenca() ? "Presente" : "Ausente";
    doc["gases"] = readGases() ? "Detectado" : "Não detectado";

    String response;
    serializeJson(doc, response);
    server.send(200, "application/json", response);
}

// Rota para controlar os atuadores (Luz e Ar Condicionado)
void handleControlActuators() {
    if (server.hasArg("luz")) {
        String luz = server.arg("luz");
        controlLuz(luz == "on");
    }
    if (server.hasArg("ar_condicionado")) {
        String ac = server.arg("ar_condicionado");
        controlArCondicionado(ac == "on");
    }

    server.send(200, "text/plain", "Comando recebido");
}

// Rota para definir a rotina automatizada
void handleSetRoutine() {
    if (server.hasArg("presenca")) {
        bool presenca = server.arg("presenca") == "true";
        if (presenca) {
            controlLuz(true);
            controlArCondicionado(true);
        } else {
            controlLuz(false);
            controlArCondicionado(false);
        }
    }
    server.send(200, "text/plain", "Rotina configurada");
}

void setup() {
    // Inicializa a comunicação serial
    Serial.begin(115200);

    // Conecta à rede Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando-se ao Wi-Fi...");
    }
    Serial.println("Conectado ao Wi-Fi");

    // Configuração das rotas
    server.on("/sensors", HTTP_GET, handleGetSensorsData);   // Rota para obter dados dos sensores
    server.on("/actuators", HTTP_POST, handleControlActuators);  // Rota para controlar atuadores
    server.on("/routine", HTTP_POST, handleSetRoutine);   // Rota para configurar rotina automatizada

    // Inicia o servidor HTTP
    server.begin();
    Serial.println("Servidor HTTP iniciado");
}

void loop() {
    server.handleClient();  // Mantém o servidor HTTP funcionando
}
