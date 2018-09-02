/*********************************************************************
*   2017-06-28
*   2017-07-03  色情報列挙体追加
*   Yuki Ando
*********************************************************************/
#ifndef HSV_H_
#define HSV_H_

#include "ev3api.h"
#include "ColorSensor.h"

class HSV : public ev3api::ColorSensor {    // ライブラリのカラーセンサーを継承
private:
    double R, G, B;                         //　正規化されたRGB値
    double max;                             // HSV最大値
    double min;                             // HSV最小値
    int h, s, v;                            // HSV 色判定用 360° 100%

    struct hsv_value_t {                    //　HSV格納用構造体
        double h;                           // 0   - 360            Hue(色相)
        double s;                           // 0.0 - 1.0 (0 - 100)  Saturation(彩度)
        double v;                           // 0.0 - 1.0 (0 - 100)  Value(明度)
    };
    
    int colorid;
    enum color_num {                        // 色情報用列挙体 白、黒、赤、緑、青、黄、木、灰、異常
        WHITE = 0, BLACK = 1, RED = 2, GREEN = 3, BLUE = 4, YELLOW = 5, WOOD = 6, GRAY = 7, ERROR = 8,
    } color;                                //　色情報格納場所
    rgb_raw_t rgb_val;                      //　ev3api::RGB Raw値を格納する構造体
    hsv_value_t hsv_val;                    //　HSV格納場所

    // LCD表示用
    char rgb_r[20], rgb_g[20], rgb_b[20], hsv_h[20], hsv_s[20], hsv_v[20] ,cut[20];

    int count;

public:
    HSV(ePortS);                            // コンストラクタ カラーセンサーポートを指定
    int GetRAW_R(void){return rgb_val.r;};  // R RAW値を返す
    int GetRAW_G(void){return rgb_val.g;};  // G RAW値を返す
    int GetRAW_B(void){return rgb_val.b;};  // B RAW値を返す
    int GetNor_R(void){return R;};          // R 正規化値を返す
    int GetNor_G(void){return G;};          // G 正規化値を返す
    int GetNor_B(void){return B;};          // B 正規化値を返す
    int GetHue(void){return h;};            // 色相を返す
    int GetSaturation(void){return s;};     // 彩度を返す
    int GetValue(void){return v;};          // 明度を返す
    int GetColorNumber(void){return color;};// 色番号を返す
    void Convert(int mode, bool flag_NEO);  // HSV変換
    void Disp(void);                        // LCD表示
};

#endif

/*  カラーセンサーで識別できるカラーの番号 EV3API
    enum colorid_t {
        COLOR_NONE = 0,
        COLOR_BLACK = 1,
        COLOR_BLUE = 2,
        COLOR_GREEN = 3,
        COLOR_YELLOW = 4,
        COLOR_RED = 5,
        COLOR_WHITE = 6,
        COLOR_BROWN = 7,
        TNUM_COLOR
    }
*/
