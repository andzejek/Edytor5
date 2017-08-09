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
///pamietaj ze menu kiedy nie jest powiązane z oknem nie ulega usunięciu?(co zrobić z tym fantem?)

extern wchar_t EditorClassName[];
extern wchar_t PaintToolsClassName[];
extern wchar_t ColorPaletteClassName[];
extern wchar_t ShapesToolClassName[];
BOOL OpenSaveImageDialog(HWND, LPWSTR, WORD, BOOL);
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

    void switchFullScreen();
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
    ///CPaintBuffer *layers[10];
    ///int currentLayer=0;
    //CPaintBuffer *alphaBuff;///(1.paintBuff->nextBuff 2.alphabuff by alphablend->nextBuff 3.nextbuff->hdc!

    HWND hWindow;
    CMenu menu;
    bool fullScreen;
    bool menuIsVisible;

    HDC hdc;
    struct paintSettings{///kazdy paintbuffer powinien miec swoje ustawienia rysowania! a edytor powienien miec
                        ///tylko domyslne dla nowego? czy kazdy w zaleznosci od trybu musi miec wlasne ustawienia?
    COLORREF color1;
    COLORREF color2;
    PaintMode paintMode;
    FigureMode figureMode;
    Figures figure;///selected shape
    LOGFONT lf;///?? musze tutaj dopisać chyba wielkosc czcionki (kolor juz sie zmienia z palety)
    __int16 brush[2];///orientacja pedzla
    int cover;///to mialo być pokrycie np flamastra lub spreya
    int penSize;///
    bool selecting;///???
    bool transparent;
    POINT selectStart;///ale lepszy bedzie jako RECT? po co 2 zmienne?
    POINT selectEnd;
    vector <POINT> polyPoints;///chyba? chodzi o wielokąt
    };
    PaintMode paintMode;
    FigureMode figureMode;
    Figures figure;
    LOGFONT lf;
    __int16 brush[2];
    int cover;
    int penSize;
    bool selecting;///???
    bool transparent;
    ///bool selected;????
    POINT selectStart;///Real odnosi sie do okna glownego
    POINT selectEnd;
    POINT selectStartReal;//moze sie jeszcze przyda? select i tak powinien być na hdc edytora i nic z tego ze migocze (ms paint tez tak ma).
    POINT selectEndReal;
    bool changeLeftSelectRectBorder;
    bool changeRightSelectRectBorder;
    bool changeTopSelectRectBorder;
    bool changeBottomSelectRectBorder;
    bool changeSelectRectPos;
    RECT windowRect,clientRect;

    bool leftMouseButtonHold;
    POINT leftMouseButtonDownPos;
    vector <POINT> polyPoints;
    COLORREF currentColor;///nie wiem co to
    POINT prev,prevReal;///poprzednie polozenie kursora.
    bool lButtonHold;
    COLORREF color1,color2;
    wchar_t textBuffor[2048];///bufor textu do narysowania w paintbuforze a to nie wiem czy a byc w paint settings
};

#endif // CEDITOR_H


