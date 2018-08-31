#include "Scenario.h"
using namespace ev3api;
extern Result result[10];
extern int wait_event(void);
//extern	EvLog*	elog;


Scenario::Scenario(RunPattern* runP, RoboLoc* rloc, Block_area* barea)
	: mRP(runP), mRloc(rloc), mBArea(barea) {
        block_ptn = 5;
}

void Scenario::R(){
    // タイム計測
    // mRP->setStartTime();
    // Rコー
    // スタート
    mRP->set_pid_params(0.0, 0.01, 0.0);    
    mRP->run_pid(0, 30, 50);
	// 直進1
	mRP->set_pid_params(1.0, 0.03, 0.09); //(1.4, 0.01, 0.05)
    mRP->run_pid(0, 60, 2000);
    ev3_speaker_play_tone(NOTE_A4, 300);
    // カーブ1
    mRP->set_pid_params(1.6, 0.03, 0.15);
    mRP->run_pid(0, 55, 1820);
    ev3_speaker_play_tone(NOTE_A4, 300);
    //直進2
    mRP->set_pid_params(1.0, 0.03, 0.09); //1.3, 0.01, 0.05
    mRP->run_pid(0, 55, 450);
    ev3_speaker_play_tone(NOTE_A4, 300);
    // カーブ2
    mRP->set_pid_params(1.6, 0.03, 0.13);
    mRP->run_pid(0, 45, 550);
    ev3_speaker_play_tone(NOTE_A4, 300);
    //カーブ3
    mRP->set_pid_params(2.05, 0.03, 0.13);
    mRP->run_pid(0, 45, 650);
    ev3_speaker_play_tone(NOTE_A4, 300);
    //直進3
    mRP->set_pid_params(1.0, 0.03, 0.075); //1.3, 0.01, 0.
    mRP->run_pid(0, 50, 700);
    ev3_speaker_play_tone(NOTE_A4, 300);
    // カーブ4
    //mRP->reset_pid_params();
    mRP->set_pid_params(1.8, 0.03, 0.13);
    mRP->run_pid(0, 45, 1200);
    ev3_speaker_play_tone(NOTE_A4, 300);
    //直進4
    mRP->set_pid_params(1.0, 0.03, 0.075); //1.3, 0.01, 0.05
    mRP->run_pid(0, 50, 2700);
    ev3_speaker_play_tone(NOTE_A4, 300);
    mRP->set_pid_params(1.0, 0.03, 0.075); //1.3, 0.01, 0.05
    mRP->run_pid(0, 40, 500);
	// 直進2
    //mRP->reset_pid_params();
    //mRP->set_pid_params(2.2, 1.8, 0.05);
    //mRP->run_pid(1, 80, 1500);
	//mRP->set_pid_params(0.6, 0.1, 0.05);
	//mRP->run_pid(0, 61, 1500);// 60, 1300
    //試走会にて200mmオーバー
    //mRP->move(30, 2, 100);
    //灰色
    //mRP->set_pid_params(0.0, 0.0, 0.0);
    //mRP->run_pid(0, 35, 200);
    //エッジ切り替え1,40
    //mRP->run_pid(1, 20, 100);

    
    //Reset PID
    //mRP->reset_pid_params();
    //mRP->set_pid_params(0.6, 0.1, 0.1);
    //mRP->run_pid(1, 30, 100);
    
}

