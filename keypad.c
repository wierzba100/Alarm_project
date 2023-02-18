/*
 * File:   keypad.c
 * Author: filip
 *
 * Created on December 10, 2022, 5:59 PM
 */


#include "xc.h"
#include "keypad.h"

char Keypad[ROWS][COLUMNS] = {
  {'1', '2', '3',},
  {'4', '5', '6',},
  {'7', '8', '9',},
  {'*', '0', '#',}
};


int sum_of_2d_arr;
uint8_t row_index, column_index;
uint8_t Keypad_table[4][3];
int getKey()
{
    ROW_0_SetLow();
    
    Keypad_table[0][0] = 1;//COL_0_GetValue();
    Keypad_table[0][1] = COL_1_GetValue();
    Keypad_table[0][2] = COL_2_GetValue();
    
    ROW_0_SetHigh();
    ROW_1_SetLow();
    
    Keypad_table[1][0] = COL_0_GetValue();
    Keypad_table[1][1] = COL_1_GetValue();
    Keypad_table[1][2] = COL_2_GetValue();
    
    ROW_1_SetHigh();
    ROW_2_SetLow();
    
    Keypad_table[2][0] = COL_0_GetValue();
    Keypad_table[2][1] = COL_1_GetValue();
    Keypad_table[2][2] = COL_2_GetValue();
    
    ROW_2_SetHigh();
    ROW_3_SetLow();
    
    Keypad_table[3][0] = COL_0_GetValue();
    Keypad_table[3][1] = COL_1_GetValue();
    Keypad_table[3][2] = COL_2_GetValue();
    
    ROW_3_SetHigh();
    
    sum_of_2d_arr = 0;
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLUMNS; j++)
        {
               sum_of_2d_arr = sum_of_2d_arr + Keypad_table[i][j];
        }
    }
    
    
    if(sum_of_2d_arr == (ROWS * COLUMNS) - 1)
    {
        for (int i = 0; i < ROWS; i++) 
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                if (Keypad_table[i][j] == 0)
                {
                    row_index = i;
                    column_index = j;
                }
            }
        }
        return Keypad[row_index][column_index];
    }else
    {
        return -1;
    }
}
