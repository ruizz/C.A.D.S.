/*******************************************************************************
* File Name: LCD_Char_1.c
* Version 1.90
*
* Description:
*  This file provides source code for the Character LCD component's API.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "LCD_Char_1.h"


static void LCD_Char_1_WrDatNib(uint8 nibble) ;
static void LCD_Char_1_WrCntrlNib(uint8 nibble) ;

/* Stores the state of conponent. Indicates wherewer component is 
* in enable state or not.
*/
uint8 LCD_Char_1_enableState = 0u;

uint8 LCD_Char_1_initVar = 0u;


/*******************************************************************************
* Function Name: LCD_Char_1_Init
********************************************************************************
*
* Summary:
*  Perform initialization required for components normal work.
*  This function initializes the LCD hardware module as follows:
*        Enable 4-bit interface
*        Clear the display
*        Enable auto cursor increment
*        Resets the cursor to start position
*  Also loads custom character set to LCD if it was defined in the customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Char_1_Init(void) 
{
    /* INIT CODE */
    CyDelay(40u);                                                        /* Delay 40 ms */
    LCD_Char_1_WrCntrlNib(LCD_Char_1_DISPLAY_8_BIT_INIT);    /* Selects 8-bit mode */
    CyDelay(5u);                                                         /* Delay 5 ms */
    LCD_Char_1_WrCntrlNib(LCD_Char_1_DISPLAY_8_BIT_INIT);    /* Selects 8-bit mode */
    CyDelay(15u);                                                        /* Delay 15 ms */
    LCD_Char_1_WrCntrlNib(LCD_Char_1_DISPLAY_8_BIT_INIT);    /* Selects 8-bit mode */
    CyDelay(1u);                                                         /* Delay 1 ms */
    LCD_Char_1_WrCntrlNib(LCD_Char_1_DISPLAY_4_BIT_INIT);    /* Selects 4-bit mode */
    CyDelay(5u);                                                         /* Delay 5 ms */

    LCD_Char_1_WriteControl(LCD_Char_1_CURSOR_AUTO_INCR_ON);    /* Incr Cursor After Writes */
    LCD_Char_1_WriteControl(LCD_Char_1_DISPLAY_CURSOR_ON);      /* Turn Display, Cursor ON */
    LCD_Char_1_WriteControl(LCD_Char_1_DISPLAY_2_LINES_5x10);   /* 2 Lines by 5x10 Characters */
    LCD_Char_1_WriteControl(LCD_Char_1_DISPLAY_CURSOR_OFF);     /* Turn Display, Cursor OFF */
    LCD_Char_1_WriteControl(LCD_Char_1_CLEAR_DISPLAY);          /* Clear LCD Screen */
    LCD_Char_1_WriteControl(LCD_Char_1_DISPLAY_ON_CURSOR_OFF);  /* Turn Display ON, Cursor OFF */
    LCD_Char_1_WriteControl(LCD_Char_1_RESET_CURSOR_POSITION);  /* Set Cursor to 0,0 */
    CyDelay(5u);

    #if(LCD_Char_1_CUSTOM_CHAR_SET != LCD_Char_1_NONE)
        LCD_Char_1_LoadCustomFonts(LCD_Char_1_customFonts);
    #endif /* LCD_Char_1_CUSTOM_CHAR_SET != LCD_Char_1_NONE */
}


/*******************************************************************************
* Function Name: LCD_Char_1_Enable
********************************************************************************
*
* Summary:
*  Turns on the display.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
* Theory:
*  This finction has no effect when it called first time as
*  LCD_Char_1_Init() turns on the LCD.
*
*******************************************************************************/
void LCD_Char_1_Enable(void) 
{
    LCD_Char_1_DisplayOn();
    LCD_Char_1_enableState = 1u;
}


