#include "Block_area.h"
#include <stdio.h>
#include <stdlib.h>

signed char polygon[][6] = {
	{ 0, 8, 9, 6, 13, 14},		// pentagon 1
	{ 1, 14, 9, 6, 13, 8},		// pentagon 2
	{ 2, 0, 2, 6, 5, 8 },		// square 1
	{ 3, 0, 9, 6, 3, 7},		// square 2
	{ 4, 0, 12, 10, 5, 8},		// square 3
	{ 5, 0, 9, 11, 15, 7},		// square 4
	{ 6, 0, 2, 10, 5, 1},		// concave square 1
	{ 7, 0, 2, 0, 5, 1},		// triangle 1
	{ 8, 0, 2, 6, 3, 0},		// triangle 2
	{ 9, 0, 4, 0, 3, 7},		// triangle 3
	{ 10, 0, 0, 10, 5, 1},		// triangle 4
	{ 11, 0, 4, 11, 0, 7},		// triangle 5
	{ 12, 0, 12, 0, 13, 8},		// triangle 6
	{ 13, 0, 9, 0, 15, 14},		// triangle 7
	{ 14, 0, 4, 11, 3, 7},		// concave square 2 not used
};

int selected_result;
Result result[13];

void Path::p_end(void) {
	int i, temp;

	for (i = 0; i < (cnt2 - cnt1) / 2; ++i) {
		temp = data[cnt1 + i];
		data[cnt1 + i] = data[cnt2 - 1 - i];
		data[cnt2 - 1 - i] = temp;
	}
}

void Path::end(void) {
//	int i;

	data[0] = distance; data[1] = no_hop; data[2] = cnt2;
/*
	for (i = 0; i < cnt2; ++ i) { 
		printf(" %d", data[i]);
	}
	printf("\n");
*/
}

void Path::p_copy(int pdata[], int min_dict) {
	int i;
//	cnt = data[2];
	if (cnt2 >= P_SIZE) printf("p_copy_error!!");
	for (i = 0; i < cnt2; ++ i) { 
		pdata[i] = data[i];
	}
	pdata[P_SIZE - 1] = min_dict;
//	printf("pdata[200]= %d\n", pdata[200]);
}

void No_solution::set_data(int code, int t1, int t2, int t3, int t4, int t5) {
		s_data[next][0] = code; s_data[next][1] = t1; s_data[next][2] = t2;
		s_data[next][3] = t3; s_data[next][4] = t4; s_data[next++][5] = t5;
}

void No_solution::set_solutions(void) {
	set_data( 210401, 5, 1, 6, 13, 8 );		// added on 20170914
	set_data( 210511, 8, 1, 6, 5, 7 );
	set_data( 215791, 12, 1, 6, 5, 8 );
	set_data( 217001, 13, 1, 10, 5, 7 );
	set_data( 218332, 14, 1, 6, 13, 8 );	// added on 20170914
	set_data( 802415, 2, 1, 6, 13, 8 );		// added on 20170914
	set_data( 802525, 2, 1, 6, 5, 8 );
	set_data( 815747, 12, 1, 6, 5, 8 );
	set_data( 816077, 14, 1, 6, 13, 7 );
	set_data( 816957, 13, 1, 6, 5, 8 );
	set_data( 818288, 14, 1, 6, 5, 8 );		// added on 20170914
	set_data( 1201931, 2, 5, 10, 13, 7 );	// added on 20170914
	set_data( 1202481, 2, 5, 10, 3, 14 );
	set_data( 1202459, 2, 5, 10, 3, 14 );	// added on 20170914
	set_data( 1206771, 2, 1, 10, 13, 7 );	// added on 20170914
	set_data( 1207761, 6, 1, 10, 5, 14 );	// added on 20170914
	set_data( 1209433, 8, 5, 10, 13, 7 );	// added on 20170914
	set_data( 1210423, 8, 5, 10, 13, 7 );
	set_data( 1216011, 13, 5, 10, 3, 7 );	// added on 20170914
	set_data( 1216033, 13, 5, 10, 3, 7 );
	set_data( 1216473, 13, 5, 10, 15, 8 );	// added on 20170914
	set_data( 1217342, 14, 5, 10, 3, 7 );	// added on 20170914
	set_data( 1217364, 14, 5, 10, 3, 7 );	// added on 20170914
	set_data( 1217804, 14, 5, 10, 15, 8 );	// added on 20170914
	set_data( 1302360, 2, 1, 6, 5, 8 );
	set_data( 1309422, 8, 1, 11, 5, 14 );
	set_data( 1310302, 6, 1, 10, 5, 8 );
	set_data( 1314702, 12, 1, 6, 3, 8 );
	set_data( 1402360, 2, 1, 6, 5, 8 );		// added on 20170915
	set_data( 1410302, 6, 1, 11, 5, 8 );	// added on 20170915
}
	
int No_solution::get_data(int gcode, int *data) {
	int i, j;

//	printf("gcode= %d\n", gcode);
	for (i = 0; i < next; ++i) {
		if (s_data[i][0] == gcode) {
			data[0] = 14;
			for (j = 1; j <= N_BLK; ++j) {
				data[j] = s_data[i][j];
			}
			return 1;
		}
	}
	return 0;
}

void No_solution::show(void) {
	int i, j, g, code;

	printf("Target locations for no solution cases\n");
	for (i = 0; i <next; ++i) {
		g = s_data[i][0] / 100000;
		code = s_data[i][0] % 100000;
		printf("%2d green= %2d code= %5d target: [ ", i, g, code);
		for (j = 1; j <= 5; ++j)
			printf("%2d ", s_data[i][j]);
		printf("]\n");
	}
}

