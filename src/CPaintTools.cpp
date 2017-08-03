#include "CPaintTools.h"
#include "../DIALOG_NEW.h"
int CPaintTools::onCreate(CREATESTRUCT *cs){

            GetClientRect(hWindow,&clientRect);

            hbmIconSelectArea=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE( IdIconSelectArea) );
            hbmIconSelectRect=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE( IdIconSelectRect) );
            hbmIconRubber=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE( IdIconRubber) );
            hbmIconFillBucket=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconFillBucket ) );
            hbmIconGetColor=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconGetColor ) );
            hbmIconLupe=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconLupe  ) );
            hbmIconPencil=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE( IdIconPencil ) );
            hbmIconBrush=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconBrush  ) );
            hbmIconSpray=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE( IdIconSpray) );
            hbmIconText=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconText ) );
            hbmIconFigures=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconFigures ) );

            hbmIconTransparent=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconTransparent ) );
            hbmIconNoTransparent=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconNoTransparent ) );


            hbmIconFigureModeFrame=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconFigureModeFrame ) );
            hbmIconFigureModeFillFrame=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconFigureModeFillFrame) );
            hbmIconFigureModeFill=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconFigureModeFill ) );

            hbmIconFigureRectangle=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconFigureRectangle ) );
            hbmIconFigureEllipse=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconFigureEllipse ) );
            hbmIconFigureLine=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconFigureLine ) );
            hbmIconFigurePolygon=(HBITMAP) LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(IdIconFigurePolygon ) );

            buttonSelectArea=CreateWindowEx( 0, L"BUTTON", L"selectarea", WS_CHILD | WS_VISIBLE|BS_BITMAP,0, 0, clientRect.right/2, 32, hWindow, (HMENU)BUTTON_SELECTAREA, 0, NULL );
            SendMessage(buttonSelectArea, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconSelectArea);
            buttonSelectRect=CreateWindowEx( 0, L"BUTTON", L"selectrect", WS_CHILD | WS_VISIBLE|BS_BITMAP, clientRect.right/2, 0, clientRect.right/2, 32, hWindow, (HMENU)BUTTON_SELECTRECT, 0, NULL );
            SendMessage(buttonSelectRect, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconSelectRect);

            buttonRubber=CreateWindowEx( 0, L"BUTTON", L"rubber", WS_CHILD | WS_VISIBLE|BS_BITMAP,0, 32, clientRect.right/2, 32, hWindow, (HMENU)BUTTON_RUBBER, 0, NULL );
            SendMessage(buttonRubber, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconRubber);
            buttonFillBucket=CreateWindowEx( 0, L"BUTTON", L"fillbucket", WS_CHILD | WS_VISIBLE|BS_BITMAP, clientRect.right/2, 32, clientRect.right/2, 32, hWindow, (HMENU)BUTTON_FILLBUCKET, 0, NULL );
            SendMessage(buttonFillBucket, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconFillBucket);

            buttonGetColor=CreateWindowEx( 0, L"BUTTON", L"getcolor", WS_CHILD | WS_VISIBLE|BS_BITMAP,0, 64, clientRect.right/2, 32, hWindow, (HMENU)BUTTON_GETCOLOR, 0, NULL );
            SendMessage(buttonGetColor, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconGetColor);
            buttonLupe=CreateWindowEx( 0, L"BUTTON", L"lupe", WS_CHILD | WS_VISIBLE|BS_BITMAP, clientRect.right/2, 64, clientRect.right/2, 32, hWindow, (HMENU)BUTTON_LUPE, 0, NULL );
            SendMessage(buttonLupe, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconLupe);

            buttonPencil=CreateWindowEx( 0, L"BUTTON", L"pencil", WS_CHILD | WS_VISIBLE|BS_BITMAP,0, 96, clientRect.right/2, 32, hWindow, (HMENU)BUTTON_PENCIL, 0, NULL );
            SendMessage(buttonPencil, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconPencil);
            buttonBrush=CreateWindowEx( 0, L"BUTTON", L"brush", WS_CHILD | WS_VISIBLE|BS_BITMAP, clientRect.right/2, 96, clientRect.right/2, 32, hWindow, (HMENU)BUTTON_BRUSH, 0, NULL );
            SendMessage(buttonBrush, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconBrush);

            buttonSpray=CreateWindowEx( 0, L"BUTTON", L"spray", WS_CHILD | WS_VISIBLE|BS_BITMAP,0, 128, clientRect.right/2, 32, hWindow, (HMENU)BUTTON_SPRAY, 0, NULL );
            SendMessage(buttonSpray, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconSpray);
            buttonText=CreateWindowEx( 0, L"BUTTON", L"text", WS_CHILD | WS_VISIBLE|BS_BITMAP, clientRect.right/2, 128, clientRect.right/2, 32, hWindow, (HMENU)BUTTON_TEXT, 0, NULL );
            SendMessage(buttonText, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconText);

            buttonFigures=CreateWindowEx( 0, L"BUTTON", L"figures", WS_CHILD | WS_VISIBLE|BS_BITMAP, 0, 224, clientRect.right,32, hWindow, (HMENU)BUTTON_FIGURES, 0, NULL );
            SendMessage(buttonFigures, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconFigures);

            editPenSize = CreateWindowEx( WS_EX_CLIENTEDGE, L"EDIT", L"1", WS_CHILD | WS_VISIBLE | WS_BORDER|ES_NUMBER, 0, 256, clientRect.right,20, hWindow, (HMENU)EDIT_PENSIZE,0, NULL );
            SendMessage( editPenSize, EM_SETLIMITTEXT,3,0);

            ///editCover = CreateWindowEx( WS_EX_CLIENTEDGE, L"EDIT", L"1", WS_CHILD | WS_VISIBLE | WS_BORDER|ES_NUMBER, 0, 292, clientRect.right,20, hWindow, (HMENU)EDIT_COVER,0, NULL );
            ///SendMessage( editPenSize, EM_SETLIMITTEXT,3,0);
            frame = CreateWindowEx( 0, L"STATIC", L"Ramka", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_ETCHEDFRAME,0, 292+64, clientRect.right,100, hWindow, NULL, 0, NULL );
            buttonNoTransparent=CreateWindowEx( 0, L"BUTTON", L"notransparent", WS_CHILD | WS_VISIBLE|BS_BITMAP|BS_FLAT, 5, 292+5+64, clientRect.right-10,32, hWindow, (HMENU)BUTTON_NOTRANSPARENT, 0, NULL );
            SendMessage(buttonNoTransparent, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconNoTransparent);
            buttonTransparent=CreateWindowEx( 0, L"BUTTON", L"transparent", WS_CHILD | WS_VISIBLE|BS_BITMAP|BS_FLAT, 5, 292+5+32+64, clientRect.right-10,32, hWindow, (HMENU)BUTTON_TRANSPARENT, 0, NULL );
            SendMessage(buttonTransparent, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconTransparent);
            MoveWindow(frame,0, 292+64, clientRect.right,72,true);

            buttonFigureModeFrame=CreateWindowEx( 0, L"BUTTON", L"figuremodeframe", WS_CHILD | WS_VISIBLE|BS_BITMAP|BS_FLAT, 5, 292+5+64, clientRect.right-10,21, hWindow, (HMENU)BUTTON_FIGURE_MODE_FRAME, 0, NULL );
            SendMessage(buttonFigureModeFrame, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconFigureModeFrame);
            buttonFigureModeFillFrame=CreateWindowEx( 0, L"BUTTON", L"figuremodefillframe", WS_CHILD | WS_VISIBLE|BS_BITMAP|BS_FLAT, 5, 292+5+21+64, clientRect.right-10,21, hWindow, (HMENU)BUTTON_FIGURE_MODE_FILLFRAME, 0, NULL );
            SendMessage(buttonFigureModeFillFrame, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconFigureModeFillFrame);
            buttonFigureModeFill=CreateWindowEx( 0, L"BUTTON", L"figuremodefill", WS_CHILD | WS_VISIBLE|BS_BITMAP|BS_FLAT, 5, 292+5+21+21+64, clientRect.right-10,21, hWindow, (HMENU)BUTTON_FIGURE_MODE_FILL, 0, NULL );
            SendMessage(buttonFigureModeFill, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconFigureModeFill);
            MoveWindow(frame,0, 292+64, clientRect.right,72,true);

            buttonFigureRectangle=CreateWindowEx( 0, L"BUTTON", L"figure rectangle", WS_CHILD | WS_VISIBLE|BS_BITMAP,0, 160, clientRect.right/2, 32, hWindow, (HMENU)BUTTON_FIGURE_RECTANGLE, 0, NULL );
            SendMessage(buttonFigureRectangle, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconFigureRectangle);
            buttonFigureEllipse=CreateWindowEx( 0, L"BUTTON", L"figure ellipse", WS_CHILD | WS_VISIBLE|BS_BITMAP,clientRect.right/2, 160, clientRect.right/2, 32, hWindow, (HMENU)BUTTON_FIGURE_ELLIPSE, 0, NULL );
            SendMessage(buttonFigureEllipse, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconFigureEllipse);
            buttonFigureLine=CreateWindowEx( 0, L"BUTTON", L"figure line", WS_CHILD | WS_VISIBLE|BS_BITMAP,0, 192, clientRect.right/2, 32, hWindow, (HMENU)BUTTON_FIGURE_LINE, 0, NULL );
            SendMessage(buttonFigureLine, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconFigureLine);
            buttonFigurePolygon=CreateWindowEx( 0, L"BUTTON", L"figure polygon", WS_CHILD | WS_VISIBLE|BS_BITMAP,clientRect.right/2,192, clientRect.right/2, 32, hWindow, (HMENU)BUTTON_FIGURE_POLYGON, 0, NULL );
            SendMessage(buttonFigurePolygon, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbmIconFigurePolygon);

            //HWND buttonFigureEllipse=
            color1=0;
            color2=0;
            //EnableWindow(buttonBrush,FALSE);
            EnableWindow(buttonSelectArea,FALSE);
            paintAtt=ATT_NULL;
            //EnableWindow(buttonLupe,FALSE);
            return 0;
}
int CPaintTools::onDestroy(){
    DeleteObject(hbmIconSelectArea);
    DeleteObject(hbmIconSelectRect);
    DeleteObject(hbmIconRubber);
    DeleteObject(hbmIconFillBucket);
    DeleteObject(hbmIconGetColor);
    DeleteObject(hbmIconLupe);
    DeleteObject(hbmIconPencil);
    DeleteObject(hbmIconBrush);
    DeleteObject(hbmIconSpray);
    DeleteObject(hbmIconText);

    DeleteObject(hbmIconTransparent);
    DeleteObject(hbmIconNoTransparent);

    DeleteObject(hbmIconFigureModeFrame);
    DeleteObject(hbmIconFigureModeFillFrame);
    DeleteObject(hbmIconFigureModeFill);

    DeleteObject(hbmIconFigureRectangle);
    DeleteObject(hbmIconFigureEllipse);
    DeleteObject(hbmIconFigureLine);
    DeleteObject(hbmIconFigurePolygon);
    return 0;
    //DestroyWindow(hWindow);
}
int CPaintTools::onClose(){
    ShowWindow(hWindow,SW_HIDE);
    return 0;
}
int CPaintTools::onPaint(){
    PAINTSTRUCT ps;
    HDC hdc=BeginPaint(hWindow,&ps);
    HBRUSH brush1=CreateSolidBrush(color1);
    HBRUSH brush2=CreateSolidBrush(color2);
    HBRUSH old=(HBRUSH)SelectObject(hdc,brush2);
    Rectangle(hdc,30,346,70,306);
    SelectObject(hdc,brush1);
    Rectangle(hdc,10,326,50,286);
    SelectObject(hdc,old);
    EndPaint(hWindow,&ps);
    SelectObject(hdc,old);
    EndPaint(hWindow,&ps);
    DeleteObject(brush1);
    DeleteObject(brush2);
    return 0;
}
int CPaintTools::onCommand(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){

            if(paintAtt==ATT_NULL)
            {
                ShowWindow(buttonFigureModeFill,SW_HIDE);
                ShowWindow(buttonFigureModeFrame,SW_HIDE);
                ShowWindow(buttonFigureModeFillFrame,SW_HIDE);
                ShowWindow(buttonTransparent,SW_HIDE);
                ShowWindow(buttonNoTransparent,SW_HIDE);
                ShowWindow(frame,SW_HIDE);
            }
            if(paintAtt==ATT_TRANSPARENT){
                ShowWindow(buttonFigureModeFill,SW_HIDE);
                ShowWindow(buttonFigureModeFrame,SW_HIDE);
                ShowWindow(buttonFigureModeFillFrame,SW_HIDE);
                ShowWindow(buttonTransparent,SW_SHOW);
                ShowWindow(buttonNoTransparent,SW_SHOW);
                ShowWindow(frame,SW_SHOW);
            }
            if(paintAtt==ATT_FIGURE)
            {
                ShowWindow(buttonTransparent,SW_HIDE);
                ShowWindow(buttonNoTransparent,SW_HIDE);
                ShowWindow(buttonFigureModeFill,SW_SHOW);
                ShowWindow(buttonFigureModeFrame,SW_SHOW);
                ShowWindow(buttonFigureModeFillFrame,SW_SHOW);
                ShowWindow(frame,SW_SHOW);
            }
            if((HIWORD(wParam) == EN_CHANGE) &&
            (LOWORD(wParam) == EDIT_PENSIZE))
            {
                wchar_t bufor[16];
                GetWindowText((HWND)lParam,bufor,16);
                penSize= wcstol (bufor,0,10);
                if(penSize<=0) {penSize=1;SetWindowText(editPenSize,L"1");}
                SendMessage(hParentWindow,WM_COMMAND,CMD_SET_PEN_SIZE,penSize);
                return 0;
            }
            if((HIWORD(wParam) == EN_CHANGE) &&
            (LOWORD(wParam) == EDIT_COVER))
            {
                wchar_t bufor[16];
                GetWindowText((HWND)lParam,bufor,16);
                cover= wcstol (bufor,0,10);
                if(cover<=0) {cover=1;SetWindowText(editCover,L"1");}
                SendMessage(hParentWindow,WM_COMMAND,CMD_SET_COVER,cover);
                return 0;
            }
            if(wParam==CMD_SET_COLOR_1){
                    InvalidateRect(hWindow,0,0);
                    color1=lParam;return 0;
            }
            if(wParam==CMD_SET_COLOR_2){
                    InvalidateRect(hWindow,0,0);
                    color2=lParam;return 0;
            }
            if(wParam==CMD_SET_PEN_SIZE)
            {
                penSize=lParam;
                wchar_t bufor[16];
                wsprintf(bufor,L"%d",penSize);
                SetWindowText(editPenSize,bufor);
                return 0;
            }
            if(wParam==CMD_SET_COVER)
            {
                cover=lParam;
                wchar_t bufor[16];
                wsprintf(bufor,L"%d",cover);
                SetWindowText(editCover,bufor);
                return 0;
            }
            if(HIWORD(wParam) == 0)
            {
            selecting=false;
            if(wParam<=BUTTON_TRANSPARENT)SendMessage((HWND)lastSelectedButton, BM_SETSTATE, false, 0);
            switch(wParam)
            {
                case BUTTON_SELECTAREA: paintMode=0; selecting=true;paintAtt=ATT_TRANSPARENT;break;
                case BUTTON_SELECTRECT: paintMode=MODE_SELECT;paintAtt=ATT_TRANSPARENT; selecting=true;  break;
                case BUTTON_RUBBER:     paintMode=MODE_RUBBER;paintAtt=ATT_NULL;  break;
                case BUTTON_FILLBUCKET: paintMode=MODE_FILL;paintAtt=ATT_NULL;    break;
                case BUTTON_GETCOLOR:   paintMode=MODE_GETCOLOR;paintAtt=ATT_NULL;break;
                case BUTTON_LUPE:       paintMode=MODE_LUPE;paintAtt=ATT_NULL;            break;
                case BUTTON_PENCIL:     paintMode=MODE_PENCIL;paintAtt=ATT_NULL;  break;
                case BUTTON_BRUSH:      paintMode=MODE_BRUSH;paintAtt=ATT_NULL;ShowWindow(buttonNoTransparent,SW_HIDE) ;           break;
                case BUTTON_SPRAY:      paintMode=MODE_SPRAY;paintAtt=ATT_NULL;   break;
                case BUTTON_TEXT:       paintMode=MODE_TEXT;paintAtt=ATT_TRANSPARENT;            break;
                case BUTTON_FIGURES:    paintMode=MODE_GEOMETRY;paintAtt=ATT_FIGURE;             break;

                case BUTTON_TRANSPARENT: transparent=true;       break;
                case BUTTON_NOTRANSPARENT: transparent=false;    break;

                case BUTTON_FIGURE_MODE_FRAME: figureMode=FMODE_FRAME; break;
                case BUTTON_FIGURE_MODE_FILLFRAME: figureMode=FMODE_FILLFRAME; break;
                case BUTTON_FIGURE_MODE_FILL: figureMode=FMODE_FILL; break;

                case BUTTON_FIGURE_RECTANGLE: SendMessage(hParentWindow,WM_COMMAND,CMD_SET_FIGURE,RECTANGLE);paintMode=MODE_GEOMETRY;paintAtt=ATT_FIGURE;break;
                case BUTTON_FIGURE_ELLIPSE: SendMessage(hParentWindow,WM_COMMAND,CMD_SET_FIGURE,ELLIPSE);paintMode=MODE_GEOMETRY;paintAtt=ATT_FIGURE;break;
                case BUTTON_FIGURE_LINE: SendMessage(hParentWindow,WM_COMMAND,CMD_SET_FIGURE,LINE);paintMode=MODE_GEOMETRY;paintAtt=ATT_FIGURE;break;
                case BUTTON_FIGURE_POLYGON: SendMessage(hParentWindow,WM_COMMAND,CMD_SET_FIGURE,POLYGON);paintMode=MODE_GEOMETRY;paintAtt=ATT_FIGURE;break;

                default:                paintMode=0;
            }
            if(wParam<=BUTTON_TRANSPARENT)
            {
            SendMessage((HWND)lParam, BM_SETSTATE, true, 0);
            lastSelectedButton=(HWND)lParam;
            }
            SendMessage(hParentWindow,WM_COMMAND,CMD_SET_TRANSPARENT,transparent);
            SendMessage(hParentWindow,WM_COMMAND,CMD_SELECT_PAINT_TOOL,paintMode);
            SendMessage(hParentWindow,WM_COMMAND,CMD_SET_FIGURE_MODE,figureMode);
            SetActiveWindow(hParentWindow);

            }

            /*switch(paintMode)
            {
                case BUTTON_SELECTAREA: SendMessage((HWND)buttonSelectArea, BM_SETSTATE, false, 0);;break;
                case BUTTON_SELECTRECT: SendMessage((HWND)buttonSelectRect, BM_SETSTATE, false, 0);  break;
                case BUTTON_RUBBER:     SendMessage((HWND)buttonRubber, BM_SETSTATE, false, 0);  break;
                case BUTTON_FILLBUCKET: SendMessage((HWND)buttonFillBucket, BM_SETSTATE, false, 0);    break;
                case BUTTON_GETCOLOR:   SendMessage((HWND)buttonGetColor, BM_SETSTATE, false, 0);            break;
                case BUTTON_LUPE:       SendMessage((HWND)buttonLupe, BM_SETSTATE, false, 0);           break;
                case BUTTON_PENCIL:     SendMessage((HWND)buttonPencil, BM_SETSTATE, false, 0);  break;
                case BUTTON_BRUSH:      SendMessage((HWND)buttonBrush, BM_SETSTATE, false, 0);            break;
                case BUTTON_SPRAY:      SendMessage((HWND)buttonSpray, BM_SETSTATE, false, 0);   break;
                case BUTTON_TEXT:       SendMessage((HWND)buttonText, BM_SETSTATE, false, 0);            break;
            }*/
            return 0;
}
int CPaintTools::onLeftButtonDown(short x,short y,int keys){
    CHOOSECOLOR ccl;
    COLORREF TabKol[ 16 ];
    ZeroMemory(TabKol,sizeof(COLORREF)*16);
    BOOL bResult;

    ZeroMemory( & ccl, sizeof( CHOOSECOLOR ) );
    ccl.lStructSize = sizeof( CHOOSECOLOR );
    ccl.hwndOwner = hWindow;
    ccl.lpCustColors = TabKol;
    ccl.Flags = CC_ANYCOLOR|CC_RGBINIT;

    if(x>10&&x<50&&y>286&&y<326)
    {
        ccl.rgbResult=color1;
        bResult = ChooseColor( & ccl );
        if(bResult)
        {
        color1=ccl.rgbResult;
        SendMessage(hParentWindow,WM_COMMAND,CMD_SET_COLOR_1,color1);
        }

    }
    else if(x>30&&x<70&&y>306&&y<346)
    {
        ccl.rgbResult=color2;
        bResult = ChooseColor( & ccl );
        if(bResult)
        {
        color2=ccl.rgbResult;
        SendMessage(hParentWindow,WM_COMMAND,CMD_SET_COLOR_2,color2);
        }
    }
    InvalidateRect(hWindow,0,true);
    SendMessage(hWindow,WM_PAINT,0,0);
    return 0;
}

