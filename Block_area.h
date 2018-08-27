#ifdef __cplusplus
extern "C" {
#endif

#ifndef BLOCKAREA_H_
#define BLOCKAREA_H_

#include <stdio.h>

#define N_BLK		5
#define N_RNG		18
#define C_BLACK		1
#define C_BLUE		2
#define C_GREEN		3
#define C_YELLOW	4
#define C_RED		5
#define INT_MAX_B	100000000
#define N_PORT		5

#define L_GREEN		2
#define REVERSE_ROUTE 0

#define TURN				110
#define TURN_BLOCK			111
#define MOVE_FORWARD		112
#define MOVE_FORWARD_BLOCK	113
#define RELEASE				114
#define STOP				120
//#define DISTANCE_LIMIT		1000
#define A1	10000		// ècóÒíìé‘
#define A2	11000		// best effort

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
		next_ring = a; angle = b; distance = c;
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
	Port port[5];
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

#define P_SIZE 201
class Path
{
private:
	int cnt1;
	int cnt2;
	int no_hop;
	int distance;
	int min_dictionary;
public:
	Path(void) { cnt1 = 3; cnt2 = 3;}
	int data[P_SIZE];
	void set(int n, int d) { no_hop = n; distance = d; }
	void init(void) { cnt1 = 3; cnt2 = 3; }
	void p_init(void) { cnt1 = cnt2; }
	void new_ring(int ring) { data[cnt2++] = ring; }
	void p_end(void);
	int get_distance() { return distance; }
	void p_copy(int pdata[], int min_dict);
	void end(void);
};

class No_solution
{
private:
	int s_data[30][6];
	int next;
public:
	No_solution(void) { next = 0; }
	void set_data(int code, int t1, int t2, int t3, int t4, int t5);
	void set_solutions(void);
	int get_data(int, int*);
	void show(void);
};

class Result
{
public:
	Result(void) { }
	int distance;
	int min_pdata[P_SIZE];
	int min_target_loc[6];
	int orders[300];
	void show(void);
	void clear() { distance = INT_MAX_B; }
};

class Block_area
{
private:
	Ring ring[N_RNG];
	Path path;
	int min_dict;
	int l_green;
	signed char dict[120][N_BLK];
	int init_location[6];
	int target_location[6];
	int min_pdata[P_SIZE];
	int min_target_loc[6];
	int pdata[P_SIZE];
	int orders[300];
	int o_n;
	int reverse_route;	// added on 20170905
	int entry_ring;		// added on 20170905
	No_solution no_solution;
public:
	Block_area(void) {
		make_dict();
		init_rings();
//		show_rings();
		l_green = L_GREEN;
		reverse_route = REVERSE_ROUTE;
		no_solution.set_solutions();
		no_solution.show();
	}
	void set_green(int g) { l_green = g; }
	int get_green() { return(l_green); }
	void set_order(int ord, int par1, int par2) {
		orders[o_n++] = ord; orders[o_n++] = par1; orders[o_n++] = par2;
	}
	void make_dict();
	void init_rings();
	void show_rings();
	int show_blocks();
	int dijkstra(int start);
	int find_route_distance(int s, int d, int *n, int *dist);
	int move_one_block(int start, int dest1, int dest2, int *n, int *dist);
	int move_all_blocks(int n, int mode);
	int move_all(int mode);
	int input_bt(void);
	int input_bt(FILE* bt);
	int non_color_location(int color, int n);
	int color_location(int color, int n);
	int decode(int code);
	int encode(int location[]);
	int angle(int current, int prev, int next, int *dist, int *ln);
	int issue_robot_orders(int data[]);
	void poly_penta(int n1, int n2);
	void poly_penta_special(int n1, int n2);
	int poly_common_1(int* min);
	int poly_common_1_special(int* min);
	void poly_common_2(int* min);
	void poly_sqr(int n1, int n2, int mode);
	void poly_sqr_special(int n1, int n2, int mode);
	void poly_tri(int n1, int n2, int mode);
	void copy_result(int n);
	void test2(void);
	void test2(FILE* bt);
	void ttest(int);
	void test3(void);
	void test5(void);
	void test6(int m);
	void test7(void);
	void test_common(int code);
	int select();
//	int select(int limit_1, int limit_2);
//	int select_all(int limit_1, int limit_2);
	int check_duplication(int data[]);
	void test_decode(void);
	int no_solution_cases(int code);
};

#endif

#ifdef __cplusplus
}
#endif
