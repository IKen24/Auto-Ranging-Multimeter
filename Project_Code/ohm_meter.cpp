#include "mbed.h"

AnalogIn adcIn(A0);
AnalogOut dacOut(A2);


// int main(){
//     while (true) {
//         float dacVoltage = 1.0;
//         dacOut.write(dacVoltage);


//         float voltage = adcIn.read()*dacVoltage;
//         float resistance;

//         float knownResistor = 1000.0;
//         resistance = (knownResistor * voltage)/(dacVoltage - voltage);

//         printf("Resistance: %.2f Ohms\r\n", resistance);

//         ThisThread::sleep_for(500ms);
//     }
// }