#include "stdafx.h"
HBITMAP loadImage(wchar_t *_fileName){
    Gdiplus::GdiplusStartupInput gpStartupInput;
    ULONG_PTR gpToken;
    GdiplusStartup(&gpToken, &gpStartupInput, NULL);
    HBITMAP result = NULL;
    Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile(_fileName, false);
    if (bitmap)
    {
        bitmap->GetHBITMAP(Gdiplus::Color(255, 255, 255), &result);
        delete bitmap;
    }
    Gdiplus::GdiplusShutdown(gpToken);
    return result;
}
int saveImage(wchar_t* _fileName,HBITMAP _image){
    Gdiplus::GdiplusStartupInput gpStartupInput;
    ULONG_PTR gpToken;
    GdiplusStartup(&gpToken, &gpStartupInput, NULL);
    CLSID bmpClsid,jpgClsid,gifClsid,tifClsid,pngClsid;
    CLSIDFromString(L"{557CF400-1A04-11D3-9A73-0000F81EF32E}", &bmpClsid);
    CLSIDFromString(L"{557CF401-1A04-11D3-9A73-0000F81EF32E}", &jpgClsid);
    CLSIDFromString(L"{557CF402-1A04-11D3-9A73-0000F81EF32E}", &gifClsid);
    CLSIDFromString(L"{557CF405-1A04-11D3-9A73-0000F81EF32E}", &tifClsid);
    CLSIDFromString(L"{557CF406-1A04-11D3-9A73-0000F81EF32E}", &pngClsid);
    //int size=wcslen(_fileName);
    wchar_t *start=wcschr(_fileName,'.');
    //MessageBox(0,_fileName,start,0);
    CLSID *encoderClsid=&bmpClsid;
    if(!wcscmp(start,L".bmp")) encoderClsid=&bmpClsid;
    if(!wcscmp(start,L".jpg")) encoderClsid=&jpgClsid;
    if(!wcscmp(start,L".jpeg")) encoderClsid=&jpgClsid;
    if(!wcscmp(start,L".gif")) encoderClsid=&gifClsid;
    if(!wcscmp(start,L".tif")) encoderClsid=&tifClsid;
    if(!wcscmp(start,L".png")) encoderClsid=&pngClsid;
    Gdiplus::Bitmap* image=new Gdiplus::Bitmap(_image,NULL);
    image->FromHBITMAP(_image,NULL);
    int stat=image->Save(_fileName,encoderClsid,0);
    if(stat!=Gdiplus::Ok) MessageBox(0,L"image save fail",L"Error",MB_OK|MB_ICONHAND);
    delete image;
    Gdiplus::GdiplusShutdown(gpToken);
    return 0;
}
HBITMAP create32DIB(HDC _hdc,int _width,int _height,BYTE **data){
    BITMAPINFO BitmapInfo;
    ZeroMemory(&BitmapInfo,sizeof(BITMAPINFO));
    BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    BitmapInfo.bmiHeader.biWidth = _width;
    BitmapInfo.bmiHeader.biHeight = -_height;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32;
    BitmapInfo.bmiHeader.biCompression = BI_RGB;
    return CreateDIBSection(_hdc, &BitmapInfo, DIB_RGB_COLORS, (VOID**)data, NULL, 0);
}

