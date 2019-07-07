#include<windows.h>
#ifndef CALCULATOR_H
#define CALCULATOR_H

void InitializeValues(HWND);
void Addition(float, float, HWND);
void Subtraction(float, float, HWND);
void Multiplication(float, float, HWND);
void Division(float, float, HWND);
void Modulus(float, float, HWND);
void ResetValues(HWND);
void CreateLogFileForAddition(int, int);
void CreateLogFileForSubtraction(int, int);
void CreateLogFileForMultiplication(int, int);
void CreateLogFileForDivision(int, int);
void CreateLogFileForModulus(int, int);
void CreateLogFileForResetCheck(float, float, float, int, int, int, int, int);

#endif CALCULATOR_H