/*******************************************************************************
* Function Name: LCD_Char_1_Start
********************************************************************************
*
* Summary:
*  Perform initialization required for components normal work.
*  This function initializes the LCD hardware module as follows:
*        Enable 4-bit interface
*        Clear the display
*        Enable auto cursor increment
*        Resets the cursor to start position
*  Also loads custom character set to LCD if it was defined in the customizer.
*  If it was not the first call in this project then it just turns on the
*  display
*
*
* Parameters:
*  LCD_Char_1_initVar - global variable.
*
* Return:
*  LCD_Char_1_initVar - global variable.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Char_1_Start(void) 
{
    /* If not initialized then perform initialization */
    if(LCD_Char_1_initVar == 0u)
    {
        LCD_Char_1_Init();
        LCD_Char_1_initVar = 1u;
    }

    /* Turn on the LCD */
    LCD_Char_1_Enable();
}


/*******************************************************************************
* Function Name: LCD_Char_1_Stop
********************************************************************************
*
* Summary:
*  Turns off the display of the LCD screen.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Char_1_Stop(void) 
{
    /* Calls LCD Off Macro */
    LCD_Char_1_DisplayOff();
    LCD_Char_1_enableState = 0u;
}


/*******************************************************************************
*  Function Name: LCD_Char_1_Position
********************************************************************************
*
* Summary:
*  Moves active cursor location to a point specified by the input arguments
*
* Parameters:
*  row:     Specific row of LCD module to be written
*  column:  Column of LCD module to be written
*
* Return:
*  None.
*
* Note:
*  This only applies for LCD displays which use the 2X40 address mode.
*  This results in Row 2 offset from row one by 0x28.
*  When there are more than 2 rows, each row must be fewer than 20 characters.
*
*******************************************************************************/
void LCD_Char_1_Position(uint8 row, uint8 column) 
{
    switch (row)
    {
        case (uint8)0:
            LCD_Char_1_WriteControl(LCD_Char_1_ROW_0_START + column);
            break;
        case (uint8) 1:
            LCD_Char_1_WriteControl(LCD_Char_1_ROW_1_START + column);
            break;
        case (uint8) 2:
            LCD_Char_1_WriteControl(LCD_Char_1_ROW_2_START + column);
            break;
        case (uint8) 3:
            LCD_Char_1_WriteControl(LCD_Char_1_ROW_3_START + column);
            break;
        default:
            /* if default case is hit, invalid row argument was passed.*/
            break;
    }
}


/*******************************************************************************
* Function Name: LCD_Char_1_PrintString
********************************************************************************
*
* Summary:
*  Writes a zero terminated string to the LCD.
*
* Parameters:
*  string:  pointer to head of char8 array to be written to the LCD module
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_Char_1_PrintString(char8 const string[]) 
{
    uint8 indexU8 = 1u;
    char8 current = *string;

    /* Until null is reached, print next character */
    while((char8) '\0' != current)
    {
        LCD_Char_1_WriteData((uint8)current);
        current = string[indexU8];
        indexU8++;
    }
}


/*******************************************************************************
*  Function Name: LCD_Char_1_PutChar
********************************************************************************
*
* Summary:
*  Writes a single character to the current cursor position of the LCD module.
*  Custom character names (_CUSTOM_0 through
*  _CUSTOM_7) are acceptable as inputs.
*
* Parameters:
*  character:  character to be written to the LCD
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_Char_1_PutChar(char8 character) 
{
    LCD_Char_1_WriteData((uint8)character);
}


/*******************************************************************************
*  Function Name: LCD_Char_1_WriteData
********************************************************************************
*
* Summary:
*  Writes a data byte to the LCD module's Data Display RAM.
*
* Parameters:
*  dByte:  byte to be written to LCD module.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_Char_1_WriteData(uint8 dByte) 
{
    uint8 nibble;

    LCD_Char_1_IsReady();
    nibble = dByte >> LCD_Char_1_NIBBLE_SHIFT;

    /* Write high nibble */
    LCD_Char_1_WrDatNib(nibble);

    nibble = dByte & LCD_Char_1_NIBBLE_MASK;
    /* Write low nibble */
    LCD_Char_1_WrDatNib(nibble);
}


