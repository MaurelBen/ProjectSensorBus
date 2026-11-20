# ProjectSensorBus

The goal of this project is to create a sensor bus that can be used to read multiple sensors datas in a parallel manner.
The type of the data is only known by the sensor (for exemple an TemperatureSensor have the temperature but a windSensor will have a speed and a direction).


The code is easily maintainable, the ISensor abstract class allows a polymorphism on the type of sensor, and the SensorReader class can be overloaded (especially the printvalues method) with a different display or display target.
The code of version 1.0 is based on a manager who manages everything from the back end. Sensors are updated via threads which are instantiated at the same time as the manager and distribute the different sensor created.

Early on this project i was creating as many thread as sensors but it cost more cpu time than with only one thead. So i change it to be more relevant. 
Currently i set a pool of 8 thread taking a part of the whole pool of sensors and update them if needed. This repartition is update each time we add or remove a sensor to avoid miss matching index.

During add or remove, i use a mutex to lock down the memory acces and avoid data race. 

Threads are handled by jThreads witch respect the RAII principle and are automaticly and nicely free at the end of their context (in that case the manager. When we remove delete the manager, threads are automaticly free).

The UI is only used to perform the various actions that can be carried out using the manager.

I tried in this projet to respect the more i can get the design patern i know to have a clean and flex code.

## Build

cmake -B build 

cmake --build build --config Release

./build/Release/sensor_sim.exe

### Prérequis
CMake ≥ 3.20

I use some smart pointers and jthreads (instead of basic pointers and basic thread) that i haven't experiments a lot in my dev life to be able to fully learn how they work
Compilateur C++17 (MSVC 2022, GCC 11+, Clang 14+) 


## Limits and future improvement

Actually, the ui is really poor, i have to project to add more fonctionnality (like creation option or freeze update)
I have not test every inch of this programm so i will add some unit test 
I also had to run some benchmark on the tread performance to see the real limits of my architechture.


