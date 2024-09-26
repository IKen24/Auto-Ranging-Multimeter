// Voltage Level Shift Voltmeter Design

// This voltmeter design requires the use of one AnalogIn pin and the 5V microcontroller supply.

#include "mbed.h"


void get_voltage(){

    AnalogIn adc(A3); // Setting up an analog pin to read in voltage values
    
    adc.set_reference_voltage(3.333333);       // Setting the reference voltage to 3.33333 V, which is the maximum possible node voltage (at 5V input)
                                               // This maximises the resolution of the pin (all bits are used to represent a possible value)
    
    float Vread = adc.read_voltage();           // Returns the voltage as a float, so long as it's below the reference value
    float Vout = 3 * (Vread - 1.666666);        // Equation for linear relationship between voltage read at node and voltage input --> see Falstad file for more details
    float Vout_adjusted = Vout - 0.03;          // Adjusting the voltage value for a small  measurement error, approx. 30 mV

    printf("Voltage: %.2f", Vout_adjusted);
}
