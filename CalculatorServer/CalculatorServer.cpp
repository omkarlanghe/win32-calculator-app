#include<windows.h>
#include"Calculator.h"

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break; 
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return(TRUE);
}

extern "C" float Addition(float num1, float num2)
{
	return(num1 + num2);
}
extern "C" float Subtraction(float num1, float num2)
{
	return(num1 - num2);
}
extern "C" float Multiplication(float num1, float num2)
{
	return(num1 * num2);
}
extern "C" float Division(float num1, float num2)
{
	return(num1 / num2);
}
extern "C" int Modulus(int num1, int num2)
{
	return(num1%num2);
}
