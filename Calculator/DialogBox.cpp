#include<windows.h>
#include "MyDialog.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
void InitializeValues(HWND);
void Addition(float, float, HWND);
void Subtraction(float, float, HWND);
void Multiplication(float, float, HWND);
void Division(float, float, HWND);
void Modulus(int, int, HWND);
void ResetValues(HWND);
void CreateLogFileForAddition(int, int);
void CreateLogFileForSubtraction(int, int);
void CreateLogFileForMultiplication(int, int);
void CreateLogFileForDivision(int, int);
void CreateLogFileForModulus(int, int);

struct MYINPUT {
	TCHAR num1[255], num2[255];
};
MYINPUT in;

static float iNum1 = 0, iNum2 = 0;
static float ifNum1 = 0, ifNum2 = 0;
float result = 0;
static int addStatus = 0, subStatus = 0, mulStatus = 0, divStatus = 0, modStatus = 0;
static int addCounter = 0, subCounter = 0, mulCounter = 0, divCounter = 0, modCounter = 0;

enum numbers {
	zero,
	one,
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Calculator");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("My Calculator"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1925,
		1100,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInst;
	RECT rc;
	HDC hdc;
	PAINTSTRUCT ps;

	//int GWL_HINSTANCE = -6;
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		DrawText(hdc, TEXT("Press spacebar to continue or esc to exit"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 0x20:
			hInst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
			DialogBox(hInst, MAKEINTRESOURCE(ID_DATAENTRY), hwnd, reinterpret_cast<DLGPROC>(MyDlgProc));
			break;

		case 27:
			DestroyWindow(hwnd);
			break;
		}
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL CALLBACK MyDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	HBRUSH hbrBkgnd = NULL;
	TCHAR str[255];
	switch (iMsg) {
	case WM_INITDIALOG:
		InitializeValues(hDlg);
		EnableWindow(GetDlgItem(hDlg, ID_NUM1ET), FALSE);
		EnableWindow(GetDlgItem(hDlg, ID_NUM2ET), FALSE);
		EnableWindow(GetDlgItem(hDlg, ID_RESULTET), FALSE);
		return(TRUE);
		break;
	case WM_CTLCOLORDLG:
		hdc = HDC(wParam);
		SetBkColor(hdc, RGB(30, 30, 30));
		if (hbrBkgnd == NULL)
		{
			hbrBkgnd = CreateSolidBrush(RGB(30, 30, 30));
		}
		return(INT_PTR)hbrBkgnd;
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_0:
			ifNum1 = ifNum1 * 10 + numbers::zero;
			swprintf_s(str, TEXT("%f"), ifNum1);
			SetDlgItemText(hDlg, ID_NUM1ET, str);


			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::zero;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(iNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::zero;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(iNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::zero;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(iNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::zero;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(iNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::zero;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(iNum1, ifNum2, hDlg);
			}
			break;
			
		case ID_1:
			ifNum1 = ifNum1 * 10 + numbers::one;
			swprintf_s(str, TEXT("%f"), ifNum1);
			SetDlgItemText(hDlg, ID_NUM1ET, str);
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::one;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(iNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::one;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(iNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(iNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(iNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(iNum1, ifNum2, hDlg);
			}
			break;

		case ID_2:
			ifNum1 = ifNum1 * 10 + numbers::two;
			swprintf_s(str, TEXT("%f"), ifNum1);
			SetDlgItemText(hDlg, ID_NUM1ET, str);
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(iNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(iNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(iNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(iNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(iNum1, ifNum2, hDlg);
			}
			break;

		case ID_3:
			ifNum1 = ifNum1 * 10 + numbers::three;
			swprintf_s(str, TEXT("%f"), ifNum1);
			SetDlgItemText(hDlg, ID_NUM1ET, str);
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::three;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(iNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::three;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(iNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::three;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(iNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::three;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(iNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::three;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(iNum1, ifNum2, hDlg);
			}
			break;

		case ID_4:
			ifNum1 = ifNum1 * 10 + numbers::four;
			swprintf_s(str, TEXT("%f"), ifNum1);
			SetDlgItemText(hDlg, ID_NUM1ET, str);
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::four;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(iNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::four;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(iNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::four;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(iNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::four;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(iNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::four;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(iNum1, ifNum2, hDlg);
			}
			break;

		case ID_5:
			ifNum1 = ifNum1 * 10 + numbers::five;
			swprintf_s(str, TEXT("%f"), ifNum1);
			SetDlgItemText(hDlg, ID_NUM1ET, str);
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::five;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(iNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::five;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(iNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::five;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(iNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::five;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(iNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::five;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(iNum1, ifNum2, hDlg);
			}
			break;

		case ID_6:
			ifNum1 = ifNum1 * 10 + numbers::six;
			swprintf_s(str, TEXT("%f"), ifNum1);
			SetDlgItemText(hDlg, ID_NUM1ET, str);
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::six;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(iNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::six;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(iNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::six;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(iNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::six;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(iNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::six;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(iNum1, ifNum2, hDlg);
			}
			break;

		case ID_7:
			ifNum1 = ifNum1 * 10 + numbers::seven;
			swprintf_s(str, TEXT("%f"), ifNum1);
			SetDlgItemText(hDlg, ID_NUM1ET, str);
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::seven;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(iNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::seven;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(iNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::seven;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(iNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::seven;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(iNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::seven;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(iNum1, ifNum2, hDlg);
			}
			break;

		case ID_8:
			ifNum1 = ifNum1 * 10 + numbers::eight;
			swprintf_s(str, TEXT("%f"), ifNum1);
			SetDlgItemText(hDlg, ID_NUM1ET, str);
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::eight;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(iNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::eight;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(iNum1, iNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::eight;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(iNum1, iNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::eight;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(iNum1, iNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::eight;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(iNum1, iNum2, hDlg);
			}
			break;

		case ID_9:
			ifNum1 = ifNum1 * 10 + numbers::nine;
			swprintf_s(str, TEXT("%f"), ifNum1);
			SetDlgItemText(hDlg, ID_NUM1ET, str);
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::nine;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(iNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::nine;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(iNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::nine;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(iNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::nine;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(iNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				ifNum2 = ifNum2 * 10 + numbers::nine;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(iNum1, ifNum2, hDlg);
			}
			break;

		case ID_ADD:
			addStatus = 1;
			addCounter += 1;
			Addition(ifNum1, ifNum2, hDlg);
			CreateLogFileForAddition(addStatus, addCounter);
			break;
		
		case ID_SUB:
			subStatus = 1;
			subCounter += 1;
			Subtraction(ifNum1, ifNum2, hDlg);
			CreateLogFileForSubtraction(subStatus, subCounter);
			break;

		case ID_MUL:
			mulStatus = 1;
			mulCounter += 1;
			Multiplication(ifNum1, ifNum2, hDlg);
			CreateLogFileForMultiplication(mulStatus, mulCounter);
			break;
		
		case ID_DIV:
			divStatus = 1;
			divCounter += 1;
			Division(ifNum1, ifNum2, hDlg);
			CreateLogFileForDivision(divStatus, divCounter);
			break;
		
		case ID_MOD:
			modStatus = 1;
			modCounter += 1;
			Modulus(ifNum1, ifNum2, hDlg);
			CreateLogFileForModulus(modStatus, modCounter);
			break;
		
		case ID_EXIT:
			MessageBox(hDlg, TEXT("Are you sure you want to exit?"), TEXT("End Task"), MB_ICONQUESTION | MB_OK);
			EndDialog(hDlg, 0);
 			break;

		case ID_RESET:
			ResetValues(hDlg);
			break;
		}
		return(TRUE);
	}
	return(FALSE);
}

void Addition(float num1, float num2, HWND hDlg) {
	HMODULE hLib = NULL;
	typedef float(*pfnAddition)(float, float);
	pfnAddition pfnAdd = NULL;
	const static float N1 = num1;
	TCHAR str[255];

	//result = N1 + num2;
	hLib = LoadLibrary(TEXT("CalculatorServer.dll"));

	pfnAdd = (pfnAddition)GetProcAddress(hLib, "Addition");
	if (hLib == NULL)
	{
		MessageBox(hDlg, TEXT("Cannot Load Dll\n"), TEXT("Error"), MB_OK);
		DestroyWindow(hDlg);
	}
	result = pfnAdd(N1, num2);
	swprintf_s(str, TEXT("%f"), result);
	SetDlgItemText(hDlg, ID_RESULTET, str);
}

void Subtraction(float num1, float num2, HWND hDlg) {
	HMODULE hLib = NULL;
	typedef float(*pfnSubtraction)(float, float);
	pfnSubtraction pfnSub = NULL;
	const static int N1 = num1;
	TCHAR str[255];

	//result = N1 - num2;
	hLib = LoadLibrary(TEXT("CalculatorServer.dll"));

	pfnSub = (pfnSubtraction)GetProcAddress(hLib, "Subtraction");
	if (hLib == NULL)
	{
		MessageBox(hDlg, TEXT("Cannot Load Dll\n"), TEXT("Error"), MB_OK);
		DestroyWindow(hDlg);
	}
	result = pfnSub(N1, num2);
	swprintf_s(str, TEXT("%f"), result);
	SetDlgItemText(hDlg, ID_RESULTET, str);
}

void Multiplication(float num1, float num2, HWND hDlg)
{
	HMODULE hLib = NULL;
	typedef float(*pfnMultiplication)(float, float);
	pfnMultiplication pfnMul = NULL;
	const static float N1 = num1;
	TCHAR str[255];

	//result = N1 * num2;
	hLib = LoadLibrary(TEXT("CalculatorServer.dll"));

	pfnMul = (pfnMultiplication)GetProcAddress(hLib, "Multiplication");
	if (hLib == NULL)
	{
		MessageBox(hDlg, TEXT("Cannot Load Dll\n"), TEXT("Error"), MB_OK);
		DestroyWindow(hDlg);
	}
	result = pfnMul(N1, num2);
	swprintf_s(str, TEXT("%f"), result);
	SetDlgItemText(hDlg, ID_RESULTET, str);
}

void Division(float num1, float num2, HWND hDlg)
{
	HMODULE hLib = NULL;
	typedef float(*pfnDivision)(float, float);
	pfnDivision pfnDiv = NULL;
	const static float N1 = num1;
	TCHAR str[255];

	if (num2 == 0)
	{
		MessageBox(hDlg, TEXT("Divide by Zero Error"), TEXT("End Task"), MB_OK);
	}
	else
	{
		hLib = LoadLibrary(TEXT("CalculatorServer.dll"));
		pfnDiv = (pfnDivision)GetProcAddress(hLib, "Division");
		if (hLib == NULL)
		{
			MessageBox(hDlg, TEXT("Cannot Load Dll\n"), TEXT("Error"), MB_OK);
			DestroyWindow(hDlg);
		}
		//result = N1 / num2;
		result = pfnDiv(N1, num2);
		swprintf_s(str, TEXT("%f"), result);
		SetDlgItemText(hDlg, ID_RESULTET, str);
	}
}

void Modulus(int num1, int num2, HWND hDlg)
{
	HMODULE hLib = NULL;
	typedef int(*pfnModulus)(int, int);
	pfnModulus pfnMod = NULL;
	const static int N1 = num1;
	TCHAR str[255];

	if (num2 == 0)
	{
		MessageBox(hDlg, TEXT("Exception"), TEXT("End Task"), MB_OK);
	}
	else
	{
		hLib = LoadLibrary(TEXT("CalculatorServer.dll"));
		pfnMod = (pfnModulus)GetProcAddress(hLib, "Modulus");
		if (hLib == NULL)
		{
			MessageBox(hDlg, TEXT("Cannot Load Dll\n"), TEXT("Error"), MB_OK);
			DestroyWindow(hDlg);
		}
		//result = N1 % num2;
		result = pfnMod(N1, num2);
		swprintf_s(str, TEXT("%d"), result);
		SetDlgItemText(hDlg, ID_RESULTET, str);
	}
}

void CreateLogFileForAddition(int status, int counter)
{
	FILE *fptr;
	fopen_s(&fptr, "log.txt", "w");
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\tAddition was performed : %d\n\n times", counter);
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fclose(fptr);
	MessageBox(NULL, TEXT("Log file created successfully"), TEXT("Success"), MB_ICONINFORMATION | MB_OK);
}

void CreateLogFileForSubtraction(int status, int counter)
{
	FILE *fptr;
	fopen_s(&fptr, "log.txt", "w");
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\tSubtraction was performed : %d\n\n times", counter);
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fclose(fptr);
	MessageBox(NULL, TEXT("Log file created successfully"), TEXT("Success"), MB_ICONINFORMATION | MB_OK);
}

void CreateLogFileForMultiplication(int status, int counter)
{
	FILE *fptr;
	fopen_s(&fptr, "log.txt", "w");
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\tmultiplication was performed : %d\n\n times", counter);
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fclose(fptr);
	MessageBox(NULL, TEXT("Log file created successfully"), TEXT("Success"), MB_ICONINFORMATION | MB_OK);
}

void CreateLogFileForDivision(int status, int counter)
{
	FILE *fptr;
	fopen_s(&fptr, "log.txt", "w");
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\tdivision was performed : %d\n\n times", counter);
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fclose(fptr);
	MessageBox(NULL, TEXT("Log file created successfully"), TEXT("Success"), MB_ICONINFORMATION | MB_OK);
}

void CreateLogFileForModulus(int status, int counter)
{
	FILE *fptr;
	fopen_s(&fptr, "log.txt", "w");
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\tmodulus was performed : %d\n\n times", counter);
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fclose(fptr);
	MessageBox(NULL, TEXT("Log file created successfully"), TEXT("Success"), MB_ICONINFORMATION | MB_OK);
}

void ResetValues(HWND hDlg)
{
	TCHAR str[255];
	result = 0, iNum1 = 0, iNum2 = 0, ifNum1 = 0, ifNum2 = 0, addStatus = 0, subStatus = 0,
		mulStatus = 0, divStatus = 0, modStatus = 0;

	swprintf_s(str, TEXT("%d"), iNum1);
	SetDlgItemText(hDlg, ID_NUM1ET, str);
	swprintf_s(str, TEXT("%d"), iNum2);
	SetDlgItemText(hDlg, ID_NUM2ET, str);
	swprintf_s(str, TEXT("%d"), result);
	SetDlgItemText(hDlg, ID_RESULTET, str);

}

void InitializeValues(HWND hDlg)
{
	TCHAR str[255];
	swprintf_s(str, TEXT("%f"), 0.0);
	//SetDlgItemText(hDlg, ID_NUM1ET, str);
	swprintf_s(str, TEXT("%f"), 0.0);
	//SetDlgItemText(hDlg, ID_NUM2ET, str);
}
