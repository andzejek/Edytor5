#ifndef DIALOG_NEW_H
#define DIALOG_NEW_H
#include <windows.h>
#include <stdio.h>
#define IDD_DIALOG_NEW 200
#define IDC_LABEL 201
#define IDC_WIDTH 202
#define IDC_HEIGHT 203
#define IDC_WIN_RES    204
#define IDC_EDIT_RES  205
#define IDC_CLIENT_RES 206

///icons for painttoolwnd
#define IdIconSelectArea 901
#define IdIconSelectRect 902
#define IdIconRubber     903
#define IdIconFillBucket 904
#define IdIconGetColor   905
#define IdIconLupe       906
#define IdIconPencil     907
#define IdIconBrush      908
#define IdIconSpray      909
#define IdIconText       910
#define IdIconFigures    911

#define IdIconTransparent   912
#define IdIconNoTransparent 913

#define IdIconFigureModeFrame       914
#define IdIconFigureModeFillFrame   915
#define IdIconFigureModeFill        916

#define IdIconFigureRectangle 917
#define IdIconFigureEllipse 918

#define IdIconFigureLine 919
#define IdIconFigurePolygon 920

struct DIALOGNEWRESULT
{
    DIALOGNEWRESULT(int x,int y): width(x),height(y) {}
    int width,height;
};
BOOL CALLBACK DIALOG_NEW_PROC( HWND, UINT, WPARAM, LPARAM );
#endif //DIALOG_NEW
//#define MAINICON 123

