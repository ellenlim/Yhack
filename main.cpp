#include "mbed.h"

#define MAX14690_I2C_ADDR    0x50

DigitalOut led1(LED1); //red
DigitalOut led2(LED2); //green
DigitalOut led3(LED3); //blue
DigitalOut cs(P5_3);
I2C i2cm2(P5_7, P6_0);
SPI spi(P5_1, P5_2, P5_0);

int main()
{
    while (true) {
        cs = 0;
        char data[2];
        int temp;
        
        spi.format(8,3);
        spi.frequency(1000000);
    
        cs = 1;
        
        spi.write(0x01);
        data[0] = spi.write(0x00);
        data[1] = spi.write(0x00);
        
        temp = data[0] + (data[1]<<8);
        printf("Register = %x \n", temp);
        
        //If temperature is above 6C, flash red
        if(temp > 6) {
            led1 = 1;
            led2 = 0;
            led3 = 0;
        }
        //Else if temperature is between 2C and 6C, flash green
        else if(temp <= 6 && temp >= 2) {
            led1 = 0;
            led2 = 1;
            led3 = 0;
        }
        //Else flash blue
        else {
            led1 = 0;
            led2 = 0;
            led3 = 1;
        }
        
        cs = 0;
        
    }
}

