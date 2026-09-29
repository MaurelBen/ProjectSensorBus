# ProjectSensorBus

The goal of this project is to create a sensor bus that can be used to read multiple sensors datas in a parallel manner.
The type of the data is only known by the sensor (for exemple an TemperatureSensor have the temperature but a windSensor will have a speed and a direction)

I will do 2 modele of sensor update:
- first i will do a sequencial one, with an array that will update all sensor register in an array
- then i will do a parrallel update with threads

i will also do a customable dump of this value.
At start i will do a standart one, the output will be: sensor value - time
then i will do customable data reader to print data read in a file
