#include "Block.h"
#include <stdio.h>
#include <stdlib.h>

/* Global variables */
int selected_result;
Result result[24];

/* the first figure is the square id, while other
   figures are area id sorted by color order */
signed char square[][5] = {
	{ 0, 4, 5, 1, 0},		// square 0
	{ 1, 2, 5, 1, 6},		// square 1
	{ 2, 2, 3, 7, 6 },		// square 2
	{ 4, 4, 5, 9, 8 },		// square 3
	{ 5, 10, 5, 9, 6},		// square 4
	{ 6, 10, 11, 7, 6},		// square 5
	{ 8, 12, 13, 9, 8},		// square 6
	{ 9, 10, 13, 9, 14},	// square 7
	{ 10, 10, 11, 15, 14 },	// square 8
};

signed char power_blk[][3] = {
	{ 0, -1, -1 },
	{ 1, 0, 5 },
	{ 2, 1, 6 },
	{ 3, 4, 9 },
	{ 4, 5, 10 },
	{ 5, 1, 4 },
	{ 6, 2, 5 },
	{ 7, 5, 8 },
	{ 8, 6, 9 },
};

void Result::show(void)
{
	int i, j;

	printf("Distance= %d ", distance);
	if (distance < INT_MAX_B) {
		printf("B_loc= [ ");
		for (j = 0; j < 6; ++j) printf("%d ", b_loc[j]);
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
	int i, j, k, l;
	int n = 0;
	for (i = 2; i <= N_BLK; ++i) {
		for (j = 2; j <= N_BLK; ++j) {
			if (j == i) continue;
			for (k = 2; k <= N_BLK; ++k) {
				if (k == i || k == j) continue;
				for (l = 2; l <= N_BLK; ++l) {
					if ( l == i || l == j || l == k) continue;
					//int sum = i + j + k + l;
					//printf("n = %2d sum = %2d   %d %d %d %d\n", n, sum, i, j, k, l);
					dict[n][0] = -1; dict[n][1] = i; dict[n][2] = j; dict[n][3] = k; dict[n][4] = l;
					++n;
				}
			}
		}
	}
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
	ring[0].set_color(C_RED);
	ring[0].port[0].set(1, 0, 450); ring[0].port[1].set(4, -90, 400);

	ring[1].set_color(C_YELLOW);
	ring[1].port[0].set(2, 0, 450); ring[1].port[1].set(5, -90, 400);
	ring[1].port[2].set(0, -180, 450);

	ring[2].set_color(C_BLUE);
	ring[2].port[0].set(3, 0, 450); ring[2].port[1].set(6, -90, 400);
	ring[2].port[2].set(1, -180, 450);

	ring[3].set_color(C_GREEN);
	ring[3].port[0].set(7, -90, 400); ring[3].port[1].set(2, -180, 450);

	ring[4].set_color(C_BLUE);
	ring[4].port[0].set(5, 0, 450); ring[4].port[1].set(8, -90, 400);
	ring[4].port[2].set(0, 90, 400); ring[4].port[3].set(16, -90, INT_MAX_B);

	ring[5].set_color(C_GREEN);
	ring[5].port[0].set(6, 0, 450); ring[5].port[1].set(9, -90, 400);
	ring[5].port[2].set(4, -180, 450); ring[5].port[3].set(1, 90, 400);

	ring[6].set_color(C_RED);
	ring[6].port[0].set(7, 0, 450); ring[6].port[1].set(10, -90, 400);
	ring[6].port[2].set(5, -180, 450); ring[6].port[3].set(2, 90, 400);

	ring[7].set_color(C_YELLOW);
	ring[7].port[0].set(11, -90, 400); ring[7].port[1].set(6, -180, 450);
	ring[7].port[2].set(3, 90, 400); ring[7].port[3].set(17, -30, 700); // Exit

	ring[8].set_color(C_RED);
	ring[8].port[0].set(9, 0, 450); ring[8].port[1].set(12, -90, 400);
	ring[8].port[2].set(4, 90, 400); ring[8].port[3].set(16, -180, INT_MAX_B);

	ring[9].set_color(C_YELLOW);
	ring[9].port[0].set(10, 0, 450); ring[9].port[1].set(13, -90, 400);
	ring[9].port[2].set(8, -180, 450); ring[9].port[3].set(5, 90, 400);

	ring[10].set_color(C_BLUE);
	ring[10].port[0].set(11, 0, 450); ring[10].port[1].set(14, -90, 400);
	ring[10].port[2].set(9, -180, 450); ring[10].port[3].set(6, 90, 400);

	ring[11].set_color(C_GREEN);
	ring[11].port[0].set(15, -90, 400); ring[11].port[1].set(10, -180, 450);
	ring[11].port[2].set(7, 90, 400); ring[11].port[3].set(17, 0, 500); // Exit

	ring[12].set_color(C_BLUE);
	ring[12].port[0].set(13, 0, 450); ring[12].port[1].set(8, 90, 400);
	ring[12].port[3].set(16, 90, INT_MAX_B);

	ring[13].set_color(C_GREEN);
	ring[13].port[0].set(14, 0, 450); ring[13].port[1].set(12, -180, 450);
	ring[13].port[2].set(9, 90, 400);


	ring[14].set_color(C_RED);
	ring[14].port[0].set(15, 0, 450); ring[14].port[1].set(13, -180, 450);
	ring[14].port[2].set(10, 90, 400);


	ring[15].set_color(C_YELLOW);
	ring[15].port[0].set(14, -180, 450); ring[15].port[1].set(11, 90, 400);
	ring[15].port[2].set(17, 30, 700); // Exit

	ring[16].set_color(0);
	ring[16].port[0].set(8, 0, 0); ring[16].port[1].set(12, -45, 10000);
	ring[16].port[2].set(4, 45, 5000);

	ring[17].set_color(0);
}

void Block_area::show_rings()
{
	int i, j;
	for (i = 0; i <N_RNG; ++i) {
		printf("%2d | %2d %2d\n", i, ring[i].get_color(), ring[i].get_bflag());
		for (j = 0; j < N_PORT; ++j) {
			printf("  %2d | %2d %2d %2d %2d\n", j, ring[i].port[j].get_next_ring(),
				ring[i].port[j].get_angle(), ring[i].port[j].get_distance(), ring[i].port[j].get_line());
		}
	}
}

int Block_area::show_blocks()
{
	int i;
	int sum = 0;

	for (i = 0; i < N_RNG; ++i)
		sum += ring[i].get_bflag();
	printf("sum = %d   ", sum);
	for (i = 0; i < N_RNG; ++i)
		printf("%1d ", ring[i].get_bflag());
	printf("\n");
	return 0;
}

int Block_area::decode(int code, int b_loc[])
{
	int n, i; // b_loc[4] is the power block code

	n = code;
	for (i = 0; i < 5; ++i) {
		b_loc[4 - i] = n % 16;
		n = n / 16;
	}
	//printf("pb= %d b0= %d b1= %d b2= %d b3= %d\n", b_loc[4], b_loc[0], b_loc[1], b_loc[2], b_loc[3]);
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
			//printf("i = %d j = %d nring = %d visited= %d weight=%d\n", i, j, nring, ring[nring].get_visited(), weight);
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
	//printf("distance= %d   %d←", ring[d].get_distance(), d);
	path.append_ring(d);
	*dist = ring[d].get_distance();
	*n = 1;
	for (p_ring = ring[d].get_prev(); p_ring != s; p_ring = ring[p_ring].get_prev()) {
		++*n;
		//printf("%d←", p_ring);
		path.append_ring(p_ring);
 	}
	//printf("%d\n", s);
	path.append_ring(s);
	path.p_reverse();
	return 0;
}

int Block_area::move_one_block(int start, int dest1, int dest2, int *n, int *dist)
{
	int res;
	int m, d;

	path.p_init();
	res = find_route_distance(start, dest1, &m, &d);
	if (res == INT_MAX_B) return res;
	path.append_ring(100);
	if (dest1 == 17) return 0;
	path.p_init();
	*n = m;
	*dist = d;
	res = find_route_distance(dest1, dest2, &m, &d);
	if (res == INT_MAX_B) return res;
	path.append_ring(101);
	*n += m;
	*dist += d;
	*n += 1;		// release
	int x = ring[dest2].get_distance() - ring[ring[dest2].get_prev()].get_distance();
	*dist += x;
	//printf("release: %d %d←%d\n", x, ring[dest2].get_prev(), dest2);

	path.p_init();
	path.append_ring(ring[dest2].get_prev());
	path.append_ring(dest2);
	path.p_reverse();
	path.append_ring(102);

	ring[dest1].set_bflag(0);
	ring[dest2].set_bflag(1);
	return (ring[dest2].get_prev());
}

/* n is the index of the order dictionary */
int Block_area::move_four_blocks(int n)
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
	s_ring = 16;	// start ring is normally 16
	for (i = 1; i < N_BLK; ++i) { // i = 1,2,3,4
		int color = dict[n][i]; // moving order of block colors
		d_ring1 = init_location[color]; // ring number of source
		d_ring2 = target_location[color]; // ring number of destination
		//printf("s_ring= %d d_ring1= %d d_ring2= %d\n", s_ring, d_ring1, d_ring2);
		if (d_ring1 == d_ring2) continue; // ************ 20170906 important bug *************
		if (ring[d_ring2].get_bflag() == 1) return(INT_MAX_B);
		//printf("before i= %d move_one_block s_ring= %d d_ring1= %d d_ring2= %d\n", i, s_ring, d_ring1, d_ring2);
		s_ring = move_one_block(s_ring, d_ring1, d_ring2, &m, &d);
		//printf("after move_one_block s_ring= %d d_ring1= %d d_ring2= %d\n", s_ring, d_ring1, d_ring2);
		no += m;
		dist += d;
		if (s_ring == INT_MAX_B) return(s_ring);
	}

	path.p_init();
//	printf("s_ring1= %d\n", s_ring);
	s_ring = find_route_distance(s_ring, 17, &m, &d); // move to exit
//	printf("s_ring2= %d\n", s_ring);
	if (s_ring == INT_MAX_B) return(s_ring);
	no += m;
	dist += d;
//	printf("result: n= %d distance= %d\n", no, dist);

	path.set(no, dist);
	path.end();
	return s_ring;
}

