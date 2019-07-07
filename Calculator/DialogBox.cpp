#include<windows.h>
#include "MyDialog.h"
#include "Calculator.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

#pragma region GlobalVariables
static float ifNum1 = 0,
	ifNum2 = 0;

float result = 0;

static int addStatus = 0,
	subStatus = 0,
	mulStatus = 0,
	divStatus = 0,
	modStatus = 0,
	initialStatus = 1;

static int addCounter = 0,
	subCounter = 0,
	mulCounter = 0,
	divCounter = 0,
	modCounter = 0;

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
#pragma endregion

#pragma region WinMain
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
#pragma endregion

#pragma  region WndProc
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
#pragma endregion

#pragma region MyDlgProc
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

	case WM_CTLCOLORSTATIC:
		hdc = HDC(wParam);
		SetTextColor(hdc, RGB(30, 148, 148));
		SetBkColor(hdc, RGB(30, 30, 30));
		if (hbrBkgnd == NULL)
		{
			hbrBkgnd = CreateSolidBrush(RGB(30, 30, 30));
		}
		return (INT_PTR)hbrBkgnd;
		break;

	case WM_CTLCOLOREDIT:
		hdc = HDC(wParam);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(60, 60, 60));
		return(INT_PTR)CreateSolidBrush(RGB(60, 60, 60));
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_0:
			if (initialStatus == 1)
			{
				ifNum1 = ifNum1 * 10 + numbers::zero;
				swprintf_s(str, TEXT("%f"), ifNum1);
				SetDlgItemText(hDlg, ID_NUM1ET, str);
			}
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::zero;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(ifNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				//type second number and make a call to sub function
				ifNum2 = ifNum2 * 10 + numbers::zero;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(ifNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				//type second number and make a call to mul function
				ifNum2 = ifNum2 * 10 + numbers::zero;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(ifNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				//type second number and make a call to div function
				ifNum2 = ifNum2 * 10 + numbers::zero;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(ifNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				//type second number and make a call to mod function
				ifNum2 = ifNum2 * 10 + numbers::zero;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(ifNum1, ifNum2, hDlg);
			}
			break;

		case ID_1:
			if (initialStatus == 1)
			{
				ifNum1 = ifNum1 * 10 + numbers::one;
				swprintf_s(str, TEXT("%f"), ifNum1);
				SetDlgItemText(hDlg, ID_NUM1ET, str);
			}
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::one;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(ifNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				//type second number and make a call to sub function
				ifNum2 = ifNum2 * 10 + numbers::one;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(ifNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				//type second number and make a call to mul function
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(ifNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				//type second number and make a call to div function
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(ifNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				//type second number and make a call to mod function
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(ifNum1, ifNum2, hDlg);
			}
			break;

		case ID_2:
			if (initialStatus == 1)
			{
				ifNum1 = ifNum1 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum1);
				SetDlgItemText(hDlg, ID_NUM1ET, str);
			}
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(ifNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				//type second number and make a call to sub function
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(ifNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				//type second number and make a call to mul function
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(ifNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				//type second number and make a call to div function
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(ifNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				//type second number and make a call to mod function
				ifNum2 = ifNum2 * 10 + numbers::two;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(ifNum1, ifNum2, hDlg);
			}
			break;

		case ID_3:
			if (initialStatus == 1)
			{
				ifNum1 = ifNum1 * 10 + numbers::three;
				swprintf_s(str, TEXT("%f"), ifNum1);
				SetDlgItemText(hDlg, ID_NUM1ET, str);
			}
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::three;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(ifNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				//type second number and make a call to sub function
				ifNum2 = ifNum2 * 10 + numbers::three;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(ifNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				//type second number and make a call to mul function
				ifNum2 = ifNum2 * 10 + numbers::three;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(ifNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				//type second number and make a call to div function
				ifNum2 = ifNum2 * 10 + numbers::three;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(ifNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				//type second number and make a call to mod function
				ifNum2 = ifNum2 * 10 + numbers::three;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(ifNum1, ifNum2, hDlg);
			}
			break;

		case ID_4:
			if (initialStatus == 1)
			{
				ifNum1 = ifNum1 * 10 + numbers::four;
				swprintf_s(str, TEXT("%f"), ifNum1);
				SetDlgItemText(hDlg, ID_NUM1ET, str);
			}
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::four;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(ifNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				//type second number and make a call to sub function
				ifNum2 = ifNum2 * 10 + numbers::four;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(ifNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				//type second number and make a call to mul function
				ifNum2 = ifNum2 * 10 + numbers::four;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(ifNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				//type second number and make a call to div function
				ifNum2 = ifNum2 * 10 + numbers::four;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(ifNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				//type second number and make a call to mod function
				ifNum2 = ifNum2 * 10 + numbers::four;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(ifNum1, ifNum2, hDlg);
			}
			break;

		case ID_5:
			if (initialStatus == 1)
			{
				ifNum1 = ifNum1 * 10 + numbers::five;
				swprintf_s(str, TEXT("%f"), ifNum1);
				SetDlgItemText(hDlg, ID_NUM1ET, str);
			}
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::five;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(ifNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				//type second number and make a call to sub function
				ifNum2 = ifNum2 * 10 + numbers::five;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(ifNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				//type second number and make a call to mul function
				ifNum2 = ifNum2 * 10 + numbers::five;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(ifNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				//type second number and make a call to div function
				ifNum2 = ifNum2 * 10 + numbers::five;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(ifNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				//type second number and make a call to mod function
				ifNum2 = ifNum2 * 10 + numbers::five;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(ifNum1, ifNum2, hDlg);
			}
			break;

		case ID_6:
			if (initialStatus == 1)
			{
				ifNum1 = ifNum1 * 10 + numbers::six;
				swprintf_s(str, TEXT("%f"), ifNum1);
				SetDlgItemText(hDlg, ID_NUM1ET, str);
			}
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::six;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(ifNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				//type second number and make a call to sub function
				ifNum2 = ifNum2 * 10 + numbers::six;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(ifNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				//type second number and make a call to mul function
				ifNum2 = ifNum2 * 10 + numbers::six;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(ifNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				//type second number and make a call to div function
				ifNum2 = ifNum2 * 10 + numbers::six;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(ifNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				//type second number and make a call to mod function
				ifNum2 = ifNum2 * 10 + numbers::six;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(ifNum1, ifNum2, hDlg);
			}
			break;

		case ID_7:
			if (initialStatus == 1)
			{
				ifNum1 = ifNum1 * 10 + numbers::seven;
				swprintf_s(str, TEXT("%f"), ifNum1);
				SetDlgItemText(hDlg, ID_NUM1ET, str);
			}
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::seven;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(ifNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				//type second number and make a call to sub function
				ifNum2 = ifNum2 * 10 + numbers::seven;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(ifNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				//type second number and make a call to mul function
				ifNum2 = ifNum2 * 10 + numbers::seven;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(ifNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				//type second number and make a call to div function
				ifNum2 = ifNum2 * 10 + numbers::seven;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(ifNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				//type second number and make a call to mod function
				ifNum2 = ifNum2 * 10 + numbers::seven;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(ifNum1, ifNum2, hDlg);
			}
			break;

		case ID_8:
			if (initialStatus == 1)
			{
				ifNum1 = ifNum1 * 10 + numbers::eight;
				swprintf_s(str, TEXT("%f"), ifNum1);
				SetDlgItemText(hDlg, ID_NUM1ET, str);
			}
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::eight;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(ifNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				//type second number and make a call to sub function
				ifNum2 = ifNum2 * 10 + numbers::eight;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(ifNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				//type second number and make a call to mul function
				ifNum2 = ifNum2 * 10 + numbers::eight;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(ifNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				//type second number and make a call to div function
				ifNum2 = ifNum2 * 10 + numbers::eight;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(ifNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				//type second number and make a call to mod function
				ifNum2 = ifNum2 * 10 + numbers::eight;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(ifNum1, ifNum2, hDlg);
			}
			break;

		case ID_9:
			if (initialStatus == 1)
			{
				ifNum1 = ifNum1 * 10 + numbers::nine;
				swprintf_s(str, TEXT("%f"), ifNum1);
				SetDlgItemText(hDlg, ID_NUM1ET, str);
			}
			if (addStatus == 1)
			{
				//type second number and make a call to add function
				ifNum2 = ifNum2 * 10 + numbers::nine;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Addition(ifNum1, ifNum2, hDlg);
			}
			else if (subStatus == 1)
			{
				//type second number and make a call to sub function
				ifNum2 = ifNum2 * 10 + numbers::nine;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Subtraction(ifNum1, ifNum2, hDlg);
			}
			else if (mulStatus == 1)
			{
				//type second number and make a call to mul function
				ifNum2 = ifNum2 * 10 + numbers::nine;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Multiplication(ifNum1, ifNum2, hDlg);
			}
			else if (divStatus == 1)
			{
				//type second number and make a call to div function
				ifNum2 = ifNum2 * 10 + numbers::nine;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Division(ifNum1, ifNum2, hDlg);
			}
			else if (modStatus == 1)
			{
				//type second number and make a call to mod function
				ifNum2 = ifNum2 * 10 + numbers::nine;
				swprintf_s(str, TEXT("%f"), ifNum2);
				SetDlgItemText(hDlg, ID_NUM2ET, str);
				Modulus(ifNum1, ifNum2, hDlg);
			}
			break;

		case ID_ADD:
			initialStatus = 0;
			addStatus = 1;
			addCounter += 1;
			Addition(ifNum1, ifNum2, hDlg);
			CreateLogFileForAddition(addStatus, addCounter);
			break;

		case ID_SUB:
			initialStatus = 0;
			subStatus = 1;
			subCounter += 1;
			Subtraction(ifNum1, ifNum2, hDlg);
			CreateLogFileForSubtraction(subStatus, subCounter);
			break;

		case ID_MUL:
			initialStatus = 0;
			mulStatus = 1;
			mulCounter += 1;
			Multiplication(ifNum1, ifNum2, hDlg);
			CreateLogFileForMultiplication(mulStatus, mulCounter);
			break;

		case ID_DIV:
			initialStatus = 0;
			divStatus = 1;
			divCounter += 1;
			Division(ifNum1, ifNum2, hDlg);
			CreateLogFileForDivision(divStatus, divCounter);
			break;

		case ID_MOD:
			initialStatus = 0;
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
#pragma endregion

#pragma region Addition
void Addition(float num1, float num2, HWND hDlg) {
	HMODULE hLib = NULL;
	typedef float(*pfnAddition)(float, float);
	pfnAddition pfnAdd = NULL;
	TCHAR str[255];

	hLib = LoadLibrary(TEXT("CalculatorServer.dll"));

	pfnAdd = (pfnAddition)GetProcAddress(hLib, "Addition");
	if (hLib == NULL)
	{
		MessageBox(hDlg, TEXT("Cannot Load Dll\n"), TEXT("Error"), MB_OK);
		DestroyWindow(hDlg);
	}
	result = pfnAdd(num1, num2);
	swprintf_s(str, TEXT("%f"), result);
	SetDlgItemText(hDlg, ID_RESULTET, str);
}
#pragma endregion

#pragma region Subtraction
void Subtraction(float num1, float num2, HWND hDlg) {
	HMODULE hLib = NULL;
	typedef float(*pfnSubtraction)(float, float);
	pfnSubtraction pfnSub = NULL;
	TCHAR str[255];

	hLib = LoadLibrary(TEXT("CalculatorServer.dll"));

	pfnSub = (pfnSubtraction)GetProcAddress(hLib, "Subtraction");
	if (hLib == NULL)
	{
		MessageBox(hDlg, TEXT("Cannot Load Dll\n"), TEXT("Error"), MB_OK);
		DestroyWindow(hDlg);
	}
	result = pfnSub(num1, num2);
	swprintf_s(str, TEXT("%f"), result);
	SetDlgItemText(hDlg, ID_RESULTET, str);
}
#pragma endregion

#pragma region Multiplication
void Multiplication(float num1, float num2, HWND hDlg) {
	HMODULE hLib = NULL;
	typedef float(*pfnMultiplication)(float, float);
	pfnMultiplication pfnMul = NULL;
	TCHAR str[255];

	hLib = LoadLibrary(TEXT("CalculatorServer.dll"));

	pfnMul = (pfnMultiplication)GetProcAddress(hLib, "Multiplication");
	if (hLib == NULL)
	{
		MessageBox(hDlg, TEXT("Cannot Load Dll\n"), TEXT("Error"), MB_OK);
		DestroyWindow(hDlg);
	}
	result = pfnMul(num1, num2);
	swprintf_s(str, TEXT("%f"), result);
	SetDlgItemText(hDlg, ID_RESULTET, str);
}
#pragma endregion

#pragma region Division
void Division(float num1, float num2, HWND hDlg) {
	HMODULE hLib = NULL;
	typedef float(*pfnDivision)(float, float);
	pfnDivision pfnDiv = NULL;
	TCHAR str[255];
	if (num2 == 0)
	{
		MessageBox(hDlg, TEXT("Divide by Zero Error"), TEXT("End Task"), MB_OK | MB_ICONERROR);
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
		result = pfnDiv(num1, num2);
		swprintf_s(str, TEXT("%f"), result);
		SetDlgItemText(hDlg, ID_RESULTET, str);
	}
}
#pragma endregion

#pragma region Modulus
void Modulus(float num1, float num2, HWND hDlg) {
	HMODULE hLib = NULL;
	typedef int(*pfnModulus)(int, int);
	pfnModulus pfnMod = NULL;
	TCHAR str[255];

	if (num2 == 0)
	{
		swprintf_s(str, TEXT("%f"), num2);
		SetDlgItemText(hDlg, ID_RESULTET, str);
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
		result = pfnMod(num1, num2);
		swprintf_s(str, TEXT("%f"), result);
		SetDlgItemText(hDlg, ID_RESULTET, str);
	}
}
#pragma endregion

#pragma region CreateLogFiles
void CreateLogFileForAddition(int status, int counter) {
	FILE *fptr;
	fopen_s(&fptr, "log.txt", "a");
	//fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\tAddition was performed : %d time(s)\n", counter);
	//fprintf_s(fptr, "\t\t####################################################\n\n");
	fclose(fptr);
	// MessageBox(NULL, TEXT("Log file created successfully"), TEXT("Success"), MB_ICONINFORMATION | MB_OK);
}

void CreateLogFileForSubtraction(int status, int counter) {
	FILE *fptr;
	fopen_s(&fptr, "log.txt", "a");
	//fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\tSubtraction was performed :  %d time(s)\n", counter);
	//fprintf_s(fptr, "\t\t####################################################\n\n");
	fclose(fptr);
	//MessageBox(NULL, TEXT("Log file created successfully"), TEXT("Success"), MB_ICONINFORMATION | MB_OK);
}

void CreateLogFileForMultiplication(int status, int counter) {
	FILE *fptr;
	fopen_s(&fptr, "log.txt", "a");
	//fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\tmultiplication was performed :  %d time(s)\n", counter);
	//fprintf_s(fptr, "\t\t####################################################\n\n");
	fclose(fptr);
	//MessageBox(NULL, TEXT("Log file created successfully"), TEXT("Success"), MB_ICONINFORMATION | MB_OK);
}

void CreateLogFileForDivision(int status, int counter) {
	FILE *fptr;
	fopen_s(&fptr, "log.txt", "a");
	//fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\tdivision was performed :  %d time(s)\n", counter);
	//fprintf_s(fptr, "\t\t####################################################\n\n");
	fclose(fptr);
	//MessageBox(NULL, TEXT("Log file created successfully"), TEXT("Success"), MB_ICONINFORMATION | MB_OK);
}

void CreateLogFileForModulus(int status, int counter) {
	FILE *fptr;
	fopen_s(&fptr, "log.txt", "a");
	//fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "\t\tmodulus was performed :  %d time(s)\n", counter);
	//fprintf_s(fptr, "\t\t####################################################\n\n");
	fclose(fptr);
	//MessageBox(NULL, TEXT("Log file created successfully"), TEXT("Success"), MB_ICONINFORMATION | MB_OK);
}

void CreateLogFileForResetCheck(float result, float ifNum1, float ifNum2,
	int addStatus, int subStatus, int mulStatus, int divStatus, int modStatus) {
	FILE *fptr;
	fopen_s(&fptr, "resetlog.txt", "w");
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fprintf_s(fptr, "%d%d%d%d%d%d%d%d\n\n", result, ifNum1, ifNum2, addStatus, subStatus, mulStatus, divStatus, modStatus);
	fprintf_s(fptr, "\t\t####################################################\n\n");
	fclose(fptr);
}
#pragma endregion

#pragma region ResetValues
void ResetValues(HWND hDlg) {
	TCHAR str[255];
	result = 0,
		ifNum1 = 0,
		ifNum2 = 0,
		addStatus = 0,
		subStatus = 0,
		mulStatus = 0,
		divStatus = 0,
		modStatus = 0,
		initialStatus = 1;

	swprintf_s(str, TEXT("%d"), ifNum1);
	SetDlgItemText(hDlg, ID_NUM1ET, str);
	swprintf_s(str, TEXT("%d"), ifNum2);
	SetDlgItemText(hDlg, ID_NUM2ET, str);
	swprintf_s(str, TEXT("%d"), result);
	SetDlgItemText(hDlg, ID_RESULTET, str);
	CreateLogFileForResetCheck(result, ifNum1, ifNum2, addStatus, subStatus, mulStatus, divStatus, modStatus);
}
#pragma endregion

#pragma region InitializeValues
void InitializeValues(HWND hDlg)
{
	TCHAR str[255];
	swprintf_s(str, TEXT("%f"), 0);
	SetDlgItemText(hDlg, ID_NUM1ET, str);
	swprintf_s(str, TEXT("%f"), 0);
	SetDlgItemText(hDlg, ID_NUM2ET, str);
	swprintf_s(str, TEXT("%f"), 0);
	SetDlgItemText(hDlg, ID_RESULTET, str);
}
#pragma endregion
