/*******************************************************************************
* File Name: Clock_16Bit.h
* Version 2.0
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Clock_16Bit_H)
#define CY_CLOCK_Clock_16Bit_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Clock_16Bit_Start(void) ;
void Clock_16Bit_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Clock_16Bit_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Clock_16Bit_StandbyPower(uint8 state) ;
void Clock_16Bit_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Clock_16Bit_GetDividerRegister(void) ;
void Clock_16Bit_SetModeRegister(uint8 modeBitMask) ;
void Clock_16Bit_ClearModeRegister(uint8 modeBitMask) ;
uint8 Clock_16Bit_GetModeRegister(void) ;
void Clock_16Bit_SetSourceRegister(uint8 clkSource) ;
uint8 Clock_16Bit_GetSourceRegister(void) ;
#if defined(Clock_16Bit__CFG3)
void Clock_16Bit_SetPhaseRegister(uint8 clkPhase) ;
uint8 Clock_16Bit_GetPhaseRegister(void) ;
#endif /* defined(Clock_16Bit__CFG3) */

#define Clock_16Bit_Enable()                       Clock_16Bit_Start()
#define Clock_16Bit_Disable()                      Clock_16Bit_Stop()
#define Clock_16Bit_SetDivider(clkDivider)         Clock_16Bit_SetDividerRegister(clkDivider, 1)
#define Clock_16Bit_SetDividerValue(clkDivider)    Clock_16Bit_SetDividerRegister((clkDivider) - 1, 1)
#define Clock_16Bit_SetMode(clkMode)               Clock_16Bit_SetModeRegister(clkMode)
#define Clock_16Bit_SetSource(clkSource)           Clock_16Bit_SetSourceRegister(clkSource)
#if defined(Clock_16Bit__CFG3)
#define Clock_16Bit_SetPhase(clkPhase)             Clock_16Bit_SetPhaseRegister(clkPhase)
#define Clock_16Bit_SetPhaseValue(clkPhase)        Clock_16Bit_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(Clock_16Bit__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Clock_16Bit_CLKEN              (* (reg8 *) Clock_16Bit__PM_ACT_CFG)
#define Clock_16Bit_CLKEN_PTR          ((reg8 *) Clock_16Bit__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Clock_16Bit_CLKSTBY            (* (reg8 *) Clock_16Bit__PM_STBY_CFG)
#define Clock_16Bit_CLKSTBY_PTR        ((reg8 *) Clock_16Bit__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Clock_16Bit_DIV_LSB            (* (reg8 *) Clock_16Bit__CFG0)
#define Clock_16Bit_DIV_LSB_PTR        ((reg8 *) Clock_16Bit__CFG0)
#define Clock_16Bit_DIV_PTR            ((reg16 *) Clock_16Bit__CFG0)

/* Clock MSB divider configuration register. */
#define Clock_16Bit_DIV_MSB            (* (reg8 *) Clock_16Bit__CFG1)
#define Clock_16Bit_DIV_MSB_PTR        ((reg8 *) Clock_16Bit__CFG1)

/* Mode and source configuration register */
#define Clock_16Bit_MOD_SRC            (* (reg8 *) Clock_16Bit__CFG2)
#define Clock_16Bit_MOD_SRC_PTR        ((reg8 *) Clock_16Bit__CFG2)

#if defined(Clock_16Bit__CFG3)
/* Analog clock phase configuration register */
#define Clock_16Bit_PHASE              (* (reg8 *) Clock_16Bit__CFG3)
#define Clock_16Bit_PHASE_PTR          ((reg8 *) Clock_16Bit__CFG3)
#endif /* defined(Clock_16Bit__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Clock_16Bit_CLKEN_MASK         Clock_16Bit__PM_ACT_MSK
#define Clock_16Bit_CLKSTBY_MASK       Clock_16Bit__PM_STBY_MSK

/* CFG2 field masks */
#define Clock_16Bit_SRC_SEL_MSK        Clock_16Bit__CFG2_SRC_SEL_MASK
#define Clock_16Bit_MODE_MASK          (~(Clock_16Bit_SRC_SEL_MSK))

#if defined(Clock_16Bit__CFG3)
/* CFG3 phase mask */
#define Clock_16Bit_PHASE_MASK         Clock_16Bit__CFG3_PHASE_DLY_MASK
#endif /* defined(Clock_16Bit__CFG3) */

#endif /* CY_CLOCK_Clock_16Bit_H */


/* [] END OF FILE */
