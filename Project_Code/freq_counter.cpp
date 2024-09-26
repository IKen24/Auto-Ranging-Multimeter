#include "mbed.h"
#include <chrono>


//Based off double 3904 voltage-controlled voltage amp, 2.2k base
//resistor to primary transistor gives a threshold voltage of 500mV, 
//while 10k gives a threshold voltage of 700mV, 400mV without a base resistor



float sample(){
    DigitalIn freqIn(D4);
    Timer t;
    bool running = true;
    bool measuring = false;
    long long timeus;
    float freq;

    while(running){

        //Measure the digital state of the freqIn pin, and if a sequential
        //zero then one is recorded, timer is started. Chose not the use built-in
        //rising edge detector, as that would require total rewrite for little to 
        //no improvement

        int pinVal = freqIn.read();
        if (pinVal == 0 && measuring == false){
            pinVal = freqIn.read();
            if (pinVal == 1 && measuring == false){
                t.start();
                measuring = true; 
                
            }
        }

        //If a low is detected on the digital in, and the measuring flag
        //is high, the timer is stopped, the elapsed time is microseconds
        //cast to timeus, and the measuring and running flags brought low

        if (pinVal == 0 && measuring == true){
            t.stop();
            timeus = std::chrono::duration_cast<chrono::microseconds>(t.elapsed_time()).count();
            measuring = false;
            running = false;
        }


    }

    //Return the time measured by the function

    return timeus;

}


void freq_main(){

    //Set the button as a digital in, and instantiate variables for averaging

    //DigitalIn button(BUTTON1); "to enable the button to be used in main instead"

    float sum = 0;
    float i = 0;

        //If the button is depressed, and the function is not already measuring,
        //if statement will sample the input, add the measured time to the total,
        //and increment the sample number counter

    while (i < 10){ //changed triggering method to whether the sample number is less than 10, instead of button
        float time = sample();
        sum += time;
        i += 1;
    }

        //If the number of samples taken is greater than zero, ie that a signal has been 
        //measured, the average time of the pulses is calculated, the frequency thus found,
        //and printed to the serial out. The averageing variables are then set to zero

       
    if (i > 1){
        float average = sum/i;
        float freq = 1/((average/1e6)*2);
        if (freq > 1000){
         printf("The frequency of the signal is %.2f kHz \n", freq/1000);
        }
        else{
            printf("The frequency of the signal is %.2f Hz \n", freq);
        }
        sum = 0;
        i = 0;
    }

}

// Currently 95% accurate at 40kHz, 94% accurate at 50kHz, ~85% accurate at 100kHz


//printf tends to add at least 2500μs of execution time