int Block_area::move_four_blocks_to_squares(int pblk) {
	int sqi, sq, n, res, i, bi;
	int min = INT_MAX_B;
	printf("pblk= %d init_loc[2:5]= [ ", pblk);
	for (i = 2; i < 6; ++i)
		printf("%d ", init_location[i]);
	printf("]\n");
	for (bi = 1; bi <= 2; ++bi) {
		sq = power_blk[pblk][bi];
		for (sqi = 0; sqi <= 8; ++sqi) 
			if (square[sqi][0] == sq ) break;
		//printf("power_blk = %d bi= %d square = %d sqi= %d\n", pblk, bi, sq, sqi);
		for (i = 1; i < 5; ++i) { // i = 1,2,3,4
			target_location[i + 1] = square[sqi][i];
			//printf("target_location[%d]= %d ", i, target_location[i + 1]);
		}
		//printf("\n");
		for (n = 0; n < 24; ++n) { // for all possible orders
			for (i = 0; i < 16; ++i)
				ring[i].set_bflag(0);
			for (i = 2; i < 6; ++i)
				ring[init_location[i]].set_bflag(1);
			res = move_four_blocks(n);
			if (res < INT_MAX_B) {
				//printf("move_blocks_to_squares: power_blk = %d square = %d order = %d res = %d distance= %d\n", pblk, sq, n, res, path.get_distance());
				if (min > path.get_distance()) {	
					min = path.get_distance();
					min_target = sq;
					min_order = n;
					//printf("min_update: min_order= %d\n", min_order);
					path.p_copy(pdata, min_order);
				}
			}
		}
	}
	return(min);
}

