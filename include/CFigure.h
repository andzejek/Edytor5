#ifndef CFIGURE_H
#define CFIGURE_H

#include "../stdafx.h"




class CFigure{
    public:
        virtual CFigure* clone();
        virtual void drawToDC(HDC hdc);
        //virtual CFigure(CFigure *_figure);
        virtual ~CFigure(){};

    protected:
    private:

};
class CFill:public CFigure{
    POINT start;
    COLORREF color;
public:
    CFill(POINT _start,COLORREF _color){
            color=_color;
            start=_start;
        }
    void drawToDC(HDC hdc)
    {
        DeleteObject(SelectObject(hdc,CreateSolidBrush(color)));
        ExtFloodFill(hdc,start.x,start.y,GetPixel(hdc,start.x,start.y),FLOODFILLSURFACE);
    }
    CFigure* clone()
    {
        CFigure *temp=new CFill(start,color);
        return temp;
    }
    ~CFill(){};
};
class CLine:public CFigure{
    POINT start,end;
    COLORREF color;
    int size;
    public:
        /*CLine(POINT _start,POINT _end){
            color=RGB(0,0,0);
            size=5;
            start=_start;
            end=_end;
        }*/
        CLine(POINT _start,POINT _end,int _size,COLORREF _color){
            color=_color;
            size=_size;
            start=_start;
            end=_end;
        }
    void drawToDC(HDC hdc){
        //printf("linia od %d %d do %d %d\n",start.x,start.y,end.x,end.y);
        //mif(GetDCBrushColor(hdc)!=color)
        DeleteObject(SelectObject(hdc,CreatePen(PS_SOLID,size,color)));
        MoveToEx(hdc,start.x,start.y,0);
        LineTo(hdc,end.x,end.y);
    }
    CFigure* clone()
    {
        CFigure *temp=new CLine(start,end,size,color);
        return temp;
    }
    ~CLine(){}
};
class CEllipse : public CFigure{
    POINT start,end;
    bool transparent;
    int size;
    COLORREF color,fillColor;
    public:
        CEllipse(POINT _start,POINT _end,int _size,COLORREF _color,COLORREF _fillColor,bool _transparent){
            color=_color;
            transparent=_transparent;
            fillColor=_fillColor;
            size=_size;
            start=_start;
            end=_end;
        }
    void drawToDC(HDC hdc){
        DeleteObject(SelectObject(hdc,CreatePen(PS_SOLID,size,color)));
        if(transparent)
        {

            DeleteObject(SelectObject(hdc, GetStockObject(HOLLOW_BRUSH)));
        }
        else
        {
            DeleteObject(SelectObject(hdc,CreateSolidBrush(fillColor)));
        }
        //
        Ellipse(hdc,start.x,start.y,end.x,end.y);
    }
    CFigure* clone()
    {
        CFigure *temp=new CEllipse(start,end,size,color,fillColor,transparent);
        return temp;
    }
    ~CEllipse(){}
};
class CRectangle : public CFigure{
    POINT start,end;
    bool transparent;
    int size;
    COLORREF color,fillColor;
    public:
        CRectangle(POINT _start,POINT _end,int _size,COLORREF _color,COLORREF _fillColor,bool _transparent){
            color=_color;
            transparent=_transparent;
            fillColor=_fillColor;
            size=_size;
            start=_start;
            end=_end;
        }
    void drawToDC(HDC hdc){
        DeleteObject(SelectObject(hdc,CreatePen(PS_SOLID,size,color)));
        if(transparent)
        {

            DeleteObject(SelectObject(hdc, GetStockObject(HOLLOW_BRUSH)));
        }
        else
        {
            DeleteObject(SelectObject(hdc,CreateSolidBrush(fillColor)));
            //FillRect()
        }
        //
        Rectangle(hdc,start.x,start.y,end.x,end.y);
    }
    CFigure* clone()
    {
        CFigure *temp=new CRectangle(start,end,size,color,fillColor,transparent);
        return temp;
    }
    ~CRectangle(){}
};
class CPixel : public CFigure{
    POINT start;
    COLORREF color;
public:
    CPixel(POINT _start,COLORREF _color)
    {
        color=_color;
        start=_start;
    }
    void drawToDC(HDC hdc)
    {
        SetPixel(hdc,start.x,start.y,color);
    }
    CFigure* clone()
    {
        return new CPixel(start,color);
    }
    ~CPixel(){}
};
class CClean:public CFigure{
    CClean(){};
    void drawToDC(HDC hdc,int width,int height)
    {
        RECT rect;rect.top=0;rect.left=0;rect.right=width;rect.bottom=height;
        HBRUSH brush=CreateSolidBrush(RGB(255,255,255));
        FillRect(hdc,&rect,brush);
        DeleteObject(brush);
    }
    CFigure* clone()
    {
        CFigure *temp=new CClean;
        return temp;
    }
    ~CClean(){};
};
class CRubber: public CFigure{
private:
    POINT start;
    int size;
    COLORREF color;
public:
    CRubber(POINT _start,int _size,COLORREF _color){
        start=_start;
        size=_size;//bo size 1 daje 0! ale fail przy redo sie pogrubiala linia xd ;P
        color=_color;
    };

