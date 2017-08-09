#include "CPaintBuffer.h"
///#include "Vfw.h"
CPaintBuffer::CPaintBuffer(HWND _hwnd,int _width,int _height){
    isSketch=false;
    scaleX=1;
    scaleY=1;
    hwnd=_hwnd;
    width=_width;
    height=_height;

    hdc=GetDC(hwnd);
    memDC=CreateCompatibleDC(hdc);
    printf("Create DC:%d\n",(int)memDC);
//______________________________________________________
    BITMAPINFO BitmapInfo;
        ZeroMemory(&BitmapInfo,sizeof(BITMAPINFO));
        BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        BitmapInfo.bmiHeader.biWidth = _width;
        BitmapInfo.bmiHeader.biHeight = -_height;
        BitmapInfo.bmiHeader.biPlanes = 1;
        BitmapInfo.bmiHeader.biBitCount = 32;
        BitmapInfo.bmiHeader.biCompression = BI_RGB;

        HBITMAP blank = CreateDIBSection(memDC, &BitmapInfo, DIB_RGB_COLORS, (void**)&memBytes, NULL, 0);
        printf("Create BITMAP:%d\n",(int)blank);
///______________________________________________________*/
    //deleteObject(blank);
    //blank=CreateCompatibleBitmap(hdc,width,height);
    oldBm=(HBITMAP)SelectObject(memDC,blank);

    renderDC=CreateCompatibleDC(hdc);
    blank = CreateDIBSection(renderDC, &BitmapInfo, DIB_RGB_COLORS, (void**)&renderBytes, NULL, 0);
    oldRenderBmp=(HBITMAP)SelectObject(renderDC,blank);

    sketchDC=CreateCompatibleDC(hdc);
    blank = CreateDIBSection(sketchDC, &BitmapInfo, DIB_RGB_COLORS, (void**)&sketchBytes, NULL, 0);
    oldSketchBmp=(HBITMAP)SelectObject(sketchDC,blank);

    restoreDC=CreateCompatibleDC(hdc);
    printf("Create DC:%d\n",(int)restoreDC);
    HBITMAP blank2=CreateCompatibleBitmap(hdc,width,height);
    oldBm2=(HBITMAP)SelectObject(restoreDC,blank2);

    HPEN newPen2=CreatePen(PS_SOLID,1,RGB(0,0,0));
    oldPen2=(HPEN)SelectObject(restoreDC,newPen2);
    HBRUSH newBrush2=CreateSolidBrush(RGB(255,255,0));
    oldBrush2=(HBRUSH) SelectObject(restoreDC,newBrush2);

    //RECT rect;rect.top=0;rect.left=0;rect.right=width;rect.bottom=height;
    HPEN newPen=CreatePen(PS_SOLID,1,RGB(0,0,0));
    oldPen=(HPEN)SelectObject(memDC,newPen);
    HBRUSH newBrush=CreateSolidBrush(RGB(255,255,0));
    oldBrush=(HBRUSH) SelectObject(memDC,newBrush);
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

    DeleteObject(SelectObject(memDC,oldBm));
    DeleteObject(SelectObject(memDC,oldPen));
    DeleteObject(SelectObject(memDC,oldBrush));
    DeleteDC(memDC);


    DeleteObject(SelectObject(restoreDC,oldBm2));
    DeleteObject(SelectObject(restoreDC,oldPen2));
    DeleteObject(SelectObject(restoreDC,oldBrush2));
    DeleteDC(restoreDC);

    ReleaseDC(hwnd,hdc);
}
void CPaintBuffer::resize(int _width,int _height){
    width=_width;
    height=_height;
    //______________________________________________________
    BITMAPINFO BitmapInfo;
        ZeroMemory(&BitmapInfo,sizeof(BITMAPINFO));
        BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        BitmapInfo.bmiHeader.biWidth = _width;
        BitmapInfo.bmiHeader.biHeight = -_height;
        BitmapInfo.bmiHeader.biPlanes = 1;
        BitmapInfo.bmiHeader.biBitCount = 32;
        BitmapInfo.bmiHeader.biCompression = BI_RGB;

        HBITMAP blanka = CreateDIBSection(memDC, &BitmapInfo, DIB_RGB_COLORS, (void**)&memBytes, NULL, 0);
//______________________________________________________*/
    //HBITMAP blanka=CreateCompatibleBitmap(hdc,width,height);
    DeleteObject(SelectObject(memDC,blanka));

    blanka = CreateDIBSection(renderDC, &BitmapInfo, DIB_RGB_COLORS, (void**)&renderBytes, NULL, 0);
    DeleteObject(SelectObject(renderDC,blanka));

    blanka = CreateDIBSection(sketchDC, &BitmapInfo, DIB_RGB_COLORS, (void**)&sketchBytes, NULL, 0);
    DeleteObject(SelectObject(sketchDC,blanka));

    HBITMAP blank2a=CreateCompatibleBitmap(hdc,width,height);
    DeleteObject(SelectObject(restoreDC,blank2a));

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
    ///StretchBlt(hdc, 0, 0, wrect.right, wrect.bottom, memDC, drawRect.left, drawRect.top, drawRect.right/scaleX, drawRect.bottom/scaleY, SRCCOPY);
    //HDC hdce=GetDC(edit);
        //StretchBlt(renderDC,0,0,300,300,hdce,0,0,300,300,SRCCOPY);
        //ReleaseDC(edit,hdce);
    SetStretchBltMode(hdc,COLORONCOLOR);
    StretchBlt(hdc, x, y, drawRect.right/scaleX, drawRect.bottom/scaleY, renderDC, drawRect.left, drawRect.top, drawRect.right, drawRect.bottom, SRCCOPY);
    /*StretchBlt(hdc, 0, 0, wrect.right/2, wrect.bottom/2, memDC, drawRect.left, drawRect.top, drawRect.right/scaleX, drawRect.bottom/scaleY, SRCCOPY);
    StretchBlt(hdc, wrect.right/2, wrect.bottom/2, wrect.right/2, wrect.bottom/2, restoreDC, drawRect.left, drawRect.top, drawRect.right/scaleX, drawRect.bottom/scaleY, SRCCOPY);
    ///Ellipse(hdc,0,0,100,100); tutaj zaznaczanie! ;p*/
}
void CPaintBuffer::drawFigure(CFigure *figure){
    if(figures.size()>10000)
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
        printf("figures.size()=%d\n",figures.size());
        restore();
    }
