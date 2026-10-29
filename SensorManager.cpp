#include "SensorManager.h"
#include <numeric>
#define SLEEPINGTIME std::chrono::milliseconds(1000)

void SensorManager::add(std::unique_ptr<ISensor> sensor) {
	if (sensor == nullptr) return;
	sensors.push_back(std::move(sensor));
	displayBuffer.push_back("");
	return;
}

void SensorManager::remove(std::unique_ptr<ISensor> sensor) {
	std::erase(sensors,sensor);
	displayBuffer.pop_back();
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


	auto debut = std::chrono::steady_clock::now();	

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

	auto fin = std::chrono::steady_clock::now();
	auto us = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut);
	std::cerr << "Duree : " << us.count() << " micro \n";

	
	// Affichage dans le thread courant
	auto nextDisplay = std::chrono::system_clock::now();
	int i = 1;
	while (std::chrono::system_clock::now() < end) {
		std::cout << " ---- New loop ---- " << i << std::endl;
		/*
		debut = std::chrono::steady_clock::now();
		displayValueMt();
		fin = std::chrono::steady_clock::now();
		us = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut);
		std::cerr << "Duree : " << us.count() << " micro s\n";*/

		displayValueMtBuffered();

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

static void readMonoSensorBuffered(ISensor& sensor,std::string* value) {
	SensorReader reader = SensorReader();
	reader.readSensor(sensor);
	*value = reader.getValues();
}

void SensorManager::displayValueMt() const
{
	std::vector<std::thread> threads;
	threads.reserve(sensors.size());
	for (size_t i = 0; i < sensors.size(); ++i) {
		threads.emplace_back(readMonoSensor, std::ref(*sensors[i]));
	}
	for (auto& t : threads)
		t.join();
}

void SensorManager::displayValueMtBuffered() const
{
	using namespace std::chrono;
	using namespace std;
	std::vector<std::thread> threads;
	auto t0 = steady_clock::now();
	threads.reserve(sensors.size());
	for (size_t i = 0; i < sensors.size(); ++i) {
		threads.emplace_back(readMonoSensorBuffered, std::ref(*sensors[i]), &displayBuffer[i]);
	}
	for (auto& t : threads)
		t.join();
	auto t1 = steady_clock::now();
	auto temp = std::accumulate(displayBuffer.begin(), displayBuffer.end(), std::string{});
	auto t2 = steady_clock::now();

	std::cout << temp<< std::endl;
	auto t3 = steady_clock::now();

	cout << "Update Thread" << t1 - t0 << endl;
	cout << "Concat string" << t2 - t1 << endl;
	cout << "print string" << t3 - t2 << endl;
	
}

void SensorManager::displayValue() const
{
	
	SensorReader reader = SensorReader();
	for (auto& sensor : sensors) {
		reader.readSensor(*sensor);
		reader.printValues();
	}
}
