#ifndef CPAINTBUFFER_H
#define CPAINTBUFFER_H
#include "../stdafx.h"

using namespace std;
#include "CFigure.h"
class CEditor;

//#include "CEditor.h"
class CPaintBuffer{

    friend CEditor;
    //friend void CEditor::drawPaintBuffer(CPaintBuffer*);
public:
    CPaintBuffer(HWND,int,int);
    void drawFigure(CFigure *figure);///
    void resize(int,int);///
    void clean();///
    void scaleUp(){
        scaled=true;
        scaleX*=0.9;
        scaleY*=0.9;
        //char bufor[256];
        //sprintf(bufor,"scale x=%f scale y=%f",scaleX,scaleY);
        //SetWindowTextA(hwnd,bufor);
    }
    void scaleDown(){
        scaled=true;
        scaleX/=0.9;
        scaleY/=0.9;
        //char bufor[256];
        //sprintf(bufor,"scale x=%f scale y=%f",scaleX,scaleY);
        //SetWindowTextA(hwnd,bufor);
    }
    /*void selectArea(POINT start,POINT end){
        DeleteObject(SelectObject(hdc,CreatePen(PS_DOT,1,RGB(128,128,128))));
        DeleteObject(SelectObject(hdc, GetStockObject(HOLLOW_BRUSH)));
        Rectangle(hdc,start.x,start.y,end.x,end.y);
    }*/
    void restore();
    void saveToFile(wchar_t *_fileName);
    void loadFromFile(wchar_t *_fileName);
    void undo();
    int getWidth() {return width;}
    int getHeight() {return height;}
    void drawPaintBuffToRenderBuff()
    {

        if(isSketch)
        {
            BLENDFUNCTION bf;
            bf.AlphaFormat=0;
            bf.BlendFlags=0;
            bf.BlendOp=AC_SRC_OVER;
            bf.SourceConstantAlpha=111;
            StretchBlt(renderDC, 0, 0, width, height, memDC, 0, 0, width, height, SRCCOPY);
            AlphaBlend(renderDC,0,0,width,height,sketchDC,0,0,width,height,bf);

            //ERROR_TEST;
            /*for(int i=0;i<width;i++)
            for(int j=0;j<height;j++)
            {
                renderBytes[(i*height+j)*4+2]=(memBytes[(i*height+j)*4+2]+sketchBytes[(i*height+j)*4+2])/2;
                renderBytes[(i*height+j)*4+1]=(memBytes[(i*height+j)*4+1]+sketchBytes[(i*height+j)*4+1])/2;
                renderBytes[(i*height+j)*4]=(memBytes[(i*height+j)*4]+sketchBytes[(i*height+j)*4])/2;
            }*/
        }
        else
        {
            SetStretchBltMode(renderDC,COLORONCOLOR);
            StretchBlt(renderDC, 0, 0, width, height, memDC, 0, 0, width, height, SRCCOPY);
        }

    }
    void drawPolygonToRenderBuff(vector <POINT> polyPoints,int penSize,COLORREF color1,COLORREF color2,bool transparent)
    {
        CPolygon polygon(&*polyPoints.begin(),polyPoints.size(),penSize,color1,color2,transparent);
        polygon.drawToDC(renderDC);
    }
    void drawTextToBuff(RECT rect,wchar_t* text,LPLOGFONT lplogfont,COLORREF color,COLORREF color2,bool transparent)
    {
        CText2 text2(rect,text,lplogfont,color,color2,transparent);
        drawFigure(&text2);
        /*HFONT oldf=(HFONT)SelectObject(memDC,CreateFontIndirect( lplogfont ));
        SetBkMode(memDC, TRANSPARENT);
        DrawText(memDC,text,wcslen(text),&rect,DT_EDITCONTROL|DT_WORDBREAK);
        printf("juz narysowalem do DC!\n");
        DeleteObject(SelectObject(memDC,oldf));*/
    }
    void drawTextToRenderBuff(RECT rect,wchar_t* text,LPLOGFONT lplogfont,COLORREF color,COLORREF color2,bool transparent)
    {
        HFONT oldf=(HFONT)SelectObject(renderDC,CreateFontIndirect( lplogfont ));
        SetTextColor(renderDC,color);
        SetBkMode(renderDC, TRANSPARENT);
        SetBkColor(renderDC,color2);
        if(transparent) SetBkMode(renderDC,TRANSPARENT);
        else SetBkMode(renderDC,OPAQUE);
        DrawText(renderDC,text,wcslen(text),&rect,DT_EDITCONTROL|DT_WORDBREAK);
        printf("juz narysowalem do rDC!\n");
        DeleteObject(SelectObject(renderDC,oldf));
    }
    void drawSelectRectToRenderBuff(RECT rect)
    {

        HPEN old=(HPEN)SelectObject(renderDC,CreatePen(PS_DOT,1,RGB(128,128,128)));
        HBRUSH old2=(HBRUSH)SelectObject(renderDC, GetStockObject(HOLLOW_BRUSH));
        Rectangle(renderDC,rect.left,rect.top,rect.right,rect.bottom);
        DeleteObject(SelectObject(renderDC,old));
        DeleteObject(SelectObject(renderDC,old2));

    }
    void drawRenderBuffToDC(HDC hdc)
    {
        drawFullScreen();
    }
    HDC getMemDC(){return memDC;}///do wyrzucenia
    void drawFullScreen();///do wyrzucenia
    virtual ~CPaintBuffer();
    POINT getSize(){POINT pt;pt.x=width;pt.y=height;return pt;}///do wyrzucenia
    double getScaleX(){return scaleX;}///do wyrzucenia
    double getScaleY(){return scaleY;}///do wyrzucenia
    COLORREF getPixel(int x,int y){///??? niech sobie zostanie "próbnik koloru"

        return GetPixel(memDC,x,y);
    }
    void addSketch(wchar_t* _fileName);
    RECT getDrawRect(){///do wyrzucenia
        RECT rect;
         rect.left=x;
         rect.top=y;
         rect.right=drawRect.right/scaleX;
         rect.bottom=drawRect.bottom/scaleY;
         return rect;
        }
protected:
private:
    HDC memDC,restoreDC,renderDC;
    HDC sketchDC;
    wchar_t currSketchPath[1024];
    BYTE    *sketchBytes,*memBytes,*restoreBytes,*renderBytes;
    bool isSketch;
    RECT drawRect;///do wyrzucenia
    int width,height;
    double scaleX,scaleY;///do wyrzucenia
    bool scaled;///do wyrzucenia
    list<CFigure*> figures;

    HBITMAP oldBm;
    HBITMAP oldBm2;
    HPEN oldPen,oldPen2;
    HBRUSH oldBrush,oldBrush2;

    HBITMAP oldRenderBmp;
    HBITMAP oldSketchBmp;

    int x=0,y=0;///do wyrzucenia

    HDC hdc;///do wyrzucenia
    HWND hwnd;
};

#endif // CPAINTBUFFER_H


