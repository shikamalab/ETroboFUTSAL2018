#include <stdio.h>
#include "Path.h"

void Path::append_ring(int ring) { 
	data[cnt2++] = ring;
	if (cnt2 > P_SIZE) printf("Path error\n");
}

void Path::p_reverse(void) {
	int i, temp;
	for (i = 0; i < (cnt2 - cnt1) / 2; ++i) {
		temp = data[cnt1 + i];
		data[cnt1 + i] = data[cnt2 - 1 - i];
		data[cnt2 - 1 - i] = temp;
	}
}

void Path::p_copy(int pdata[], int min_dict) {
	int i;
	if (cnt2 >= P_SIZE) printf("p_copy_error!!");
	for (i = 0; i < cnt2; ++ i) { 
		pdata[i] = data[i];
	}
	pdata[3] = min_dict;
}