/*******************************************************************************
*  Function Name: LCD_Char_1_WriteControl
********************************************************************************
*
* Summary:
*  Writes a command byte to the LCD module.
*
* Parameters:
*  cByte:   byte to be written to LCD module.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_Char_1_WriteControl(uint8 cByte) 
{
    uint8 nibble;

    LCD_Char_1_IsReady();

    nibble = cByte >> LCD_Char_1_NIBBLE_SHIFT;
    
    /* WrCntrlNib(High Nibble) */
    LCD_Char_1_WrCntrlNib(nibble);
    nibble = cByte & LCD_Char_1_NIBBLE_MASK;

    /* WrCntrlNib(Low Nibble) */
    LCD_Char_1_WrCntrlNib(nibble);
}


/*******************************************************************************
* Function Name: LCD_Char_1_IsReady
********************************************************************************
*
* Summary:
*  Polls LCD until the ready bit is set.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  Changes pins to High-Z.
*
*******************************************************************************/
void LCD_Char_1_IsReady(void) 
{
    uint8 value;

    /* Clear the LCD port*/
    LCD_Char_1_PORT_DR_REG &= ((uint8)(~LCD_Char_1_PORT_MASK));

    /* PSoC4 has a bit different port/pin organization for setting Drive Modes than
    * PSoC3/5.
    */
    #if (CY_PSOC4)
        
        /* Mask off data pins to clear old values out */
        value = LCD_Char_1_PORT_PC_REG & ((uint32) (~ LCD_Char_1_DM_DATA_MASK));
        /* Load in high Z values for data pins, others unchanged */
        LCD_Char_1_PORT_PC_REG = value | LCD_Char_1_HIGH_Z_DATA_DM;

    #else
    
        /* Change Port to High-Z Status on data pins */

        /* Mask off data pins to clear old values out */
        value = LCD_Char_1_PORT_DM0_REG & ((uint8)(~LCD_Char_1_DATA_MASK));
        /* Load in high Z values for data pins, others unchanged */
        LCD_Char_1_PORT_DM0_REG = value | (LCD_Char_1_HIGH_Z_DM0 & LCD_Char_1_DATA_MASK);

        /* Mask off data pins to clear old values out */
        value = LCD_Char_1_PORT_DM1_REG & ((uint8)(~LCD_Char_1_DATA_MASK));
        /* Load in high Z values for data pins, others unchanged */
        LCD_Char_1_PORT_DM1_REG = value;

        /* Mask off data pins to clear old values out */
        value = LCD_Char_1_PORT_DM2_REG & ((uint8)(~LCD_Char_1_DATA_MASK));
        /* Load in high Z values for data pins, others unchanged */
        LCD_Char_1_PORT_DM2_REG = value;
    
    #endif /* CY_PSOC4 */
    
    /* Make sure RS is low */
    LCD_Char_1_PORT_DR_REG &= ((uint8)(~LCD_Char_1_RS));

    /* Set R/W high to read */
    LCD_Char_1_PORT_DR_REG |= LCD_Char_1_RW;

    do
    {
        /* 40 ns delay required before rising Enable and 500ns between neighbour Enables */
        CyDelayUs(0u);

        /* Set E high */
        LCD_Char_1_PORT_DR_REG |= LCD_Char_1_E;

        /* 360 ns delay the setup time for data pins */
        CyDelayUs(1u);

        /* Get port state */
        value = LCD_Char_1_PORT_PS_REG;

        /* Set enable low */
        LCD_Char_1_PORT_DR_REG &= ((uint8)(~LCD_Char_1_E));

        /* This gives a true delay between disably Enable bit and poling Ready bit */
        CyDelayUs(0u);

        /* Extract ready bit */
        value &= LCD_Char_1_READY_BIT;

        /* Set E high as we in 4-bit interface we need extra oparation */
        LCD_Char_1_PORT_DR_REG |= LCD_Char_1_E;

        /* 360 ns delay the setup time for data pins */
        CyDelayUs(1u);

        /* Set enable low */
        LCD_Char_1_PORT_DR_REG &= ((uint8)(~LCD_Char_1_E));

        /* Repeat until bit 4 is not zero. */

    } while (value != 0u);

    /* Set R/W low to write */
    LCD_Char_1_PORT_DR_REG &= ((uint8)(~LCD_Char_1_RW));

    /* Clear the LCD port*/
    LCD_Char_1_PORT_DR_REG &= ((uint8)(~LCD_Char_1_PORT_MASK));

    #if (CY_PSOC4)
        
        /* Mask off data pins to clear old values out */
        value = LCD_Char_1_PORT_PC_REG & ((uint32)(~ LCD_Char_1_DM_DATA_MASK));
        /* Load in high Z values for data pins, others unchanged */
        LCD_Char_1_PORT_PC_REG = value | LCD_Char_1_STRONG_DATA_DM;

    #else

        /* Change Port to Output (Strong) on data pins */
        /* Mask off data pins to clear high z values out. Configure data pins 
        * to Strong Drive, others unchanged.
        */
        LCD_Char_1_PORT_DM0_REG &= ((uint8)(~LCD_Char_1_DATA_MASK));
        /* Mask off data pins to clear high z values out */
        value = LCD_Char_1_PORT_DM1_REG & ((uint8)(~LCD_Char_1_DATA_MASK));
        /* Configure data pins to Strong Drive, others unchanged */
        LCD_Char_1_PORT_DM1_REG = value | (LCD_Char_1_STRONG_DM1 & LCD_Char_1_DATA_MASK);

        /* Mask off data pins to clear high z values out */
        value = LCD_Char_1_PORT_DM2_REG & ((uint8)(~LCD_Char_1_DATA_MASK));
        /* Configure data pins to Strong Drive, others unchanged */
        LCD_Char_1_PORT_DM2_REG = value | (LCD_Char_1_STRONG_DM2 & LCD_Char_1_DATA_MASK);
    
    #endif /* CY_PSOC4 */
}