void Scenario::L(){
    //b_area->test2(gBT->get_bt());
	// Lコース
	// スタート
    //mRP->TurnR(90);


	mRP->set_pid_params(0.0, 0.01, 0.0);    
    mRP->run_pid(0, 30, 50);
    // 直進1
    mRP->set_pid_params(1.05, 0.1, 0.15); //2.4, 0.1, 0.09
    mRP->run_pid(0, 65, 200);    
    mRP->set_pid_params(1.05, 0.1, 0.15); //2.4, 0.1, 0.09
    mRP->run_pid(0, 75, 2000);//75
    // 第１コーナー
    mRP->set_pid_params(2, 0.01, 0.1);//2.16
    mRP->run_pid(0, 65, 1800);
        // 直進2
    mRP->set_pid_params(1.1, 0.05, 0.12);//2.13
    mRP->run_pid(0, 65, 1600);
    mRP->set_pid_params(1.0, 0.08, 0.09);
    mRP->run_pid(0, 45, 150);   //速度余裕有
    ev3_speaker_play_tone(NOTE_AS4, 300);
    // 第2コーナー
    mRP->set_pid_params(1.8, 0.0, 0.1);
    mRP->run_pid(0, 40, 600);
    // 直進3
    mRP->set_pid_params(1.0, 0.1, 0.09);
    mRP->run_pid(0, 40, 650);
    ev3_speaker_play_tone(NOTE_AS4, 300);
    // 第3コーナー Ｄの値０．０６元の Ｉの下の値０．０５
    mRP->set_pid_params(1.93, 0.1, 0.09);
    mRP->run_pid(0, 40, 750);
        // 直進4
    mRP->set_pid_params(1.05, 0.1, 0.09);
    mRP->run_pid(0, 50, 200);
    mRP->set_pid_params(1.0, 0.1, 0.09);
    mRP->run_pid(0, 60, 2150);
    ev3_speaker_play_tone(NOTE_AS4, 300);
        //ゴール後
    mRP->set_pid_params(2.13, 0.0, 0.11);
    mRP->run_pid(0, 50, 650);
}

void Scenario::RGB2HSV(void){
    int color;
    mRP->SetArmAngle(30, 45);
    color = mRP->RGB2HSV();

    switch(color) {
        case 0:;
        case 1:;
        case 2:;
        case 3:;
        case 4:;
        case 5:;
        case 6:;
        default:;
    }
}

void Scenario::TEST(void){
    // mRP->SetArmAngle(80, -20); //-20
    // mRP->set_pid_params(0.4, 0.15, 0.006);
    // mRP->ColorDetect(0);
    // mRP->Turn(-30);
    // mRP->ColorDetect(0);
    // mRP->Turn(-90);
    // mRP->ColorDetect(0);
    // mRP->Turn(-30);
    // mRP->ColorDetect(0);
    // mRP->Turn(-60);
    // mRP->ColorDetect(0);
    // mRP->Turn(-120);
    // mRP->ColorDetect(0);
    // mRP->Turn(-60);
    // while(1){
    // mRP->ColorDetect(0);
    // mRP->Turn(-120);
    // mRP->ColorDetect(0);
    // mRP->Turn(-60);
    //mRP->flag_NEO = true;
    //mRP->eyesight(30);
    mRP->set_pid_params(0.00, 0.02, 0.0);
    mRP->run_pid(0, 30, 50);

    mRP->set_pid_params(2.25, 0.03, 0.12);
    mRP->run_pid(0, 75, 2000);
    ev3_speaker_play_tone(NOTE_A4, 300);
    //カーブ１
    mRP->set_pid_params(3.1, 0.03, 0.103);
    mRP->run_pid(0, 70, 450);
    //直進２
    mRP->set_pid_params(2.5, 0.03, 0.1);
    mRP->run_pid(2.5, 0.03, 0.1);
    //カーブ２
    mRP->set_pid_params(1.6, 0.03, 0.13);
    mRP->run_pid(0, 65, 550);
    //カーブ３
    mRP->set_pid_params(2.15, 0.03, 0.13);
    mRP->run_pid(0, 65, 650);
    //直進３
    mRP->set_pid_params(1.5, 0.01, 0.05);
    mRP->run_pid(0, 70, 700);
    ev3_speaker_play_tone(NOTE_A4, 300);
    //カーブ４
    mRP->set_pid_params(2.15, 0.03, 0.13);
    mRP->run_pid(0, 65, 1200);
    ev3_speaker_play_tone(NOTE_A4, 300);
    //直進４
    mRP->set_pid_params(1.45, 0.01, 0.08);
    mRP->run_pid(0, 70, 2700);
    ev3_speaker_play_tone(NOTE_A4, 300);
    //mRP->KenShow();
    // mRP->move(40, 0, 300);
    // mRP->SetArmAngle(30, -25);
}