void Result::show(void)
{
	int i, j;

	printf("Distance= %d ", distance);
	if (distance < INT_MAX_B) {
		printf("Target_loc= [ ");
		for (j = 0; j <= N_BLK; ++j) printf("%d ", min_target_loc[j]);
		printf("]\n");
		j = orders[0];
		for (i = 0; i < orders[0]; i += 3) {
			printf("%d %d %d ", orders[i], orders[i + 1], orders[i + 2]);
		}
		printf("\n\n");
	}
}

void Block_area::make_dict()
{
	int i, j, k, l, m;
	int n = 0;

	for (i = 1; i <= N_BLK; ++i) {
		for (j = 1; j <= N_BLK; ++j) {
			if (j == i) continue;
			for (k = 1; k <= N_BLK; ++k) {
				if (k == i || k == j) continue;
				for (l = 1; l <= N_BLK; ++l) {
					if (l == i || l == j || l == k) continue;
					for (m = 1; m <= N_BLK; ++m) {
						if (m == i || m == j || m == k || m == l) continue;
//						int sum = i + j + k + l + m;
//						printf("n = %d sum = %d   %d %d %d %d %d\n", n, sum, i, j, k, l, m);
						dict[n][0] = i; dict[n][1] = j; dict[n][2] = k;
						dict[n][3] = l; dict[n][4] = m;
						++n;
					}
				}
			}
		}
	}
/*
	for (i = 0; i < 120; ++i) {
		printf("i = %3d | ", i);
		for (j = 0; j < N_BLK; ++j) {
			printf("%d ", dict[i][j]);
		}
		printf("\n");
	}
*/
}

void Block_area::init_rings()
{
	int i, j;
	for (i = 0; i < N_RNG; ++i) {
		ring[i].set_bflag(0);
		for (j = 0; j < N_BLK; ++j) {
			ring[i].port[j].set(-1, 0, 0, 1);
		}
	}
	ring[0].set_color(0);
	ring[0].port[0].set(10, 0, 0);
	ring[0].port[1].set(12, 0, 1000000);	// modified

	ring[1].set_color(C_RED);
	ring[1].port[0].set(2, 0, 779);
	ring[1].port[1].set(5, -30, 450);
	ring[1].port[2].set(10, -75, 636);

	ring[2].set_color(C_BLUE);
	ring[2].port[0].set(3, 0, 779);
	ring[2].port[1].set(6, -30, 450);
	ring[2].port[2].set(5, -150, 450);
	ring[2].port[3].set(1, -180, 779);

	ring[3].set_color(C_YELLOW);
	ring[3].port[0].set(4, 0, 779);
	ring[3].port[1].set(7, -30, 450);
	ring[3].port[2].set(6, -150, 450);
	ring[3].port[3].set(2, -180, 779);

	ring[4].set_color(C_BLUE);
	ring[4].port[0].set(17, -45, 317, 0);	// exit
	ring[4].port[1].set(11, -105, 636);
	ring[4].port[2].set(7, -150, 450);
	ring[4].port[3].set(3, -180, 779);

	ring[5].set_color(C_YELLOW);
	ring[5].port[0].set(2, 30, 450);
	ring[5].port[1].set(8, -30, 450);
	ring[5].port[2].set(10, -120, 450);
	ring[5].port[3].set(1, 150, 450);

	ring[6].set_color(C_GREEN);
	ring[6].port[0].set(3, 30, 450);
	ring[6].port[1].set(9, -30, 450);
	ring[6].port[2].set(16, -90, 329, 0);
	ring[6].port[3].set(8, -150, 450);
	ring[6].port[4].set(2, 150, 450);

	ring[7].set_color(C_RED);
	ring[7].port[0].set(4, 30, 450);
	ring[7].port[1].set(11, -60, 450);
	ring[7].port[2].set(9, -150, 450);
	ring[7].port[3].set(3, 150, 450);

	ring[8].set_color(C_RED);
	ring[8].port[0].set(6, 30, 450);
	ring[8].port[1].set(16, -15, 403, 0);
	ring[8].port[2].set(13, -60, 450);
	ring[8].port[3].set(12, -120, 450);
	ring[8].port[4].set(5, 150, 450);

	ring[9].set_color(C_BLUE);
	ring[9].port[0].set(7, 30, 450);
	ring[9].port[1].set(15, -60, 450);
	ring[9].port[2].set(14, -120, 450);
	ring[9].port[3].set(16, -165, 403, 0);
	ring[9].port[4].set(6, -210, 450);

	ring[10].set_color(C_GREEN);
	ring[10].port[0].set(5, 60, 450);
	ring[10].port[1].set(12, -30, 450);
	ring[10].port[3].set(1, 105, 636);
	ring[10].port[2].set(0, -120, 0);

	ring[11].set_color(C_GREEN);
	ring[11].port[0].set(17, 30, 298, 0);	// exit
	ring[11].port[1].set(4, 75, 636); 
	ring[11].port[2].set(15, -150, 450);
	ring[11].port[3].set(7, 120, 450);

	ring[12].set_color(C_BLUE);
	ring[12].port[0].set(8, 60, 450);
	ring[12].port[1].set(13, 0, 450);
	ring[12].port[2].set(10, 150, 450);
	ring[12].port[3].set(0, 150, 1000000);	// modified

	ring[13].set_color(C_YELLOW);
	ring[13].port[0].set(14, 0, 329);
	ring[13].port[1].set(12, 180, 450);
	ring[13].port[2].set(8, 120, 450);
	ring[13].port[3].set(16, 60, 329, 0);

	ring[14].set_color(C_RED);
	ring[14].port[0].set(15, 0, 450);
	ring[14].port[1].set(13, 180, 329);
	ring[14].port[2].set(16, 120, 329);
	ring[14].port[3].set(9, 60, 450);

	ring[15].set_color(C_YELLOW);
//	ring[15].port[0].set(17, 0, 0);		ring 15 is not used for exit
	ring[15].port[0].set(11, 30, 450);
	ring[15].port[1].set(14, 180, 450);
	ring[15].port[2].set(9, 120, 450);

	ring[16].set_color(0);
	ring[16].port[0].set(9, 15, 403, 0);
	ring[16].port[1].set(14, -60, 329, 0);
	ring[16].port[2].set(13, -120, 329, 0);
	ring[16].port[3].set(8, 165, 403, 0);
	ring[16].port[4].set(6, 90, 329, 0);

	ring[17].set_color(0);
	ring[17].port[0].set(4, 0, 135);		// ***** for reverse route *****
	ring[17].port[1].set(11, 0, -150);		// ***** for reverse route *****
}