/*******************************************************************************
*  Function Name: LCD_Char_1_WrDatNib
********************************************************************************
*
* Summary:
*  Writes a data nibble to the LCD module.
*
* Parameters:
*  nibble:  byte containing nibble in least significant nibble to be written
*           to LCD module.
*
* Return:
*  None.
*
*******************************************************************************/
static void LCD_Char_1_WrDatNib(uint8 nibble) 
{
    LCD_Char_1_IsReady();

    /* RS shoul be low to select data register */
    LCD_Char_1_PORT_DR_REG |= LCD_Char_1_RS;
    /* Reset RW for write operation */
    LCD_Char_1_PORT_DR_REG &= ((uint8)(~LCD_Char_1_RW));

    /* Two following lines of code will provide us with 40ns delay */
    /* Clear data pins */
    LCD_Char_1_PORT_DR_REG &= ((uint8)(~LCD_Char_1_DATA_MASK));

    /* Write in data, bring E high*/
    #if(0u != LCD_Char_1_PORT_SHIFT) /* MISRA forbids shift by 0 so need to handle that */
        LCD_Char_1_PORT_DR_REG |= 
            (LCD_Char_1_E | ((uint8)(((uint8) nibble) << LCD_Char_1_PORT_SHIFT)));
    #else
        LCD_Char_1_PORT_DR_REG |= (LCD_Char_1_E | nibble);
    #endif /* (0u != LCD_Char_1_PORT_SHIFT) */

    /* Minimum of 230 ns delay */
    CyDelayUs(1u);

    LCD_Char_1_PORT_DR_REG &= ((uint8)(~LCD_Char_1_E));
}