void Scenario::DoPuzzle(){
    mRP->reset_pid_params();
    // パズル侵入
    mRP->set_pid_params(1., 1.7, 0.01);
    mRP->SetArmAngle(80, -20); //-20
    mRP->ColorDetect(0);
    mRP->move(-20, 0, 120);
    mRP->reset_pid_params();
    mRP->set_pid_params(0.4, 0.15, 0.006);


    //入口選択
//    block_ptn = mBArea->select(10000);
    block_ptn = mBArea->select();

    //配列の2番目から入るリングを取得
    if (result[block_ptn].orders[1] == 10){
        mRP->ColorDetect(0);
    } else {
        mRP->TurnR(30);
        mRP->LineDetect(1);
        mRP->ColorDetect(0);

    }

    //ここからパズル（予定
    //Block()が実際に動作し、並べ終わった後
    //ゴールエリアまでの距離を返す(int)
    int goalDist = Block();

    if(goalDist != 0){
	    //黒線を探しブロックエリアから脱出
	    mRP->LineDetect(0);

	    //PIDを使い、車庫前まで移動
	    mRP->set_pid_params(1.8, 0.34, 0.1);    //1.5, 0.24, 0.1
	    mRP->run_pid(16, 40, goalDist);

	    mRP->Chusya();
	}
}

int Scenario::Block(void){
    //mRP->SetArmAngle(30, -30);  //pwm, angle 30 -20
    //mRP->set_pid_params(0.4, 0.1, 0.0);   //0.4 0.1 0
    //mRP->ColorDetect(0);
    //mRP->Turn(-90);
    int i = 3;
    char time[30];
    // iは3づつ増える
    // orders[0]には全体の長さの３の倍数になってる
    while (i < result[block_ptn].orders[0] - 3){
        switch(result[block_ptn].orders[i]){
            case 110:   //TURN
                ev3_speaker_play_tone(NOTE_AS4, 300);
                sprintf(time,"Turn :%3d :%2d", result[block_ptn].orders[i + 1], result[block_ptn].orders[i + 2]);
                ev3_lcd_draw_string(time,0,60);
                mRP->Turn(result[block_ptn].orders[i + 1]);
                break;
            case 111:   //TURN_BLOCK
                ev3_speaker_play_tone(NOTE_D5, 300);
                sprintf(time,"Turn_B :%3d :%2d", result[block_ptn].orders[i + 1], result[block_ptn].orders[i + 2]);
                ev3_lcd_draw_string(time,0,60);
                mRP->TurnWithBlock(result[block_ptn].orders[i + 1]);
                break;
            case 112:   //FORWARD
                ev3_speaker_play_tone(NOTE_F5, 300);
                sprintf(time,"Forward :%3d :%2d", result[block_ptn].orders[i + 1], result[block_ptn].orders[i + 2]);
                ev3_lcd_draw_string(time,0,60);
                mRP->ColorDetect(0);
                break;
            case 113:   //FORWARD_BLOCK
                ev3_speaker_play_tone(NOTE_A5, 300);
                sprintf(time,"Forward_B :%3d :%2d", result[block_ptn].orders[i + 1], result[block_ptn].orders[i + 2]);
                ev3_lcd_draw_string(time,0,60);
                if (result[block_ptn].orders[i + 2])
                    mRP->ColorDetect(0);
                else
                    mRP->move(22, -2, 230);
                break;
            case 114:   //RELEASE
                ev3_speaker_play_tone(NOTE_C6, 300);
                sprintf(time,"Release :%3d :%2d", result[block_ptn].orders[i + 1], result[block_ptn].orders[i + 2]);
                ev3_lcd_draw_string(time,0,60);
                (result[block_ptn].orders[i + 2]) ? mRP->Release(0) : mRP->Release(1);
                break;
            default:    //END
                ev3_speaker_play_tone(NOTE_B6, 300);
                sprintf(time,"ERROR! :%3d :%2d", result[block_ptn].orders[i + 1], result[block_ptn].orders[i + 2]);
                ev3_lcd_draw_string(time,0,60);
                break;
        }
        i = i + 3;
        if (wait_event())   ext_tsk();
    }

    if (result[block_ptn].orders[i] == 120){
    		return 0;
    } else if(result[block_ptn].orders[i+1] > 300){ //298 or 317
        return 450;
    } else {
        return 560;
    } 
}