void Block_area::show_rings()
{
	int i, j;
	for (i = 0; i <N_RNG; ++i) {
		printf("%2d | %2d %2d\n", i, ring[i].get_color(), ring[i].get_bflag());
		for (j = 0; j < N_BLK; ++ j) {
			printf("  %2d | %2d %2d %2d %2d\n", j, ring[i].port[j].get_next_ring(),
				ring[i].port[j].get_angle(), ring[i].port[j].get_distance(), ring[i].port[j].get_line());
		}
	}
}

int Block_area::show_blocks()
{
	int i;
	int sum = 0;

	for(i = 0; i < N_RNG; ++i)
		sum += ring[i].get_bflag();
	printf("sum = %d   ", sum);
	for (i = 0; i < N_RNG; ++i)
		printf("%1d ", ring[i].get_bflag());
	printf("\n");
	return 0;
}

int Block_area::dijkstra(int start)
{
	int i, j, next, min;

//	printf("\ndijkstra start= %d\n", start);
	for (i = 0; i < N_RNG; ++i) {
		ring[i].set_visited(0);
		ring[i].set_distance(INT_MAX_B);
	}
	ring[start].set_distance(0);
	next = start;
	do {
		i = next;
		ring[i].set_visited(1);
		for (j = 0; j < N_PORT; ++j) {  // for each port of ring[i]
			int nring = ring[i].port[j].get_next_ring(); // next ring from ring[i]
			int weight = ring[i].port[j].get_distance(); // distance from ring[i]
			if (nring == -1) break;				// previous code was 0. this is a bug
//			printf("i = %d j = %d nring = %d visited= %d weight=%d\n", i, j, nring, ring[nring].get_visited(), weight);
			if (ring[nring].get_visited() == 1) continue;
// 			printf("i = %d j = %d nring = %d \n", i, j, nring);
			if (ring[i].get_distance() + weight < ring[nring].get_distance()) {
				ring[nring].set_distance(ring[i].get_distance() + weight);
				ring[nring].set_prev(i);
			}
		}
		min = INT_MAX_B;
		for (i = 0; i < 16; ++i) {
			if (ring[i].get_visited() == 0 && ring[i].get_bflag() == 0 && ring[i].get_distance() < INT_MAX_B) {
				if (min > ring[i].get_distance()) {
					min = ring[i].get_distance();		// modified on 2017/0914
					next = i;							// modified on 2017/0914
				}
			}
		}
	} while (min < INT_MAX_B);
	return 0;
}

int Block_area::find_route_distance(int s, int d, int *n, int *dist)
{
	dijkstra(s);
	if (ring[d].get_distance() == INT_MAX_B) return INT_MAX_B;
	int p_ring = ring[d].get_prev();
//	printf("distance= %d   %d?", ring[d].get_distance(), d);
	path.new_ring(d);
	*dist = ring[d].get_distance();
	*n = 1;
	for (p_ring = ring[d].get_prev(); p_ring != s; p_ring = ring[p_ring].get_prev()) {
		++*n;
//		printf("%d?", p_ring);
		path.new_ring(p_ring);
 	}
//	printf("%d\n", s);
	path.new_ring(s);
	path.p_end();
	return 0;
}

int Block_area::move_one_block(int start, int dest1, int dest2, int *n, int *dist)
{
	int res;
	int m, d;

	path.p_init();
	res = find_route_distance(start, dest1, &m, &d);
	if (res == INT_MAX_B) return res;
	path.new_ring(100);
	if (dest1 == 17) return 0;
	path.p_init();
	*n = m;
	*dist = d;
	res = find_route_distance(dest1, dest2, &m, &d);
	if (res == INT_MAX_B) return res;
	path.new_ring(101);
	*n += m;
	*dist += d;
	*n += 1;		// release
	int x = ring[dest2].get_distance() - ring[ring[dest2].get_prev()].get_distance();
	*dist += x;
//	printf("release: %d %d?%d\n", x, ring[dest2].get_prev(), dest2);

	path.p_init();
	path.new_ring(ring[dest2].get_prev());
	path.new_ring(dest2);
	path.p_end();
	path.new_ring(102);

	ring[dest1].set_bflag(0);
	ring[dest2].set_bflag(1);
	return(ring[dest2].get_prev());
}

