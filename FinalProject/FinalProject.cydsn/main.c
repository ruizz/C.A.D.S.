#include <device.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265359

/*  Global values to be used by all functions */
uint16  counts[4];
uint8   chan = 0;
uint8   sample;


/*  Helper functions */
void    Get_Counts();
float   Calc_Degs();
void    Output_Data(float);

void main() {

    /*  Initialize the mux for the channels. This disconnects all of them,
        the selects the first channel. */
    AMux_1_Init();
    AMux_1_Select(0);
    
    /*  Initialize the LCD for diagnostic information and testing. */
    LCD_Char_1_Start();
    
    /*  Start the ADC, and begin taking reading. It is constantly running, so 
        there is no need to start and stop it. */
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();
    
    /*  Starts the VDCA and sets the voltage to 0.0V. This will default the
        camera to 0degs. */
    VDAC8_1_Start();
    VDAC8_1_SetValue(0);
    
    /*  Initializes and start the counter. The counter will be reset when the first
        sound is heard. */
    Counter_1_Start();

    /*  Values being declared and initialized for the program. */
    memset(counts, 0x0, 8);

    /*  Start the main program loop */
    for(;;) {
        /*  Reset the timer and clear it's FIFO */
        Control_Reg_1_Write(1);
        Control_Reg_1_Write(0);
        Counter_1_ClearFIFO();
        
        /*  Wait for a conversion and take a sample. */
        ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
        sample = ADC_SAR_1_GetResult8();
        
        /*  If the sample passes a certain threshold, then let's enter the
            sampling stage. */
        if(sample > 150) {
            /*  This function captures the timer values for all of the
                microphones. */
            Get_Counts();
            
            /*  Here, Calc_Degs() calculates the direction of the sound from
                the data captured in Get_Counts(). Then, Output_Data takes
                the calculated degree, converts it to the correct voltage,
                outputs the degree voltage through the DAC, and prints 
                diagnostic information on the LCD screen. */
            Output_Data(Calc_Degs());

            /*  Reset the memory and pause the PSoC for 2 seconds. */
            memset(counts, 0x0, 8);
            CyDelay(2000);
        }
        
        /* Switch channels to the next one. */
        chan = (chan + 1) % 4;
        AMux_1_Select(chan);
    }
}

/*  This function populates the counts[] vector with timer data so that the
    direction of the sound can be calculated. */
void Get_Counts() {
    /*  Take the initial counter value for the channel which heard the sound first. */
    counts[chan] = Counter_1_ReadCounter();
    chan = (chan + 1) % 4;
    AMux_1_Select(chan);
    
    /*  Loop through and collect the timer data for the other channels. This
        is mostly the exact same as capturing the first value: by looping. */
    uint8 count = 1;
    while (count < 4) {
        ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
        sample = ADC_SAR_1_GetResult8();
        if((sample > 145) && (counts[chan] == 0)) {
            counts[chan] = Counter_1_ReadCounter();
            count++;
        }
        
        chan = (chan + 1) % 4;
        AMux_1_Select(chan);
    }
}

/*  Calculate the degrees as a float from the captured counter data above,
    and return its value.*/
float Calc_Degs() {
    /*  Find the first channel that heard the sound. This timer value is always
        below 500, usually around 100. */
    uint8 i;
    for(i = 0; i < 4; i++) {
        if(counts[i] < 500) { chan = i; }
    }
    
    /*  Depending on what channel heard it first, we will take the values of the
        channels to the left and to the right, and use trig to find degrees. */
    float degs = 0;
    float mid = 0;
    float diff = 0;
    /*  Switch statement for each channel. Depending on the cardinal directin, we
        need to add a certain amount to go all the way around the circle. */
    switch(chan) {
        case(0):
            /*  Find the middle point between the two times. */
            mid = (counts[1] + counts[2]) / 2;
            /*  Find the difference between the times. */
            diff = fabsf(counts[1] - counts[2]);
            
            /*  Using these above values, use trig to get a degree offset from
                the cardinal direction. */
            degs = atan(diff / mid) * 180 / PI;
            
            /* Depending on the value, add 395 so no negative degrees exist. */
            if(counts[1] < counts[2]) { degs = -degs + 359; }
        break;
        
        /*  The rest are the same, but now we add 90, 180, 270 degrees to ensure
            the offset degrees are added to the correct cardinal value. */
        case(2):
            mid = (counts[0] + counts[3]) / 2;
            diff = fabsf(counts[0] - counts[3]);
            
            degs = atan(diff / mid) * 180 / PI;
            
            if(counts[0] < counts[3]) { degs = -degs; }
            
            degs = degs + 90;
        break;
        
        case(3):
            mid = (counts[1] + counts[2]) / 2;
            diff = fabsf(counts[1] - counts[2]);
            
            degs = atan(diff / mid) * 180 / PI;
            
            if(counts[2] < counts[1]) { degs = -degs; }
            
            degs = degs + 180;
        break;
        
        case(1):
            mid = (counts[0] + counts[3]) / 2;
            diff = fabsf(counts[0] - counts[3]);
            
            degs = atan(diff / mid) * 180 / PI;
            
            if(counts[3] < counts[0]) { degs = -degs + 10; }
            
            degs = degs + 270;
        break;
    }
    
    return degs;
}

void Output_Data(float degs) {
    /*  Send the degree information to the Arduino (servo controller). */
    VDAC8_1_SetValue((195 * degs) / 359);
    
    /* Display diagnostic information on the LDC. */
    LCD_Char_1_ClearDisplay();
    LCD_Char_1_Position(0,12);
    LCD_Char_1_PrintNumber(chan);
    LCD_Char_1_Position(0,0);
    LCD_Char_1_PrintNumber(counts[0]);
    LCD_Char_1_Position(0,6);
    LCD_Char_1_PrintNumber(counts[1]);
    LCD_Char_1_Position(1,0);
    LCD_Char_1_PrintNumber(counts[2]);
    LCD_Char_1_Position(1,6);
    LCD_Char_1_PrintNumber(counts[3]);
    LCD_Char_1_Position(1,12);
    LCD_Char_1_PrintNumber(degs);
}

/* [] END OF FILE */
