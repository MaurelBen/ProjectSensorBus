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
        if (!choice) {
            if (!std::cin) break;
            std::cout << "Entree invalide\n";
            continue;
        }
        switch (static_cast<Action>(*choice)) {
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

/* IA Made */
std::optional<int> UserInterface::readInt(const std::string& prompt) const {
    std::cout << prompt << std::flush;
    std::string line;
    if (!std::getline(std::cin, line)) return std::nullopt;
    
    int value{};
    const char* end = line.data() + line.size();
    const auto [ptr, ec] = std::from_chars(line.data(), end, value);
    if (ec != std::errc{} || ptr != end) return std::nullopt;
    return value;
}


void UserInterface::handleAdd() {
    auto choice = readInt("UpdateDeltaTime en millisecond (50ms min)?");
    while (!choice) {
        if (!std::cin) return;
        std::cout << "Entree invalide\n";
        choice = readInt("UpdateDeltaTime en millisecond (50ms min)?");
    }
    const std::chrono::milliseconds dt = std::chrono::milliseconds(std::max<int>(*choice, 50));
    std::cout<< "Un nouveau capteur a ete ajoute avec un dt de " << dt << std::endl;

    m_manager.get()->add(std::make_unique<TemperatureSensor>("TempSensor", dt));
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