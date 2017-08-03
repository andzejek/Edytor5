#include <math.h>

///from wikipedia abs->fabs mod->fmod
COLORREF HSLtoRGB(float H,float S,float L)
{
    float C=(1.0f-fabs(2*L-1.0f))*S;
    float X=C*(1.0f-fabs(fmod(H/60.0f,2)-1.0f));
    float m=L-C/2.0f;
    float pR=0,pG=0,pB=0;
    if     (H>=0&&H<=60)     {pR=C;pG=X;pB=0;}
    else if(H>=60&&H<=120)   {pR=X;pG=C;pB=0;}
    else if(H>=120&&H<=180)  {pR=0;pG=C;pB=X;}
    else if(H>=180&&H<=240)  {pR=0;pG=X;pB=C;}
    else if(H>=240&&H<=300)  {pR=X;pG=0;pB=C;}
    else if(H>=300&&H<=360)  {pR=C;pG=0;pB=X;}
    return RGB((pR+m)*255.0f,(pG+m)*255.0f,(pB+m)*255.0f);
}
int HSLtoBGR(float H,float S,float L)
{
    float C=(1.0f-fabs(2*L-1.0f))*S;
    float X=C*(1.0f-fabs(fmod(H/60.0f,2)-1.0f));
    float m=L-C/2.0f;
    float pR=0,pG=0,pB=0;
    if     (H>=0&&H<=60)     {pR=C;pG=X;pB=0;}
    else if(H>=60&&H<=120)   {pR=X;pG=C;pB=0;}
    else if(H>=120&&H<=180)  {pR=0;pG=C;pB=X;}
    else if(H>=180&&H<=240)  {pR=0;pG=X;pB=C;}
    else if(H>=240&&H<=300)  {pR=X;pG=0;pB=C;}
    else if(H>=300&&H<=360)  {pR=C;pG=0;pB=X;}
    return RGB((pB+m)*255.0f,(pG+m)*255.0f,(pR+m)*255.0f);
}

