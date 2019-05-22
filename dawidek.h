#pragma once

#include <stdio.h>
#include <Windows.h>
#include <corecrt_math.h>
#include <corecrt_math_defines.h>

PAINTSTRUCT ps;
HPEN pn = NULL;
HBRUSH br = NULL;
HDC hdc, hdcParent;
HBITMAP hBmp;
HFONT hFont = NULL;
RECT rc;

double depth = 1.002;

HFONT _stdcall SetFont(LPCSTR font, int size, BOOL italic, BOOL underline, BOOL strikeout) {
	if (hFont != NULL) DeleteObject(hFont);
	hFont = NULL;
	hFont = CreateFontA(size, 0, 0, 0, FW_DONTCARE, italic, underline, strikeout, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, font);
	//SendMessageA(NULL, WM_SETFONT, (WPARAM)hFont, TRUE);
	SelectObject(hdc, hFont);
	return hFont;
}

HPEN _stdcall SetPen(int style, LONG width, COLORREF color) {
	if (pn != NULL) DeleteObject(pn);
	pn = NULL;
	pn = CreatePen(style, width, color);
	SetTextColor(hdc, color);
	SelectObject(hdc, pn);
	return pn;
}

BOOL _stdcall Print(int x, int y, LPCSTR text) {
	return TextOutA(hdc, x, y, text, strlen(text));
}
BOOL _stdcall ResetPen() {
	if (pn != NULL) { return DeleteObject(pn); }
	else { return FALSE; }
}

HBRUSH _stdcall SetSolidBrush(COLORREF color) {
	if (br != NULL) DeleteObject(br);
	br = NULL;
	br = CreateSolidBrush(color);
	SelectObject(hdc, br);
	return br;
}

BOOL _stdcall ResetBrush() {
	if (br != NULL) { return DeleteObject(br); }
	else { return FALSE; }
}

typedef struct tagPOINT3D {

	double x;
	double y;
	double z;

} POINT3D, *LPPOINT3D;

BOOL DrawLine3D(double x1, double y1, double z1, double x2, double y2, double z2) {

	int X1 = (int)(pow(depth, -z1)*(x1 - rc.right / 2) + rc.right / 2);
	int Y1 = (int)(pow(depth, -z1)*(y1 - rc.bottom / 2) + rc.bottom / 2);
	
	int X2 = (int)(pow(depth, -z2)*(x2 - rc.right / 2) + rc.right / 2);
	int Y2 = (int)(pow(depth, -z2)*(y2 - rc.bottom / 2) + rc.bottom / 2);

	//MoveToEx(hdc, );
	MoveToEx(hdc, X1, Y1, NULL);
	return LineTo(hdc, X2, Y2);
}
BOOL DrawLine3D(tagPOINT3D p1, tagPOINT3D p2) {

	int X1 = (int)(pow(depth, -p1.z)*(p1.x - rc.right / 2) + rc.right / 2);
	int Y1 = (int)(pow(depth, -p1.z)*(p1.y - rc.bottom / 2) + rc.bottom / 2);

	int X2 = (int)(pow(depth, -p2.z)*(p2.x - rc.right / 2) + rc.right / 2);
	int Y2 = (int)(pow(depth, -p2.z)*(p2.y - rc.bottom / 2) + rc.bottom / 2);

	//MoveToEx(hdc, );
	MoveToEx(hdc, X1, Y1, NULL);
	return LineTo(hdc, X2, Y2);
}