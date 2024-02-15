/* 
 * File:   mcal_external_interrupt.h
 * Author: Blu-Ray
 *
 * Created on February 12, 2024, 2:09 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/********************************** Includes **********************************/
#include "mcal_interrupt_config.h"

/*********************************** Macros ***********************************/

/********************** Function Like Macro Declarations **********************/

// External Interrupts (INT0, INT1, INT2) Feature Enable
#if EXTERNAL_INTERRUPTS_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

// Macro to enable external interrupt INT0
#define EXT_INT0_InterruptEnable()     (INTCONbits.INT0E = 1)

// Macro to disable external interrupt INT0
#define EXT_INT0_InterruptDisable()    (INTCONbits.INT0E = 0)

// Macro to clear external interrupt INT0 flag
#define EXT_INT0_InterruptFlagClear()  (INTCONbits.INT0IF = 0)

// Macro to set INT0 to trigger on rising edge
#define EXT_INT0_RisingEdgeSet()       (INTCON2bits.INTEDG0 = 1)

// Macro to set INT0 to trigger on falling edge
#define EXT_INT0_FallingEdgeSet()      (INTCON2bits.INTEDG0 = 0)

// Macro to enable external interrupt INT1
#define EXT_INT1_InterruptEnable()     (INTCON3bits.INT1E = 1)

// Macro to disable external interrupt INT1
#define EXT_INT1_InterruptDisable()    (INTCON3bits.INT1E = 0)

// Macro to clear external interrupt INT1 flag
#define EXT_INT1_InterruptFlagClear()  (INTCON3bits.INT1F = 0)

// Macro to set INT1 to trigger on rising edge
#define EXT_INT1_RisingEdgeSet()       (INTCON2bits.INTEDG1 = 1)

// Macro to set INT1 to trigger on falling edge
#define EXT_INT1_FallingEdgeSet()      (INTCON2bits.INTEDG1 = 0)

// Macro to enable external interrupt INT2
#define EXT_INT2_InterruptEnable()     (INTCON3bits.INT2E = 1)

// Macro to disable external interrupt INT2
#define EXT_INT2_InterruptDisable()    (INTCON3bits.INT2E = 0)

// Macro to clear external interrupt INT2 flag
#define EXT_INT2_InterruptFlagClear()  (INTCON3bits.INT2IF = 0)

// Macro to set INT2 to trigger on rising edge
#define EXT_INT2_RisingEdgeSet()       (INTCON2bits.INTEDG2 = 1)

// Macro to set INT2 to trigger on falling edge
#define EXT_INT2_FallingEdgeSet()      (INTCON2bits.INTEDG2 = 0)

// If interrupt priority levels are enabled
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

// Macro to set INT1 to high priority
#define EXT_INT1_HighPrioritySet()  (INTCON3bits.INT1IP = 1)

// Macro to set INT1 to low priority
#define EXT_INT1_LowPrioritySet()   (INTCON3bits.INT1IP = 0)

// Macro to set INT2 to high priority
#define EXT_INT2_HighPrioritySet()  (INTCON3bits.INT2IP = 1)

// Macro to set INT2 to low priority
#define EXT_INT2_LowPrioritySet()   (INTCON3bits.INT2IP = 0)

#endif // INTERRUPT_PRIORITY_LEVELS_ENABLE

#endif // EXTERNAL_INTERRUPTS_INTx_FEATURE_ENABLE

// External Interrupts OnChange Feature Enable
#if EXTERNAL_INTERRUPTS_OnChange_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

// Macro to enable external interrupts on PORTB pins change
#define EXT_RBx_InterruptEnable()      (INTCONbits.RBIE = 1)

// Macro to disable external interrupts on PORTB pins change
#define EXT_RBx_InterruptDisable()      (INTCONbits.RBIE = 0)

// Macro to clear external interrupts on PORTB pins change flag
#define EXT_RBx_InterruptFlagClear()   (INTCONbits.RBIF = 0)

// If interrupt priority levels are enabled
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

// Macro to set external interrupts on PORTB pins change to high priority
#define EXT_RBx_HighPrioritySet()   (INTCON2bits.RBIP = 1)

// Macro to set external interrupts on PORTB pins change to low priority
#define EXT_RBx_LowPrioritySet()    (INTCON2bits.RBIP = 0)

#endif // INTERRUPT_PRIORITY_LEVELS_ENABLE

#endif // EXTERNAL_INTERRUPTS_OnChange_FEATURE_ENABLE

/*************************** Data Types Declarations **************************/
#if EXTERNAL_INTERRUPTS_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
typedef enum {
    INTERRUPT_FALLING_EDGE,
    INTERRUPT_RISING_EDGE        
}interrupt_INTx_edge;

typedef enum {
    INTERRUPT_EXTERNAL_INT0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2
}interrupt_INTx_src;

typedef struct {
    void (* EXT_InterruptHandler) (void);
    pin_config_t           mcu_pin;
    interrupt_INTx_src     source;
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg priority;
    #endif // INTERRUPT_PRIORITY_LEVELS_ENABLE
    interrupt_INTx_edge    edge;
}inetrrupt_INTx_t;
#endif // EXTERNAL_INTERRUPTS_INTx_FEATURE_ENABLE

#if EXTERNAL_INTERRUPTS_OnChange_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
typedef struct {
    void (* EXT_InterruptHandler) (void);
    pin_config_t           mcu_pin;
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg priority;
    #endif // INTERRUPT_PRIORITY_LEVELS_ENABLE
}inerrupt_RBx_t;
#endif // EXTERNAL_INTERRUPTS_OnChange_FEATURE_ENABLE
/*************************** Functions Declarations ***************************/
#if EXTERNAL_INTERRUPTS_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/**
 * @brief Initialize External Interrupt INTx
 * 
 * @param int_obj Pointer to a structure containing interrupt configuration
 * @return Std_ReturnType Standard return type indicating success or failure
 */
Std_ReturnType Interrupt_INTx_Init  (const inetrrupt_INTx_t *int_obj);

/**
 * @brief Deinitialize External Interrupt INTx
 * 
 * @param int_obj Pointer to a structure containing interrupt configuration
 * @return Std_ReturnType Standard return type indicating success or failure
 */
Std_ReturnType Interrupt_INTx_DeInit(const inetrrupt_INTx_t *int_obj);
#endif // EXTERNAL_INTERRUPTS_INTx_FEATURE_ENABLE

#if EXTERNAL_INTERRUPTS_OnChange_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/**
 * @brief Initialize External Interrupt on PORTB pins change
 * 
 * @param int_obj Pointer to a structure containing interrupt configuration
 * @return Std_ReturnType Standard return type indicating success or failure
 */
Std_ReturnType Interrupt_RBx_Init   (const inerrupt_RBx_t *int_obj);

/**
 * @brief Deinitialize External Interrupt on PORTB pins change
 * 
 * @param int_obj Pointer to a structure containing interrupt configuration
 * @return Std_ReturnType Standard return type indicating success or failure
 */
Std_ReturnType Interrupt_RBx_DeInit (const inerrupt_RBx_t *int_obj);
#endif // EXTERNAL_INTERRUPTS_OnChange_FEATURE_ENABLE
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */
