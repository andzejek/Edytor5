#ifndef CWINDOWEVENTS_H
#define CWINDOWEVENTS_H
#include "../stdafx.h"
///satyczna tablica w ktorej bedziemy zliczac
struct Event{///still useless
    HWND hwnd;
    UINT msg;
    WPARAM wParam;
    LPARAM lParam;
    Event(HWND _hwnd,UINT _msg,WPARAM _wParam,LPARAM _lParam)
    {
        hwnd=_hwnd;
        msg=_msg;
        wParam=_wParam;
        lParam=_lParam;
    }
};
class CWindowEvents{
public:
    virtual int onSysColorChange()                                              {return 0x5AEBE140;}
    virtual int onEraseBKGND()                                                  {return 0x5AEBE140;}
    virtual int onVScroll(WPARAM wParam)                                        {return 0x5AEBE140;}
    virtual int onHScroll(WPARAM wParam)                                        {return 0x5AEBE140;}
    virtual int onCreate(CREATESTRUCT* createStruct)=0;
    virtual int onDestroy()=0;
    virtual int onKeyDown(int key,int flag)                                     {return 0x5AEBE140;}
    virtual int onMouseMove(short x,short y,int keys)                           {return 0x5AEBE140;}
    virtual int onPaint()                                                       {return 0x5AEBE140;}
    virtual int onLeftButtonDown(short x,short y,int keys)                      {return 0x5AEBE140;}
    virtual int onRightButtonDown(short x,short y,int keys)                     {return 0x5AEBE140;}
    virtual int onLeftButtonUp(short x,short y,int keys)                        {return 0x5AEBE140;}
    virtual int onRightButtonUp(short x,short y,int keys)                       {return 0x5AEBE140;}
    virtual int onCommand(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){return 0x5AEBE140;}
    virtual int onClose()                                                       {return 0x5AEBE140;}
    virtual int onMouseWheel(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){return 0x5AEBE140;}
    virtual int onSize()                                                        {return 0x5AEBE140;}
    virtual int onWindowPosChange()                                             {return 0x5AEBE140;}
    int event(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        //Event event(hwnd,message,wParam,lParam);
        int ret=0;
        switch (message)
        {
        case WM_WINDOWPOSCHANGING:ret=onWindowPosChange();                                      break;
        case WM_SYSCOLORCHANGE: ret=onSysColorChange();                                         break;
        case WM_ERASEBKGND:     ret=onEraseBKGND();                                             break;
        case WM_HSCROLL:        ret=onHScroll(wParam);                                          break;
        case WM_VSCROLL:        ret=onVScroll(wParam);                                          break;
        case WM_CLOSE:          ret=onClose();                                                  break;
        case WM_SIZE:           ret=onSize();                                                   break;
        case WM_CREATE:         ret=onCreate((CREATESTRUCT*) lParam);                           break;
        case WM_DESTROY:        ret=onDestroy();                                                break;
        case WM_KEYDOWN:        ret=onKeyDown(wParam,lParam);                                   break;
        case WM_PAINT:          ret=onPaint();                                                  break;
        case WM_LBUTTONDOWN:    ret=onLeftButtonDown(LOWORD(lParam),HIWORD(lParam),wParam);     break;
        case WM_LBUTTONUP:      ret=onLeftButtonUp(LOWORD(lParam),HIWORD(lParam),wParam);       break;
        case WM_RBUTTONDOWN:    ret=onRightButtonDown(LOWORD(lParam),HIWORD(lParam),wParam);    break;
        case WM_RBUTTONUP:      ret=onRightButtonUp(LOWORD(lParam),HIWORD(lParam),wParam);      break;
        case WM_MOUSEMOVE:      ret=onMouseMove(LOWORD(lParam),HIWORD(lParam),wParam);          break;
        case WM_MOUSEWHEEL:     ret=onMouseWheel(hwnd,message,wParam,lParam);                   break;
        case WM_COMMAND:        ret=onCommand(hwnd,message,wParam,lParam);                      break;
        default:               return DefWindowProc (hwnd, message, wParam, lParam);
        }
        if(ret==0x5AEBE140) return DefWindowProc (hwnd, message, wParam, lParam);
     return 0;
    }

};

#endif // CWINDOWEVENTS_H