#define errhandler(A,B) printf(A)
PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp){///from MSDN
    BITMAP bmp;
    PBITMAPINFO pbmi;
    WORD    cClrBits;

    // Retrieve the bitmap color format, width, and height.
    if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
        errhandler("GetObject", hwnd);

    // Convert the color format to a count of bits.
    cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
    if (cClrBits == 1)
        cClrBits = 1;
    else if (cClrBits <= 4)
        cClrBits = 4;
    else if (cClrBits <= 8)
        cClrBits = 8;
    else if (cClrBits <= 16)
        cClrBits = 16;
    else if (cClrBits <= 24)
        cClrBits = 24;
    else cClrBits = 32;

    // Allocate memory for the BITMAPINFO structure. (This structure
    // contains a BITMAPINFOHEADER structure and an array of RGBQUAD
    // data structures.)

     if (cClrBits < 24)
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR,
                    sizeof(BITMAPINFOHEADER) +
                    sizeof(RGBQUAD) * (1<< cClrBits));

     // There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel

     else
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR,
                    sizeof(BITMAPINFOHEADER));

    // Initialize the fields in the BITMAPINFO structure.

    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbmi->bmiHeader.biWidth = bmp.bmWidth;
    pbmi->bmiHeader.biHeight = bmp.bmHeight;
    pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
    pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
    if (cClrBits < 24)
        pbmi->bmiHeader.biClrUsed = (1<<cClrBits);

    // If the bitmap is not compressed, set the BI_RGB flag.
    pbmi->bmiHeader.biCompression = BI_RGB;

    // Compute the number of bytes in the array of color
    // indices and store the result in biSizeImage.
    // The width must be DWORD aligned unless the bitmap is RLE
    // compressed.
    pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8
                                  * pbmi->bmiHeader.biHeight;
    // Set biClrImportant to 0, indicating that all of the
    // device colors are important.
     pbmi->bmiHeader.biClrImportant = 0;
     return pbmi;
 }
