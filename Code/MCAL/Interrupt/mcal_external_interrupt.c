#include "mcal_external_interrupt.h"

#if EXTERNAL_INTERRUPTS_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (* INT0_InterruptHandler) (void) = NULL;
static void (* INT1_InterruptHandler) (void) = NULL;
static void (* INT2_InterruptHandler) (void) = NULL;

static Std_ReturnType Interrupt_INTx_Enable(const inetrrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const inetrrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const inetrrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const inetrrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const inetrrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const inetrrupt_INTx_t *int_obj);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init(const inetrrupt_INTx_t *int_obj);
#endif // INTERRUPT_PRIORITY_LEVELS_ENABLE
#endif // EXTERNAL_INTERRUPTS_INTx_FEATURE_ENABLE

#if EXTERNAL_INTERRUPTS_OnChange_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_RBx_Enable(const inerrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const inerrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const inerrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Clear_Flag(const inerrupt_RBx_t *int_obj);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init(const inetrrupt_INTx_t *int_obj);
#endif // INTERRUPT_PRIORITY_LEVELS_ENABLE
#endif // EXTERNAL_INTERRUPTS_OnChange_FEATURE_ENABLE

#if EXTERNAL_INTERRUPTS_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
Std_ReturnType Interrupt_INTx_Init  (const inetrrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj)
    {
        /* Disable the interrupt to make sure it's unmasked during the initialization */
        ret = Interrupt_INTx_Disable(int_obj);
        /* Clear the flag bit of the interrupt */
        ret = Interrupt_INTx_Clear_Flag(int_obj);
        /* Configure the interrupt I/O pin */
        ret = Interrupt_INTx_Pin_Init(int_obj);
        /* Set the edge trigger bit (Falling/Rising)  */
        ret = Interrupt_INTx_Edge_Init(int_obj);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        /* Set the priority bit (High/Low) */
        ret = Interrupt_INTx_Priority_Init(int_obj);
#endif // INTERRUPT_PRIORITY_LEVELS_ENABLE
        /* Configure the callback function */ 
        ret = Interrupt_INTx_SetInterruptHandler(int_obj);
        /* Enable the interrupt */
        ret = Interrupt_INTx_Enable(int_obj);
    } else {/* Nothing */}
    
    return ret;
}

Std_ReturnType Interrupt_INTx_DeInit(const inetrrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj)
    {
        ret = E_OK;
    } else {/* Nothing */}
    
    return ret;
}
#endif // EXTERNAL_INTERRUPTS_INTx_FEATURE_ENABLE

#if EXTERNAL_INTERRUPTS_OnChange_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
Std_ReturnType Interrupt_RBx_Init   (const inerrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj)
    {
        ret = E_OK;
    } else {/* Nothing */}
    
    return ret;
}

Std_ReturnType Interrupt_RBx_DeInit (const inerrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj)
    {
        ret = E_OK;
    } else {/* Nothing */}
    
    return ret;
}
#endif // EXTERNAL_INTERRUPTS_OnChange_FEATURE_ENABLE

#if EXTERNAL_INTERRUPTS_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Enable(const inetrrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj)
    {
        ret = E_OK;
        switch (int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 : EXT_INT0_InterruptEnable(); break;
            case INTERRUPT_EXTERNAL_INT1 : EXT_INT1_InterruptEnable(); break;
            case INTERRUPT_EXTERNAL_INT2 : EXT_INT2_InterruptEnable(); break;
            default : ret = E_NOT_OK;
        }
    } else {/* Nothing */}
    
    return ret;
}

static Std_ReturnType Interrupt_INTx_Disable(const inetrrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj)
    {
        ret = E_OK;
        switch (int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 : EXT_INT0_InterruptDisable(); break;
            case INTERRUPT_EXTERNAL_INT1 : EXT_INT1_InterruptDisable(); break;
            case INTERRUPT_EXTERNAL_INT2 : EXT_INT2_InterruptDisable(); break;
            default : ret = E_NOT_OK;
        }
    } else {/* Nothing */}
    
    return ret; 
}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init(const inetrrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj)
    {
        ret = E_OK;
        switch (int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority)        {EXT_INT1_LowPrioritySet();}
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {EXT_INT1_HighPrioritySet();}
                else {ret = E_NOT_OK;}
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority)        {EXT_INT2_LowPrioritySet();}
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {EXT_INT2_HighPrioritySet();}
                else {ret = E_NOT_OK;}
                break;
            default : ret = E_NOT_OK;
        }
    } else {/* Nothing */}
    
    return ret;
}
#endif // INTERRUPT_PRIORITY_LEVELS_ENABLE

static Std_ReturnType Interrupt_INTx_Edge_Init(const inetrrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj)
    {
        ret = E_OK;
        switch (int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 :
                if(INTERRUPT_FALLING_EDGE == int_obj->edge)      {EXT_INT0_FallingEdgeSet();}
                else if (INTERRUPT_RISING_EDGE == int_obj->edge) {EXT_INT0_RisingEdgeSet();}
                else {ret = E_NOT_OK;}
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge)      {EXT_INT1_FallingEdgeSet();}
                else if (INTERRUPT_RISING_EDGE == int_obj->edge) {EXT_INT1_RisingEdgeSet();}
                else {ret = E_NOT_OK;}
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge)      {EXT_INT2_FallingEdgeSet();}
                else if (INTERRUPT_RISING_EDGE == int_obj->edge) {EXT_INT2_RisingEdgeSet();}
                else {ret = E_NOT_OK;}
                break;
            default : ret = E_NOT_OK;
        }
    } else {/* Nothing */}
    
    return ret;
}

static Std_ReturnType Interrupt_INTx_Pin_Init(const inetrrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj)
    {
        ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
    } else {/* Nothing */}
    
    return ret;
}

static Std_ReturnType Interrupt_INTx_Clear_Flag(const inetrrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj)
    {
        ret = E_OK;
        switch (int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 : EXT_INT0_InterruptFlagClear(); break;
            case INTERRUPT_EXTERNAL_INT1 : EXT_INT1_InterruptFlagClear(); break;
            case INTERRUPT_EXTERNAL_INT2 : EXT_INT2_InterruptFlagClear(); break;
            default : ret = E_NOT_OK;
        }
    } else {/* Nothing */}
    
    return ret;
}

static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const inetrrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if (int_obj)
    {
        if(int_obj->EXT_InterruptHandler)
        {
            ret = E_NOT_OK;
            switch (int_obj->source)
            {
                case INTERRUPT_EXTERNAL_INT0 : 
                    INT0_InterruptHandler = int_obj->EXT_InterruptHandler;
                    break;
                case INTERRUPT_EXTERNAL_INT1 : 
                    INT1_InterruptHandler = int_obj->EXT_InterruptHandler;
                    break;
                case INTERRUPT_EXTERNAL_INT2 : 
                    INT2_InterruptHandler = int_obj->EXT_InterruptHandler;
                    break;
                default : ret = E_NOT_OK;
            }
            
        }
        
    } else {/* Nothing */}
    
    return ret;
}
#endif // EXTERNAL_INTERRUPTS_INTx_FEATURE_ENABLE

