#include "ChiliWin.h"
#include "WindowsMessageMap.h"
#include <sstream>
#include "Window.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static WindowsMessageMap mm;
	OutputDebugString(mm(msg, lParam, wParam).c_str());		//usar para debugar eventos

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_KEYDOWN:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, "Respects");
		}
		break;
	case WM_KEYUP:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, "F IS DEAD");
		}
		break;
	case WM_CHAR:
	{
		static std::string title;
		title.push_back((char)wParam);
		SetWindowText(hWnd, title.c_str());
	}
	break;
	case WM_LBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);
		std::ostringstream oss;
		oss << "(" << pt.x << "," << pt.y << ")";
		SetWindowText(hWnd, oss.str().c_str());
	}
	break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdShow,
	int nCmdShow)
{
	try
	{

		Window wnd(800, 300, "Teste de instancia de janela");

		/*const auto pClassName = "hw3dtestClassName";
		//register window class
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = pClassName;
		wc.hIconSm = nullptr;
		RegisterClassEx(&wc);
		//create window instance
		HWND hWnd = CreateWindowEx(
			0, pClassName,
			"Happy Window",
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			200, 200, 640, 480,
			nullptr, nullptr, hInstance, nullptr
		);
		//show window
		ShowWindow(hWnd, SW_SHOW);
	*/

	//message
		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (wnd.kbd.KeyIsPressed(VK_SPACE))
			{
				MessageBox(nullptr, "Botão apertado!", "Apertou Espaço!", MB_OK | MB_ICONEXCLAMATION);
			}
		}

		if (gResult == -1)
		{
			return -1;
		}
		else
		{
			return msg.wParam;
		}
	}
	catch (const ChiliException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Exceção Padrão", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "Sem informações disponíveis", "Exceção desconhecida", MB_OK | MB_ICONEXCLAMATION);
	}

	return 0;
}