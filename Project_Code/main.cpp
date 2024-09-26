#include "mbed.h"
#include "freq_counter.hpp"
#include "capacitance.hpp"
#include "resistance.hpp"

BufferedSerial serial_port(USBTX, USBRX);

int main() {
    // while (true) {
    //     char c;
    //     if (serial_port.read(&c, 1)) {
    //         if (c == 'c') {
    //             capacitance();
    //         } else if (c == 'f') {
    //             freq_main();
    //         // } else if (c == 'v') {
    //         //     voltage();
    //         } else if (c == 'r') {
    //             // printf("about to get the resistance\n");
    //             resistance();
    //         } else {
    //             printf("Invalid Character");
    //         }
    //     }
    //     ThisThread::sleep_for(100ms);
    // }
    // resistance();   
    capacitance();
}