int Block_area::move_all_blocks(int n, int mode)
{
	int i, j, s_ring, d_ring1, d_ring2;
	int m, d;
	int no = 0;
	int dist = 0;

	for (i = 0; i < N_RNG; ++i)
		ring[i].set_bflag(0);

	for (i = 1; i <= N_BLK; ++i) {
		j = init_location[i];
		ring[j].set_bflag(1);
	}
	path.init();
	s_ring = 0;	// start ring usually 0  ***** for reverse route *****
	if (reverse_route) s_ring = 17;
	for (i = 0; i < N_BLK; ++i) {
		int color = dict[n][i];
		d_ring1 = init_location[color]; 
		d_ring2 = target_location[color];
		if (d_ring2 == 0) continue;
		if (d_ring1 == d_ring2) continue; // **************** 20170906 important bug *****************
		if (ring[d_ring2].get_bflag() == 1) return(INT_MAX_B);
//		printf("before i= %d move_one_block s_ring= %d d_ring1= %d d_ring2= %d\n", i, s_ring, d_ring1, d_ring2);
		s_ring = move_one_block(s_ring, d_ring1, d_ring2, &m, &d);
//		printf("after move_one_block s_ring= %d d_ring1= %d d_ring2= %d\n", s_ring, d_ring1, d_ring2);
		no += m;
		dist += d;
		if (s_ring == INT_MAX_B) return(s_ring);
	}
	if (mode == 0) {
		if (reverse_route == 0) {  // 20170905
			path.p_init();
	//		printf("s_ring1= %d\n", s_ring);
			s_ring = find_route_distance(s_ring, 17, &m, &d);			// move to exit ***** for reverse route *****
	//		printf("s_ring2= %d\n", s_ring);
			if (s_ring == INT_MAX_B) return(s_ring);
			no += m;
			dist += d;
	//		printf("result: n= %d distance= %d\n", no, dist);
		}
		else {
			s_ring = 0;			// for revers route
		}
	}
	else {
		s_ring = 0;
	}

	path.set(no, dist);
	path.end();
	return s_ring;
}

int Block_area::move_all(int mode)
{
	int i, res;

	int min = INT_MAX_B;
	for (i = 0; i < 120; ++i) {
		res = move_all_blocks(i, mode);
		if (res == 0) {
			if (min > path.get_distance()) {	
				min = path.get_distance();
				min_dict = i;
//				printf("min_dict= %d\n", min_dict);
				path.p_copy(pdata, min_dict);
			}
/*
			int j;
			printf("n= %d ", i);
			printf("[ ");
			for (j = 1; j <= N_BLK; ++j) printf("%d ", init_location[j]);
			printf("] [ ");
			for (j = 1; j <= N_BLK; ++j) printf("%d ", target_location[j]);
			printf("] [ ");
			for (j = 0; j < N_BLK; ++j) printf("%d ", dict[i][j]);
			printf("] res= %d\n", res);
*/
		}
	}
	return min;
}

int Block_area::input_bt(void)
{
	int ch, i, flag, code;
	char msg[] = "input code : ";
	char stb[] = "0123456789"; 

	flag = 0;
	int cbuf[100];
	int pnt = 0;
	i = 0;
	while (1) {
		ch = msg[i++];
		if (ch == 0) break; 
		putchar(ch);
	}
	while ((ch = getchar()) != EOF && flag == 0) {  // ch = fgetc(bt)
		putchar(ch);								// fputc(ch, bt)
		switch(ch)
		{
			case '\b': if (--pnt < 0) pnt = 0; break;
			case '\n': flag = 1; break;
			default: {
				for (i = 0; i < 10; ++i) 
					if (stb[i] == ch) cbuf[pnt++] = i; break;
			}
		}
		if (flag) break;
	}
	code = 0;
	for (i = 0; i < pnt; ++i) {
		code = code * 10 + cbuf[i];
	}
	return code;
}

int Block_area::input_bt(FILE* bt) // 20170731
{
	int ch, i, flag, code;
	char msg[] = "Input code : ";
	char stb[] = "0123456789"; 

	flag = 0;
	int cbuf[100];
	int pnt = 0;
	i = 0;
	while (1) {
		ch = msg[i++];
		if (!ch) break;  // if the end of string, break;
		fputc(ch, bt);
	}
	while ((ch = fgetc(bt)) != EOF && flag == 0) {  // 20170731
		fputc(ch, bt);								// 20170731
		switch(ch)
		{
			case '\b': if (--pnt < 0) pnt = 0; break;
			case '\n': flag = 1; break;
			case 13: flag = 1; break;
			default: {
				for (i = 0; i < 10; ++i) 
					if (stb[i] == ch) cbuf[pnt++] = i; break;
			}
		}
		if (flag) break;
	}
	fputc(13, bt);	// 20170731
	fputc(10, bt);	// 20170731
	code = 0;
	for (i = 0; i < pnt; ++i) {
		code = code * 10 + cbuf[i];
		fputc(stb[cbuf[i]], bt);	// 20170801
	}
	fputc(13, bt);	// 20170731
	fputc(10, bt);	// 20170731
	return code;
}

int Block_area::non_color_location(int color, int n) // non color location id -> color location id
{
	int i;
	int m = 1;
	for (i = 1; i < 16; ++i) {
		if (ring[i].get_color() == color) continue;
		if (i == n) return(m);
		++m;
	}
	return -1;
}

int Block_area::color_location(int color, int n) // color location id -> non color location id
{
	int i;
	int m = 1;
	for (i = 1; i < 16; ++i) {
		if (ring[i].get_color() == color) continue;
		if (m == n) return(i);
		++m;
	}
	return -1;
}

int Block_area::decode(int code)
{
	int n, black, blue, yellow, red;

	n = code;
	blue = n % 11 + 1;
	n = n / 11;
	yellow = n % 11 + 1;
	n = n / 11;
	red = n % 11 + 1;
	black = n / 11 + 1;
	init_location[C_BLACK] = black;
	init_location[C_BLUE] = color_location(C_BLUE, blue);
	init_location[C_GREEN] = get_green();
	init_location[C_YELLOW] = color_location(C_YELLOW, yellow);
	init_location[C_RED] = color_location(C_RED, red);

	if ((init_location[C_BLACK] == init_location[C_BLUE]) || (init_location[C_BLACK] == init_location[C_GREEN]) ||
		(init_location[C_BLACK] == init_location[C_YELLOW]) || (init_location[C_BLACK] == init_location[C_RED])) return -1;
	if ((init_location[C_BLUE] == init_location[C_GREEN]) || (init_location[C_BLUE] == init_location[C_YELLOW]) ||
		(init_location[C_BLUE] == init_location[C_RED])) return -1;
	if ((init_location[C_GREEN] == init_location[C_YELLOW]) || (init_location[C_GREEN] == init_location[C_RED])) return -1;
	if ((init_location[C_YELLOW] == init_location[C_RED])) return -1;

//	printf("code = %d black = %d blue = %d yellow = %d red = %d ? ", code, black, blue, yellow, red);
//	printf("Location : black = %d blue = %d green = %d yellow = %d red = %d\n", 
//		black, init_location[C_BLUE], init_location[C_GREEN], init_location[C_YELLOW], init_location[C_RED]);
	return 0;
}

