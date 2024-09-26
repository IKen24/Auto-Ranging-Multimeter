#include "mbed.h"
#include <chrono>

using namespace std::chrono;
AnalogIn capVoltage(PA_0);
DigitalOut v(D7);

struct capValues {
    double voltage;
    double time;
};

capValues runAndFindCapacitance(double duration){
    ThisThread::sleep_for(duration / 10);
    Timer time;
    time.start();
    v = 1;
    ThisThread::sleep_for(duration);
    double voltage = capVoltage.read();
    v = 0; 
    time.stop();
    auto elapsedTime = duration_cast<microseconds>(time.elapsed_time()).count();
    double timeSec = elapsedTime * 1e-6;
    return {
        voltage,
        timeSec
    };
}

void capacitance() {
    const float RESISTANCE = 987000; 
    v = 0; 
    ThisThread::sleep_for(3s);
    double dur = 10e-3; 
    capValues cV = {
        0, 0
    };
    while (cV.voltage < 0.1){
        cV = runAndFindCapacitance(dur);
        dur *= 10;
    };
    printf("Time %f\n", cV.time);
    printf("Voltage %f\n", cV.voltage);
    double capacitanceValue = -cV.time / (RESISTANCE * log(1 - cV.voltage));
    if (capacitanceValue >= 1e-6) {
        printf("Capacitance: %f microFarads\n", capacitanceValue * 1e6);
    } else {
        printf("Capacitance: %f nanoFarads\n", capacitanceValue * 1e9);
    }

    return;
}