/*******************************************************************************
*  Function Name: LCD_Char_1_WrCntrlNib
********************************************************************************
*
* Summary:
*  Writes a control nibble to the LCD module.
*
* Parameters:
*  nibble:  byte containing nibble in least significant nibble to be written
*           to LCD module.
*
* Return:
*  None.
*
*******************************************************************************/
static void LCD_Char_1_WrCntrlNib(uint8 nibble) 
{
    /* RS and RW shoul be low to select instruction register and  write operation respectively */
    LCD_Char_1_PORT_DR_REG &= ((uint8)(~(LCD_Char_1_RS | LCD_Char_1_RW)));

    /* Two following lines of code will give provide ua with 40ns delay */
    /* Clear data pins */
    LCD_Char_1_PORT_DR_REG &= ((uint8)(~LCD_Char_1_DATA_MASK));

    /* Write control data and set enable signal */
    #if(0u != LCD_Char_1_PORT_SHIFT) /* MISRA forbids shift by 0 so need to handle that */
        LCD_Char_1_PORT_DR_REG |= 
            (LCD_Char_1_E | ((uint8)(((uint8) nibble) << LCD_Char_1_PORT_SHIFT)));
    #else
        LCD_Char_1_PORT_DR_REG |= (LCD_Char_1_E | nibble);
    #endif /* (0u != LCD_Char_1_PORT_SHIFT) */

    /* Minimum of 230 ns delay */
    CyDelayUs(1u);

    LCD_Char_1_PORT_DR_REG &= ((uint8)(~LCD_Char_1_E));
}


#if(LCD_Char_1_CONVERSION_ROUTINES == 1u)

    /*******************************************************************************
    *  Function Name: LCD_Char_1_PrintInt8
    ********************************************************************************
    *
    * Summary:
    *  Print a byte as two ASCII characters.
    *
    * Parameters:
    *  value:  The byte to be printed out as ASCII characters.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void LCD_Char_1_PrintInt8(uint8 value) 
    {
        static char8 const CYCODE LCD_Char_1_hex[16u] = "0123456789ABCDEF";
        
        LCD_Char_1_PutChar((char8) LCD_Char_1_hex[value >> LCD_Char_1_BYTE_UPPER_NIBBLE_SHIFT]);
        LCD_Char_1_PutChar((char8) LCD_Char_1_hex[value & LCD_Char_1_BYTE_LOWER_NIBBLE_MASK]);
    }


    /*******************************************************************************
    *  Function Name: LCD_Char_1_PrintInt16
    ********************************************************************************
    *
    * Summary:
    *  Print a uint16 as four ASCII characters.
    *
    * Parameters:
    *  value:   The uint16 to be printed out as ASCII characters.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void LCD_Char_1_PrintInt16(uint16 value) 
    {
        LCD_Char_1_PrintInt8((uint8)(value >> LCD_Char_1_U16_UPPER_BYTE_SHIFT));
        LCD_Char_1_PrintInt8((uint8)(value & LCD_Char_1_U16_LOWER_BYTE_MASK));
    }


    /*******************************************************************************
    *  Function Name: LCD_Char_1_PrintNumber
    ********************************************************************************
    *
    * Summary:
    *  Print an uint32 value as a left-justified decimal value.
    *
    * Parameters:
    *  value:  The byte to be printed out as ASCII characters.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void LCD_Char_1_PrintNumber(uint16 value) 
    {

        char8 number[LCD_Char_1_NUMBER_OF_REMAINDERS];
        char8 temp[LCD_Char_1_NUMBER_OF_REMAINDERS];

        uint8 digIndex = 0u;
        uint8 numDigits;

        /* Load these in reverse order */
        while(value >= LCD_Char_1_TEN)
        {
            temp[digIndex] = (value % LCD_Char_1_TEN) + '0';
            value /= LCD_Char_1_TEN;
            digIndex++;
        }

        temp[digIndex] = (value % LCD_Char_1_TEN) + '0';
        numDigits = digIndex;

        /* While index is greater than or equal to zero copy number
        * from temporary array to number[].
        */
        while (digIndex != 0u)
        {
            number[numDigits - digIndex] = temp[digIndex];
            digIndex--;
        }
        
        /* Copy last digit */
        number[numDigits] = temp[0u];

        /* Null Termination */
        number[numDigits + 1u] = (char8) '\0';

        /* Print out number */
        LCD_Char_1_PrintString(&number[0u]);
    }

#endif /* LCD_Char_1_CONVERSION_ROUTINES == 1u */


/* [] END OF FILE */
