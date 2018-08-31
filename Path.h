#define P_SIZE 200
#define P_HEADER_SIZE 5

#ifndef PATH_H
#define PATH_H

class Path
{
private:
	int cnt1;
	int cnt2;
	int no_hop;
	int distance;
	int min_dictionary;
	int data[P_SIZE];
public:
	Path(void) { init(); }
	void set(int n, int d) { no_hop = n; distance = d; }
	void init() { cnt1 = P_HEADER_SIZE; cnt2 = P_HEADER_SIZE; }
	void p_init(void) { cnt1 = cnt2; }
	void append_ring(int ring);
	void p_reverse(void);
	int get_distance() { return distance; }
	void p_copy(int pdata[], int min_dict);
	void end(void) { data[0] = distance; data[1] = no_hop; data[2] = cnt2; }
};

#endif
