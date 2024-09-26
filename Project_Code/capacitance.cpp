#include "mbed.h"
#include <chrono>
#include <cstdio>

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
    v = 1;
    time.start();
    ThisThread::sleep_for(duration);
    double voltage = capVoltage.read();
    time.stop();
    v = 0; 
    auto elapsedTime = duration_cast<microseconds>(time.elapsed_time()).count();
    double timeSec = elapsedTime * 1e-6;
    return {
        voltage,
        timeSec
    };
}

void capacitance() {
    v = 0; 
    const float RESISTANCE = 4.938e6; 
    // while (capVoltage.read() > 0.0001){
    //     printf("capVoltage %f\n", capVoltage.read());
    //     ;
    // }
    double dur = 10e-3; 
    capValues cV = {0, 0};
    while (cV.voltage < 0.1 && cV.time < 5) {
        printf("dur : %f\n", dur);
        cV = runAndFindCapacitance(dur);
        dur *= 10;
    }
    printf("time : %f\n", cV.time);
    printf("voltage: %f\n", cV.voltage);
    double capacitanceValue = -cV.time / (RESISTANCE * log(1 - cV.voltage));
    if (capacitanceValue >= 1e-6) {
        printf("Capacitance: %f microFarads\n", capacitanceValue * 1e6);
    } else if (capacitanceValue >= 1e-9) {
        printf("Capacitance: %f nanoFarads\n", capacitanceValue * 1e9);
    } else {
        printf("Capacitance: %f picoFarads\n", capacitanceValue * 1e12);
    }

    return;
}