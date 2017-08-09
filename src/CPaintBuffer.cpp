#include "CPaintBuffer.h"
///#include "Vfw.h"
CPaintBuffer::CPaintBuffer(HWND _hwnd,int _width,int _height){
    isSketch=false;
    scaleX=1;
    scaleY=1;
    hwnd=_hwnd;///zamiast hwnd moze samo hdc?
    width=_width;
    height=_height;

    hdc=GetDC(hwnd);

    memDC=CreateCompatibleDC(hdc);
    oldMemBmp=(HBITMAP)SelectObject(memDC,create32DIB(memDC,_width,_height,&memBytes));
    renderDC=CreateCompatibleDC(hdc);
    oldRenderBmp=(HBITMAP)SelectObject(renderDC,create32DIB(renderDC,_width,_height,&renderBytes));
    sketchDC=CreateCompatibleDC(hdc);
    oldSketchBmp=(HBITMAP)SelectObject(sketchDC,create32DIB(sketchDC,_width,_height,&sketchBytes));
    restoreDC=CreateCompatibleDC(hdc);
    oldRestoreBmp=(HBITMAP)SelectObject(restoreDC,create32DIB(restoreDC,_width,_height,&restoreBytes));

    HPEN newRestorePen=CreatePen(PS_SOLID,1,RGB(0,255,255));
    oldRestorePen=(HPEN)SelectObject(restoreDC,newRestorePen);
    HBRUSH newRestoreBrush=CreateSolidBrush(RGB(255,255,0));
    oldRestoreBrush=(HBRUSH) SelectObject(restoreDC,newRestoreBrush);


    HPEN newMemPen=CreatePen(PS_SOLID,1,RGB(0,255,255));
    oldMemPen=(HPEN)SelectObject(memDC,newMemPen);
    HBRUSH newMemBrush=CreateSolidBrush(RGB(255,255,0));
    oldMemBrush=(HBRUSH) SelectObject(memDC,newMemBrush);


    drawRect.left=0;
    drawRect.right=width;
    drawRect.top=0;
    drawRect.bottom=height;
    printf("width=%d",width);
    clean();
    BitBlt(restoreDC, 0, 0, width,height, memDC, 0, 0, SRCCOPY );
    scaled=true;
}
CPaintBuffer::~CPaintBuffer(){
    list<CFigure*>::iterator it;
    it = figures.begin();
    while(it != figures.end())
    {
        delete (*it);
        ++it;
    }

    DeleteObject(SelectObject(renderDC,oldRenderBmp));
    DeleteObject(SelectObject(sketchDC,oldSketchBmp));
    DeleteDC(renderDC);
    DeleteDC(sketchDC);

    DeleteObject(SelectObject(memDC,oldMemBmp));
    DeleteObject(SelectObject(memDC,oldMemPen));
    DeleteObject(SelectObject(memDC,oldMemBrush));
    DeleteDC(memDC);


    DeleteObject(SelectObject(restoreDC,oldRestoreBmp));
    DeleteObject(SelectObject(restoreDC,oldRestorePen));
    DeleteObject(SelectObject(restoreDC,oldRestoreBrush));
    DeleteDC(restoreDC);

    ReleaseDC(hwnd,hdc);
}
void CPaintBuffer::resize(int _width,int _height){
    width=_width;
    height=_height;

    DeleteObject(SelectObject(memDC,create32DIB(memDC,_width,_height,&memBytes)));
    DeleteObject(SelectObject(renderDC,create32DIB(renderDC,_width,_height,&renderBytes)));
    DeleteObject(SelectObject(sketchDC,create32DIB(sketchDC,_width,_height,&sketchBytes)));
    DeleteObject(SelectObject(restoreDC,create32DIB(restoreDC,_width,_height,&restoreBytes)));

    RECT rect;rect.top=0;rect.left=0;rect.right=width;rect.bottom=height;
    HBRUSH brush=CreateSolidBrush(RGB(255,255,255));
    FillRect(memDC,&rect,brush);
    FillRect(restoreDC,&rect,brush);
    DeleteObject(brush);


    drawRect.left=0;
    drawRect.right=width;
    drawRect.top=0;
    drawRect.bottom=height;

    if(isSketch) addSketch(currSketchPath);
}
void CPaintBuffer::clean(){
    RECT rect;rect.top=0;rect.left=0;rect.right=width;rect.bottom=height;
    HBRUSH brush=CreateSolidBrush(RGB(255,255,255));
    FillRect(memDC,&rect,brush);
    //FillRect(restoreDC,&rect,brush);
    DeleteObject(brush);
}
void CPaintBuffer::drawFullScreen(){

    RECT wrect;
    GetClientRect(hwnd,&wrect);
    static unsigned int time;
    if(time+100<GetTickCount())
    {
        time=GetTickCount();
    if(GetAsyncKeyState(VK_LEFT)) { x-=drawRect.right/10.0f;scaled=true;}
    if(GetAsyncKeyState(VK_RIGHT)) {x+=drawRect.right/10.0f;scaled=true;}
    if(GetAsyncKeyState(VK_UP)) {  y-=drawRect.bottom/10.0f;scaled=true;}
    if(GetAsyncKeyState(VK_DOWN)) {y+=drawRect.bottom/10.0f;scaled=true;}

    }
    if(scaled)
    {
    scaled=false;
    HBRUSH brush=CreateSolidBrush(RGB(128,128,128));
    FillRect(hdc,&wrect,brush);
    DeleteObject(brush);
    }
    if(x>(wrect.right-100)) x-=100;
    if(y>wrect.bottom-100) y-=100;
    if(x+drawRect.right/scaleX<+100) x+=100;
    if(y+drawRect.bottom/scaleY<+100) y+=100;

    SetStretchBltMode(hdc,COLORONCOLOR);
    StretchBlt(hdc, x, y, drawRect.right/scaleX, drawRect.bottom/scaleY, renderDC, drawRect.left, drawRect.top, drawRect.right, drawRect.bottom, SRCCOPY);
}
void CPaintBuffer::drawFigure(CFigure *figure){
    if(figures.size()>5000)
    {
        for(int i=0;i<100;i++)
        {

            (*figures.begin())->drawToDC(restoreDC);
            delete (*figures.begin());
            figures.pop_front();
        }
    }
    if(figures.size()%1000==0)printf("figures.size()=%d\n",figures.size());
    figure->drawToDC(memDC);
    figures.push_back(figure->clone());
}
void CPaintBuffer::restore(){

    clean();
    BitBlt(memDC, 0, 0, width,height, restoreDC, 0, 0, SRCCOPY );
    list<CFigure*>::iterator it;
    it = figures.begin();
    while(it != figures.end())
    {
        (*it)->drawToDC(memDC);
        ++it;
    }
}
void CPaintBuffer::undo(){

        for(int i=0;i<20&&figures.size();i++){
                delete ((figures.back()));
                figures.pop_back();}
        ///printf("figures.size()=%d\n",figures.size());
        restore();
    }
