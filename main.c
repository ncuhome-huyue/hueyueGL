//先开个坑
//svpng.inc 来自Milo大佬
#include <iostream>
#include <cstring>
#include <math.h>
#include "svpng.inc"

#define Width 512
#define Height 512
static unsigned char img[Width * Height * 3];

void setpixel(int x, int y) {
    unsigned char* p = img + ((Height - y) * Width + x) * 3;
    p[0] = p[1] = p[2] = 0;
}

void draw(int x1,int y1,int x2,int y2){
    int x,y,xA,yA;
    if (y1>y2){
        yA=y1-y2;xA=x1-x2;
    } else{
        yA=y2-y1;xA=x2-x1;
    }
    int F=x=y=0;
    int n=abs(xA)+abs(yA);
    for (int i = 0; i < n; ++i) {
        if (xA>0){
            if (F>=0){x++;F-=yA;}
            else{y++;F+=xA;}
        } else{
            if (F>0){y++;F-=xA;}
            else{x--;F+=yA;}
        }
        if (y1>y2){
            setpixel(x+x2,y+y2);
        } else{
            setpixel(x+x1,y+y1);
        }
    }

}

void drawTrangle(int x1,int y1,int x2,int y2,int x3,int y3){
    int yUp,yDown;
    if (x1>x2){int temp=x1;x1=x2;x2=temp;temp=y1;y1=y2;y2=temp;}
    if (x2>x3){int temp=x2;x2=x3;x3=temp;temp=y2;y2=y3;y3=temp;}
    if (x1>x2){int temp=x1;x1=x2;x2=temp;temp=y1;y1=y2;y2=temp;}
    int n1=x2-x1,n2=x3-x2;
    yUp=y1;yDown=y1;
    int F1=0,F2=0,xA1=x3-x1,yA1=y3-y1,xA2=x2-x1,yA2=y2-y1;
    for (int i = 0; i < n1; ++i) {
        while (true){
            if (yA1>0){
                if (F1>=0){F1-=yA1;break;}
                else{yUp++;F1+=xA1;}
            } else{
                if (F1<=0){F1-=yA1;break;}
                else{yUp--;F1-=xA1;}
            }
        }
        while (true){
            if (yA2>0){
                if (F2>=0){F2-=yA2;break;}
                else{yDown++;F2+=xA2;}
            } else{
                if (F2<=0){F2-=yA2;break;}
                else{yDown--;F2-=xA2;}
            }
        }
        if (yDown>yUp)for (int j = yUp; j <= yDown; ++j)setpixel(x1+i,j);
        else for (int j = yDown; j <= yUp; ++j) setpixel(x1+i,j);
    }
    F1=0;F2=0;
    xA2=x3-x2;yA2=y3-y2;
    for (int i = 0; i <= n2; ++i) {
        while (true){
            if (yA1>0){
                if (F1>=0){F1-=yA1;break;}
                else{yUp++;F1+=xA1;}
            } else{
                if (F1<=0){F1-=yA1;break;}
                else{yUp--;F1-=xA1;}
            }
        }
        while (true){
            if (yA2>0){
                if (F2>=0){F2-=yA2;break;}
                else{yDown++;F2+=xA2;}
            } else{
                if (F2<=0){F2-=yA2;break;}
                else{yDown--;F2-=xA2;}
            }
        }
        if (yDown>yUp)for (int j = yUp; j <= yDown; ++j)setpixel(x2+i,j);
        else for (int j = yDown; j <= yUp; ++j) setpixel(x2+i,j);
    }
}


int main(){
    memset(img, 255, sizeof(img));
    drawTrangle(200,300,100,400,0,0);
    svpng(fopen("line_bresenham.png", "wb"), Width, Height, img, 0);
}
