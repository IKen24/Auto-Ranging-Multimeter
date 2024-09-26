#include "mbed.h"
#include <chrono>

using namespace std::chrono;
AnalogIn resVoltage(PA_1);
DigitalOut vR(D6);

struct resValues {
    double voltage;
    double time;
};

resValues runAndFindResistance(double duration){
    ThisThread::sleep_for(duration / 10);
    Timer time;
    vR = 1;
    time.start();
    ThisThread::sleep_for(duration);
    double voltage = resVoltage.read();
    time.stop();
    vR = 0; 
    auto elapsedTime = duration_cast<microseconds>(time.elapsed_time()).count();
    double timeSec = elapsedTime * 1e-6;
    return {
        voltage,
        timeSec
    };
}

void resistance() {
    // printf("hello there\n");
    while (resVoltage.read() > 0.001){
        ;
    };
    const float CAPACITANCE = 0.9365e-3; 
    vR = 0; 
    double dur = 10e-3; 
    resValues rV = {
        0, 0
    };
    while (rV.voltage < 0.1 && rV.time < 5){
        rV = runAndFindResistance(dur);
        // printf("time %f\n", rV.time);
        // printf("voltage %f\n", rV.voltage);
        // printf("duration : %f\n", dur);
        dur*=10;
    };
    // printf("time %f\n", rV.time);
    // printf("voltage %f\n", rV.voltage);
    double resistanceValue = -rV.time / (CAPACITANCE * log(1 - rV.voltage));
    if (resistanceValue >= 1e3) {
        printf("Resistance: %f kOhm\n", resistanceValue / 1e3);
    } else {
        printf("Resistance: %f Ohm\n", resistanceValue);
    }
    return;
}