int Block_area::encode(int location[])
{
	int code, black, blue, yellow, red; 

	printf("black = %d blue = %d yellow = %d red = %d\n", location[C_BLACK], location[C_BLUE], location[C_YELLOW], location[C_RED]);
	black = location[C_BLACK];
	blue = non_color_location(C_BLUE, location[C_BLUE]);
	yellow = non_color_location(C_YELLOW, location[C_YELLOW]);
	red = non_color_location(C_RED, location[C_RED]);
	code = black - 1;
	code = code * 11 + red - 1;
	code = code * 11 + yellow - 1;
	code = code * 11 + blue - 1;
	printf("code = %d black = %d red = %d yellow = %d blue = %d\n", code, black, red, yellow, blue);
	return code;
}

int Block_area::angle(int current, int prev, int next, int *dist, int *ln)
{
	int i, p_angle, n_angle, delt_angle;

	p_angle = 0;
	n_angle = 0;
	for (i = 0; i < N_PORT; ++i) {
		if (ring[current].port[i].get_next_ring() == prev) p_angle = ring[current].port[i].get_angle();
		if (ring[current].port[i].get_next_ring() == next) {
			n_angle = ring[current].port[i].get_angle();
			*dist = ring[current].port[i].get_distance();
			*ln = ring[current].port[i].get_line();
		}
	}
//	printf("cur= %d p_angle= %d n_angle= %d\n", current, p_angle, n_angle);
	delt_angle = n_angle - p_angle - 180;
	if (delt_angle < -180) delt_angle += 360;
	else if (delt_angle > 180) delt_angle -= 360;
	return delt_angle;
}

int Block_area::issue_robot_orders(int data[])
{
	int cur;
	int prev;
	int next;
	int i, ang, n;
	int distance;
	int line;
	int state = 0;
	n = data[2];
	o_n = 0;
	entry_ring = -1;
	set_order(0, 0, 0);	// reserve space
	for (i = 4; i < n - 1; ++i) {
		if (data[i] == 100) {
			i++;
			continue;
		}
		else if (data[i] == 101) {
			i += 2;
			continue;
		}
		else if (data[i] == 102) {
			state = 0;
			continue;
		}
		else if (data[i + 1] >= 100) {
			cur = data[i];
			prev = data[i - 1];
			next = data[i + 3];
			if (data[i + 1] == 100) state = 1;
			else if (data[i + 1] == 101) state = 2;
		}
		else if (data[i - 1] >= 100) {
			cur = data[i];
			prev = data[i - 3];
			next = data[i + 1];
		}
		else {
			cur = data[i];
			prev = data[i - 1];
			next = data[i + 1];
		}
		ang = angle(cur, prev, next, &distance, &line);
		if (state == 0) {
			set_order(TURN, ang, 0);
			set_order(MOVE_FORWARD, distance, line);
		}
		if (state == 1) {
			set_order(TURN_BLOCK, ang, 0);
			set_order(MOVE_FORWARD_BLOCK, distance, line);
		}
		if (state == 2) {
			set_order(RELEASE, distance, line);
		}

		if (entry_ring < 0) entry_ring = cur;

/*
		int j = 1;
		printf("j= %2d i= %2d prev= %2d cur= %2d next= %2d",  j++, i, prev, cur, next);
		printf("  turn %4d ", ang);
		if (state == 0) printf(" move_forward            %3d", distance);
		if (state == 1) printf(" move_forward_with_block %3d", distance);
		if (state == 2) printf(" release_block           %3d", distance);
		if (line) printf(" with_line\n");
		else printf(" without_line\n");
*/

	}
	orders[0] = o_n;
	orders[1] = entry_ring;

	for (i = 0; i < orders[0]; i += 3) {
		printf("%d %d %d ", orders[i], orders[i + 1], orders[i + 2]);
	}
	printf("\n\n");

	return 0;
}

void Block_area::test_decode(void)
{
	int i;
	int n = 0;

	for (i = 0; i <= 19965; ++i) {
		if (decode(i) < 0) continue;
		++n;
	}
	printf("number of codes = %d\n", n);
}

void Block_area::poly_penta(int n1, int n2)
{
	int i, pn, min;

	min = INT_MAX_B;
	for (pn = n1; pn <= n2; ++pn) {
		for (i = 0; i < 6; ++i) {
			target_location[i] = polygon[pn][i];
		}
		poly_common_1(&min);
	}
	poly_common_2(&min);
}

void Block_area::poly_penta_special(int n1, int n2)
{
	int i, pn, min;

	min = INT_MAX_B;
	for (pn = n1; pn <= n2; ++pn) {
		for (i = 0; i < 6; ++i) {
			target_location[i] = polygon[pn][i];
		}
		poly_common_1_special(&min);
	}
	poly_common_2(&min);
}

