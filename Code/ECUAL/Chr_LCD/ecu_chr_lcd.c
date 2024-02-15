#include "ecu_chr_lcd.h"

static pin_config_t data_pins[DATA_BUS_WIDTH];
static pin_config_t enable_pin;
static pin_config_t rs_pin;

static Std_ReturnType lcd_assign_pins(const chr_lcd_t *const lcd);
static Std_ReturnType lcd_send_enable_signal();
static Std_ReturnType lcd_send_bits(const uint8 command);

Std_ReturnType lcd_init(const chr_lcd_t *lcd)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(lcd)
    {
        uint8 counter;
        ret = lcd_assign_pins(lcd);
        
        for(counter = 0; counter < DATA_BUS_WIDTH; counter++)
            ret = gpio_pin_initialize(&data_pins[counter]);
        ret &= gpio_pin_initialize(&enable_pin);
        ret &= gpio_pin_initialize(&rs_pin);
        
        __delay_ms(20);
        ret &= lcd_send_command(lcd, _LCD_FUNCTION_SET_8BIT_INTERFACE);
        
        __delay_ms(5);
        ret &= lcd_send_command(lcd, _LCD_FUNCTION_SET_8BIT_INTERFACE);
        
        __delay_us(150);
        ret &= lcd_send_command(lcd, _LCD_FUNCTION_SET_8BIT_INTERFACE);
        
#if _LCD_INTERFACE_TYPE==_LCD_8BIT
        ret &= lcd_send_command(lcd, _LCD_FUNCTION_SET_8BIT_INTERFACE | _LCD_FUNCTION_SET_2ROW_MODE);
#elif _LCD_INTERFACE_TYPE==_LCD_4BIT
        ret &= lcd_send_command(lcd, _LCD_FUNCTION_SET_4BIT_INTERFACE >> 4);  // From data sheet
        ret &= lcd_send_command(lcd, _LCD_FUNCTION_SET_4BIT_INTERFACE | _LCD_FUNCTION_SET_2ROW_MODE);
#endif
        ret &= lcd_send_command(lcd, _LCD_DISPLAY_ON);
        ret &= lcd_send_command(lcd, _LCD_CLEAR_DISPLAY);
        ret &= lcd_send_command(lcd, _LCD_ENTRY_MODE_SET_INCREMENT);
        ret &= lcd_send_command(lcd, _LCD_CURSOR_HOME);
    }
    
    return ret;
}

Std_ReturnType lcd_send_command(const chr_lcd_t *lcd, uint8 command)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(lcd)
    {
        ret = E_OK;
        ret = lcd_assign_pins(lcd);
        ret &= gpio_pin_write_logic(&rs_pin, GPIO_LOW);
        ret &= lcd_send_bits(command);
    }
    
    return ret;
}

Std_ReturnType lcd_send_data(const chr_lcd_t *lcd, uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(lcd)
    {
        ret = E_OK;
        ret = lcd_assign_pins(lcd);
        ret &= gpio_pin_write_logic(&rs_pin, GPIO_HIGH);
        ret &= lcd_send_bits(data);
    }
    
    return ret;
}

Std_ReturnType lcd_send_data_pos(const chr_lcd_t *lcd, uint8 row, uint8 column, uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(lcd)
    {
        ret = E_OK;
        column--;
        switch (row)
        {
            case 1:
                ret &= lcd_send_command(lcd, (_LCD_DDRAM_START + 0x00) + column);
                break;
            case 2:
                ret &= lcd_send_command(lcd, (_LCD_DDRAM_START + 0x40) + column);
                break;
            case 3:
                ret &= lcd_send_command(lcd, (_LCD_DDRAM_START + 0x14) + column);
                break;
            case 4:
                ret &= lcd_send_command(lcd, (_LCD_DDRAM_START + 0x54) + column);
                break;
        }
        ret &= lcd_send_data(lcd, data);
    }
    
    return ret;
}

Std_ReturnType lcd_send_string(const chr_lcd_t *lcd, uint8 *str)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(lcd)
    {
        uint8 counter = 0;
        ret = E_OK;
        
        while(str[counter] != '\0')
           ret &= lcd_send_data(lcd, str[counter++]);
    }
    
    return ret;
}

Std_ReturnType lcd_send_string_pos(const chr_lcd_t *lcd, uint8 row, uint8 column, uint8 *str)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(lcd)
    {
        uint8 counter = 0;
        
        ret = E_OK;
        column--;
        switch (row)
        {
            case 1:
                ret &= lcd_send_command(lcd, (_LCD_DDRAM_START + 0x00) + column);
                break;
            case 2:
                ret &= lcd_send_command(lcd, (_LCD_DDRAM_START + 0x40) + column);
                break;
            case 3:
                ret &= lcd_send_command(lcd, (_LCD_DDRAM_START + 0x14) + column);
                break;
            case 4:
                ret &= lcd_send_command(lcd, (_LCD_DDRAM_START + 0x54) + column);
                break;
        }
        while(str[counter] != '\0')
           ret &= lcd_send_data(lcd, str[counter++]);
    }
    
    return ret;
}