/* form node 16 to all other nodes holding no block */
void Block_area::test1(void)
{
	ring[1].set_bflag(1); ring[4].set_bflag(1); ring[10].set_bflag(1); ring[15].set_bflag(1);
	show_blocks();

	int d;
	int n = 0;
	int dist = 0;
	for (d = 0 ; d < 15; ++d) {
		if (ring[d].get_bflag() == 0) {
			find_route_distance(16, d, &n, &dist);
			printf("16 -> %d n = %d dist = %d\n", d, n, dist);
		}
	}

	printf("\n\n");
	move_one_block(16, 4, 11, &n, &dist);
	show_blocks();

	int res, sq, i;
	init_location[2] = 1; init_location[3] = 4; init_location[4] = 10; init_location[5] = 15;
	for (sq = 0; sq < 8; ++sq) {
		for (i = 1; i < 5; ++i) { // i = 1,2,3,4
			target_location[i + 1] = square[sq][i]; // target_location[3] = 11; target_location[4] = 7; target_location[5] = 6;
		}
	
		for (n = 0; n < 24; ++n) {
			res = move_four_blocks(n);
			if (res < INT_MAX_B) {
				printf("square = %d order = %d res = %d\n", sq, n, res);
				show_blocks();
			}
		}
	}

	int pblk, j;
	for (pblk = 1; pblk <= 8; ++pblk) {

		for (j = 0; j < 16; ++j) 
			ring[j].set_bflag(0); 
		ring[1].set_bflag(1); ring[4].set_bflag(1); ring[10].set_bflag(1); ring[15].set_bflag(1);

		dist = move_four_blocks(pblk);
		if (dist != INT_MAX_B) {
			printf("min_distance= %d min_order= %d\n", dist, min_order);
			printf("distance= %d no_hops= %d cnt2= %d pdata[3]= %d\n", pdata[0], pdata[1], pdata[2], pdata[3]);
			for (i = 5; i <= pdata[2]; ++i)
				printf("path[%d]= %d ", i, pdata[i]);
			printf("\n");
		}
	}
}

