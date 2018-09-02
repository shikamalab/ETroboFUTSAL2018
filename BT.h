/*
 * BT.h
 *
 *      Author: T. shikama
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BT_H_
#define BT_H_

#define MSG_LEN  4

class BT {
	int bt_count;
	int bt_size;
//	int gdrive_mode;
	int32_t bt_cmd;
	FILE*	bt;
	FILE* 	fp;
	char s[256];
	char bt_message[MSG_LEN + 1];
	char bt_log[100][40];
public:
	int color;
	int color1;
	BT();
	int open(void);
	void recv_cmd(void);
	int proc_msg(char h);
	void file_transfer(void);
	int eflag;
	signed char bt_forward;
	signed char bt_turn;
	signed char bt_arm;
	signed char bt_tail;
};

#endif /* BT_H_ */

#ifdef __cplusplus
}
#endif
