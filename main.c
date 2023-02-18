/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.1
        Device            :  PIC24FJ128GA705
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.70
        MPLAB 	          :  MPLAB X v5.50
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include <string.h>

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/adc1.h"
#include "mcc_generated_files/tmr1.h"
#include "keypad.h"

/*
                         Main application
 */

#define PASSWORD_LENGTH 4 //MAX 9

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    Buzzer_SetLow();
    char key;
    char current_password[PASSWORD_LENGTH + 1] = "55";
    char input_password[PASSWORD_LENGTH + 1] = "";
    char new_password[PASSWORD_LENGTH + 1] = "";
    memset(input_password, '\0', sizeof(input_password));
    TMR1_Start();
    while (1)
    {
        switch(state)
        {
            case 0:
                key = getKey();
                if(key != -1)
                {
                    if(key == '0')
                    {
                        memset(input_password, '\0', sizeof(input_password));
                        Led_Red_SetHigh();
                    }else if (key == '#')
                    {
                        if(strcmp(input_password, current_password) == 0)
                        {
                            state = 1;
                            Led_Blue_SetHigh();
                            sleep(100);
                            break;
                        }else
                        {
                            Led_Red_SetLow();
                        }
                    }else
                    {
                        input_password[strlen(input_password)] = key;
                        while(getKey() != '#')
                        {
                            Led_Yellow_SetLow();
                        }
                        Led_Yellow_SetHigh();
                    }
                }
                
                
                
                sleep(30);
                Led_Blue_Toggle();
                break;
            case 1:
                    key = getKey();
                    if(key != -1)
                    {
                        if(key == '#')
                        {
                            memset(input_password, '\0', sizeof(input_password));
                            Led_Green_SetHigh();
                            sleep(100);
                            state = 0;
                            break;
                        }else if(key == '0')
                        {
                            memset(new_password, '\0', sizeof(new_password));
                            Led_Green_SetHigh();
                            sleep(100);
                            state = 2;
                        }
                        sleep(30);
                    }
                    Led_Green_Toggle();
            case 2:
                key = getKey();
                if(key != -1)
                {
                    if(key == '0')
                    {
                        Led_Yellow_SetHigh();
                        state = 1;
                        sleep(100);
                        break;
                    }else if(key == '#')
                    {
                        strcpy (current_password, new_password);
                        Led_Yellow_SetHigh();
                        state = 1;
                        sleep(100);
                        break;
                    }else
                    {
                        new_password[strlen(new_password)] = key;
                        while(getKey() != '*')
                        {
                            Led_Green_SetLow();
                        }
                        Led_Green_SetHigh();
                    }
                    sleep(30);
                    Led_Yellow_Toggle();
                }
            case 3:
                key = getKey();
                if(key != -1)
                {
                    if(key == '0')
                    {
                        memset(input_password, '\0', sizeof(input_password));
                        Led_Green_SetHigh();
                    }else if (key == '#')
                    {
                        if(strcmp(input_password, current_password) == 0)
                        {
                            state = 1;
                            Buzzer_SetLow();
                            Led_Red_SetHigh();
                            sleep(100);
                            break;
                        }else
                        {
                            Led_Green_SetLow();
                        }
                    }else
                    {
                        input_password[strlen(input_password)] = key;
                        while(getKey() != '#')
                        {
                            Led_Yellow_SetLow();
                        }
                        Led_Yellow_SetHigh();
                    }
                }
                uint8_t buzzer = Buzzer_GetValue();
                sleep(30);
                Led_Red_Toggle();
                break;
                
            default:
                break;
        }
    }
    return 1;
}
/**
 End of File
*/