void Scenario::L_SHORT(){
    //b_area->test2(gBT->get_bt());
    // Lコース
    // スタート
    //mRP->TurnR(90);
    mRP->SetArmAngle(30, -30);  //pwm, angle
    mRP->set_pid_params(0.6, 0.1, 0.05);

    mRP->ShortCut();
    DoPuzzle();
}

void Scenario::RRP(){
    // タイム計測
    mRP->setStartTime();
    // Rコース相撲限定
    // スタート
    mRP->set_pid_params(0.0, 0.02, 0.0);
    mRP->run_pid(1, 40, 50);

    //ゴール直後
    mRP->set_pid_params(1.5, 0.02, 0.10);
    mRP->run_pid(1, 40, 150);
    ev3_speaker_play_tone(NOTE_A4, 300);//灰色直前

    //灰色をよけるために右にずれる
    mRP->move(30, 1, 200);
    
    //第三カーブ
    mRP->set_pid_params(2.4, 0.0, 0.1);
    mRP->run_pid(1, 40, 1300);
    mRP->set_pid_params(0.5, 0.05, 0.1);


    // ET相撲NEO
    mRP->flag_NEO = true;

    mRP->eyesight(30);
    mRP->AcrossTheLine(0, 258);
    mRP->TurnR90();

    // 1
    switch (mRP->RingDetect()) {
        case 0: // 押出
            mRP->move(30, 0, 100);
            mRP->move(-30, 1.95, 150);
            mRP->TurnR180();
            break;
        case 1: // ブロックの色を読まず押出
            mRP->move(30, 0, 87);
            mRP->move(-30, 1.95, 160);
            mRP->TurnR180();
            break;
        case 2: // ブロックの色を読まず寄切
        default:// 寄切
            mRP->SetTailAngle(60, -135);
            mRP->TurnR180();
            mRP->move(30, 0.5, 30);
            mRP->SetTailAngle(60, 135);
            break;
    }
    // 2
    switch (mRP->RingDetect()) {
        case 0: // 押出
            mRP->move(30, 0, 100);
            mRP->move(-30, 0, 175);
            mRP->TurnR90();
            break;
        case 1: // ブロックの色を読まず押出
            mRP->move(30, 0, 90);
            mRP->move(-30, 0, 175);
            mRP->TurnR90();
            break;
        case 2: // ブロックの色を読まず寄切
        default:// 寄切
            mRP->move(30, 0, 10);
            mRP->TurnL180();
            mRP->move(30, 0, 95);
            mRP->TurnL80();
            break;
    }

    mRP->run_pid(4, 35, 284);
    mRP->TurnR90();

    // 3
    switch (mRP->RingDetect()) {
        case 0: // 押出
            mRP->move(30, 0, 100);
            mRP->move(-30, 0.0, 150);
            mRP->TurnL180();
            break;
        case 1: // ブロックの色を読まず押出
            mRP->move(30, 0, 90);
            mRP->move(-30, 1.8, 160);
            mRP->TurnL180();
            break;
        case 2: // ブロックの色を読まず寄切
        default:// 寄切
            mRP->SetTailAngle(60, 180);
            mRP->TurnL180();
            mRP->move(30, 2.2, 30);
            mRP->SetTailAngle(60, -180);
            break;
    }
    // 4
    switch (mRP->RingDetect()) {
        case 0: // 押出
            mRP->move(30, 0, 100);
            mRP->move(-30, 0, 180);
            mRP->TurnR90();
            mRP->move(-10, -0.2, 15);
            break;
        case 1: // ブロックの色を読まず押出
            mRP->move(30, 0, 90);
            mRP->move(-30, 0, 190);
            mRP->TurnR90();
            mRP->move(-10, -0.2, 15);
            break;
        case 2: // ブロックの色を読まず寄切
        default:// 寄切
            mRP->SetTailAngle(60, -135);
            mRP->TurnR180();
            mRP->move(30, 0, 90);
            mRP->TurnL90();
            mRP->move(-10,-0.2, 15);
            mRP->SetTailAngle(60, 135);
            break;
    }

    // 線路跨ぎ
    mRP->eyesight(30);
    mRP->AcrossTheLine(1, 260);
    mRP->TurnR90();

    // 5
    switch (mRP->RingDetect()) {
        case 0: // 押出
            mRP->move(30, 0, 100);
            mRP->move(-30, 1.95, 155);
            mRP->TurnR180();
            break;
        case 1: // ブロックの色を読まず押出
            mRP->move(30, 0, 90);
            mRP->move(-30, 1.95, 165);
            mRP->TurnR180();
            break;
        case 2: // ブロックの色を読まず寄切
        default:// 寄切
            mRP->SetTailAngle(60, -135);
            mRP->TurnR180();
            mRP->move(30, -1.5, 35);
            mRP->SetTailAngle(60, 135);
            break;
    }
    // 6
    switch (mRP->RingDetect()) {
        case 0: // 押出
            mRP->move(30, 0, 100);
            mRP->move(-30, 0, 175);
            mRP->TurnR90();
            break;
        case 1: // ブロックの色を読まず押出
            mRP->move(30, 0, 90);
            mRP->move(-30, 0, 175);
            mRP->TurnR90();
            break;
        case 2: // ブロックの色を読まず寄切
        default:// 寄切
            mRP->move(30, 0, 10);
            mRP->TurnL180();
            mRP->move(30, 0, 95);
            mRP->TurnL80();
            break;
    }

    mRP->run_pid(4, 35, 284);
    mRP->TurnR90();

    // 7
    switch (mRP->RingDetect()) {
        case 0: // 押出
            mRP->move(30, 0, 100);
            mRP->move(-30, 0, 150);
            mRP->TurnL180();
            break;
        case 1: // ブロックの色を読まず押出
            mRP->move(30, 0, 80);
            mRP->move(-30, 1.8, 150);
            mRP->TurnL180();
            break;
        case 2: // ブロックの色を読まず寄切
        default:// 寄切
            mRP->SetTailAngle(60, 180);
            mRP->TurnL180();
            mRP->move(30, 2.2, 30);
            mRP->SetTailAngle(60, -180);
            break;
    }
    // 8
    switch (mRP->RingDetect()) {
        case 0: // 押出
            mRP->move(30, 0, 100);
            mRP->move(-30, 0, 180);
            mRP->TurnR90();
            mRP->move(-10, -1.0, 35);
            break;
        case 1: // ブロックの色を読まず押出
            mRP->move(30, 0, 95);
            mRP->move(-30, 0, 175);
            mRP->TurnR90();
            mRP->move(-10, -1.0, 35);
            break;
        case 2: // ブロックの色を読まず寄切
        default:// 寄切
            mRP->SetTailAngle(60, -135);
            mRP->TurnR180();
            mRP->move(30, 0, 100);
            mRP->TurnL90();
            mRP->move(-10, 1.5, 10);
            mRP->SetTailAngle(60, 135);
            break;
    }

    // 懸賞
    mRP->reset_pid_params();
    mRP->KenShow();

    //mRP->eyesight(30);
    //mRP->AcrossTheLine(2, 100);

    mRP->flag_NEO = false;
    mRP->reset_pid_params();
    mRP->run_pid(0, 30, 200);
    mRP->run_pid(0, 45, 300);
    mRP->TurnR(85);
    mRP->run_pid(1, 45, 470);
    mRP->banzai();
}