void Block_area::poly_sqr(int n1, int n2, int mode)
{
	int i, k, pn, min;

	min = INT_MAX_B;
	for (pn = n1; pn <= n2; ++pn) {
		for (i = 0; i < 6; ++i) {
			target_location[i] = polygon[pn][i];
		}
		for (k = 0; k <= 16; ++k) {
			if ((mode == 1) && (k != 16)) continue;
			else if ((mode == 0) && (k == 16)) continue;
			target_location[1] = k;
			poly_common_1(&min);
//			printf("test1 min_pdata[200]= %d\n", min_pdata[200]);
		}
//		printf("test2 min_pdata[200]= %d\n", min_pdata[200]);
	}
	poly_common_2(&min);
}

void Block_area::poly_sqr_special(int n1, int n2, int mode)
{
	int i, k, pn, min;

	min = INT_MAX_B;
	for (pn = n1; pn <= n2; ++pn) {
		for (i = 0; i < 6; ++i) {
			target_location[i] = polygon[pn][i];
		}
		for (k = 0; k <= 16; ++k) {
			if ((mode == 1) && (k != 16)) continue;
			else if ((mode == 0) && (k == 16)) continue;
			target_location[1] = k;
			poly_common_1_special(&min);
		}
	}
	poly_common_2(&min);
}

int Block_area::poly_common_1(int* min)
{
	int i, j, res;

	if (check_duplication(target_location) == 1) return 1;

//	printf("target_location= ");
//	for (i = 0; i < 6; ++i) printf("%d ", target_location[i]);
//	printf("\n");

	res = move_all(0);
//	printf("res= %d\n", res);
	if (res < *min) {
		*min = res;
		j = pdata[2];
		for (i = 0; i < j; ++i) { 
			min_pdata[i] = pdata[i];
		}
		min_pdata[P_SIZE - 1] = pdata[P_SIZE - 1]; // min_dict copy
//		printf("common1 min_pdata[200]= %d\n", min_pdata[200]);
		for (i = 0; i < 6; ++i) {
			min_target_loc[i] = target_location[i];
		}
	}
	return 0;
}

int Block_area::poly_common_1_special(int* min)
{
	int i, j, res;

	if (check_duplication(target_location) == 1) return 1;
/*
	printf("target_location= ");
	for (i = 0; i < 6; ++i) printf("%d ", target_location[i]);
	printf("\n");
*/
	res = move_all(1);
//	printf("res= %d\n", res);
	if (res < *min) {
		*min = res;
		j = pdata[2];
		for (i = 0; i < j; ++i) { 
			min_pdata[i] = pdata[i];
		}
		min_pdata[P_SIZE - 1] = pdata[P_SIZE - 1]; // min_dict copy
//		printf("common1 min_pdata[200]= %d\n", min_pdata[200]);
		for (i = 0; i < 6; ++i) {
			min_target_loc[i] = target_location[i];
		}
	}
	return 0;
}

void Block_area::poly_common_2(int *min)
{
	int j;

	printf(" %d ", *min);
	min_pdata[0] = *min;
	if (*min < INT_MAX_B) {

		printf("Min_target_loc= [ ");
		for (j = 0; j <= N_BLK; ++j) printf("%d ", min_target_loc[j]);
		printf("] ");
		printf("Min_dict= %d Order= [ ", min_pdata[P_SIZE - 1]);
		for (j = 0; j < N_BLK; ++j) printf("%d ", dict[min_pdata[P_SIZE - 1]][j]);
		printf("]\n");

//		j = min_pdata[2];
//		for (i = 0; i < j; ++i) printf("%d ", min_pdata[i]);
//		printf("\n");
		issue_robot_orders(min_pdata);
	}
	else {
		printf("\n\n");
	}
}

void Block_area::poly_tri(int n1, int n2, int mode)
{
	int i, kb, kc, color,pn, min;

	min = INT_MAX_B;
	for (pn = n1; pn <= n2; ++pn) {
		for (i = 0; i < 6; ++i) {
			target_location[i] = polygon[pn][i];
		}

		color = 0;
		for (i = 2; i <= N_BLK; ++i) {
			if (target_location[i] == 0) { 
				color = i;
//				printf("color= %d\n", color);
				break;
			}
		}
		if (color == 0) {
			printf("Error! test1_tri\n"); return;
		}

		if (mode == 0) {
			for (kb = 0; kb < 16; ++kb) {
				target_location[1] = kb;

				poly_common_1(&min); 
			}
		}
		else if (mode == 1) {
			for (kc = 1; kc < 16; ++kc) {
				for (kb = 0; kb < 16; ++kb) {  // modified on 20170915
					if (ring[kc].get_color() != color) continue;
					target_location[color] = kc;
					target_location[1] = kb;

					poly_common_1(&min);
				}
			}
		}
		else if (mode == 2) {
			for (kc = 1; kc < 16; ++kc) {
				if (ring[kc].get_color() != color) continue;
				target_location[color] = kc;
				target_location[1] = 16;

				poly_common_1(&min);
			}
		}
		else {	
			for (kb = 0; kb <= 15; ++kb) {
				target_location[color] = 16;
				target_location[1] = kb;

				poly_common_1(&min);
			}
		}
	}
	poly_common_2(&min);
}

void Block_area::copy_result(int n)
{
	int i, j;

	result[n].distance = min_pdata[0];
//	printf("result[%d].distance= %d\n", n, result[n].distance);
	j = min_pdata[2];
	for (i = 0; i < j; ++i) { 
		result[n].min_pdata[i] = min_pdata[i];
	}
	for (i = 0; i < 6; ++i) {
		result[n].min_target_loc[i] = min_target_loc[i];
	}
	for (i = 0; i < orders[0]; ++i) {
		result[n].orders[i] = orders[i];
	}
	/* following codes are added for the special concave square case  on 20171023*/
	if (n == 10) {
		result[n].orders[ orders[0]] = STOP;
		result[n].orders[ orders[0]+1] = 0;
		result[n].orders[ orders[0]+2] = 0;
		result[n].orders[0] +=3;
	}
}