void Block_area::test2(void)
{
	int i, j, k, flag, b_loc[5], dist;
	int n = 1;

//	for (i = 84723; i <= 84730; ++i) {
//	for (i = 4658; i <= 4658; ++i) {
	for (i = 843512; i <= 843512; ++i) {
		if (decode(i, &b_loc[0]) < 0) continue;
		if (b_loc[4] == 0 || b_loc[4] >= 9) continue;
		flag = 0;
		for (j = 0; j < N_BLK - 1; ++j) {
			for (k = j + 1; k < N_BLK - 1; ++k) {
				if (b_loc[j] == b_loc[k]) flag = 1;
				//if (ring[b_loc[j]].get_color() == ring[b_loc[k]].get_color()) flag = 1;
			}
		}
		if (flag) continue;
		printf("\nN= %d Code= %d  PBLK= %d ", n++, i, b_loc[4]);
		printf("[ ");
		for (j = 0; j < N_BLK - 1; ++j) printf("%d ", b_loc[j]);
		printf("]\n"); 
		
		for (j = 0; j < 24; ++j) {
			for (k = 0; k < 4; ++ k) { // k=0,1,2,3
				int dc = dict[j][k + 1];
				int rg = ring[b_loc[k]].get_color();
				if (dc == rg) {
					flag = 1; break;
				}
				//printf("j = %d dict = %d ring_c= %d\n", j, dc, rg); 
				init_location[dict[j][k + 1]] = b_loc[k];
			}
			if (flag) { flag = 0; continue; }
			printf("init_loc_id= %d ", j);
			dist = move_four_blocks_to_squares(b_loc[4]);

			if (dist < INT_MAX_B) {
				//printf("min_order= %d\n", min_order);
				printf("distance= %d no_hops= %d cnt2= %d pdata[3]= %d\n", pdata[0], pdata[1], pdata[2], pdata[3]);
				for (k = 5; k <= 12; ++k)
				printf("path[%d]= %d ", k, pdata[k]);
				printf("\n");
				//show_blocks();
			}
		}
	}
}