#define errhandler(A,B) printf(A)
void CPaintBuffer::saveToFile(wchar_t *_fileName){

        BYTE *bytes;
        HBITMAP temp=create32DIB(memDC,width,height,&bytes);
        CopyMemory(bytes,memBytes,width*height*4);
        saveImage(_fileName,temp);
        DeleteObject(temp);
}
void CPaintBuffer::loadFromFile(wchar_t *_fileName){
    HBITMAP image=loadImage(_fileName);
    HDC hdcTemp=CreateCompatibleDC(hdc);
    HBITMAP old=(HBITMAP) SelectObject(hdcTemp,image);
    BITMAP bmInfo;
    GetObject( image, sizeof( bmInfo ), & bmInfo );
    resize(bmInfo.bmWidth,bmInfo.bmHeight);
    BitBlt(memDC, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, hdcTemp, 0, 0, SRCCOPY );
    BitBlt(restoreDC, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, hdcTemp, 0, 0, SRCCOPY );
    SelectObject(hdcTemp,old);
    DeleteObject(image);
    DeleteDC(hdcTemp);
    scaled=true;
}
void CPaintBuffer::addSketch(wchar_t *_fileName){
    HBITMAP image =loadImage(_fileName);
    HDC hdcTemp=CreateCompatibleDC(hdc);
    HBITMAP old=(HBITMAP) SelectObject(hdcTemp,image);
    BITMAP bmInfo;
    GetObject( image, sizeof( bmInfo ), & bmInfo );
    SetStretchBltMode(sketchDC,HALFTONE);
    StretchBlt(sketchDC, 0, 0, width,height,hdcTemp,0,0,bmInfo.bmWidth, bmInfo.bmHeight, SRCCOPY );
    isSketch=true;

    SelectObject(hdcTemp,old);
    DeleteObject(image);
    DeleteDC(hdcTemp);
    wsprintf(currSketchPath,L"%ls",_fileName);
    ///isSketchLoaded=true;
    scaled=true;
}
