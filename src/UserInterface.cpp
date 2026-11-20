#include "../include/UserInterface.h"
#include <numeric>

UserInterface::UserInterface() {
    m_manager = std::make_unique<SensorManager>();
}

void UserInterface::run() {
    bool running = true; 
    m_manager.get()->dumpState();
    while (running) {
        showMenu();
        const auto choice = readInt("> ");
        if (choice < 0) {
            continue;
        }
        switch (static_cast<Action>(choice)) {
        case Action::AddSensor:    handleAdd();    break;
        case Action::RemoveSensor: handleRemove(); break;
        case Action::PrintState:   handleDump();  break;
        case Action::DisplaySensorValue:   handleDisplay();  break;
        case Action::Quit:         running = false; break;
        default: std::cout << "Choix inconnu\n";
        }
    }
}

void UserInterface::showMenu() const {
    std::cout << "\n1. Ajouter un capteur\n"
        "2. Retirer un capteur\n"
        "3. Afficher l'etat actuel du manager\n"
        "4. Afficher les valeurs des capteurs\n"
        "0. Quitter\n";
}


int UserInterface::readInt(const std::string& prompt) const {
    std::cout << prompt << std::endl;
    std::string temp;
    std::cin >> temp;
    int value;
    try {
        value = stoi(temp);
    } 
    catch(const std::invalid_argument&){
        std::cerr << "Entree invalide, un nombre est attendu" << std::endl;
        value = -1;
    }

    return value;
}


void UserInterface::handleAdd() {
    auto choice = readInt("UpdateDeltaTime en millisecond (" + std::to_string(SLEEPINGTIME.count()) +" min) ? ");
    while (choice< SLEEPINGTIME.count()) {
        std::cout << "Entree invalide: un entier > 50 est necessaire" << std::endl;
        choice = readInt("UpdateDeltaTime en millisecond ("+ std::to_string(SLEEPINGTIME.count()) +" min) ? ");
    }
    std::cout<< "Un nouveau capteur a ete ajoute avec un dt de " << choice << std::endl;

    m_manager.get()->add(std::make_unique<TemperatureSensor>("TempSensor", std::chrono::milliseconds(choice)));
    return;
}
void UserInterface::handleRemove() {
    m_manager.get()->removeLast();
    return;
}
void UserInterface::handleDump() const {
    m_manager.get()->dumpState();
    return;
}
void UserInterface::handleDisplay() const {
    m_manager.get()->displayValueMtBuffered();
    return;
}