void Block_area::test3(void)
{
	int i, j, k, flag, b_loc[5], dist;
	int n = 1;

//	for (i = 84723; i <= 84730; ++i) {
	for (i = 4658; i <= 843512; ++i) {
//	for (i = 843512; i <= 843512; ++i) {
		if (decode(i, &b_loc[0]) < 0) continue;
		if (b_loc[4] == 0 || b_loc[4] >= 9) continue;
		flag = 1;
		for (j = 0; j < 4; ++j) {
			if (b_loc[j] == 8) flag = 0;
		}
		if (flag) continue;
		int sum = 0;
		for (j = 0; j < N_BLK - 1; ++j) {
			for (k = j + 1; k < N_BLK - 1; ++k) {
				if (b_loc[j] == b_loc[k]) flag = 1;			
				//if (ring[b_loc[j]].get_color() == ring[b_loc[k]].get_color()) flag = 1;
				if (ring[b_loc[j]].get_color() == ring[b_loc[k]].get_color()) ++sum;
			}
		}
		if (flag) continue;
		if (sum >= 3) continue;
		printf("\nN= %d Code= %d  PBLK= %d ", n++, i, b_loc[4]);
		printf("[ ");
		for (j = 0; j < N_BLK - 1; ++j) printf("%d ", b_loc[j]);
		printf("]\n"); 
		
		for (j = 0; j < 24; ++j) {
			for (k = 0; k < 4; ++ k) { // k=0,1,2,3
				int dc = dict[j][k + 1];
				int rg = ring[b_loc[k]].get_color();
				if (dc == rg) {
					flag = 1; break;
				}
				//printf("j = %d dict = %d ring_c= %d\n", j, dc, rg); 
				init_location[dict[j][k + 1]] = b_loc[k]; 
			}
			if (flag) { flag = 0; continue; }
			if (init_location[2] != 8) continue;
			//if (ring[init_location[3]].get_color() == ring[init_location[4]].get_color() && ring[init_location[4]].get_color() == ring[init_location[5]].get_color()) continue;

			printf("init_loc_id= %d ", j);
			dist = INT_MAX_B;
			dist = move_four_blocks_to_squares(b_loc[4]);

			if (dist < INT_MAX_B) {
				//printf("min_order= %d\n", min_order);
				printf("distance= %d no_hops= %d cnt2= %d pdata[3]= %d\n", pdata[0], pdata[1], pdata[2], pdata[3]);
				for (k = 5; k <= 12; ++k)
				printf("path[%d]= %d ", k, pdata[k]);
				printf("\n");
				//show_blocks();
			}
		}
	}
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
	//printf("cur= %d prev= %d next= %d p_angle= %d n_angle= %d\n", current, prev, next, p_angle, n_angle);
	delt_angle = n_angle - p_angle - 180;
	if (delt_angle < -180) delt_angle += 360;
	else if (delt_angle > 180) delt_angle -= 360;
	return delt_angle;
}

// dataの配列からシナリオの配列orderを作成する。orderはクラスのprivateメンバ、他の配列にコピーする。
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
	for (i = 5; i < n -1; ++i) {
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
		if (entry_ring != -1)
			ang = angle(cur, prev, next, &distance, &line);
		else {
			ang = 0; distance = 0; line = 0; // for initial
		}

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
	}
	orders[0] = o_n;
	orders[1] = entry_ring;
	orders[2] = data[6];
	for (i = 0; i < orders[0]; i += 3) {
		fprintf(fp, "%d %d %d ", orders[i], orders[i + 1], orders[i + 2]);
	}
	fprintf(fp, "\n\n");

	return 0;
}

int Block_area::select(int m0, int m1, int m2, int m3)
{
	int i;
	for (i = 0; i < 24; ++i) {
		if ((result[i].b_loc[2] == m0) && (result[i].b_loc[3] == m1) && 
			(result[i].b_loc[4] == m2) && (result[i].b_loc[5] == m3)) return i;
	}

	int min_i = -1;
	int min_dist = INT_MAX_B;
	for (i = 0; i < 24; ++i) {
		printf("i= %d blue_loc= %d distance= %d\n", i, result[i].b_loc[2], result[i].distance); 
		if (result[i].b_loc[2] == 8) {
			if ((min_i < 0) || (min_dist > result[i].distance)) {
				min_i = i;
				min_dist = result[i].distance;
			}
		}
	}
	return min_i;
}

void Block_area::test4(int pb, int nb, int ng, int ny, int nr)
{
	fp = fopen("path_orders.txt", "w");
	if (fp == NULL) {
		printf("ファイルオープン失敗\n");
		return;
	}

	int dist = INT_MAX_B;
	init_location[2] = nb; init_location[3] = ng; init_location[4] = ny; init_location[5] = nr;

	dist = move_four_blocks_to_squares(pb);

	int k;
	if (dist < INT_MAX_B) {
		//printf("min_order= %d\n", min_order);
		fprintf(fp, "distance= %d no_hops= %d cnt2= %d pdata[3]= %d\n", pdata[0], pdata[1], pdata[2], pdata[3]);
		for (k = 5; k < pdata[2]; ++k)
			fprintf(fp, "path[%d]= %d ", k, pdata[k]);
		fprintf(fp, "\n");
		//show_blocks();
		issue_robot_orders(pdata);
	}
	fclose(fp);
}

