#include "../include/SensorManager.h"


constexpr size_t NBTHREADS = 8;

SensorManager::SensorManager() {
	size_t nThreads = NBTHREADS;
	for (size_t i = 0; i < nThreads; ++i) {
		
		m_workers.emplace_back([this,i, nThreads](std::stop_token st) {
			while (!st.stop_requested()) {
				{
					std::shared_lock lock(m_mutex);
					size_t n = sensors.size();
					const size_t beginIndex = i * n / nThreads;
					const size_t lastIndex = (i + 1) * n / nThreads;
					for (size_t index = beginIndex; index < lastIndex; ++index) {
						if (sensors[index]->tryUpdate()) {
							sensors[index]->updateValues();
						}
					}
				}
				std::this_thread::sleep_for(SLEEPINGTIME);
			}
			});
	}
}


void SensorManager::add(std::unique_ptr<ISensor> sensor) {
	if (sensor == nullptr) return;
	std::unique_lock lock(m_mutex);
	sensors.push_back(std::move(sensor));
	displayBuffer.push_back("");
	return;
}

void SensorManager::remove(std::unique_ptr<ISensor> sensor) {
	std::unique_lock lock(m_mutex);
	if (std::erase(sensors, sensor) > 0) {
		displayBuffer.pop_back();
	}
	return;
}

void SensorManager::removeLast() {
	std::unique_lock lock(m_mutex);
	if (sensors.size() == 0) return;
	std::unique_ptr<ISensor> temp = std::move(sensors.back());
	sensors.pop_back();
	displayBuffer.pop_back();
	std::cout << temp.get()->getName() << " has been removed." << std::endl;;
	return;
}

void SensorManager::dumpState() const{
	std::shared_lock lock(m_mutex);
	std::cout << "Actuellement dans le manager il y a " + std::to_string(sensors.size()) + " sensor(s)" << std::endl;
	for (const auto& s : sensors) {
		std::cout << " - " << s->getName() << " - dt : " << s->getUpdateDt() << std::endl;
	}
	return;
}

/*
void SensorManager::LoopUpdateSensors(milliseconds duration) {
	system_clock::time_point start = system_clock::now();
	system_clock::time_point end = start+duration;
	std::cout << " ---- New loop ---- " << std::endl;
	while (start <= end) {
		updateSensors();
		//displayValue();
		std::this_thread::sleep_for(SLEEPINGTIME);
		start = system_clock::now();
		std::cout << " ---- New loop ---- " << std::endl;
	}
}

void SensorManager::LoopUpdateSensorsMt(milliseconds duration) {
	// Cycle lifetime
	system_clock::time_point start = system_clock::now();
	system_clock::time_point end = start + duration;

	// Thread setup
	const size_t n = sensors.size();
	const size_t nThreads = std::min<size_t>(NBTHREADS, n);
	
	std::vector<std::jthread> workers;
	workers.reserve(nThreads);

	// Update threads
	for (size_t t = 0; t < nThreads; ++t) {
		const size_t beginIndex = t * n / nThreads;
		const size_t lastIndex = (t + 1) * n / nThreads;
		workers.emplace_back([this, beginIndex, lastIndex, end](std::stop_token st) {
			auto next = system_clock::now();
			while (!st.stop_requested() && next < end) {
				for (size_t i = beginIndex; i < lastIndex; ++i) {
					if (sensors[i]->tryUpdate()) {
						sensors[i]->updateValues();
					}
					next += sensors[i]->getUpdateDt();
					
				}
				std::this_thread::sleep_until(next);
			}
		});
	}

	
	// Display data
	auto nextDisplay = system_clock::now();
	int i = 1;
	while (system_clock::now() < end) {
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
*/

void SensorManager::displayValueMtBuffered() const
{
	std::shared_lock lock(m_mutex);
	const size_t sensorSize = sensors.size();
	const size_t nThreads = std::min<size_t>(NBTHREADS, sensorSize);

	std::vector<std::jthread> threads;
	threads.reserve(nThreads);

	auto t0 = steady_clock::now();
	for (size_t t = 0; t < nThreads; ++t) {
		const size_t beginIndex = t * sensorSize / nThreads;
		const size_t lastIndex = (t + 1) * sensorSize / nThreads;
		threads.emplace_back([this, beginIndex, lastIndex] {
			SensorReader reader = SensorReader();
				for (size_t index = beginIndex; index < lastIndex; ++index) {
					reader.readSensor(*sensors[index].get());
					displayBuffer[index] = reader.getValues();
				}
		});
	}

	for (size_t t = 0; t < nThreads; ++t) {
		threads[t].join();
	}
	std::string temp;
	for (int i = 0; i < displayBuffer.size(); i++) {
		temp += displayBuffer[i];
	}
	std::cout << temp << std::endl;
}

void SensorManager::displayValue() const
{
	
	SensorReader reader = SensorReader();
	for (auto& sensor : sensors) {
		reader.readSensor(*sensor);
		reader.printValues();
	}
}
