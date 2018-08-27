/*
 * UI.cpp
 *
 *      Author: shikama
 */

#include "ev3api.h"
#include "UI.h"

UI::UI(void) {
	ev3_led_set_color(LED_GREEN);
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	btn_cnt = 0;
}

int UI::input_check(void){
	if (ev3_button_is_pressed(RIGHT_BUTTON)) {
        btn_cnt++;
        if(btn_cnt == 1){
            ev3_speaker_play_tone(NOTE_C4, 50);
            return (1);
        }
    }
    else if (ev3_button_is_pressed(LEFT_BUTTON )) {
        btn_cnt++;
        if(btn_cnt == 1){
            ev3_speaker_play_tone(NOTE_C4, 50);
            return (2);
        }
    }
    else if (ev3_button_is_pressed(UP_BUTTON )) {
        btn_cnt++;
        if(btn_cnt == 1){
            ev3_speaker_play_tone(NOTE_C4, 50);
            return (3);
        }
    }
    else if (ev3_button_is_pressed(DOWN_BUTTON )) {
        btn_cnt++;
        if(btn_cnt == 1){
            ev3_speaker_play_tone(NOTE_C4, 50);
            return (4);
        }
    }
    else if (ev3_button_is_pressed(ENTER_BUTTON )) {
        btn_cnt++;
        if(btn_cnt == 1){
            ev3_speaker_play_tone(NOTE_D5, 200);
            return (5);
        }
    }
    else btn_cnt = 0;
    return (0);
	/*
	if (ev3_button_is_pressed(RIGHT_BUTTON)) {
		ev3_speaker_play_tone(NOTE_A4, 300);
		tslp_tsk(300);
		return (1);
	}
	else if (ev3_button_is_pressed(ENTER_BUTTON )) {
		ev3_speaker_play_tone(NOTE_A4, 300);
		tslp_tsk(300);
		return (2);
	}
	return (0);
	*/
}

int UI::exec(void)
{
	msg_id = 0;
	ev3_speaker_set_volume(5);
	while (1) {
		disp_msg(msg_id);
		code = input_check();
		if (code == 1) {
			if (++msg_id == 5) { msg_id = 0; }
		}
		else if (code == 5)
			break;
	}
	tslp_tsk(200); /* 300msec wait */
	ev3_lcd_draw_string("Ready to start      ", 20, 46);
	return (msg_id);
}

void UI::disp_msg(int mid) {
	char s1[] = "R Course   ";
	char s2[] = "L Course   ";
	char s3[] = "RGB to HSV ";
	char s4[] = "TEST       ";
	char s5[] = "L SHORTCUT ";
	char *buf;

	if (mid == 0) buf = s1;
	else if (mid == 1) buf = s2;
	else if (mid == 2) buf = s3;
	else if (mid == 3) buf = s4;
	else buf = s5;
	ev3_lcd_draw_string(buf, 20, 30);
}

int UI::InputCode(void){
	//char num[10][] = {"0","1","2","3","4","5","6","7","8","9"};
	char mark[2][14] = {"    A    ","    V    "};
	char s1[] = "Input Initial Code...";
	char *buf;
	char num[5][10] = {"0","0","0","0","0"};
	int init_code[5] = {0,0,0,0,0};
	int select_digit = 4; // range:0-4
	int answer = 0;

    int btn_code = 0;
    ev3_speaker_set_volume(5);

    buf = s1;
    ev3_lcd_draw_string(buf, 0, 0);

    while (1) {
    	// =============Draw===============
        for (int i=0; i<5; i++){
        	sprintf(num[i], "%d", init_code[i]);
        	ev3_lcd_draw_string(num[i], 100 - 10 * i, 50);
  		}
  		buf = mark[0];
  		ev3_lcd_draw_string(buf, 60 - 10 * select_digit, 34);
  		buf = mark[1];
  		ev3_lcd_draw_string(buf, 60 - 10 * select_digit, 65);
        //sprintf(sturn,"Turn   :%3d ",(int)turn_val);
        //ev3_lcd_draw_string(sturn,0,100);

        // =============Input==============
        btn_code = input_check();
        if (btn_code == 1) {		//right
            if (--select_digit == -1) select_digit = 4;
        }
        else if (btn_code == 2){	//left
            if (++select_digit == 5) select_digit = 0;
        }
        else if (btn_code == 3){	//up
        	if (++init_code[select_digit] == 10) init_code[select_digit] = 0;
        }
        else if (btn_code == 4){	//down
        	if (--init_code[select_digit] == -1) init_code[select_digit] = 9;
        }
        else if (btn_code == 5) {	//enter
            answer = init_code[4] * 10000
        	+ init_code[3] * 1000 
        	+ init_code[2] * 100 
        	+ init_code[1] * 10 
        	+ init_code[0]; 
        	return answer;
        }
        else {
        	
        }
    }
    ev3_lcd_draw_string("Ready to start      ", 20, 46);
}