// コードを与えて	４ブロックに対する色割り当ての経路を計算
void Block_area::test5(int code)
{
	int j, k, flag, b_loc[5], dist;
	int rn = 0; // 書込むresult配列の番号
	
	fp = fopen("test5_log.txt", "w");

	decode(code, &b_loc[0]);
	fprintf(fp, "Code= %d  PBLK= %d ", code, b_loc[4]);
	fprintf(fp, "[ ");
	for (j = 0; j < N_BLK - 1; ++j) fprintf(fp, "%d ", b_loc[j]);
	fprintf(fp, "]\n"); 
		
	for (j = 0; j < 24; ++j) {
		for (k = 0; k < 4; ++ k) { // k = 0,1,2,3
			int dc = dict[j][k + 1];
			int rg = ring[b_loc[k]].get_color();
			if (dc == rg) {
				flag = 1; break; //	置き場とブロックの色が同じ場合は排除する
			}
			//printf("j = %d dict = %d ring_c= %d\n", j, dc, rg); 
			init_location[dict[j][k + 1]] = b_loc[k]; 
		}
		if (flag) { flag = 0; continue; }
		//if (init_location[2] != 8) continue; // 地区大会では青ブロックの初期置き場は8番
		//if (ring[init_location[3]].get_color() == ring[init_location[4]].get_color() && ring[init_location[4]].get_color() == ring[init_location[5]].get_color()) continue;

		fprintf(fp, "rn= %d  init_loc_id= %d [B,G,Y,R] = [ ", rn, j);
		for (k = 0; k < 4; ++k) {
			fprintf(fp, "%d ", init_location[k + 2]);
		}
		fprintf(fp, "]\n");
		dist = INT_MAX_B;
		//dist = move_four_blocks_to_squares(b_loc[4]);
		dist = move_four_blocks_to_targets(b_loc[4]);

		if (dist < INT_MAX_B) {
			fprintf(fp, "min_order= %d [ ", min_order);
			for (k = 1; k < 5; ++k) {
				fprintf(fp, "%d ", dict[min_order][k]);
			}
			fprintf(fp, "]\n");
			fprintf(fp, "min_target= %d [ ", min_target);
			for (k = 0; k < 4; ++k) {
				fprintf(fp, "%d ", target_tb[min_target][k]);
			}
			fprintf(fp, "]\n");
			fprintf(fp, "distance= %d no_hops= %d cnt2= %d pdata[3]= %d\n", pdata[0], pdata[1], pdata[2], pdata[3]);
			//for (k = 5; k < pdata[2]; ++k)
			for (k = 5; k < pdata[2]; ++k)
				fprintf(fp, "path[%d]= %d ", k, pdata[k]);
			fprintf(fp, "\n");
			issue_robot_orders(pdata);

			result[rn].distance = dist;
			result[rn].b_loc[0] = b_loc[4];
			result[rn].b_loc[1] = 0;
			for (k = 2; k < 6; ++k) {
				result[rn].b_loc[k] = init_location[k];
			}
			for (k = 0; k < orders[0]; ++k) result[rn].orders[k] = orders[k];
			++rn;
		}
	}
	k = 0;
	while (1) {
		if (result[k].distance == INT_MAX_B) break;
		result[k++].show();
	}
	fclose(fp);
}

void Block_area::test6(void)
{
	selected_result = select(8, 12, 0, 4); // 色ブロックの配置でresultを選択
	printf("selected_result= %d\n", selected_result);
}

void Block_area::test8(void)
{
	selected_result = select(8, 12, 0, 4); // 色ブロックの配置でresultを選択
	printf("selected_result= %d\n", selected_result);
	selected_result = select(8, 0, 12, 4); // 色ブロックの配置でresultを選択
	printf("selected_result= %d\n", selected_result);
	selected_result = select(8, 4, 0, 12); // 色ブロックの配置でresultを選択
	printf("selected_result= %d\n", selected_result);
	selected_result = select(8, 0, 4, 12); // 色ブロックの配置でresultを選択
	printf("selected_result= %d\n", selected_result);
	selected_result = select(8, 99, 4, 12); // 色ブロックの配置でresultを選択
	printf("selected_result= %d\n", selected_result);
}

