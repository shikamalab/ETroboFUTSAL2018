#include "Scenario.h"
#include "stdio.h"
using namespace ev3api;

extern int selected_result;
extern Result result[24];

extern int wait_event(void);
//extern	EvLog*	elog;


Scenario::Scenario(RunPattern* runP, RoboLoc* rloc, Block_area* barea)
	: mRP(runP), mRloc(rloc), mBArea(barea) {
        block_ptn = 5;
}

void Scenario::R(){
    // タイム計測
    mRP->setStartTime();
    // Rコース(未完成)
    // スタート
    mRP->set_pid_params(0.00, 0.01, 0.0);
    mRP->run_pid(0, 30, 50);

    // for CS
    // // 直進1
    mRP->set_pid_params(1.0, 0.03, 0.09);
    mRP->run_pid(0, 60, 2000);
    ev3_speaker_play_tone(NOTE_A4, 300);
    // カーブ1
    mRP->set_pid_params(1.74, 0.01, 0.15);
    mRP->run_pid(0, 55, 1840);
    ev3_speaker_play_tone(NOTE_A4, 300);
    // 直進2
    mRP->set_pid_params(1.0, 0.03, 0.09);
    mRP->run_pid(0, 55, 450);
    ev3_speaker_play_tone(NOTE_A4, 300);
    // カーブ2
    mRP->set_pid_params(1.6, 0.03, 0.13);
    mRP->run_pid(0, 45, 550);
    // カーブ3
    mRP->set_pid_params(2.3, 0.03, 0.10);
    mRP->run_pid(0, 45, 650);
    ev3_speaker_play_tone(NOTE_A4, 300);
    // 直進3
    mRP->set_pid_params(1.0, 0.03, 0.075);
    mRP->run_pid(0, 50, 700);
    ev3_speaker_play_tone(NOTE_A4, 300);
    // カーブ4
    mRP->set_pid_params(1.75, 0.03, 0.13);
    mRP->run_pid(0, 45, 1200);
    // 直進4
    mRP->set_pid_params(1.0, 0.03, 0.09);
    mRP->run_pid(0, 50, 2570);
    ev3_speaker_play_tone(NOTE_A4, 300);
    mRP->set_pid_params(0.9, 0.03, 0.075);
    mRP->run_pid(0, 20, 530);
    ev3_speaker_play_tone(NOTE_A4, 300);
    // 灰色
    mRP->run_pid(2, 30, 150);
    ev3_speaker_play_tone(NOTE_A4, 300);
    // 灰色後直線1
    mRP->set_pid_params(0.35, 0.15, 0.08);
     mRP->run_pid(0, 30, 250);
     //ev3_speaker_play_tone(NOTE_A4, 300);
    // //灰色後カーブ2
     mRP->set_pid_params(0.7, 0.15, 0.05);
     mRP->run_pid(0, 20, 700);
     //ev3_speaker_play_tone(NOTE_A4, 300);
    // //灰色後直線2
     mRP->set_pid_params(1.0, 0.15, 0.01);
     mRP->run_pid(0, 10, 300);
     //ev3_speaker_play_tone(NOTE_A4, 300);
     //無理やりエッジ切り替え
     mRP->TurnR(10);
     mRP->move(10, 2, 10);
    //灰色後直線3
    mRP->set_pid_params(1.0, 0.15, 0.01);
    mRP->run_pid(1, 10, 290); //340
    //ev3_speaker_play_tone(NOTE_A4, 300);
   
    // //パズル侵入
     DoPuzzle();

}

void Scenario::L(){
    mRP->set_pid_params(0.0, 0.01, 0.0);    
    mRP->run_pid(0, 30, 50);
	// 直進1
	mRP->set_pid_params(1.0, 0.03, 0.077);
	mRP->run_pid(0, 65, 2200);//65
	// 第１コーナー
	mRP->set_pid_params(1.0, 0.0, 0.1);//1.2
	mRP->run_pid(0, 55, 1800);//50
    // 直進2
	mRP->set_pid_params(1.0, 0.1, 0.09);
	mRP->run_pid(0, 55, 1600);//50
	mRP->set_pid_params(1.0, 0.1, 0.09);
	mRP->run_pid(0, 50, 150);	//45
	ev3_speaker_play_tone(NOTE_AS4, 300);
	// 第2コーナー
    mRP->set_pid_params(1.8, 0.0, 0.09);//1.8, 0.0, 0.09
    mRP->run_pid(0, 45, 600);
    // 直進3
    mRP->set_pid_params(1.0, 0.1, 0.09);
    mRP->run_pid(0, 45, 650);
    ev3_speaker_play_tone(NOTE_AS4, 300);
    // 第3コーナー Ｄの値０．０６元の Ｉの下の値０．０５
    mRP->set_pid_params(1.84, 0.0, 0.09);  // 1.84, 0.1, 0.075
    mRP->run_pid(0, 45, 750);
    // 直進4
    mRP->set_pid_params(1.1, 0.1, 0.08);
	mRP->run_pid(0, 55, 200);
	mRP->set_pid_params(1.1, 0.1, 0.08); //1.1,  0.1,  0.08
	mRP->run_pid(0, 61, 200);
	mRP->set_pid_params(1.1, 0.1, 0.08);
	mRP->run_pid(0, 65, 2000);
    //ゴール後
    //mRP->set_pid_params(1.7, 0.00, 0.1);
    //mRP->run_pid(0, 40, 570);
    
}

