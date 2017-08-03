#include "DIALOG_NEW.h"
BOOL CALLBACK DIALOG_NEW_PROC( HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    switch( Msg )
    {
    case WM_COMMAND:
        {
            switch( LOWORD( wParam ) )
            {
                case IDOK:
                    {
                        HWND hWidth = GetDlgItem( hwnd, IDC_WIDTH);
                        HWND hHeight= GetDlgItem( hwnd, IDC_HEIGHT);
                        char buff[32];
                        ZeroMemory(buff,32);
                        int width,height;
                        if(GetWindowTextLength(hWidth))
                        {
                        GetWindowText(hWidth,buff,32);
                        sscanf(buff,"%d",&width);
                        } else width=0;
                        if(GetWindowTextLength(hHeight))
                        {
                        GetWindowText(hHeight,buff,32);
                        sscanf(buff,"%d",&height);
                        } else height=0;
                        printf("height=%d width=%d\n",height,width);
                        if(height<=0||width<=0) return FALSE;
                        else {
                            DIALOGNEWRESULT *dnr=new DIALOGNEWRESULT(width,height);
                            EndDialog( hwnd,(int)dnr);
                        }
                    }break;
                case IDCANCEL: EndDialog( hwnd, 0 ); break;
                case IDC_WIN_RES:
                    {
                        HWND hWidth = GetDlgItem( hwnd, IDC_WIDTH);
                        HWND hHeight= GetDlgItem( hwnd, IDC_HEIGHT);
                        int width=GetSystemMetrics(SM_CXSCREEN);
                        int height=GetSystemMetrics(SM_CYSCREEN);
                        char buff[32];
                        sprintf(buff,"%d",width);
                        SetWindowText(hWidth,buff);
                        sprintf(buff,"%d",height);
                        SetWindowText(hHeight,buff);
                    }break;
                case IDC_EDIT_RES:
                    {
                        HWND hwnd2=GetWindow(hwnd,GW_OWNER);
                        HWND hWidth = GetDlgItem( hwnd, IDC_WIDTH);
                        HWND hHeight= GetDlgItem( hwnd, IDC_HEIGHT);
                        RECT rect;
                        GetWindowRect(hwnd2,&rect);
                        int width=rect.right;
                        int height=rect.bottom;
                        char buff[32];
                        sprintf(buff,"%d",width);
                        SetWindowText(hWidth,buff);
                        sprintf(buff,"%d",height);
                        SetWindowText(hHeight,buff);
                    }break;
                case IDC_CLIENT_RES:
                    {
                        HWND hwnd2=GetWindow(hwnd,GW_OWNER);
                        HWND hWidth = GetDlgItem( hwnd, IDC_WIDTH);
                        HWND hHeight= GetDlgItem( hwnd, IDC_HEIGHT);
                        RECT rect;
                        GetClientRect(hwnd2,&rect);
                        int width=rect.right;
                        int height=rect.bottom;
                        char buff[32];
                        sprintf(buff,"%d",width);
                        SetWindowText(hWidth,buff);
                        sprintf(buff,"%d",height);
                        SetWindowText(hHeight,buff);
                    }break;
            }
        }
        break;
        default: return FALSE;
    }
    return TRUE;
}


