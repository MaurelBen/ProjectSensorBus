#include "SensorManager.h"
#define SLEEPINGTIME std::chrono::milliseconds(1000)

void SensorManager::add(std::unique_ptr<ISensor> sensor) {
	if (sensor == nullptr) return;
	sensors.push_back(std::move(sensor));
	return;
}
void SensorManager::remove(std::unique_ptr<ISensor> sensor) {
	std::erase(sensors,sensor);
	return;
}

void SensorManager::dumpState() const{
	std::string dump = " actuellement dans le manager il y a " + std::to_string(sensors.size());
	std::cout << dump << std::endl;
	for (const auto& s : sensors) {
		std::cout << " - " << s->getName() << std::endl;
	}
	return;
}

void SensorManager::LoopUpdateSensors(std::chrono::milliseconds time) {
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point end = start+time;
	std::cout << " ---- New loop ---- " << std::endl;
	while (start <= end) {
		updateSensors();
		displayValue();
		std::this_thread::sleep_for(SLEEPINGTIME);
		start = std::chrono::system_clock::now();
		std::cout << " ---- New loop ---- " << std::endl;
	}
}

void SensorManager::LoopUpdateSensorsMt(std::chrono::milliseconds time) {
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point end = start + time;
	// Un thread par capteur
	std::vector<std::jthread> workers;
	workers.reserve(sensors.size());
	for (const auto& sensor : sensors) {
		workers.emplace_back([&sensor, end](std::stop_token st) {
			auto next = std::chrono::system_clock::now();
			while (!st.stop_requested() && next < end) {
				if (sensor->tryUpdate()) {
					sensor->updateValues();
				}
				next += sensor->getUpdateDt();
				std::this_thread::sleep_until(next);
			}
			});
	}

	// Affichage dans le thread courant
	auto nextDisplay = std::chrono::system_clock::now();
	int i = 1;
	while (std::chrono::system_clock::now() < end) {
		std::cout << " ---- New loop ---- " << i << std::endl;
		displayValueMt();
		nextDisplay += SLEEPINGTIME;
		std::this_thread::sleep_until(nextDisplay);
		i++;
	}
}


void SensorManager::updateSensors()
{
	for (auto& sensor : sensors) {
		if (sensor->tryUpdate()) {
			sensor->updateValues();
		}
	}
}

static void readMonoSensor(ISensor& sensor) {
	SensorReader reader = SensorReader();
	reader.readSensor(sensor);
	reader.printValues();
}

void SensorManager::displayValueMt() const
{

	std::vector<std::thread> threads;
	threads.reserve(sensors.size());
	for (auto& sensor : sensors) {
		threads.emplace_back(readMonoSensor, std::ref(*sensor));
	}
	for (auto& t : threads)
		t.join();
}

void SensorManager::displayValue() const
{
	
	SensorReader reader = SensorReader();
	for (auto& sensor : sensors) {
		reader.readSensor(*sensor);
		reader.printValues();
	}
}