Std_ReturnType lcd_send_custom_char(const chr_lcd_t *lcd, uint8 row, uint8 column, const uint8 chr[], uint8 mem_pos)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(lcd)
    {
        uint8 count;
        ret = E_OK;
        ret = lcd_assign_pins(lcd);
        
        ret &= lcd_send_command(lcd, _LCD_CGRAM_START + mem_pos*8);
        for (count = 0; count < 8; count++)
            ret &= lcd_send_data(lcd, chr[count]);
        ret &= lcd_send_data_pos(lcd, row, column, mem_pos);
    }
    
    return ret;
}

Std_ReturnType convert_uint8_to_string(uint8 val, uint8 str[])
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(str)
    {
        uint8 count = 0;
        uint32 dividor = 100;
        ret = E_OK;
        
        str[3] = '\0';
        
        while(0 == (val/dividor)%10 && count < 2)
        {
            dividor /= 10;
            str[count++] = ' ';
        }

        for(; count <= 2; count++)
        {
            str[count] = '0' + ((val/dividor)%10);
            dividor /= 10;
        }
        
    }
    
    return ret;
}
Std_ReturnType convert_uint16_to_string(uint16 val, uint8 str[])
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(str)
    {
        uint8 count = 0;
        uint16 dividor = 10000;
        ret = E_OK;
        
        str[5] = '\0';
 
        while(0 == (val/dividor)%10 && count < 4)
        {
            dividor /= 10;
            str[count++] = ' ';
        }

        for(; count <= 4; count++)
        {
            str[count] = '0' + ((val/dividor)%10);
            dividor /= 10;
        }

    }
    
    return ret;
}
Std_ReturnType convert_uint32_to_string(uint32 val, uint8 str[])
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(str)
    {
        uint8 count = 0;
        uint32 dividor = 1000000000;
        ret = E_OK;
       
        str[10] = '\0';
        
        while(0 == (val/dividor)%10 && count < 9)
        {
            dividor /= 10;
            str[count++] = ' ';
        }

        for(; count <= 9; count++)
        {
            str[count] = '0' + ((val/dividor)%10);
            dividor /= 10;
        }
       
        
    }
    
    return ret;
}

static Std_ReturnType lcd_assign_pins(const chr_lcd_t *const lcd)
{
    Std_ReturnType ret = E_NOT_OK;
    if (lcd)
    {
        uint8 counter;
        ret = E_OK;
        for (counter = 0; counter < DATA_BUS_WIDTH; counter++)
        {
            data_pins[counter].pin_index = lcd->data[counter].pin_index;
            data_pins[counter].port_index = lcd->data[counter].port_index;
            data_pins[counter].pin_direction = GPIO_OUTPUT;
            data_pins[counter].logic = GPIO_LOW;
        }
        enable_pin.pin_direction = GPIO_OUTPUT;
        enable_pin.pin_index = lcd->en.pin_index;
        enable_pin.port_index = lcd->en.port_index;
        enable_pin.logic = GPIO_LOW;

        rs_pin.pin_direction = GPIO_OUTPUT;
        rs_pin.pin_index = lcd->rs.pin_index;
        rs_pin.port_index = lcd->rs.port_index;
        rs_pin.logic = GPIO_LOW;
    }
    
    return ret;
}


static Std_ReturnType lcd_send_enable_signal()
{
    Std_ReturnType ret = E_NOT_OK;
    
    ret = gpio_pin_write_logic(&enable_pin, GPIO_HIGH);
    __delay_us(10);
    ret &= gpio_pin_write_logic(&enable_pin, GPIO_LOW);
    
    return ret;
}

static Std_ReturnType lcd_send_bits(const uint8 bits)
{
    uint8 counter;
    Std_ReturnType ret = E_OK;
        
#if _LCD_INTERFACE_TYPE==_LCD_4BIT
    for(counter = 0; counter < DATA_BUS_WIDTH; counter++)
            ret &= gpio_pin_write_logic(&data_pins[counter], ((bits >> 4) >> counter) & 0x01);
    ret &= lcd_send_enable_signal();
#endif
    
    for(counter = 0; counter < DATA_BUS_WIDTH; counter++)
            ret &= gpio_pin_write_logic(&data_pins[counter], (bits >> counter) & 0x01);
    ret &= lcd_send_enable_signal();
  
    return ret; 
}