/* パワーブロックコードからパワースポットの可能な組み合わせを記憶する target_tb[8] を生成する*/
void Block_area::make_target_table(int pb_code)
{
	int i, j, sq, sq_i, area;
	int target_cl[4][2];
	int target_n[4];

	for (i = 0; i < 4; ++i) {
		target_cl[i][0] = target_cl[i][1] = -1;
		target_n[i] = 0;
	}
	for (i = 1; i <= 2; ++i) {
		sq = power_blk[pb_code][i];
		printf("pb_code= %d square_id= %d\n", pb_code, sq);
		for (sq_i = 0; sq_i <= 8; ++sq_i) {
			if (square[sq_i][0] == sq) break;
		}
		for (j = 1; j <= 4; ++j) {
			if (target_n[j - 1]++ == 0)
				target_cl[j - 1][0] = square[sq_i][j];
			else if (target_cl[j - 1][0] != square[sq_i][j]) {
				target_cl[j - 1][1] = square[sq_i][j];
				target_n[j - 1] = 2;
			}
			else
				target_n[j - 1] = 1;

			area = square[sq_i][j];
			printf("area= %d ", area);
		}
		printf("\n");
	}
	for (i = 0; i < 4; ++i) {
		printf("i= %d target_cl[0]= %d target_CL[1]= %d target_n= %d\n", i, target_cl[i][0], target_cl[i][1], target_n[i]);
	}
	int nb, ng, ny, nr;
	i = 0;
	for (nb = 0; nb < target_n[0]; ++nb)
		for (ng = 0; ng < target_n[1]; ++ng)
			for (ny = 0; ny < target_n[2]; ++ny)
				for (nr = 0; nr < target_n[3]; ++nr) {
					target_tb[i][0] = target_cl[0][nb]; target_tb[i][1] = target_cl[1][ng]; target_tb[i][2] = target_cl[2][ny]; target_tb[i][3] = target_cl[3][nr];
					//printf("%d b= %d g= %d y= %d r= %d\n", i++, target_cl[0][nb], target_cl[1][ng], target_cl[2][ny], target_cl[3][nr]);
					++i;
				}

	for (i = 0; i < 8; ++i) {
		printf("%d b= %d g= %d y= %d r= %d\n", i, target_tb[i][0], target_tb[i][1], target_tb[i][2], target_tb[i][3]);
	}
	printf("\n");
}

/* 4ブロックをパワースポットの可能な組み合わせを記憶する target_tb[8] に移動する最短経路を求める。*/
int Block_area::move_four_blocks_to_targets(int pblk)
{
	int n, res, i, j;
	int min = INT_MAX_B;
	printf("pblk= %d init_loc[2:5]= [ ", pblk);
	for (i = 2; i < 6; ++i)
		printf("%d ", init_location[i]);
	printf("]\n");
	make_target_table(pblk);

	for (j = 0; j < 8; ++j) {
		for (i = 0; i < 4; ++i) { // i = 0,1,2,3
			target_location[i + 2] = target_tb[j][i];
			//printf("target_location[%d]= %d ", i, target_location[i + 1]);
		}
		//printf("\n");
		for (n = 0; n < 24; ++n) { // for all possible orders
			for (i = 0; i < 16; ++i)
				ring[i].set_bflag(0);
			for (i = 2; i < 6; ++i)
				ring[init_location[i]].set_bflag(1);
			res = move_four_blocks(n);
			if (res < INT_MAX_B) {
				//printf("move_blocks_to_squares: power_blk = %d square = %d order = %d res = %d distance= %d\n", pblk, sq, n, res, path.get_distance());
				if (min > path.get_distance()) {
					min = path.get_distance();
					min_target = j; // 最短経路となる target_tb のインデックス //
					min_order = n; // 最短経路となる 順序 のインデックス //
					//printf("min_update: min_order= %d\n", min_order);
					path.p_copy(pdata, min_order);
				}
			}
		}
	}
	return(min);
}


void Block_area::test7(void)
{
	int i;

	for (i = 1; i <= 8; ++i) {
		make_target_table(i);  // i is the power block id
	}
}

int main(int argc, char *argv[])
{
	Block_area b_area;
	//int i;

	//b_area.show_rings();
	//b_area.test1();
	//b_area.test2();
	//b_area.test3();
	//b_area.test4(2, 8, 4, 12, 9);
	//b_area.test4(8, 8, 1, 2, 3);
	//b_area.test4(4, 8, 15, 14, 13); // パワーブロック4、青8、緑15、黄14、赤13
	b_area.test5(18628); // 18628, 96722, 158435, 228340
	b_area.test8();
	b_area.test6();
	//b_area.test7();
	return 0;
}