void CreateBMPFile(HWND hwnd,wchar_t* pszFile, PBITMAPINFO pbi,HBITMAP hBMP, HDC hDC){///from MSDN
     HANDLE hf;                 // file handle
    BITMAPFILEHEADER hdr;       // bitmap file-header
    PBITMAPINFOHEADER pbih;     // bitmap info-header
    LPBYTE lpBits;              // memory pointer
    DWORD dwTotal=0;              // total count of bytes
    dwTotal=dwTotal;
    DWORD cb;                   // incremental count of bytes
    BYTE *hp;                   // byte pointer
    DWORD dwTmp;


    pbih = (PBITMAPINFOHEADER) pbi;
    lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

    if (!lpBits)
         errhandler("GlobalAlloc", hwnd);

    // Retrieve the color table (RGBQUAD array) and the bits
    // (array of palette indices) from the DIB.
    if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi,
        DIB_RGB_COLORS))
    {
        errhandler("GetDIBits", hwnd);
    }

    // Create the .BMP file.
    hf = CreateFile(pszFile,
                   GENERIC_READ | GENERIC_WRITE,
                   (DWORD) 0,
                    NULL,
                   CREATE_ALWAYS,
                   FILE_ATTRIBUTE_NORMAL,
                   (HANDLE) NULL);
    if (hf == INVALID_HANDLE_VALUE)
        errhandler("CreateFile", hwnd);
    hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"
    // Compute the size of the entire file.
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) +
                 pbih->biSize + pbih->biClrUsed
                 * sizeof(RGBQUAD) + pbih->biSizeImage);
    hdr.bfReserved1 = 0;
    hdr.bfReserved2 = 0;

    // Compute the offset to the array of color indices.
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
                    pbih->biSize + pbih->biClrUsed
                    * sizeof (RGBQUAD);

    // Copy the BITMAPFILEHEADER into the .BMP file.
    if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER),
        (LPDWORD) &dwTmp,  NULL))
    {
       errhandler("WriteFile", hwnd);
    }

    // Copy the BITMAPINFOHEADER and RGBQUAD array into the file.
    if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER)
                  + pbih->biClrUsed * sizeof (RGBQUAD),
                  (LPDWORD) &dwTmp, ( NULL)))
        errhandler("WriteFile", hwnd);

    // Copy the array of color indices into the .BMP file.
    dwTotal = cb = pbih->biSizeImage;
    hp = lpBits;
    if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL))
           errhandler("WriteFile", hwnd);

    // Close the .BMP file.
     if (!CloseHandle(hf))
           errhandler("CloseHandle", hwnd);

    // Free memory.
    GlobalFree((HGLOBAL)lpBits);
}
BOOL SaveToFile(HBITMAP hBitmap, LPCTSTR lpszFileName){
  HDC hDC;

  int iBits;

  WORD wBitCount;

  DWORD dwPaletteSize=0, dwBmBitsSize=0, dwDIBSize=0, dwWritten=0;

  BITMAP Bitmap;

  BITMAPFILEHEADER bmfHdr;

  BITMAPINFOHEADER bi;

  LPBITMAPINFOHEADER lpbi;

  HANDLE fh, hDib, hPal,hOldPal=NULL;

  hDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
  iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
  DeleteDC(hDC);
  if (iBits <= 1)
    wBitCount = 1;
  else if (iBits <= 4)
    wBitCount = 4;
  else if (iBits <= 8)
    wBitCount = 8;
  else
    wBitCount = 24;
  GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
  bi.biSize = sizeof(BITMAPINFOHEADER);
  bi.biWidth = Bitmap.bmWidth;
  bi.biHeight = Bitmap.bmHeight;
  bi.biPlanes = 1;
  bi.biBitCount = wBitCount;
  bi.biCompression = BI_RGB;
  bi.biSizeImage = 0;
  bi.biXPelsPerMeter = 0;
  bi.biYPelsPerMeter = 0;
  bi.biClrImportant = 0;
  bi.biClrUsed = 0;
  dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;

  hDib = GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
  lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
  *lpbi = bi;

  hPal = GetStockObject(DEFAULT_PALETTE);
  if (hPal)
  {
    hDC = GetDC(NULL);
    hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
    RealizePalette(hDC);
  }


  GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)
    +dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);

  if (hOldPal)
  {
    SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
    RealizePalette(hDC);
    ReleaseDC(NULL, hDC);
  }

  fh = CreateFile(lpszFileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS,
    FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

  if (fh == INVALID_HANDLE_VALUE)
    return FALSE;

  bmfHdr.bfType = 0x4D42; // "BM"
  dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
  bmfHdr.bfSize = dwDIBSize;
  bmfHdr.bfReserved1 = 0;
  bmfHdr.bfReserved2 = 0;
  bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

  WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

  WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
  GlobalUnlock(hDib);
  GlobalFree(hDib);
  CloseHandle(fh);
  return TRUE;
}
void CPaintBuffer::saveToFile(wchar_t *_fileName){
    HBITMAP bitmap=(HBITMAP)GetCurrentObject(memDC,OBJ_BITMAP);
    CreateBMPFile(hwnd,_fileName,CreateBitmapInfoStruct(hwnd,bitmap),bitmap,memDC);
}
void CPaintBuffer::loadFromFile(wchar_t *_fileName){
    HBITMAP image =( HBITMAP ) LoadImage( NULL, _fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
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

    HBITMAP image =( HBITMAP ) LoadImage( NULL, _fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

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