void Scenario::RGB2HSV(void){
    int color;
    // mRP->SetArmAngle(30, -20);
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
    // スタート
      mRP->set_pid_params(0.00, 0.5, 0.0); //0.4
      mRP->run_pid(1, 30, 50); //0
   
     mRP->set_pid_params(0.35, 0.15, 0.08);
     mRP->run_pid(0, 30, 250);
     ev3_speaker_play_tone(NOTE_A4, 300);
    // //灰色後カーブ2
     mRP->set_pid_params(0.7, 0.15, 0.05);
     mRP->run_pid(0, 20, 650);
     ev3_speaker_play_tone(NOTE_A4, 300);
    // //灰色後直線2
     mRP->set_pid_params(1.0, 0.15, 0.01);
     mRP->run_pid(0, 10, 300);
     ev3_speaker_play_tone(NOTE_A4, 300);
     //無理やりエッジ切り替え
     mRP->TurnR(10);
     mRP->move(10, 2, 10);
    //灰色後直線3
    mRP->set_pid_params(1.0, 0.15, 0.01);
    mRP->run_pid(1, 10, 290); //340
    ev3_speaker_play_tone(NOTE_A4, 300);
   
    // //パズル侵入
     DoPuzzle();

  
}

void Scenario::TEST2(void){
   
}




FILE *sfp;


void Scenario::DoPuzzle(){

sfp = fopen("DoPuzzle_log.txt", "w");

fprintf(sfp, "DP1\n");

    //パズル侵入
    //mRP->reset_pid_params();
    //ev3_speaker_play_tone(NOTE_A4, 300);
   // mRP->set_pid_params(1.0, 0.7, 0.01);//0.4, 0.15, 0.03
    //mRP->SetArmAngle(80, -20); //-20
    mRP->ColorDetect(0);

    // mRP->move(0, 0, 0); //degug
    // ext_tsk();//debug

    mRP->move(-10, 0, 200);
    
    mRP->reset_pid_params();
   
    mRP->set_pid_params(0.14, 0.01, 0.045); //0.14, 0.01, 0.045
    //ev3_speaker_play_tone(NOTE_A4, 300);                      0.15, 0.01, 0.04


    
    //0.4, 0.5, 0.03
    //mRP->ColorDetect(0);

    

    //入口選択
//    block_ptn = mBArea->select(10000);
//    block_ptn = mBArea->select();
	  block_ptn = selected_result;

    //配列の3番目から入るリングを取得           変更20180722
         if (result[block_ptn].orders[2] == 8){   // 変更20180722
        mRP->ColorDetect(0);
        } 
        else if (result[block_ptn].orders[2] == 4){
        mRP->TurnL(30);
        mRP->move(10, 0, 50);
        mRP->LineDetectIN(0);
        mRP->ColorDetect(0);
        }
    else (result[block_ptn].orders[2] == 12); {
        mRP->TurnR(30);
        mRP->LineDetectIN(1);
        mRP->ColorDetect(0);
        ev3_speaker_play_tone(NOTE_A4, 300);
        //mRP->move(0, 0, 0); //degug
        //ext_tsk();//debug

        }
    

    //ここからパズル（予定
    //Block()が実際に動作し、並べ終わった後
    //ゴールエリアまでの距離を返す(int)
    int goalDist = Block();

    if(goalDist != 0){
	    //黒線を探しブロックエリアから脱出
	    mRP->LineDetectOUT(0);
        ev3_speaker_play_tone(NOTE_A4, 300);
        //mRP->move(0, 0, 0); //degug
        //ext_tsk();//debug
	    //PIDを使い、車庫前まで移動
	     mRP->set_pid_params(1.0, 0.5, 0.01);    //1.5, 0.24, 0.1
         mRP->run_pid(0, 10, 150);
         mRP->run_pid(2, 10, 150);
        ev3_speaker_play_tone(NOTE_A4, 300);
        mRP->move(10, 0, 300);
        //mRP->Chusya();
	}
}

int Scenario::Block(void){

     fprintf(sfp, "Block1\n");

     fclose(sfp);

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
                if (result[block_ptn].orders[i + 1] != 0)
                mRP->ColorDetect(0);
                break;
            case 113:   //FORWARD_BLOCK
                 ev3_speaker_play_tone(NOTE_A5, 300);
                sprintf(time,"Forward_B :%3d :%2d", result[block_ptn].orders[i + 1], result[block_ptn].orders[i + 2]);
                ev3_lcd_draw_string(time,0,60);
                if (result[block_ptn].orders[i + 2])
                    mRP->ColorDetect(0);
                else
                    mRP->move(20, -2, 230);
                break;
            case 114:   //RELEASE
                  ev3_speaker_play_tone(NOTE_C6, 300);
                sprintf(time,"Release :%3d :%2d", result[block_ptn].orders[i + 1], result[block_ptn].orders[i + 2]);
                //ev3_lcd_draw_string(time,0,60);
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
