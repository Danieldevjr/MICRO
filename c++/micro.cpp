#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <cstdlib>

// Estrutura para monitoramento de ambientes
class Sensor {
public:
    virtual void readData() = 0;
};

class SensorLuz : public Sensor {
public:
    void readData() override {
        // Aqui você poderia ler o valor real do sensor
        std::cout << "Luz: " << rand() % 100 << " lux" << std::endl;
    }
};

class SensorTemperatura : public Sensor {
public:
    void readData() override {
        std::cout << "Temperatura: " << (rand() % 10 + 20) << " °C" << std::endl;
    }
};

class SensorUmidade : public Sensor {
public:
    void readData() override {
        std::cout << "Umidade: " << (rand() % 30 + 50) << "%" << std::endl;
    }
};

class SensorGases : public Sensor {
public:
    void readData() override {
        // Aqui poderia ser detectado a presença de gases nocivos
        std::cout << "Gases nocivos: " << (rand() % 2 == 0 ? "Não detectado" : "Detectado") << std::endl;
    }
};

class SensorPresenca : public Sensor {
public:
    void readData() override {
        std::cout << "Presença: " << (rand() % 2 == 0 ? "Ausente" : "Presente") << std::endl;
    }
};

// Classe para atuadores
class Atuador {
public:
    virtual void control(bool action) = 0;
};

class AtuadorLuz : public Atuador {
public:
    void control(bool action) override {
        std::cout << "Luz " << (action ? "ligada" : "desligada") << std::endl;
    }
};

class AtuadorArCondicionado : public Atuador {
public:
    void control(bool action) override {
        std::cout << "Ar-condicionado " << (action ? "ligado" : "desligado") << std::endl;
    }
};

// Classe para controle de rotinas
class SistemaAutomacao {
public:
    void configurarRotinaPresenca(bool presenca) {
        if (presenca) {
            std::cout << "Rotina: Ajustar dispositivos conforme preferências de presença." << std::endl;
        } else {
            std::cout << "Rotina: Desligar dispositivos para economia de energia." << std::endl;
        }
    }
};

int main() {
    // Criar instâncias dos sensores
    SensorLuz sensorLuz;
    SensorTemperatura sensorTemperatura;
    SensorUmidade sensorUmidade;
    SensorGases sensorGases;
    SensorPresenca sensorPresenca;

    // Criar instâncias dos atuadores
    AtuadorLuz atuadorLuz;
    AtuadorArCondicionado atuadorArCondicionado;

    // Criar sistema de automação
    SistemaAutomacao sistema;

    // Exemplo de leitura de sensores
    sensorLuz.readData();
    sensorTemperatura.readData();
    sensorUmidade.readData();
    sensorGases.readData();
    sensorPresenca.readData();

    // Exemplo de controle de atuadores
    atuadorLuz.control(true); // Ligar luz
    atuadorArCondicionado.control(false); // Desligar ar-condicionado

    // Configuração de rotinas
    bool presenca = rand() % 2 == 0; // Simula a presença ou ausência
    sistema.configurarRotinaPresenca(presenca);

    return 0;
}
