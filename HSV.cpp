/*********************************************************************
*   2017-06-28
*   2017-07-11  転倒判定追加
*   Yuki Ando
*********************************************************************/
#include "HSV.h"

HSV::HSV(ePortS port) : ev3api::ColorSensor(port) {
    max = 0; min = 0; count = 0; color = WHITE, colorid = 0;
}

void HSV::Convert(int mode, bool flag_NEO) {
    // 反射光の強さ
    // v = this->getBrightness();

    // カラー番号（API）取得
    // colorid = this->getColorNumber();

    // 生の値取得
    this->getRawColor(rgb_val);

    // 正規化されたRGB値(0.0-1.0)
    R = rgb_val.r / 1023.0;
    G = rgb_val.g / 1023.0;
    B = rgb_val.b / 1023.0;
    // R = rgb_val.r / 511.0;
    // G = rgb_val.g / 511.0;
    // B = rgb_val.b / 511.0;

    // 最大値・最小値
    if (R >= G && R >= B) {
        max = R;
        min = (G < B) ? G : B;
    } else if (G >= R && G >= B) {
        max = G;
        min = (R < B) ? R : B;
    } else {
        max = B;
        min = (R < G) ? R : G;
    }

    // Hue(色相)
    if (max == R) {
        hsv_val.h = 60 * (G - B) / (max - min);
    } else if (max == G){
        hsv_val.h = 60 * (B - R) / (max - min) + 120;
    } else {
        hsv_val.h = 60 * (R - G) / (max - min) + 240;
    }
    if (hsv_val.h < 0.0) {
        hsv_val.h += 360.0;
    }

    // Saturation(彩度) 円柱モデル　
    hsv_val.s = ((max - min) / max);

    // Saturation(彩度) 円錐モデル　
    // hsv_val.s = max - min;

    // Value(明度)
    hsv_val.v = max;

    // 色判定用
    h = ((int)hsv_val.h) % 360;
    s = (int)(hsv_val.s * 100);
    v = (int)(hsv_val.v * 100);

    if(mode == 0){
        // R色判定
        if ((h > 350 || h < 10) && s > 70) color = RED;
        else if (h > 330 || h < 70){
            if (s > 75) color = YELLOW;
            else        color = WOOD;
        }
        else if (R + G < B) color = BLUE;
        else if (R + B < G) color = GREEN;

        else if (v < 10)    color = BLACK;
        else if (v > 20)    color = WHITE;
        else                color = GRAY;
    }
    else{
        // モデル色判定
        if (v < 10)    color = BLACK;
        else{
            if (s < 35) color = WHITE;
            else if (s < 45 && v < 40)    color = GRAY; //v25
            else{
                if (h > 330 || h < 30)    color = RED;
                else if (h < 80){
                    if (s > 65) color = YELLOW;
                    else        color = WOOD;
                }
                else if (h < 170) color = GREEN;
                else color = BLUE;
            }
        }
    }

    // // 旧色判定
    // if(v <= 6)
    //     color = BLACK;
    // else if (h >= 320 || h <= 15)
    //     color = RED;
    // else if (h >= 170){
    //     if (s > 60)
    //         color = BLUE;
    //     else if (s > 30 )
    //         color = GRAY;
    //     else
    //         color = WHITE;
    // }
    // else if (h >= 90)
    //      color = GREEN;
    // else {
    //     if (s > 60)
    //         color = YELLOW;
    //     else
    //         color = WOOD;
    // }

    // 転倒判定
    // if (s == 100 && v == 0)
    //     count++;
    // else {
    //     if (count > 0) count--;
    // }

    // if (count > 1000 && !flag_NEO && mode != 2)
    //     color = ERROR;

    // 色測定用
    if (++count > 4000)
        color = ERROR;
}

void HSV::Disp(void){
    // LCD表示
    sprintf(cut,"Count:%3d",count);

    sprintf(rgb_r,"R:%3d ",rgb_val.r);
    sprintf(rgb_g,"G:%3d ",rgb_val.g);
    sprintf(rgb_b,"B:%3d ",rgb_val.b);

    ev3_lcd_draw_string(cut,80,0);
    ev3_lcd_draw_string(rgb_r,0,0);
    ev3_lcd_draw_string(rgb_g,0,20);
    ev3_lcd_draw_string(rgb_b,0,40);

    sprintf(hsv_h,"H:%3d ",h);
    sprintf(hsv_s,"S:%f->%2d%% ",hsv_val.s, s);
    sprintf(hsv_v,"V:%f->%2d%% ",hsv_val.v, v);
    // sprintf(hsv_v,"V:%d        ",v);

    ev3_lcd_draw_string(hsv_h,0,70);
    ev3_lcd_draw_string(hsv_s,0,90);
    ev3_lcd_draw_string(hsv_v,0,110);

    switch(color){
        case 0: ev3_lcd_draw_string("WHITE ",100,60);break;
        case 1: ev3_lcd_draw_string("BLACK ",100,60);break;
        case 2: ev3_lcd_draw_string("RED   ",100,60);break;
        case 3: ev3_lcd_draw_string("GREEN ",100,60);break;
        case 4: ev3_lcd_draw_string("BLUE  ",100,60);break;
        case 5: ev3_lcd_draw_string("YELLOW",100,60);break;
        case 6: ev3_lcd_draw_string("WOOD  ",100,60);break;
        case 7: ev3_lcd_draw_string("GRAY  ",100,60);break;
        default:ev3_lcd_draw_string("ERROR ",100,60);
    }

    switch(colorid){
        case 1: ev3_lcd_draw_string("BLACK ",100,40);break;
        case 2: ev3_lcd_draw_string("BLUE  ",100,40);break;
        case 3: ev3_lcd_draw_string("GREEN ",100,40);break;
        case 4: ev3_lcd_draw_string("YELLOW",100,40);break;
        case 5: ev3_lcd_draw_string("RED   ",100,40);break;
        case 6: ev3_lcd_draw_string("WHITE ",100,40);break;
        case 7: ev3_lcd_draw_string("BROWN ",100,40);break;
        default:ev3_lcd_draw_string("NONE  ",100,40);
    }
}