    void drawToDC(HDC hdc)
    {
        RECT rect;rect.top=start.y-size/2;rect.left=start.x-size/2;rect.right=start.x+size/2;rect.bottom=start.y+size/2;
        HBRUSH brush=CreateSolidBrush(color);
        FillRect(hdc,&rect,brush);
        DeleteObject(brush);
    }
    CFigure* clone()
    {
        CFigure *temp=new CRubber(start,size,color);
        return temp;
    }
    ~CRubber(){};
};
class CSpray:public CFigure{
    COLORREF color;
    POINT start;
    int size;
    int seed;
public:
    CSpray(POINT _start,int _size,COLORREF _color,int _seed)
    {
        start=_start;
        size=_size;
        color=_color;
        seed=_seed;
        //seed=GetTickCount();
    }
    void drawToDC(HDC hdc)
    {
        srand(seed);
        for(int i=0;i<100;i++)
        {
        SetPixel(hdc,start.x-size/2+rand()%size,start.y-size/2+rand()%size,color);
        }
    }
    CFigure* clone()
    {
        CFigure *temp=new CSpray(start,size,color,seed);
        return temp;
    }
};
class CSprayFast:public CFigure{///unusable not draw to restoreDC
    COLORREF color;
    POINT start;
    int size;
    double cover;
    int seed;
    BYTE *bits;
    int width;
    int height;
public:
    CSprayFast(POINT _start,int _size,double _cover,COLORREF _color,int _seed,BYTE *_bits,int _width,int _height)
    {
        start=_start;
        size=_size;
        cover=_cover;
        color=_color;
        seed=_seed;
        bits=_bits;
        width=_width;
        height=_height;
        //seed=GetTickCount();
    }
    void drawToDC(HDC hdc)
    {
        srand(seed);
        cover/=100;
        for(int i=1;i<(size*size);i++)
        {
            if(rand()%(1+int(100/cover))==0)
            {
            int x=(start.x-size/2+rand()%size);
            int y=(start.y-size/2+rand()%size);
            if((x<width)&&(x>=0))
                if((y<height)&&(y>=0))
                {
                    *(bits+(y*width+x)*4)=GetBValue(color);
                    *(bits+(y*width+x)*4+1)=GetGValue(color);
                    *(bits+(y*width+x)*4+2)=GetRValue(color);
                }
            }
        //SetPixel(hdc,start.x-size/2+rand()%size,start.y-size/2+rand()%size,color);
        }
    }
    CFigure* clone()
    {
        CFigure *temp=new CSprayFast(start,size,cover,color,seed,bits,width,height);
        return temp;
    }
};
class CText:public CFigure{
    POINT start;
    wchar_t text[256];
public:
    CText(POINT _start,wchar_t *_text)
    {
        wsprintfW(text,L"%s",_text);
        start=_start;
        //seed=GetTickCount();
    }
    void drawToDC(HDC hdc)
    {
        TextOutW(hdc,start.x,start.y,text,wcslen(text));
    }
    CFigure* clone()
    {
        CFigure *temp=new CText(start,text);
        return temp;
    }
};
class CText2:public CFigure{
    RECT rect;
    wchar_t text[1024];
    LOGFONT logfont;
    COLORREF color,color2;
    bool transparent;
public:
    CText2(RECT _rect,wchar_t *_text,LPLOGFONT lpfont,COLORREF _color,COLORREF _color2,bool _transparent)
    {
        transparent=_transparent;
        rect=_rect;
        wsprintfW(text,L"%ls",_text);
        CopyMemory(&logfont,lpfont,sizeof(LOGFONT));
        color=_color;
        color2=_color2;
    }
    void drawToDC(HDC hdc)
    {

        HFONT newFont=CreateFontIndirect(&logfont);
        HFONT oldFont=(HFONT)SelectObject(hdc,newFont);
        SetTextColor(hdc,color);
        SetBkColor(hdc,color2);
        if(transparent) SetBkMode(hdc, TRANSPARENT);
        else SetBkMode(hdc, OPAQUE);

        DrawTextW(hdc,text,wcslen(text),&rect,DT_EDITCONTROL|DT_WORDBREAK);
        DeleteObject(SelectObject(hdc,oldFont));
    }
    CFigure* clone()
    {
        CFigure *temp=new CText2(rect,text,&logfont,color,color2,transparent);
        return temp;
    }
};
class CNegColor:public CFigure{
    POINT start,end;
public:
    CNegColor(POINT _start,POINT _end)
    {
        start=_start;
        end=_end;
    }
    void drawToDC(HDC hdc)
    {
        COLORREF color;
        for(int i=start.x;i<end.x;i++)
           for(int j=start.y;j<end.y;j++)
           {
               color=GetPixel(hdc,i,j);
               SetPixel(hdc,i,j,RGB( 255-GetRValue(color), 255-GetGValue(color), 255-GetBValue(color) ));
           }
    }
    CFigure* clone()
    {
        CFigure *temp=new CNegColor(start,end);
        return temp;
    }
};
class CPasteBMP : public CFigure{
    POINT start,end;
    BYTE *data;
    int width,height;
    HBITMAP bitmap;
private:
    CPasteBMP(POINT _start,POINT _end,BYTE *_data,int _width,int _height)
    {
        start=_start;
        end=_end;
        width=_width;
        height=_height;
        data=new BYTE[width*height*4];
        CopyMemory(data,_data,sizeof(BYTE)*width*height*4);
    }
    public:
    CPasteBMP(POINT _start,POINT _end,HDC src,int _width,int _height)
    {

        start=_start;
        end=_end;
        width=_width;
        height=_height;

        COLORREF color;
        data=new BYTE[width*height*4];
        for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            color=GetPixel(src,j,i);
            data[(i*width+j)*4+2]=GetRValue(color);
            data[(i*width+j)*4+1]=GetGValue(color);
            data[(i*width+j)*4]=GetBValue(color);
            data[(i*width+j)*4+3]=0;
        }
    }
    void drawToDC(HDC hdc)
    {
            BYTE *data2;
            printf("width=%d height=%d",width,height);
            HDC hDC = GetDC(NULL);
            HDC hdc2= CreateCompatibleDC(hdc);

            BITMAPINFO bmi;
            memset(&bmi, 0, sizeof(BITMAPINFO));
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = width;
            bmi.bmiHeader.biHeight = -height;
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = 32;
            bmi.bmiHeader.biCompression = BI_RGB;
            bitmap= CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, (void**)&data2, NULL, 0);

            CopyMemory(data2,data,sizeof(BYTE)*width*height*4);
            if(bitmap==0) MessageBox(0,0,0,0);
            HBITMAP old=(HBITMAP) SelectObject(hdc2,bitmap);
            StretchBlt(hdc,start.x,start.y,width,height,hdc2,0,0,width,height,SRCCOPY);

            SelectObject(hdc2,old);

            DeleteObject(bitmap);
            DeleteDC(hdc2);
            ReleaseDC(NULL, hDC);


        /*for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            SetPixel(hdc,start.x+j,start.y+i,RGB( data[(i*width+j)*4],data[(i*width+j)*4+1] ,data[(i*width+j)*4+2] ));
        }*/
    }
    ~CPasteBMP()
    {
        delete[]data;
        DeleteObject(bitmap);
    }
    CFigure* clone()
    {
        CFigure *temp=new CPasteBMP(start,end,data,width,height);
        return temp;
    }
};

class CPolygon :public CFigure{
    bool transparent;
    int size;
    COLORREF color,fillColor;
    POINT *points;
    int pCount;
    public:
        CPolygon(POINT *_points,int _pCount,int _size,COLORREF _color,COLORREF _fillColor,bool _transparent){
            color=_color;
            transparent=_transparent;
            fillColor=_fillColor;
            size=_size;
            pCount=_pCount;
            points=new POINT[pCount];
            CopyMemory(points,_points,pCount*sizeof(POINT));
        }
    void drawToDC(HDC hdc){
        DeleteObject(SelectObject(hdc,CreatePen(PS_SOLID,size,color)));
        if(transparent)
        {

            DeleteObject(SelectObject(hdc, GetStockObject(HOLLOW_BRUSH)));
        }
        else
        {
            DeleteObject(SelectObject(hdc,CreateSolidBrush(fillColor)));
            //FillRect()
        }
        //
        Polygon(hdc,points,pCount);
    }
    CFigure* clone()
    {
        CFigure *temp=new CPolygon(points,pCount,size,color,fillColor,transparent);
        return temp;
    }
    ~CPolygon(){
    delete []points;
    }
};
#endif // CFIGURE_H

