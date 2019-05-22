#include "dawidek.h"

WNDCLASSEXA wc= { 0 };
const char* cn = "a";

LONG fps = 1000 / 60;
int wndW = 1200;
int wndH = 600;
int viewW = wndW;
int viewH = wndH;

int labelX = -wndW;

double rot = 0;
double mov = 0.0;

bool doubleB = true;

POINT3D cVerts[8] = { 0 };
double cSize = 100.0;

int xOffset = 0;
int yOffset = 0;
LPPOINT mouse = { 0 };

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = cn;
	wc.lpfnWndProc = wndProc;
	wc.hbrBackground = NULL;

	if (!RegisterClassExA(&wc)) {
		MessageBoxA(NULL, "Wyst�pi� b��d podczas rejestracji klasy okna!", "Oj :(", MB_ICONERROR | MB_OK);
	} //else OK
	
	HWND hWnd = CreateWindowExA(WS_EX_CLIENTEDGE, cn, "Plansza wywo�awcza TVP 1", WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT, wndW, wndH, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL) {
		MessageBoxA(NULL, "Wyst�pi� b��d podczas tworzenia okna!", "Oj :(", MB_ICONERROR | MB_OK);
	}

	ShowWindow(hWnd, nCmdShow);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {

	case WM_CREATE: {
		SetTimer(hWnd, 1, fps, NULL);
		break;
	}
	case WM_TIMER: {
		InvalidateRect(hWnd, NULL, TRUE);
		SetTimer(hWnd, 1, fps, NULL);
		rot += 0.02;
		mov += 0.03;
		labelX -= 2;
		if (labelX < -wndW) labelX = 14844;
		break;
	}
	case WM_SIZE: {
		wndW = LOWORD(lParam);
		wndH = HIWORD(lParam);
		break;
	}
	case WM_ERASEBKGND: {
		return TRUE;
	}
	case WM_PAINT: {
		GetClientRect(hWnd, &rc);

		if (doubleB) {
			hdcParent = BeginPaint(hWnd, &ps);
			hdc = CreateCompatibleDC(hdcParent);
			hBmp = CreateCompatibleBitmap(hdcParent, wndW, wndH);
			SelectObject(hdc, hBmp);
		} else {
			hdc = BeginPaint(hWnd, &ps);
		}

		//Rysuj� t�o w jednolitym kolorze:
		
		SetSolidBrush(0x000000);
		Rectangle(hdc, 0, 0, rc.right, rc.bottom);

		/*SetMapMode(hdc, MM_ISOTROPIC);
		SetWindowExtEx(hdc, viewW, viewH, NULL);
		SetViewportExtEx(hdc, wndW, wndH, NULL);
		SetViewportOrgEx(hdc, wndW / 2, wndH / 2, NULL);*/
		
		// G�RNA �CIANA
		cVerts[0] = { 
			-sqrt(2)*cSize*cos(rot + 1 * M_PI / 4) + wndW / 2 + xOffset ,
			-cSize + wndH / 2 + yOffset + 32 * sin(mov),
			-sqrt(2)*cSize*sin(rot + 1 * M_PI / 4)
		};

		cVerts[1] = {
			-sqrt(2)*cSize*cos(rot + 3 * M_PI / 4) + wndW / 2 + xOffset ,
			-cSize + wndH / 2 + yOffset + 32 * sin(mov),
			-sqrt(2)*cSize*sin(rot + 3 * M_PI / 4)
		};
		cVerts[2] = {
			-sqrt(2)*cSize*cos(rot + 5 * M_PI / 4) + wndW / 2 + xOffset ,
			-cSize + wndH / 2 + yOffset + 32 * sin(mov),
			-sqrt(2)*cSize*sin(rot + 5 * M_PI / 4)
		};
		cVerts[3] = {
			-sqrt(2)*cSize*cos(rot + 7 * M_PI / 4) + wndW / 2 + xOffset ,
			-cSize + wndH / 2 + yOffset + 32 * sin(mov),
			-sqrt(2)*cSize*sin(rot + 7 * M_PI / 4)
		};

		// DOLNA �CIANA
		cVerts[4] = {
			-sqrt(2)*cSize*cos(rot + 1 * M_PI / 4) + wndW / 2 + xOffset ,
			+cSize + wndH / 2 + yOffset + 32 * sin(mov),
			-sqrt(2)*cSize*sin(rot + 1 * M_PI / 4)
		};

		cVerts[5] = {
			-sqrt(2)*cSize*cos(rot + 3 * M_PI / 4) + wndW / 2 + xOffset ,
			+cSize + wndH / 2 + yOffset + 32 * sin(mov),
			-sqrt(2)*cSize*sin(rot + 3 * M_PI / 4)
		};
		cVerts[6] = {
			-sqrt(2)*cSize*cos(rot + 5 * M_PI / 4) + wndW / 2 + xOffset ,
			+cSize + wndH / 2 + yOffset + 32 * sin(mov),
			-sqrt(2)*cSize*sin(rot + 5 * M_PI / 4)
		};
		cVerts[7] = {
			-sqrt(2)*cSize*cos(rot + 7 * M_PI / 4) + wndW / 2 + xOffset ,
			+cSize + wndH / 2 + yOffset + 32 * sin(mov),
			-sqrt(2)*cSize*sin(rot + 7 * M_PI / 4)
		};

		SetPen(PS_SOLID, 4, 0xff8fa4);
		DrawLine3D(cVerts[0], cVerts[1]);
		DrawLine3D(cVerts[1], cVerts[2]);
		DrawLine3D(cVerts[2], cVerts[3]);
		DrawLine3D(cVerts[3], cVerts[0]);

		DrawLine3D(cVerts[4], cVerts[5]);
		DrawLine3D(cVerts[5], cVerts[6]);
		DrawLine3D(cVerts[6], cVerts[7]);
		DrawLine3D(cVerts[7], cVerts[4]);

		DrawLine3D(cVerts[0], cVerts[4]);
		DrawLine3D(cVerts[1], cVerts[5]);
		DrawLine3D(cVerts[2], cVerts[6]);
		DrawLine3D(cVerts[3], cVerts[7]);

		SetBkMode(hdc, TRANSPARENT);
		SetTextAlign(hdc, TA_CENTER);
		SetFont("Arial Black", 80, FALSE, FALSE, FALSE);
		Print(wndW / 2, 0, "KOSTECZKA");

		SetFont("Arial Black", 32, FALSE, FALSE, FALSE);
		Print(wndW / 2, 64, "Demko by Dawid");

		SetFont("default", 24, TRUE, FALSE, FALSE);
		SetTextAlign(hdc, TA_RIGHT);
		Print(wndW + labelX, wndH - 32, "Moje uszanowanko, z tej strony Dawidek! Na pocz�tek opowiem nieco o wa�nych elementach. Zacznijmy od samego p��tna, czyli tego, dzi�ki czemu w og�le jeste� w stanie zobaczy� to demko. U�ywaj�c techniki zwanej \"Double Buffering\" mo�na ca�kowicie wyeliminowa� rozdarcia p��tna podczas zbyt cz�stego od�wie�ania Device Contentu (DC zaczyna \"paskowa�\" przy cz�stym od�wie�aniu np. przy u�yciu Timer�w)! Niestety, o VSync mo�na najwy�ej pomarzy�, GDI oraz GDI+ nie obs�uguj� takiego sygna�u :( Przejd�my teraz do meritum demka, czyli sze�cianu. W kodzie, wierzcho�ki sze�cianu s� zdefiniowane jako pewna struktura, kt�ra sk�ada si� z 3 zmiennych typu LONG (zupe�nie jak punkt w przestrzeni opisany za pomoc� 3 wsp�rz�dnych). Aby prawid�owo obliczy� wsp�rz�dne punkt�w wszystkich wierzcho�k�w, potrzebne b�d� 3 rzeczy: podstawowa wiedza o tym, jak dzia�a perspektywa, umiej�tno�� rzutowania punkt�w w przestrzeni na p�ask� powierzchni� 2D oraz wyobra�nia. Je�eli obiekt zacznie si� porusza� po p�aszczy�nie r�wnoleg�ej do p�aszczyzny rzutu 2D oraz nie b�dzie si� przemieszcza� w kierunku prostopad�ym do tej p�aszczyzny, jego skala nie zmieni si�. Natomiast je�eli zacznie si� przemieszcza� w kierunku kamery, zacznie si� powi�ksza� i zmniejsza�. Je�eli obiekt przesuniemy N razy bli�ej kamery, N razy zwi�kszymy jego pozorn� skal�. Bior�c za uk�ad odniesienia �rodek Device Contentu, wystarczy wsp�rz�dne X i Y rzutowanego punktu pomno�y� przez D^(-Z) gdzie D to wsp�czynnik g��bi (w tym demku wynosi on 1.002). Wi�cej informacji o rzutowaniu znajdziecie na angielskiej Wikipedii w artykule \"3D Projection\".");

		ResetPen();
		ResetBrush();

		if (doubleB) {
			BitBlt(hdcParent, 0, 0, wndW, wndH, hdc, 0, 0, SRCCOPY);
			DeleteDC(hdc);
			DeleteObject(hBmp);
		} else {
			DeleteObject(hBmp);
		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_CLOSE: {
		DestroyWindow(hWnd);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default: {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	}

	return 0;
}