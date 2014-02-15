/*******************************************************************************
* File Name: Period_1MHz.h
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

#if !defined(CY_CLOCK_Period_1MHz_H)
#define CY_CLOCK_Period_1MHz_H

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

void Period_1MHz_Start(void) ;
void Period_1MHz_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Period_1MHz_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Period_1MHz_StandbyPower(uint8 state) ;
void Period_1MHz_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Period_1MHz_GetDividerRegister(void) ;
void Period_1MHz_SetModeRegister(uint8 modeBitMask) ;
void Period_1MHz_ClearModeRegister(uint8 modeBitMask) ;
uint8 Period_1MHz_GetModeRegister(void) ;
void Period_1MHz_SetSourceRegister(uint8 clkSource) ;
uint8 Period_1MHz_GetSourceRegister(void) ;
#if defined(Period_1MHz__CFG3)
void Period_1MHz_SetPhaseRegister(uint8 clkPhase) ;
uint8 Period_1MHz_GetPhaseRegister(void) ;
#endif /* defined(Period_1MHz__CFG3) */

#define Period_1MHz_Enable()                       Period_1MHz_Start()
#define Period_1MHz_Disable()                      Period_1MHz_Stop()
#define Period_1MHz_SetDivider(clkDivider)         Period_1MHz_SetDividerRegister(clkDivider, 1)
#define Period_1MHz_SetDividerValue(clkDivider)    Period_1MHz_SetDividerRegister((clkDivider) - 1, 1)
#define Period_1MHz_SetMode(clkMode)               Period_1MHz_SetModeRegister(clkMode)
#define Period_1MHz_SetSource(clkSource)           Period_1MHz_SetSourceRegister(clkSource)
#if defined(Period_1MHz__CFG3)
#define Period_1MHz_SetPhase(clkPhase)             Period_1MHz_SetPhaseRegister(clkPhase)
#define Period_1MHz_SetPhaseValue(clkPhase)        Period_1MHz_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(Period_1MHz__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Period_1MHz_CLKEN              (* (reg8 *) Period_1MHz__PM_ACT_CFG)
#define Period_1MHz_CLKEN_PTR          ((reg8 *) Period_1MHz__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Period_1MHz_CLKSTBY            (* (reg8 *) Period_1MHz__PM_STBY_CFG)
#define Period_1MHz_CLKSTBY_PTR        ((reg8 *) Period_1MHz__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Period_1MHz_DIV_LSB            (* (reg8 *) Period_1MHz__CFG0)
#define Period_1MHz_DIV_LSB_PTR        ((reg8 *) Period_1MHz__CFG0)
#define Period_1MHz_DIV_PTR            ((reg16 *) Period_1MHz__CFG0)

/* Clock MSB divider configuration register. */
#define Period_1MHz_DIV_MSB            (* (reg8 *) Period_1MHz__CFG1)
#define Period_1MHz_DIV_MSB_PTR        ((reg8 *) Period_1MHz__CFG1)

/* Mode and source configuration register */
#define Period_1MHz_MOD_SRC            (* (reg8 *) Period_1MHz__CFG2)
#define Period_1MHz_MOD_SRC_PTR        ((reg8 *) Period_1MHz__CFG2)

#if defined(Period_1MHz__CFG3)
/* Analog clock phase configuration register */
#define Period_1MHz_PHASE              (* (reg8 *) Period_1MHz__CFG3)
#define Period_1MHz_PHASE_PTR          ((reg8 *) Period_1MHz__CFG3)
#endif /* defined(Period_1MHz__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Period_1MHz_CLKEN_MASK         Period_1MHz__PM_ACT_MSK
#define Period_1MHz_CLKSTBY_MASK       Period_1MHz__PM_STBY_MSK

/* CFG2 field masks */
#define Period_1MHz_SRC_SEL_MSK        Period_1MHz__CFG2_SRC_SEL_MASK
#define Period_1MHz_MODE_MASK          (~(Period_1MHz_SRC_SEL_MSK))

#if defined(Period_1MHz__CFG3)
/* CFG3 phase mask */
#define Period_1MHz_PHASE_MASK         Period_1MHz__CFG3_PHASE_DLY_MASK
#endif /* defined(Period_1MHz__CFG3) */

#endif /* CY_CLOCK_Period_1MHz_H */


/* [] END OF FILE */
