#include "SensorManager.h"
#include <numeric>
#define SLEEPINGTIME std::chrono::milliseconds(1000)
constexpr size_t NBTHREADS = 8;

static const std::chrono::time_zone* const timezone = std::chrono::current_zone();

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
	std::cout << "Duree : " << us.count() << " micro \n";

	
	// Affichage dans le thread courant
	auto nextDisplay = std::chrono::system_clock::now();
	int i = 1;
	while (std::chrono::system_clock::now() < end) {
		std::cout << " ---- New loop ---- " << i << std::endl;

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


void SensorManager::displayValueMtBuffered() const
{
	using namespace std::chrono;

	const size_t n = sensors.size();
	const size_t nThreads = std::min<size_t>(NBTHREADS, n);
	zoned_time readAt{ timezone, floor<milliseconds>(system_clock::now()) };

	std::vector<std::jthread> threads;
	threads.reserve(nThreads);

	auto t0 = steady_clock::now();
	for (size_t t = 0; t < nThreads; ++t) {
		const size_t begin = t * n / nThreads;
		const size_t last = (t + 1) * n / nThreads;
		threads.emplace_back([this, begin, last] {
			SensorReader reader = SensorReader();
				for (size_t i = begin; i < last; ++i) {
					reader.readSensor(*sensors[i].get());
					displayBuffer[i] = reader.getValues();
				}
		});
	}

	for (size_t t = 0; t < nThreads; ++t) {
		threads[t].join();
	}
	auto t1 = steady_clock::now();
	std::string temp;
	for (int i = 0; i < displayBuffer.size(); i++) {
		temp += displayBuffer[i];
	}

	auto t2 = steady_clock::now();

	std::cout << temp << std::endl;
	auto t3 = steady_clock::now();
	std::cout << "read " << (t1 - t0)/1000000 << std::endl;
	std::cout << "concat " <<( t2 - t1) / 1000000 << std::endl;
	std::cout << "print " <<( t3 - t2 )/ 1000000 << std::endl;
}

void SensorManager::displayValue() const
{
	
	SensorReader reader = SensorReader();
	for (auto& sensor : sensors) {
		reader.readSensor(*sensor);
		reader.printValues();
	}
}
