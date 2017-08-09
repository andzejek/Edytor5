#ifndef CEDITOR_H
#define CEDITOR_H
#include "../stdafx.h"
#include "CColorPalete.h"
#include "CPaintBuffer.h"
#include "CPaintTools.h"
#include "CShapesTool.h"
#include "CMenu.h"

//#include <CommCtrl.h>
#include "../DIALOG_NEW.h"


extern wchar_t EditorClassName[];
extern wchar_t PaintToolsClassName[];
extern wchar_t ColorPaletteClassName[];
extern wchar_t ShapesToolClassName[];
BOOL OpenSaveDialog(HWND, LPWSTR, WORD, BOOL);
class CEditor : public CWindowEvents{
    uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
    }
    int onSysColorChange() override;
    int onVScroll(WPARAM wParam) override;
    int onHScroll(WPARAM wParam) override;
    int onKeyDown(int key,int flags) override;
    int onCreate(CREATESTRUCT* cs) override;
    int onDestroy() override;
    int onClose() override;
    int onRightButtonDown(short x,short y,int keys) override;
    int onLeftButtonDown(short x,short y,int keys) override;
    int onMouseMove(short x,short y,int keys) override;
    int onLeftButtonUp(short x,short y,int keys) override;
    int onCommand(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
    int onPaint() override;
    int onMouseWheel(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

    void switchFullScreen()
    {
        if(fullScreen)
                    {
                        fullScreen=false;
                        SetWindowLong(hWindow,GWL_STYLE,WS_OVERLAPPEDWINDOW|WS_VSCROLL|WS_HSCROLL);
                        ShowWindow(hWindow,SW_SHOWMAXIMIZED);
                    }
                    else
                    {
                        fullScreen=true;
                        SetWindowLong(hWindow,GWL_STYLE,WS_POPUP);
                        SetMenu(hWindow,0);
                        menuIsVisible=false;
                        ShowWindow(hWindow,SW_SHOW);
                        //menu.set(hWindow);
                        SetWindowPos(hWindow,0,0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),SWP_NOZORDER | SWP_SHOWWINDOW);
                    }
    }
    HWND paintToolsWnd,colorPaletteWnd;
    HWND shapesToolWnd;
    HWND edit;
public:
    CEditor(HWND hwnd){
        hWindow=hwnd;
        menuIsVisible=true;
    }
    virtual ~CEditor(){

    }
    void drawPaintBuffer(CPaintBuffer*);///to wazne do zrobienia moze friend?
private:
    CPaintBuffer *paintBuff;
    //CPaintBuffer *alphaBuff;///(1.paintBuff->nextBuff 2.alphabuff by alphablend->nextBuff 3.nextbuff->hdc!

    HWND hWindow;
    CMenu menu;
    bool fullScreen;
    bool menuIsVisible;

    HDC hdc;

    PaintMode paintMode;
    FigureMode figureMode;
    Figures figure;
    LOGFONT lf;
    int cover;
    int penSize;
    bool selecting;///???
    bool transparent;
    ///bool selected;????
    POINT selectStart;///Real odnosi sie do okna glownego
    POINT selectEnd;
    POINT selectStartReal;
    POINT selectEndReal;

    RECT windowRect,clientRect;

    bool leftMouseButtonHold;
    POINT leftMouseButtonDownPos;
    vector <POINT> polyPoints;
    COLORREF currentColor;
    POINT prev,prevReal;
    bool lButtonHold;
    COLORREF color1,color2;
    wchar_t textBuffor[2048];///bufor textu do narysowania w paintbuforze
};

#endif // CEDITOR_H


