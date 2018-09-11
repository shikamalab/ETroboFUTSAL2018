#define N_BLK		5
#define N_RNG		18
#define C_BLACK		1
#define C_BLUE		2
#define C_GREEN		3
#define C_YELLOW	4
#define C_RED		5
#define INT_MAX_B	100000000
#define N_PORT		5

#define L_GREEN		15
#define REVERSE_ROUTE 0

#define TURN				110
#define TURN_BLOCK			111
#define MOVE_FORWARD		112
#define MOVE_FORWARD_BLOCK	113
#define RELEASE				114
#define STOP				120

#include "Path.h"
#include <stdio.h>

#ifndef BLOCK_H
#define BLOCK_H

class Port
{
private:
	int next_ring;
	int angle;
	int distance;
	int line;
public:
	Port(void) { }
	int get_next_ring() { return next_ring; }
	int get_angle() { return angle; }
	int get_distance() { return distance; }
	int get_line() { return line; }
	void set(int a, int b, int c) {
		next_ring = a; angle = b; distance = c; line = 1;
	}
	void set(int a, int b, int c, int d) {
		set(a, b, c); line = d;
	}
};

class Ring
{
private:
	int color;
	int bflag;		// block flag indicating existance of block
	int visited;	// for dijkstra
	int distance;	// for dijkstra
	int prev;		// for dijkstra
public:
	Ring(void) { }
	Port port[N_PORT];
	void set_color(int c) { color = c; }
	int get_color() { return color; }
	void set_bflag(int f) { bflag = f; }
	int get_bflag() { return bflag; }
	void set_visited(int v) { visited = v; }
	int get_visited() { return visited; }
	void set_distance(int d) { distance = d; }
	int get_distance() { return distance; }
	void set_prev(int p) { prev = p; }
	int get_prev() { return prev; }
};

class Result
{
public:
	Result(void) { distance = INT_MAX_B; }
	int distance;
	int b_loc[6];
	int orders[300];
	void show(void);
	void clear() { distance = INT_MAX_B; }
};

class Block_area
{
private:
	Ring ring[N_RNG];
	Path path;
	signed char dict[24][N_BLK];
	int init_location[6];
	int target_location[6];
	int min_order;
	int min_target;
	int orders[300];
	int o_n;
	int entry_ring;
	FILE *fp;
	int target_tb[8][4];
public:
	int pdata[P_SIZE];
	Block_area(void) {
		make_dict();
		init_rings();
	}
	void set_order(int ord, int par1, int par2) {
		orders[o_n++] = ord; orders[o_n++] = par1; orders[o_n++] = par2;
	}
	void make_dict();
	void init_rings();
	void show_rings();
	int show_blocks();
	int decode(int code, int b_loc[]);

	int dijkstra(int start);
	int find_route_distance(int s, int d, int *n, int *dist);
	int move_one_block(int start, int dest1, int dest2, int *n, int *dist);
	int move_four_blocks(int n);
	int move_four_blocks_to_squares(int n);
	void make_target_table(int n);
	int move_four_blocks_to_targets(int n);
	int angle(int current, int prev, int next, int *dist, int *ln);
	int issue_robot_orders(int data[]);
	int select(int m0, int m1, int m2, int m3);
	void test1(void);
	void test2(void);
	void test3(void);
	void test4(int pb, int nb, int ng, int ny, int nr);
	void test5(int code);
	void test6(void);
	void test7(void);
	void test8(void);
};

#endif
