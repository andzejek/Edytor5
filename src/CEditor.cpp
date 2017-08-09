#include "CEditor.h"

int CEditor::onCreate(CREATESTRUCT *cs){
            SendMessage(hWindow,WM_SYSCOLORCHANGE,0,0);

            paintToolsWnd=CreateWindowEx(WS_EX_TOOLWINDOW,PaintToolsClassName,L"Paint Tools",WS_OVERLAPPEDWINDOW^(WS_THICKFRAME|WS_MAXIMIZEBOX) ,0,0,80,454,hWindow,0,0,0);
            ShowWindow(paintToolsWnd,SW_SHOW);
            colorPaletteWnd=CreateWindowEx(WS_EX_TOOLWINDOW,ColorPaletteClassName,L"Color Palette",WS_OVERLAPPEDWINDOW|WS_HSCROLL ,400,400,300,300,hWindow,0,0,0);
            ShowWindow(colorPaletteWnd,SW_SHOW);
            edit = CreateWindowEx( 0, L"EDIT", L"", WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE, 0,0, 100,100, hWindow, 0,0, NULL );
            //shapesToolWnd=CreateWindowEx(WS_EX_TOOLWINDOW,ShapesToolClassName,L"Shapes<-TEST",WS_OVERLAPPEDWINDOW ,700,400,300,200,hWindow,0,0,0);
            //ShowWindow(shapesToolWnd,SW_SHOW);

            hdc=GetDC(hWindow);

            CMenu menu;
            menu.set(hWindow);

            paintBuff=new CPaintBuffer(hWindow,800,600);
            ///for(int i=0;i<10;i++) layers[i]=new CPaintBuffer(hWindow,800+rand()%500,600+rand()%500);
            ///paintBuff=layers[0];
            ///for(int i=0;i<10000;i++)
            ///paintBuff->resize(500+rand()%500,500+rand()%500); //TEST
            paintMode=MODE_PENCIL;
            penSize=10;
            color1=0;
            color2=RGB(255,255,255);
            cover=5;

            SendMessage(paintToolsWnd,WM_COMMAND,CMD_SET_COLOR_1,color1);
            SendMessage(paintToolsWnd,WM_COMMAND,CMD_SET_COLOR_2,color2);
            SendMessage(paintToolsWnd,WM_COMMAND,CMD_SET_PEN_SIZE,penSize);
            SendMessage(paintToolsWnd,WM_COMMAND,CMD_SET_COVER,cover);

            if(GetDeviceCaps(hdc,BITSPIXEL)!=32) onDestroy();///???
            return 0;
}
int CEditor::onPaint(){
            PAINTSTRUCT PS;
            HDC unusablePaintDC=BeginPaint(hWindow,&PS);
            unusablePaintDC=unusablePaintDC;
            SetStretchBltMode(hdc,COLORONCOLOR);

            drawPaintBuffer(paintBuff);

            EndPaint(hWindow,&PS);
            return 0;
}
int CEditor::onLeftButtonDown(short x,short y,int keys){
    POINT paintBuffSize=paintBuff->getSize();
                RECT drawRect=paintBuff->getDrawRect();
                x=(x-drawRect.left)*paintBuffSize.x/drawRect.right;
                y=(y-drawRect.top)*paintBuffSize.y/drawRect.bottom;
                /**POINT temp={x,y};
                POINT curr=paintBuff->resolveCoordToMe(temp);
                x=curr.x;
                                y=curr.y;*/
                leftMouseButtonDownPos.x=x;
                leftMouseButtonDownPos.y=y;
                lf.lfHeight=-MulDiv(penSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
                if(selecting)
                {
                    if(x>selectStart.x&&x<selectEnd.x)
                    if(y>selectStart.y&&y<selectEnd.y)
                    {
                        int selectWidth=selectEnd.x-selectStart.x;
                        int selectHeight=selectEnd.y-selectStart.y;
                        if(((float)x-selectStart.x)/selectWidth<0.1f)changeLeftSelectRectBorder=true;
                        else if(((float)x-selectStart.x)/selectWidth>0.9f)changeRightSelectRectBorder=true;
                        else if(((float)y-selectStart.y)/selectHeight<0.1f)changeTopSelectRectBorder=true;
                        else if(((float)y-selectStart.y)/selectHeight>0.9f)changeBottomSelectRectBorder=true;
                        else changeSelectRectPos=true;
                        return 0;
                    }
                }
                lButtonHold=true;
                ///if(paintMode)

                selecting=false;
                RECT rect;
                GetClientRect(hWindow,&rect);
                int x1=x;
                int y1=y;

                if(paintMode==MODE_LUPE) {
                        paintBuff->scaleUp();
                        onVScroll(997);
                        onHScroll(997);
                }
                if(paintMode==MODE_GEOMETRY)
                {
                    if(figure==POLYGON)
                    {
                        POINT temp;temp.x=x;temp.y=y;
                        polyPoints.push_back(temp);

                    }

                }
                if(paintMode==MODE_FILL)
                {
                    prev.x=x;
                    prev.y=y;
                    CFill fill(prev,color1);
                    paintBuff->drawFigure(&fill);
                }
                if(paintMode==MODE_PENCIL)
                {
                prev.x=x;prev.y=y;
                CPixel pixel(prev,color1);
                CLine line(prev,prev,penSize,color1);
                paintBuff->drawFigure(&pixel);
                paintBuff->drawFigure(&line);

                }
                if(paintMode==MODE_RUBBER)
                {


                prev.x=x;prev.y=y;
                CRubber line(prev,penSize,color2);
                paintBuff->drawFigure(&line);

                }
                if(paintMode==MODE_SELECT)
                {
                    selecting=true;
                    selectStart.x=x;
                    selectStart.y=y;
                    selectEnd.x=x;
                    selectEnd.y=y;

                    selectStartReal.x=x1;
                    selectStartReal.y=y1;
                    selectEndReal.x=x1;
                    selectEndReal.y=y1;
                }
                if(paintMode==MODE_TEXT)
                {

                        if((x>selectEnd.x||x<selectStart.x)||
                        (y>selectEnd.y||y<selectStart.y))
                        {
                        RECT rect;
                        rect.left=selectStart.x;
                        rect.right=selectEnd.x;
                        rect.bottom=selectEnd.y;
                        rect.top=selectStart.y;
                        paintBuff->drawTextToBuff(rect,textBuffor,&lf,color1,color2,transparent);
                        wsprintf(textBuffor,L"");
                        SetWindowText(edit,L"");
                        }
                    selecting=true;
                    prev.x=x;prev.y=y;

                    selectStart.x=x;
                    selectStart.y=y;
                    selectEnd.x=x;
                    selectEnd.y=y;

                    selectStartReal.x=x1;
                    selectStartReal.y=y1;
                    selectEndReal.x=x1;
                    selectEndReal.y=y1;

                }
                if(paintMode==MODE_BRUSH)
                {

                }
                if(paintMode==MODE_GETCOLOR) SendMessage(hWindow,WM_COMMAND,CMD_SET_COLOR_1,paintBuff->getPixel(x,y));
                if(paintMode==MODE_GEOMETRY)
                {
                    selecting=true;
                    selectStart.x=x;
                    selectStart.y=y;
                    selectEnd.x=x;
                    selectEnd.y=y;

                    selectStartReal.x=x1;
                    selectStartReal.y=y1;
                    selectEndReal.x=x1;
                    selectEndReal.y=y1;
                }
                SendMessage(hWindow,WM_PAINT,0,0);
                return 0;
}
int CEditor::onRightButtonDown(short x,short y,int keys){
    if(paintMode==MODE_LUPE)
    {
        paintBuff->scaleDown();
        onVScroll(997);
        onHScroll(997);

        }
    if(figure==POLYGON)
                    {
                        bool transparent=false;
                        int color1=(this)->color1;
                        if(figureMode==FMODE_FILL) color1=(this)->color2;
                        if(figureMode==FMODE_FRAME) transparent=true;
                        CPolygon polygon(&*polyPoints.begin(),polyPoints.size(),penSize,color1,color2,transparent);
                        paintBuff->drawFigure(&polygon);
                        polyPoints.clear();
                    }
    SendMessage(hWindow,WM_PAINT,0,0);
    return 0;
}
int CEditor::onMouseMove(short x,short y,int keys){
    prevReal.x=x;prevReal.y=y;
    POINT paintBuffSize=paintBuff->getSize();
    RECT drawRect=paintBuff->getDrawRect();
    x=(x-drawRect.left)*paintBuffSize.x/drawRect.right;
    y=(y-drawRect.top)*paintBuffSize.y/drawRect.bottom;

    if(selecting)
    {
        if(changeLeftSelectRectBorder)
        {
            selectStart.x=x;
        }
        if(changeRightSelectRectBorder)
        {
            selectEnd.x=x;
        }
        if(changeTopSelectRectBorder)
        {
            selectStart.y=y;
        }
        if(changeBottomSelectRectBorder)
        {
            selectEnd.y=y;
        }
        if(changeSelectRectPos)
        {
            selectStart.x+=(x-leftMouseButtonDownPos.x);
            selectStart.y+=(y-leftMouseButtonDownPos.y);
            selectEnd.x+=(x-leftMouseButtonDownPos.x);
            selectEnd.y+=(y-leftMouseButtonDownPos.y);
            leftMouseButtonDownPos.x=x;
            leftMouseButtonDownPos.y=y;
        }
    }
    int x1=x;
    int y1=y;


    POINT curr;curr.x=x;curr.y=y;
    if(lButtonHold){

                RECT rect;
                GetClientRect(hWindow,&rect);

                switch(paintMode)
                {
                    case MODE_PENCIL:{
                          CLine line(prev,curr,penSize,color1);
                          CPixel pixel(prev,color1);
                            paintBuff->drawFigure(&pixel);
                            paintBuff->drawFigure(&line);    break;}
                    case MODE_RUBBER:{  CRubber line(curr,penSize,color2);      paintBuff->drawFigure(&line);    break;}
                    case MODE_SPRAY: {
                        unsigned int lo,hi;
                        __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
                        CSpray spray(curr,penSize,color1,((uint64_t)hi << 32) | lo   );
                        paintBuff->drawFigure(&spray);break;
                        //CSprayFast fastSpray(curr,penSize,cover,color1,((uint64_t)hi << 32) | lo,paintBuff->pRgb,paintBuff->width,paintBuff->height);
                        //paintBuff->drawFigure(&fastSpray);break;
                        }
                    case MODE_GEOMETRY:
                    case MODE_TEXT:
                    case MODE_SELECT:
                        {
                            selectEnd.x=x;
                            selectEnd.y=y;
                            int x=x1;
                            int y=y1;
                            selectEndReal.x=x;
                            selectEndReal.y=y;
                            if(GetAsyncKeyState(VK_SHIFT))
                            {
                                ///if(selectEnd.x-selectStart.x>selectEnd.y-selectStart.y) selectEnd.x=selectEnd.x+selectEnd.y-selectStart.y;
                                ///else selectEnd.y=selectEnd.y+selectEnd.x-selectStart.x;
                            }
                        break;}
                    case MODE_BRUSH:{
                        POINT points[4];
                        points[0].x=prev.x-brush[0]; points[0].y=prev.y-brush[1];
                        points[1].x=prev.x+brush[0]; points[1].y=prev.y+brush[1];
                        points[2].x=curr.x+brush[0]; points[2].y=curr.y+brush[1];
                        points[3].x=curr.x-brush[0]; points[3].y=curr.y-brush[1];
                        CPolygon polygon(points,4,penSize/5,color1,color2,transparent);
                            paintBuff->drawFigure(&polygon);break;}
                    case MODE_UNDEFINED:break;
                    case MODE_FILL:break;
                    case MODE_LUPE:break;
                    case MODE_GETCOLOR:break;
                    case MODE_LAST_UNUSABLE:break;
                }
            }
            SendMessage(hWindow,WM_PAINT,0,0);

            prev=curr;
            if(!GetAsyncKeyState(VK_LBUTTON)) lButtonHold=false;
            return 0;
}
int CEditor::onLeftButtonUp(short x,short y,int keys){
                POINT paintBuffSize=paintBuff->getSize();
                RECT drawRect=paintBuff->getDrawRect();
                x=(x-drawRect.left)*paintBuffSize.x/drawRect.right;
                y=(y-drawRect.top)*paintBuffSize.y/drawRect.bottom;
                if(selectStart.x>selectEnd.x)
                {
                    int temp=selectStart.x;
                    selectStart.x=selectEnd.x;
                    selectEnd.x=temp;
                }
                if(selectStart.y>selectEnd.y)
                {
                    int temp=selectStart.y;
                    selectStart.y=selectEnd.y;
                    selectEnd.y=temp;
                }
                if(selectStart.x<0) selectStart.x=0;
                if(selectStart.y<0) selectStart.y=0;
                if(selectEnd.x>paintBuff->width) selectEnd.x=paintBuff->width;
                if(selectEnd.y>paintBuff->height) selectEnd.y=paintBuff->height;
                lButtonHold=false;
                if(paintMode==MODE_GEOMETRY)
                {
                    bool transparent=false;
                    int color1=(this)->color1;
                    if(figureMode==FMODE_FILL) color1=(this)->color2;
                    if(figureMode==FMODE_FRAME) transparent=true;
                    if(figure==ELLIPSE)
                    {

                        POINT tempS;
                        tempS.x=selectStart.x+penSize/2;
                        tempS.y=selectStart.y+penSize/2;
                        POINT tempE;
                        tempE.x=selectEnd.x-penSize/2;
                        tempE.y=selectEnd.y-penSize/2;
                        CEllipse ellipse(tempS,tempE,penSize,color1,color2,transparent);
                        paintBuff->drawFigure(&ellipse);
                    }
                    if(figure==RECTANGLE)
                    {                        POINT tempS;
                        tempS.x=selectStart.x+penSize/2;
                        tempS.y=selectStart.y+penSize/2;
                        POINT tempE;
                        tempE.x=selectEnd.x-penSize/2;
                        tempE.y=selectEnd.y-penSize/2;
                        ///if(tempS.x>tempE.x) tempE.x=tempS.x;
                        ///if(tempS.y>tempE.y) tempE.y=tempS.y;
                        CRectangle rectangle(tempS,tempE,penSize,color1,color2,transparent);
                        paintBuff->drawFigure(&rectangle);
                    }
                    if(figure==LINE)
                    {
                        POINT temp;
                        temp.x=x;
                        temp.y=y;
                        /*POINT tempS;POINT tempE;
                        if(leftMouseButtonDownPos.x<selectEnd.x) tempS.x=leftMouseButtonDownPos.x+penSize/2;
                        else tempS.x=leftMouseButtonDownPos.x-penSize/2;

                        if(leftMouseButtonDownPos.y>selectEnd.y) tempE.y=selectEnd.y+penSize/2;
                        else tempE.y=selectEnd.y-penSize/2;


                        tempS.y=leftMouseButtonDownPos.y-penSize/2;
                        tempE.y=selectEnd.y-penSize/2;*/

                        CLine line(leftMouseButtonDownPos,temp,penSize,color1);
                        paintBuff->drawFigure(&line);
                    }

                    ERROR_TEST
                }
                SendMessage(hWindow,WM_PAINT,0,0);
                changeLeftSelectRectBorder=false;
                changeRightSelectRectBorder=false;
                changeTopSelectRectBorder=false;
                changeBottomSelectRectBorder=false;
                changeSelectRectPos=false;
                return 0;
}
int CEditor::onDestroy(){

    paintBuff->~CPaintBuffer();
    ReleaseDC(hWindow,hdc);
    DestroyWindow(hWindow);
    DestroyWindow(paintToolsWnd);
    DestroyWindow(colorPaletteWnd);
    PostQuitMessage(0);
    return 0;
}
int CEditor::onClose(){
    paintBuff->saveToFile((wchar_t*)L"autozapis.bmp");
    SendMessage(hWindow,WM_DESTROY,0,0);
    return 0;
}
int CEditor::onKeyDown(int key,int flags){
            ///if(GetAsyncKeyState(188)) {currentLayer--; if(currentLayer<0) currentLayer=0;paintBuff=layers[currentLayer];SendMessage(hWindow,WM_PAINT,0,0);UpdateWindow(hWindow);paintBuff->scaled=true;}
            ///if(GetAsyncKeyState(190)) {currentLayer++; if(currentLayer>=10) currentLayer=9;paintBuff=layers[currentLayer];SendMessage(hWindow,WM_PAINT,0,0);UpdateWindow(hWindow);paintBuff->scaled=true;}
            if(GetAsyncKeyState(VK_CONTROL))
            {
                ///FILE
                if(key=='N') SendMessage(hWindow,WM_COMMAND,MENU_NEW,0);
                if(key=='O') SendMessage(hWindow,WM_COMMAND,MENU_OPEN,0);
                if(key=='S') SendMessage(hWindow,WM_COMMAND,MENU_SAVE,0);
                ///EDIT
                if(key=='Z') SendMessage(hWindow,WM_COMMAND,MENU_UNDO,0);
                if(key=='X') SendMessage(hWindow,WM_COMMAND,MENU_CUT,0);
                if(key=='C') SendMessage(hWindow,WM_COMMAND,MENU_COPY,0);
                if(key=='V') SendMessage(hWindow,WM_COMMAND,MENU_PASTE,0);
                if(key=='A') SendMessage(hWindow,WM_COMMAND,MENU_SELECT_ALL,0);

                return 0;
            }
            if(key==VK_F11) {
                    switchFullScreen();
            }
            if(paintMode==MODE_TEXT)
            {
                if(key==VK_ESCAPE)
                {
                    if(selecting==false)
                    {
                    if(menuIsVisible==false) {menu.set(hWindow);menuIsVisible=true;}
                    else {SetMenu(hWindow,0);menuIsVisible=false;}
                    }

                    SetWindowText(edit,L"");
                    ZeroMemory(textBuffor,256*sizeof(wchar_t));
                    paintMode=MODE_TEXT;
                    selecting=false;

                }
                else if(key==VK_RETURN)///trzeba bedzie wykorzystac edita i to takiego niewidzialnego ;P i oddac mu komuikaty keydown keyup
                {
                    PostMessage(edit,WM_KEYUP,key,flags);
                }
                else
                {
                    PostMessage(edit,WM_KEYUP,key,flags);
                }
                SendMessage(hWindow,WM_PAINT,0,0);
                return 0;
            }
            if(key==VK_ESCAPE)
            {
                if(menuIsVisible==true)
                {
                    menuIsVisible=false;
                    SetMenu(hWindow,0);

                }else{
                    menuIsVisible=true;
                    menu.set(hWindow);
                }
            }
            if(key==VK_F1)
            {
                SetLayeredWindowAttributes(hWindow, RGB(255,0,255), 255, LWA_ALPHA||LWA_COLORKEY);
            }
            if(key==VK_DELETE)
            {
                CRectangle rectangle(selectStart,selectEnd,0,color2,color2,false);
                paintBuff->drawFigure(&rectangle);
            }
            SendMessage(hWindow,WM_PAINT,0,0);
            return 0;

}
int CEditor::onCommand(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
            if(wParam==CMD_SET_PEN_SIZE) penSize=lParam;
            if(wParam==CMD_SET_COVER) cover=lParam;
            if(wParam==CMD_SET_BRUSH_DIR) { brush[0]=LOWORD(lParam);brush[1]=HIWORD(lParam);}
            if(wParam==CMD_SELECT_PAINT_TOOL){
                int prevMode=paintMode;
                paintMode=(PaintMode)lParam;
                if(paintMode!=MODE_TEXT)
                {
                    GetWindowText(edit,textBuffor,256*sizeof(wchar_t));
                    RECT rect;
                    rect.left=selectStart.x;
                    rect.right=selectEnd.x;
                    rect.bottom=selectEnd.y;
                    rect.top=selectStart.y;
                    paintBuff->drawTextToBuff(rect,textBuffor,&lf,color1,color2,transparent);
                    SetWindowText(edit,L"");
                    selecting=false;
                }
                else if(prevMode!=MODE_TEXT){
                        CHOOSEFONT cfnt;
                        ZeroMemory( & cfnt, sizeof( CHOOSEFONT ) );
                        cfnt.lStructSize = sizeof( CHOOSEFONT );
                        cfnt.hwndOwner = hWindow;
                        cfnt.Flags = CF_EFFECTS | CF_FORCEFONTEXIST | CF_SCREENFONTS|CF_INITTOLOGFONTSTRUCT;
                        cfnt.lpLogFont = & lf;
                         if( ChooseFont( & cfnt ) )
                        {
                            DWORD dwErr = CommDlgExtendedError();
                            if( dwErr ) MessageBox( hwnd, L"cos poszlo chyba nie tak?!", NULL, MB_ICONEXCLAMATION );

                        }
                        color1=cfnt.rgbColors;
                        SendMessage(paintToolsWnd,WM_COMMAND,CMD_SET_COLOR_1,color1);
                        selecting=true;
                }

            }
            if(wParam==CMD_SET_COLOR_1) {

                    color1=lParam;
                    SendMessage(paintToolsWnd,WM_COMMAND,CMD_SET_COLOR_1,color1);
                    }
            if(wParam==CMD_SET_COLOR_2) {

                    color2=lParam;
                    SendMessage(paintToolsWnd,WM_COMMAND,CMD_SET_COLOR_2,color2);
                    }
            if(wParam==CMD_SET_FIGURE) figure=(Figures)lParam;
            if(wParam==CMD_SET_TRANSPARENT) transparent=lParam;
            if(wParam==CMD_SET_FIGURE_MODE) figureMode=(FigureMode)lParam;
            if(wParam==MENU_TOOLS) ShowWindow(paintToolsWnd,SW_SHOW);
            if(wParam==MENU_NEG){
                if(selecting)
                {
                    CNegColor cng(selectStart,selectEnd);
                    paintBuff->drawFigure(&cng);
                }
            }
            if(wParam==MENU_CUT){
                if(selecting)
                {
                OpenClipboard(hWindow);
                EmptyClipboard();
                HBITMAP temp=CreateCompatibleBitmap(hdc,selectEnd.x-selectStart.x, selectEnd.y-selectStart.y);
                HDC hdc2=CreateCompatibleDC(hdc);
                HBITMAP old=(HBITMAP)SelectObject(hdc2,temp);
                StretchBlt(hdc2,0,0,selectEnd.x-selectStart.x, selectEnd.y-selectStart.y,paintBuff->memDC,selectStart.x,selectStart.y,selectEnd.x-selectStart.x, selectEnd.y-selectStart.y,SRCCOPY);
                HBITMAP temp2=(HBITMAP)SelectObject(hdc2,old);
                SetClipboardData(CF_BITMAP,temp2);
                CloseClipboard();
                DeleteDC(hdc2);
                CRectangle rectangle(selectStart,selectEnd,1,color2,color2,false);
                paintBuff->drawFigure(&rectangle);
                }
            }
            if(wParam==MENU_COPY){
                if(selecting)
                {
                OpenClipboard(hWindow);
                EmptyClipboard();
                HBITMAP temp=CreateCompatibleBitmap(hdc,selectEnd.x-selectStart.x, selectEnd.y-selectStart.y);
                HDC hdc2=CreateCompatibleDC(hdc);
                HBITMAP old=(HBITMAP)SelectObject(hdc2,temp);
                StretchBlt(hdc2,0,0,selectEnd.x-selectStart.x, selectEnd.y-selectStart.y,paintBuff->memDC,selectStart.x,selectStart.y,selectEnd.x-selectStart.x, selectEnd.y-selectStart.y,SRCCOPY);
                HBITMAP temp2=(HBITMAP)SelectObject(hdc2,old);
                SetClipboardData(CF_BITMAP,temp2);
                CloseClipboard();
                DeleteDC(hdc2);
                }
            }
            if(wParam==MENU_PASTE){
                if(selecting)
                {
                    OpenClipboard(hWindow);
                    HBITMAP bmp=(HBITMAP)GetClipboardData(CF_BITMAP);
                    if(bmp!=0)
                    {
                        BITMAP ibmp;
                        GetObject(bmp,sizeof(ibmp),&ibmp);
                        HDC hdc2=CreateCompatibleDC(hdc);
                        HDC hdc3=CreateCompatibleDC(hdc);
                        HBITMAP temp=CreateCompatibleBitmap(hdc,selectEnd.x-selectStart.x, selectEnd.y-selectStart.y);
                        HBITMAP oldFromHdc3=(HBITMAP)SelectObject(hdc3,temp);
                        HBITMAP old=(HBITMAP)SelectObject(hdc2,bmp);
                        printf("probuje wkleic %d %d!\n",(int)ibmp.bmWidth,(int)ibmp.bmHeight);
                        SetStretchBltMode(hdc3,HALFTONE);
                        StretchBlt(hdc3, 0, 0, selectEnd.x-selectStart.x, selectEnd.y-selectStart.y, hdc2, 0, 0, ibmp.bmWidth, ibmp.bmHeight, SRCCOPY);
                        GetObject(temp,sizeof(ibmp),&ibmp);
                        //StretchBlt(hdc, selectStart.x, selectStart.y, selectEnd.x-selectStart.x, selectEnd.y-selectStart.y, hdc3, 0, 0, ibmp.bmWidth, ibmp.bmHeight, SRCCOPY);
                        CPasteBMP cpbmp(selectStart,selectEnd,hdc3,ibmp.bmWidth,ibmp.bmHeight);
                        paintBuff->drawFigure(&cpbmp);
                        SelectObject(hdc2,old);
                        SelectObject(hdc3,oldFromHdc3);
                        DeleteObject(temp);
                        DeleteDC(hdc3);
                        DeleteDC(hdc2);
                    }
                    DeleteObject(bmp);
                    CloseClipboard();
                }
            }
            if(wParam==MENU_SELECT_ALL){
                selectStart.x=0;
                selectStart.y=0;
                selectEnd.x=paintBuff->getWidth();
                selectEnd.y=paintBuff->getHeight();
                selecting=true;
                SendMessage(hWindow,WM_PAINT,0,0);
            }
            if(wParam==MENU_FULLSCREEN){
                switchFullScreen();
            }
            if(wParam==MENU_ADD_SKETCH){
                wchar_t fileNameBuff[256];
                if(OpenSaveImageDialog(hwnd, fileNameBuff, 256, false))
                {
                    paintBuff->addSketch(fileNameBuff);
                }
            }
            if(wParam==MENU_ENABLE_SKETCH) paintBuff->isSketch=true;
            if(wParam==MENU_DISABLE_SKETCH) paintBuff->isSketch=false;
            if(wParam==MENU_PALETE) ShowWindow(colorPaletteWnd,SW_SHOW);
            if(wParam==MENU_PALETE_FILE){
                wchar_t fileNameBuff[256];
                if(OpenSaveImageDialog(hwnd, fileNameBuff, 256, false))
                {
                HWND temp=CreateWindowEx(WS_EX_TOOLWINDOW,ColorPaletteClassName,L"Paleta",WS_OVERLAPPEDWINDOW|WS_VISIBLE ,400,400,300,300,hWindow,0,0,fileNameBuff);
                SetWindowText(temp,fileNameBuff);
                }
            }
            if(wParam==MENU_EXIT) PostMessage(hwnd,WM_CLOSE,0,0);
            if(wParam==MENU_UNDO) paintBuff->undo();
            if(wParam==MENU_NEW) {
                    int ret = DialogBoxW( GetModuleHandle( NULL ), MAKEINTRESOURCE( 200 ), hwnd, DIALOG_NEW_PROC );
                    if(ret)
                    {
                        DIALOGNEWRESULT *dnr=(DIALOGNEWRESULT*)ret;
                    //printf("Koniec dialogu width=%d height=%d\n",dnr->width,dnr->height);
                        delete paintBuff;
                        paintBuff=new CPaintBuffer(hwnd,dnr->width,dnr->height);
                        SendMessage(hwnd,WM_PAINT,0,0);
                        delete dnr;
                    }
                    //else MessageBox(hWindow,L"FAIL",L"ERROR",MB_ICONERROR|MB_OK);
                    //paintBuff->resize(2000,3000);
            }
            if(wParam==MENU_SAVE_AS){
                wchar_t fileNameBuff[256];
                if(OpenSaveImageDialog(hwnd, fileNameBuff, 256, true))
                {
                paintBuff->saveToFile(fileNameBuff);
                SetWindowText(hwnd,fileNameBuff);
                }
            }
            if(wParam==MENU_SAVE){
                wchar_t fileNameBuff[256];
                GetWindowText(hwnd,fileNameBuff,256);
                paintBuff->saveToFile(fileNameBuff);
            }
            if(wParam==MENU_OPEN){
                wchar_t fileNameBuff[256];
                if(OpenSaveImageDialog(hwnd, fileNameBuff, 256, false))
                {

                paintBuff->loadFromFile(fileNameBuff);
                SetWindowText(hwnd,fileNameBuff);
                }
            }
            SendMessage(hwnd,WM_PAINT,0,0);
            lf.lfHeight=-MulDiv(penSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
            return 0;
}
int CEditor::onMouseWheel(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
            short x=HIWORD(wParam);
            if(wParam & MK_CONTROL )
            {
                if(x>0) {
                        paintBuff->scaleUp();
                }
                if(x<0) {
                        paintBuff->scaleDown();
                }
                SendMessage(hwnd,WM_PAINT,0,0);
                onVScroll(997);
                onHScroll(997);
                return 0;
            }
            if(x>0) penSize+=1;
            if(x<0) penSize-=1;
            if(penSize<=0) penSize=1;

            SendMessage(paintToolsWnd,WM_COMMAND,CMD_SET_PEN_SIZE,penSize);

            return 0;
}
BOOL OpenSaveImageDialog(HWND hwnd, LPWSTR szFileNameBuff, WORD wBuffSize, BOOL bSave){
    ZeroMemory(szFileNameBuff,wBuffSize);
   OPENFILENAMEW ofn;

   ZeroMemory(&ofn, sizeof(ofn));

   ofn.lStructSize = sizeof(ofn);
   ofn.hwndOwner = hwnd; //okno
   ofn.lpstrFilter = L"Image Files\0*.bmp;*.jpg;*.png;*.jpeg;*.jpe\0All Files (*.*)\0*.*\0\0"; //lista wyboru maski w formacie
// "nazwa\0rozszerzenie\0nazwa\0rozszerzenie...nazwa\0rozszerzenie\0\0"

   ofn.lpstrFile = szFileNameBuff;
   ofn.nMaxFile = wBuffSize; //rozmiar bufora szFileNameBuff, najlepiej MAX_PATH
   ofn.lpstrDefExt = L"png"; //domyślne rozszerzenie

   if(bSave) //zapis lub odczyt
   {
      ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY |
         OFN_OVERWRITEPROMPT; //więcej o flagach w MSDN pod OPENFILENAME
      if(!GetSaveFileNameW(&ofn))
         return FALSE;
   }
   else
   {
      ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
      if(!GetOpenFileNameW(&ofn))
         return FALSE;
   }
   return TRUE;
}
int CEditor::onVScroll(WPARAM wParam){
    SCROLLINFO si;
    ZeroMemory( & si, sizeof( si ) );
    si.cbSize = sizeof( SCROLLINFO );
    si.fMask = SIF_POS | SIF_PAGE | SIF_TRACKPOS;
    GetScrollInfo( hWindow, SB_VERT, & si );

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
    RECT client;
    GetClientRect(hWindow,&client);
    RECT rect=paintBuff->getDrawRect();

    if(rect.bottom>client.bottom)
    {
        si.nPage=client.bottom;
        si.nMin=0;
        si.nMax=rect.bottom;
        SetScrollInfo( hWindow, SB_VERT, & si, TRUE );
        paintBuff->y=-si.nPos;
        SendMessage(hWindow,WM_PAINT,0,0);
    }

    UpdateWindow( hWindow );
    return 0;
}
int CEditor::onHScroll(WPARAM wParam){
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



    RECT rect=paintBuff->getDrawRect();
    RECT client;
    GetClientRect(hWindow,&client);
    if(rect.right>client.right)
    {
        paintBuff->x=-si.nPos;
        SendMessage(hWindow,WM_PAINT,0,0);
        si.nPage=client.right;
        si.nMin=0;
        si.nMax=rect.right;
        SetScrollInfo( hWindow, SB_HORZ, & si, TRUE );
    }

    UpdateWindow( hWindow );
    return 0;
}
int CEditor::onSysColorChange(){
    HDC screenDC=GetDC(0);
    if(GetDeviceCaps(screenDC,BITSPIXEL)!=32){
        MessageBox(hWindow,L"Only 32bit color screen",L"FATAL ERROR",MB_ICONSTOP|MB_OK);
        DestroyWindow(hWindow);
    }
    return 0;
}
void CEditor::drawPaintBuffer(CPaintBuffer *paintBuffer){
    RECT rect;
    rect.left=selectStart.x;
    rect.right=selectEnd.x;
    rect.bottom=selectEnd.y;
    rect.top=selectStart.y;
    GetWindowText(edit,textBuffor,256*sizeof(wchar_t));
    int t=rdtsc();
    paintBuff->drawPaintBuffToRenderBuff();
    int t2=rdtsc()-t;
    printf("1zajelo to=%d\n",t2);
    if(paintMode==MODE_TEXT)paintBuff->drawTextToRenderBuff(rect,textBuffor,&lf,color1,color2,transparent);
                    bool transparent=false;
                    int color1=(this)->color1;
                    if(figureMode==FMODE_FILL) color1=(this)->color2;
                    if(figureMode==FMODE_FRAME) transparent=true;
    if(paintMode==MODE_GEOMETRY) paintBuff->drawPolygonToRenderBuff(polyPoints,penSize,color1,color2,transparent);
    if(selecting)paintBuff->drawSelectRectToRenderBuff(rect);
    t=rdtsc();
    paintBuff->drawRenderBuffToDC(hdc);
    t2=rdtsc()-t;
    printf("2zajelo to=%d\n",t2);
    rect=paintBuff->getDrawRect();
    HRGN hrgn=CreateRectRgn(rect.left,rect.top,rect.left+rect.right,rect.top+rect.bottom);
    SelectClipRgn(hdc,hrgn);///ten region po to zeby nie wychodzic z rysowaniem poza paintbuffer
    if(paintMode==MODE_RUBBER)
    {
        HBRUSH old=(HBRUSH)SelectObject(hdc,CreateSolidBrush(color2));
        Rectangle(hdc,prevReal.x-penSize/2/paintBuffer->getScaleX(),prevReal.y-penSize/2/paintBuffer->getScaleY(),prevReal.x+penSize/2/paintBuffer->getScaleX(),prevReal.y+penSize/2/paintBuffer->getScaleY());
        DeleteObject((HBRUSH)SelectObject(hdc,old));
    }

    DeleteObject(hrgn);
}
void CEditor::switchFullScreen(){
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
