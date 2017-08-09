#ifndef CPAINTTOOLS_H
#define CPAINTTOOLS_H
#include "../stdafx.h"
#include "CWindowEvents.h"
enum FigureMode
{
    FMODE_FRAME=1,
    FMODE_FILLFRAME=2,
    FMODE_FILL=3,
};
enum PaintATT
{
    ATT_NULL=0,
    ATT_BRUSHES=1,
    ATT_FIGURE=2,
    ATT_TRANSPARENT=3,
};
enum PaintMode
{
    MODE_UNDEFINED=0,
    MODE_PENCIL=1,
    MODE_FILL,
    MODE_LUPE,
    MODE_GETCOLOR,
    MODE_RUBBER,
    MODE_BRUSH,
    MODE_SPRAY,
    MODE_TEXT,
    MODE_SELECT,
    MODE_GEOMETRY,
    MODE_LAST_UNUSABLE,
};
enum Figures
{
    RECTANGLE=1,
    ELLIPSE=2,
    LINE=3,
    POLYGON=4,
};
#define CMD_SET_COLOR_1 1007
#define CMD_SET_COLOR_2 1008
#define CMD_SELECT_PAINT_TOOL 1005
#define CMD_SET_PEN_SIZE 1002
#define CMD_INC_PEN_SIZE 1003
#define CMD_DEC_PEN_SIZE 1004
#define CMD_SELECTING_ON
#define CMD_SELECTING_OFF
#define CMD_SET_COVER 1011
#define CMD_SET_BRUSH_DIR 1112

#define CMD_SET_FIGURE 1012
#define CMD_SET_FIGURE_MODE 1013
#define CMD_SET_TRANSPARENT 1014

#define BUTTON_SELECTAREA 1
#define BUTTON_SELECTRECT 2
#define BUTTON_RUBBER 3
#define BUTTON_FILLBUCKET 4
#define BUTTON_GETCOLOR 5
#define BUTTON_LUPE 6
#define BUTTON_PENCIL 7
#define BUTTON_BRUSH 8
#define BUTTON_SPRAY 9
#define BUTTON_TEXT 10


#define BUTTON_FIGURE_RECTANGLE 11
#define BUTTON_FIGURE_ELLIPSE 12
#define BUTTON_FIGURE_LINE 13
#define BUTTON_FIGURE_POLYGON 14
#define BUTTON_FIGURES 15

#define BUTTON_NOTRANSPARENT 17
#define BUTTON_TRANSPARENT 18

#define BUTTON_FIGURE_MODE_FRAME 19
#define BUTTON_FIGURE_MODE_FILLFRAME 20
#define BUTTON_FIGURE_MODE_FILL 21



#define EDIT_PENSIZE 30
#define EDIT_COVER   31


class CPaintTools : public CWindowEvents{

    public:
        CPaintTools(HWND hwnd){
            printf("CPaintTools: constructor!\n");
            hWindow=hwnd;
            hParentWindow=GetWindow(hWindow,GW_OWNER);
            if(hParentWindow==0) DestroyWindow(hWindow);///this window need "parent" to "existing"
        }
        int onCreate(CREATESTRUCT *cs)override;
        int onDestroy()override;
        int onClose()override;
        int onPaint()override;
        int onCommand(HWND hwnd,UINT message,WPARAM wparam,LPARAM lParam)override;
        int onLeftButtonDown(short x,short y,int k)override;
        virtual ~CPaintTools()
        {
            printf("CPaintTools: deconstructor!\n");
        }

    protected:

    private:
        HWND hWindow;
        HWND hParentWindow;

        RECT clientRect;

        HWND buttonSelectArea;
        HWND buttonSelectRect;
        HWND buttonRubber;
        HWND buttonFillBucket;
        HWND buttonGetColor;
        HWND buttonLupe;
        HWND buttonPencil;
        HWND buttonBrush;
        HWND buttonSpray;
        HWND buttonText;
        HWND buttonFigures;

        HWND frame;
        HWND buttonNoTransparent;
        HWND buttonTransparent;

        HWND buttonFigureModeFrame;
        HWND buttonFigureModeFillFrame;
        HWND buttonFigureModeFill;

        HWND buttonFigureRectangle;
        HWND buttonFigureEllipse;
        HWND buttonFigureLine;
        HWND buttonFigurePolygon;

        HWND editPenSize;
        HWND editCover;//for flamaster and spray,brush ... from 1 to 100;



        COLORREF color1,color2;
        PaintATT paintAtt;
        __int16 brush[2];
        int cover;
        int penSize;
        int paintMode;
        int selecting;///???
        bool transparent;
        FigureMode figureMode;

        HWND lastSelectedButton;///"help"

        HBITMAP hbmIconSelectArea;
        HBITMAP hbmIconSelectRect;
        HBITMAP hbmIconRubber;
        HBITMAP hbmIconFillBucket;
        HBITMAP hbmIconGetColor;
        HBITMAP hbmIconLupe;
        HBITMAP hbmIconPencil;
        HBITMAP hbmIconBrush;
        HBITMAP hbmIconSpray;
        HBITMAP hbmIconText;
        HBITMAP hbmIconFigures;

        HBITMAP hbmIconTransparent;
        HBITMAP hbmIconNoTransparent;

        HBITMAP hbmIconFigureModeFrame;
        HBITMAP hbmIconFigureModeFillFrame;
        HBITMAP hbmIconFigureModeFill;

        HBITMAP hbmIconFigureRectangle;
        HBITMAP hbmIconFigureEllipse;
        HBITMAP hbmIconFigureLine;
        HBITMAP hbmIconFigurePolygon;

};


#endif // CPAINTTOOLS_H

