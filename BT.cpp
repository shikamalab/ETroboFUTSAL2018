/*
 * BT.cpp
 *
 *      Author: shikama
 */

#include "ev3api.h"
#include <string.h>
#include <stdlib.h>
#include <syssvc/serial.h>
#include "BT.h"
#include "Block.h"

extern int selected_result;
extern Block_area* gB_area;

int gdrive_mode = 0;

BT::BT() {
	bt_count = 0;
	bt_size = 0;
	eflag = 0;
	bt = NULL;
}

int BT::open(void)
{
	bt = ev3_serial_open_file(EV3_SERIAL_BT);
}

void BT::recv_cmd(void)
{
	int8_t ch, res;
	int i;

	while (eflag == 0) {
		i = 0; res = 0;
		while (1)
		{
			//fputc(ch, bt);
			if ((ch = fgetc(bt)) == '\n') break;
			else if (ch == '\r') break;
			if (i == 0) { 
				res = ch;
			}
			else {
				s[i - 1] = ch;	
			}
			++i;
		}
		s[i - 1] = '\0';
		puts(s);
		proc_msg(res);
	}
}

int BT::proc_msg(char h)
{
	char ss[5];
	int i, m[4];
	int code, n, pblk, b[4];
	
	color = h;
	pblk = 0;
	if (h == 'i') {
		n = atoi(s);
		code = n;
		color1 = n;
		printf("n = %d\n", n);
		pblk = n % 16;
		n /= 16;
		for (i = 0; i < 4; ++i) {
			b[3 - i] = n % 16;
			n /= 16;
		}
		printf("pblk= %d b[0]= %d b[1]= %d b[2]= %d b[3]= %d\n", pblk, b[0], b[1], b[2], b[3]);
		gB_area->test5(code);
		fputc('a', bt);
	}
	else if (h == 'c') {
		//color1 = atoi(s);
		for (i = 0; i < 4; ++i) {
			ss[0] = s[2 * i];
			ss[1] = s[2 * i + 1];
			ss[2] = '\0';
			m[i] = atoi(ss);
		}
		printf("%d %d %d %d\n", m[0], m[1], m[2], m[3]);
		fputc('b', bt);
		color1 = 1000000 * m[0] + 10000 * m[1] + 100 * m[2] + m[3];
		selected_result = gB_area->select(m[0], m[1], m[2], m[3]);
	}
	return 0;
}

