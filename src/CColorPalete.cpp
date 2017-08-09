#include "CColorPalete.h"
#include "../HSLvsRGB.h"
int CColorPalette::onCreate(CREATESTRUCT *cs){

    hdc=GetDC(hWindow);
    SetScrollPos(hWindow,SB_HORZ,100,true);
    memdc=CreateCompatibleDC(hdc);
    if(cs->lpCreateParams!=0)
    {
        hbmColorPalette=(HBITMAP) loadImage((wchar_t*)cs->lpCreateParams);
        if(hbmColorPalette)
        {
            hbmOld=(HBITMAP)SelectObject(memdc,hbmColorPalette);
            BITMAP iBmp;
            GetObject(hbmColorPalette,sizeof(BITMAP),&iBmp);
            MoveWindow(hWindow,0,0,iBmp.bmWidth,iBmp.bmHeight,0);
            isFromFile=true;
        }
        else DestroyWindow(hWindow);
    }
    else
    {
        isFromFile=false;
        hbmColorPalette=create32DIB(hdc,256,300,&pRgb);
        hbmOld=(HBITMAP)SelectObject(memdc,hbmColorPalette);
        for(int ix=0;ix<256;ix++)
        for(int iy=0;iy<22;iy++)SetPixel(memdc,ix,iy,RGB(255,255,255));
        for(int ix=0;ix<256;ix++)
        for(int iy=278;iy<300;iy++)SetPixel(memdc,ix,iy,RGB(0,0,0));
        for(int ix=0;ix<256;ix++)
        for(int iy=22;iy<278;iy++)
        {
            SetPixel(memdc,ix,iy,HSLtoRGB(ix/256.0f*360.0f,1,(256-iy+22)/256.0f));
        }
    }
    return 0;
}
int CColorPalette::onMouseMove(short x,short y,int keys){
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hParentWindow,&pt);
    SendMessage(hParentWindow,WM_MOUSEMOVE,keys,MAKELPARAM(pt.x,pt.y));
    return 0;
}
int CColorPalette::onSize(){
    InvalidateRect(hWindow,0,1);
    return 0;
}
int CColorPalette::onClose(){
    if(isFromFile) DestroyWindow(hWindow);
    else ShowWindow(hWindow,SW_HIDE);
    return 0;
}
int CColorPalette::onDestroy(){
    SelectObject(memdc,hbmOld);
    DeleteObject(hbmColorPalette);
    DeleteDC(memdc);
    ReleaseDC(hWindow,hdc);
    return 0;
}
int CColorPalette::onPaint(){
    PAINTSTRUCT ps;
    BeginPaint(hWindow,&ps);
    BITMAP bmInfo;
    GetClientRect(hWindow,&clientRect);
    GetObject(hbmColorPalette, sizeof( bmInfo ), & bmInfo );
    SetStretchBltMode(hdc,HALFTONE);
    StretchBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, memdc, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, SRCCOPY);

    if(posible)
    {
        COLORREF color=GetPixel(hdc,lastSelectedColor.x,lastSelectedColor.y);
    SetPixel(hdc,lastSelectedColor.x,lastSelectedColor.y,RGB(255-GetRValue(color),255-GetGValue(color),255-GetBValue(color)));
    for(int i=lastSelectedColor.x-5;i<=lastSelectedColor.x+5;i++)
    {
        color=GetPixel(hdc,i,lastSelectedColor.y);
        SetPixel(hdc,i,lastSelectedColor.y,RGB(255-GetRValue(color),255-GetGValue(color),255-GetBValue(color)));
    }
    for(int i=lastSelectedColor.y-5;i<=lastSelectedColor.y+5;i++)
    {
        color=GetPixel(hdc,lastSelectedColor.x,i);
        SetPixel(hdc,lastSelectedColor.x,i,RGB(255-GetRValue(color),255-GetGValue(color),255-GetBValue(color)));
    }
    }
    EndPaint(hWindow,&ps);
    return 0;
}
int CColorPalette::onLeftButtonDown(short x,short y,int keys){
    lButtonDown=true;
    posible=false;
    InvalidateRect(hWindow,0,0);
    SendMessage(hWindow,WM_PAINT,0,0);
    SendMessage(hParentWindow,WM_COMMAND,CMD_SET_COLOR_1,GetPixel(hdc,x,y));
    lastSelectedColor.x=x;lastSelectedColor.y=y;
    return 0;
}
int CColorPalette::onRightButtonDown(short x,short y,int keys){

    SendMessage(hParentWindow,WM_COMMAND,CMD_SET_COLOR_2,GetPixel(hdc,x,y));
    lastSelectedColor.x=x;lastSelectedColor.y=y;
    InvalidateRect(hWindow,0,0);
    SetActiveWindow(hParentWindow);
    return 0;
}
int CColorPalette::onLeftButtonUp(short x,short y,int keys){

    posible=true;
    InvalidateRect(hWindow,0,0);
    SendMessage(hWindow,WM_PAINT,0,0);
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hParentWindow,&pt);
    if(!lButtonDown)SendMessage(hParentWindow,WM_LBUTTONUP,keys,MAKELPARAM(pt.x,pt.y));
    lButtonDown=false;
    SetActiveWindow(hParentWindow);
    return 0;
}
int CColorPalette::onHScroll(WPARAM wParam){
    SCROLLINFO si;
    ZeroMemory( & si, sizeof( si ) );
    si.cbSize = sizeof( SCROLLINFO );
    si.fMask = SIF_POS | SIF_PAGE | SIF_TRACKPOS;
    GetScrollInfo( hWindow, SB_HORZ, & si );

    int pozycja = si.nPos;

    switch( LOWORD( wParam ) ) {
    case SB_TOP:
        pozycja = 0;
        break;
    case SB_BOTTOM:
        pozycja = 100;
        break;
    case SB_LINEUP:
        if( pozycja > 0 ) {
            pozycja--;
        }
        break;
    case SB_LINEDOWN:
        if( pozycja < 100 ) {
            pozycja++;
        }
        break;
    case SB_PAGEUP:
        pozycja -= si.nPage;
        if( pozycja < 0 ) {
            pozycja = 0;
        }
        break;
    case SB_PAGEDOWN:
        pozycja += si.nPage;
        if( pozycja > 100 ) {
            pozycja = 100;
        }
        break;
    case SB_THUMBPOSITION:
        pozycja = si.nTrackPos;
        break;
    case SB_THUMBTRACK:
        pozycja = si.nTrackPos;
        break;
    }



    ZeroMemory( & si, sizeof( si ) );
    si.cbSize = sizeof( SCROLLINFO );
    si.fMask = SIF_POS| SIF_PAGE|SIF_RANGE;
    si.nPos = pozycja;
    si.nPage=1;
    si.nMin=0;
    si.nMax=100;
    SetScrollInfo( hWindow, SB_HORZ, & si, TRUE );
    if(pRgb!=0)
    for(int iy=22;iy<278;iy++)
    for(int ix=0;ix<256;ix++)
    {
        *(int*)(pRgb+(256*iy+ix)*4)=HSLtoBGR(ix/256.0f*360.0f,si.nPos/100.0f,(256-iy+22)/256.0f);
        //SetPixel(memdc,ix,iy,HSLtoRGB(ix/256.0f*360.0f,si.nPos/100.0f,(256-iy+22)/256.0f));
    }
    InvalidateRect(hWindow,0,1);
    UpdateWindow( hWindow );
    SendMessage(hWindow,WM_LBUTTONDOWN,0,MAKELPARAM(lastSelectedColor.x,lastSelectedColor.y));
    SendMessage(hWindow,WM_LBUTTONUP,0,MAKELPARAM(lastSelectedColor.x,lastSelectedColor.y));
    return 0;
}
int CColorPalette::onEraseBKGND(){
    return 0;
}
