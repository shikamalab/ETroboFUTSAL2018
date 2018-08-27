/*
 * UI.h
 *
 *      Author: shikama
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef UI_H_
#define UI_H_

class UI {
	int msg_id;
	int code;
	char *buf;	/* LCD display buffer */
	int btn_cnt;
public:
	UI(void);
	int input_check(void);
	int exec(void);
	void disp_msg(int);
	int InputCode(void);
};
#endif /* UI_H_ */

#ifdef __cplusplus
}
#endif