void Block_area::test2(FILE* bt)	// 20170731
{
	int ch, i;

	char msg[] = "Calculation has been completed\n";
	int res = input_bt(bt);
	if (decode(res) < 0) {
		printf("Error: illegal code\n");
		return;
	}
	test_common(res);

	i = 0;
	while (1) { 	// 	20170731
		ch = msg[i++];
		if (ch == 0) break;		
		fputc(ch, bt);
	}
}

void Block_area::test2(void)
{
	int i;

	int res = input_bt();
	if (decode(res) < 0) {
		printf("Error: illegal code\n");
		return;
	}
//	printf("\nN= %d Code= %d ", n++, i);
	printf("[ ");
	for (i = 1; i <= N_BLK; ++i) printf("%d ", init_location[i]);
	printf("]\n");
	test_common(res);
}

void Block_area::ttest(int res)	// 20170731
{
	// int ch;
	// int i;

	// char msg[] = "Calculation has been completed\n";
	//int res = init_code;
	if (decode(res) < 0) {
		printf("Error: illegal code\n");
		return;
	}
	test_common(res);

	// i = 0;
	// while (1) { 	// 	20170731
	// 	ch = msg[i++];
	// 	if (ch == 0) break;		
	// 	fputc(ch, bt);
	// }
}

void Block_area::test3(void)
{
	int i, j;

	int n = 1;
//	for (i = 16440; i < 16441; ++i) {
	for (i = 0; i <= 19965; ++i) {
//	for (i = 0; i <= 50; ++i) {
		if (decode(i) < 0) continue;
		printf("\nN= %d Code= %d ", n++, i);
		printf("[ ");
		for (j = 1; j <= N_BLK; ++j) printf("%d ", init_location[j]);
		printf("]\n"); 
		test_common(i);
	}
}

void Block_area::test_common(int code) {

	int i;
	printf("0_Pentagon");
	poly_penta(0, 1); // pentagon
	copy_result(0);
	printf("1_Square_0");
	poly_sqr(2, 5, 0); 
	copy_result(1);

	printf("2_Square_1");
	poly_sqr(2, 5, 1); 
	copy_result(2);
	printf("3_Concave_square_0");
	poly_sqr(6, 6, 0);
	copy_result(3);
	printf("4_Concave_square_1");
	poly_sqr(6, 6, 1);
	copy_result(4);
	printf("5_Triangle_0");
	poly_tri(7, 13, 0);
	copy_result(5);
	printf("6_Triangle_1");
	poly_tri(7, 13, 1);
	copy_result(6);
	printf("7_Triangle_2");
	poly_tri(7, 13, 2);
	copy_result(7);
	printf("8_Triangle_3");
	poly_tri(7, 13, 3);
	copy_result(8);
	printf("9_No_solution");
	if (no_solution_cases(code) == 0) {
		printf(" %d\n", INT_MAX_B);
		min_pdata[0] = INT_MAX_B;
	}
	copy_result(9);

	printf("\n10_Concave_special");
	poly_sqr_special(14, 14, 0); // Concave_special
	copy_result(10);

	//selected_result = select_all(DISTANCE_LIMIT_1, DISTANCE_LIMIT_2);
	selected_result = select();
	printf("Selected_result_index= %d\n", selected_result);
	if (selected_result <= 10) {
		for (i = 0; i < result[selected_result].orders[0]; ++i)
			printf("%d ", result[selected_result].orders[i]);
		printf("\n\n");
	}
}


int Block_area::select() {
	int i, j, limit;
//	int i, j, n, limit;
	int smin_j, dist;
	int select_tb[12][2] = { { 0, A1 }, { 3, A1 }, { 0, A2 }, { 1, A1 }, { 3, A2 }, { 10, A2 }, { 6, A1 }, { 1, A2 }, { 5, A1 }, { 6, A2 }, { 5, A2 }, { 9, A2 }};

	int smin = INT_MAX_B;
	smin_j = INT_MAX_B;

	for (i = 0; i < 12; ++i) {
		j = select_tb[i][0];   		// ?oH???? 0, 1, 3, 5, 6, 9, 10
		limit = select_tb[i][1];	// A1: ?c????   A2: xXgGtH[g
		
		dist = result[j].distance;
		if (dist > 100000) continue;
		if (smin > dist)  { smin = dist; smin_j = j; } 
		if (dist <= limit) return j;
	}
	if  (smin < INT_MAX_B) return smin_j;

	for (i = 0; i < 12; ++i) {
		j = select_tb[i][0];		// ?oH???? 0, 1, 3, 5, 6, 9, 10
		limit = select_tb[i][1];	// A1: ?c????   A2: xXgGtH[g
		
		dist = result[j].distance;
		if (smin > dist)  { smin = dist; smin_j = j; } 
		if (dist <= (limit + 1000000)) return j;
	}
	if  (smin < INT_MAX_B) return smin_j;
	return INT_MAX_B;
}

