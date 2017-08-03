#include "stdafx.h"
#include <commctrl.h>
#include "CEditor.h"
wchar_t EditorClassName[ ] = L"EDITOR WINDOW CLASS";
wchar_t PaintToolsClassName[ ] = L"EDITOR TOOLS CLASS";
wchar_t ColorPaletteClassName[ ] = L"EDITOR COLORS CLASS";
wchar_t ShapesToolClassName[ ] = L"EDITOR SHAPES CLASS";
LRESULT CALLBACK EditorWindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK PaintToolsWindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ShapesToolWindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ColorPaletteWindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow){
    //InitCommonControls();
    //ERROR_TEST;
    int sysWidth=GetSystemMetrics(SM_CXSCREEN);
    int sysHeight=GetSystemMetrics(SM_CYSCREEN);
    MSG messages;
    WNDCLASSEX wincl;
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = L"DEFAULT";///
    wincl.lpfnWndProc = NULL;///
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    HBRUSH brush=CreateSolidBrush(RGB(128,128,128));
    wincl.hbrBackground =brush;

    wincl.lpszClassName=EditorClassName;
    wincl.lpfnWndProc = EditorWindowProcedure;
    wincl.cbWndExtra=sizeof(CEditor*);
    if (!RegisterClassEx (&wincl)) return 0;

    wincl.lpszClassName=PaintToolsClassName;
    wincl.lpfnWndProc = PaintToolsWindowProcedure;
    wincl.cbWndExtra=sizeof(CPaintTools*);
    if (!RegisterClassEx (&wincl)) return 0;

    wincl.lpszClassName=ColorPaletteClassName;
    wincl.lpfnWndProc = ColorPaletteWindowProcedure;
    wincl.cbWndExtra=sizeof(CColorPalette*);
    if (!RegisterClassEx (&wincl)) return 0;

    wincl.lpszClassName=ShapesToolClassName;
    wincl.lpfnWndProc = ShapesToolWindowProcedure;
    wincl.cbWndExtra=sizeof(CShapesTool*);
    if (!RegisterClassEx (&wincl)) return 0;

    HWND hwnd=CreateWindowEx (0,EditorClassName,L"blank image.bmp",WS_OVERLAPPEDWINDOW|WS_VSCROLL|WS_HSCROLL,CW_USEDEFAULT,CW_USEDEFAULT,sysWidth,sysHeight,HWND_DESKTOP,NULL,hThisInstance,NULL);
    ShowWindow (hwnd, SW_SHOWMAXIMIZED);
    while (GetMessage (&messages, NULL, 0, 0)){
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    DeleteObject(brush);

    return messages.wParam;
}
LRESULT CALLBACK PaintToolsWindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    CPaintTools *paintTools=(CPaintTools*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if(message==WM_NCCREATE){
            paintTools=new CPaintTools(hwnd);
            if(paintTools)
            {
                SetWindowLong(hwnd, GWL_USERDATA,(LONG)paintTools);
            }
            else SendMessage(hwnd,WM_DESTROY,0,0);
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    if(message==WM_NCDESTROY){
        if(paintTools) delete paintTools;
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    else return paintTools->event(hwnd,message,wParam,lParam);
}
LRESULT CALLBACK ColorPaletteWindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    CColorPalette *colorPalette=(CColorPalette*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if(message==WM_NCCREATE){
            colorPalette=new CColorPalette(hwnd);
            if(colorPalette)
            {
                SetWindowLong(hwnd, GWL_USERDATA,(LONG)colorPalette);
            }
            else SendMessage(hwnd,WM_DESTROY,0,0);
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    if(message==WM_NCDESTROY){
        if(colorPalette) delete colorPalette;
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    else return colorPalette->event(hwnd,message,wParam,lParam);
}
LRESULT CALLBACK EditorWindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    CEditor *editor=(CEditor*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if(message==WM_NCCREATE){
            editor=new CEditor(hwnd);
            if(editor)
            {
                SetWindowLong(hwnd, GWL_USERDATA,(LONG)editor);
            }
            else SendMessage(hwnd,WM_DESTROY,0,0);
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    if(message==WM_NCDESTROY){
        if(editor)delete editor;
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    else return editor->event(hwnd,message,wParam,lParam);
}
LRESULT CALLBACK ShapesToolWindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    CShapesTool *shapesTool=(CShapesTool*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if(message==WM_NCCREATE){
            shapesTool=new CShapesTool(hwnd);
            if(shapesTool)
            {
                SetWindowLong(hwnd, GWL_USERDATA,(LONG)shapesTool);
            }
            else SendMessage(hwnd,WM_DESTROY,0,0);
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    if(message==WM_NCDESTROY){
        if(shapesTool)delete shapesTool;
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    else return shapesTool->event(hwnd,message,wParam,lParam);
}
/*HBITMAP invertBitmap(HBITMAP hBitmap){
    HDC memDC=CreateCompatibleDC(GetDC(0));
    BITMAPINFO bi;
	ZeroMemory(&bi, sizeof(BITMAPINFO));
    BITMAP bmInfo;
	GetObject( hBitmap, sizeof( bmInfo ), &bmInfo );

	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = bmInfo.bmWidth;
	bi.bmiHeader.biHeight = bmInfo.bmHeight;  //negative so (0,0) is at top left
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	BYTE *bits;
    HBITMAP out =CreateDIBSection(memDC, &bi, DIB_RGB_COLORS,  (VOID**)&bits, NULL, 0);
    HBITMAP old2=(HBITMAP)SelectObject(memDC,out);
    HDC memDC2=CreateCompatibleDC(memDC);
    HBITMAP old1=(HBITMAP)SelectObject(memDC2,hBitmap);

    BitBlt( memDC, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, memDC2, 0, 0, SRCINVERT);
    for(int i=0;i<bi.bmiHeader.biWidth*bi.bmiHeader.biHeight*(bi.bmiHeader.biBitCount>>3);i++) bits[i]=255-bits[i];
    SelectObject(memDC,old2);
    SelectObject(memDC2,old1);
    DeleteDC(memDC);
    DeleteDC(memDC2);
    return out;
}*/
