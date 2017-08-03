#ifndef CSHAPESTOOL_H
#define CSHAPESTOOL_H
#include "CWindowEvents.h"
#include "../DIALOG_NEW.h"
class CShapesTool:public CWindowEvents{
    public:
    CShapesTool(HWND hwnd)
    {
            hWindow=hwnd;

    }
    int onCreate(CREATESTRUCT* cs)override
    {
            hbmIconSquare=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconFigureRectangle ) );
            hbmIconCircle=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconFigureEllipse ) );

            bSquare=CreateWindowEx( 0, L"BUTTON", L"selectarea", WS_CHILD | WS_VISIBLE|BS_BITMAP,0, 0, 32, 32, hWindow,0, 0, NULL );
            SendMessage(bSquare, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconSquare);


            bCircle=CreateWindowEx( 0, L"BUTTON", L"selectarea", WS_CHILD | WS_VISIBLE|BS_BITMAP,32, 0, 32, 32, hWindow,0, 0, NULL );
            SendMessage(bCircle, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconCircle);
            return 0;
    };
    HWND hWindow;
    HBITMAP hbmIconCircle,hbmIconSquare;
    HWND bCircle,bSquare;
    int onDestroy()override
    {return 0;};
    virtual ~CShapesTool(){}

};

#endif // CSHAPESTOOL_H