/*
int Block_area::select(int limit_1, int limit_2) {

	int i, j, smin_j, dist, limit;

	int s_priority[6] = { 0, 3, 1, 6, 5, 9 }; // 1st one has the highest priority 0 
	int smin = INT_MAX_B;
	smin_j = INT_MAX_B;

	for (i = 0; i < 6; ++i) {
		j = s_priority[i];
		limit = limit_2;
		if ((j == 0) || (j == 3)) limit = limit_1;
		dist = result[j].distance;
		if (dist > 100000) continue;
//		printf("dist= %d\n", dist);
		if (smin > dist) { smin = dist; smin_j = j; } 
//		printf("ring10: i= %d j= %d dist= %d smin= %d\n", i, j, dist, smin);
		if (result[j].distance <= limit) {
			return j;
		}
	}
	if (smin < INT_MAX_B) return smin_j;

	for (i = 0; i < 6; ++i) {
		j = s_priority[i];
		limit = limit_2;
		if ((j == 0) || (j == 3)) limit = limit_1;
		dist = result[j].distance;
		if (smin > dist) { smin = dist; smin_j = j; } 
//		printf("ring12: i= %d j= %d dist= %d smin= %d smin_j= %d\n", i, j, dist, smin, smin_j);
		if (dist <= limit + 1000000) {
			return j;
		}
	}
	if (smin < INT_MAX_B) return smin_j;
	return INT_MAX_B;
}

int Block_area::select_all(int limit_1, int limit_2) {
	int res;

	res = select(limit_1, limit_2);
	if ((res == 5) || (res == 6) || (res == INT_MAX_B)) {
		int dist = result[10].distance;
		if (dist < INT_MAX_B) {
			if (dist > 1000000) dist -= 1000000;
			if (dist < limit_1) return 10;
		}
	}
	return res;
}
*/


int Block_area::check_duplication(int data[])
{
	int i, j;
	 
	for (i = 1; i < N_BLK; ++i) {
		for (j = i + 1; j <= N_BLK; ++j) {
			if (data[i] == data[j]) return 1;
		}
	}
	return 0;
}

void Block_area::test5(void)
{
	int i;
	int bk, bw, g, y, r;
	int min;

	int res = input_bt();
	if (decode(res) < 0) {
		printf("Error: illegal code\n");
		return;
	}
//	printf("\nN= %d Code= %d ", n++, i);
	printf("[ ");
	for (i = 1; i <= N_BLK; ++i) printf("%d ", init_location[i]);
	printf("]\n");

	printf("Black: "); scanf("%d", &bk);
	printf("Blue: "); scanf("%d", &bw);
	printf("Green: "); scanf("%d", &g);
	printf("Yellow: "); scanf("%d", &y);
	printf("Red: "); scanf("%d", &r);
	target_location[0] = 0;
	target_location[1] = bk;
	target_location[2] = bw;
	target_location[3] = g;
	target_location[4] = y;
	target_location[5] = r;
	printf("[ ");
	for (i = 1; i <= N_BLK; ++i) printf("%d ", target_location[i]);
	printf("]\n");

	min = INT_MAX_B;
	poly_common_1(&min);
	poly_common_2(&min);
}

void Block_area::test6(int code)
{
	int i, j, count;
	int bk, bw, g, y, r;
	int min;
	int color, nc;

//	int res = input_bt();
	if (decode(code) < 0) {
		printf("Error: illegal code\n");
		return;
	}
//	printf("\nN= %d Code= %d ", n++, i);
	printf("[ ");
	for (i = 1; i <= N_BLK; ++i) printf("%d ", init_location[i]);
	printf("]\n");

	count = 0;
	for (bk = 1; bk < 16; ++bk) {
		for(bw = 1; bw < 16; ++bw) {
			for(g = 1; g < 16; ++g) {
				for (y = 1; y < 16; ++y) {
					for (r = 1; r < 16; ++r) {

						target_location[0] = 0;
						target_location[1] = bk;
						target_location[2] = bw;
						target_location[3] = g;
						target_location[4] = y;
						target_location[5] = r;

						min = INT_MAX_B;
						poly_common_1(&min);
						if (min < INT_MAX_B) {

							nc = 0;
							for (color = 2; color < 6; ++color)
								if (ring[target_location[color]].get_color() == color) ++nc;

							printf("count= %d min= %d nc= %d ", ++count, min, nc);
							printf("Min_target_loc= [ ");
							for (j = 0; j <= N_BLK; ++j) printf("%d ", min_target_loc[j]);
							printf("]\n");

//							if (count > 1000) break;
						}
/*
						if (min < INT_MAX_B) {
							printf("[ ");
							for (i = 1; i <= N_BLK; ++i) printf("%d ", target_location[i]);
							printf("]\n");
						}
*/
					}
				}
			}
		}
	}
}

void Block_area::test7() {
	int i;
	// int i, min;

	// min = INT_MAX_B;
	int res = input_bt();
	if (decode(res) < 0) {
		printf("Error: illegal code\n");
		return;
	}
//	printf("\nN= %d Code= %d ", n++, i);
	printf("[ ");
	for (i = 1; i <= N_BLK; ++i) printf("%d ", init_location[i]);
	printf("]\n");
	printf("10_Pentagon_special");
	poly_penta_special(0, 1); // pentagon
	copy_result(10);
	printf("11_Concave_special-1");
	poly_sqr_special(6, 6, 0); // pentagon
	copy_result(11);
	printf("12_Concave_special-2");
	poly_sqr_special(14, 14, 0); // pentagon
	copy_result(12);
}

int Block_area::no_solution_cases(int code) {
	int min, gcode;
	
	gcode = l_green * 100000 + code; 
	if (no_solution.get_data(gcode, target_location) == 0) return 0;
/*
	printf("[ ");
	int i;
	for (i = 1; i <= N_BLK; ++i) printf("%d ", target_location[i]);
	printf("]\n");
*/
	min = INT_MAX_B;
	poly_common_1(&min);
	poly_common_2(&min);
	return 1;
}

int main(int argc, char *argv[])
{
	Block_area b_area;
	int n;

	if (argc >= 2) {
		n = atoi(argv[1]);
		b_area.set_green(n);
	}

//	int m;
//	if (argc >= 3) { m = atoi(argv[2]); }

	printf("initial_green_location= %d\n", b_area.get_green());
//	b_area.test2();
	b_area.test3();
//	b_area.test5();
//	b_area.test6(m);
//	b_area.test7();
	return 0;
}