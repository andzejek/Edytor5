#ifndef CCOLORPALETE_H
#define CCOLORPALETE_H
#include "../stdafx.h"
#include "CWindowEvents.h"

#define CMD_SET_COLOR_1 1007
#define CMD_SET_COLOR_2 1008
class CColorPalette : public CWindowEvents{
public:
    CColorPalette(HWND hwnd)
    {
        printf("CColorPalette: constructor!\n");
        hWindow=hwnd;
        hParentWindow=GetWindow(hWindow,GW_OWNER);
        if(hParentWindow==0) DestroyWindow(hWindow);

    }
    int onEraseBKGND()override;
    int onCreate(CREATESTRUCT* cs) override;
    int onDestroy() override;
    //void onKeyDown(int,int) override;
    int onPaint() override;
    int onMouseMove(short x,short y,int keys) override;
    int onLeftButtonUp(short x,short y,int keys) override;
    int onRightButtonDown(short x,short y,int keys) override;
    int onSize() override;
    int onClose() override;
    int onLeftButtonDown(short x,short y,int keys) override;
    int onHScroll(WPARAM wParam) override;
    virtual ~CColorPalette()
    {
        printf("CColorPalette: deconstructor!\n");
    }
private:
    bool isFromFile;
    BYTE *pRgb;
    bool posible;
    HWND hWindow;
    HWND hParentWindow;
    HBITMAP hbmColorPalette,hbmOld;
    HDC hdc,memdc;
    RECT clientRect;
    POINT lastSelectedColor;
};

#endif // CCOLORPALETE_H

