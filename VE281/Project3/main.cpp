#include <deque>
#include <iostream>
#include <getopt>
#include <list>
#include <string>
#include <vector>

#include 'binary_heap.h'
#include 'fib_heap.h'
#include 'unsorted_heap.h'

char* const short_op = "vi:";
static const struct option long_op[] = {
	{"implementation", required_argument, NULL, "i"},
	{"verbose", no_argument, NULL, "v"},
	{NULL, no_argument, NULL, 0}
};

struct point {
	unsigned x, y;
	unsigned weight;
	unsigned cost = 0;
	bool reached = false;
	bool dead = false;
	point* pre = NULL;

	point(): x(0), y(0), weight(0) {};

	struct compare_p {
		bool operator() (const point* p1, const point* p2) const {
			if (p1->cost != p2->cost) return p1->cost < p2->cost;
			if (p1->x != p2->x) return p1->x < p2->x;
			return p1->y < p2->y;
		}
	};
};



int main(int argc, char *argv[]) {
	// input: options process
	bool verbose = false;
	std::string imp;
	while (int com = getopt_long(argc, argv, short_op, long_op, NULL) != -1) {
		if (com == 'v')
			verbose = true;
		else if (com == 'i')
			imp = optarg;
		else return -1;
	}
	// input: data process

	unsigned width, height;
	unsigned bx, by, ex, ey;
	std::cin >> width;
	std::cin >> height;
	std::cin >> bx >> by;
	std::cin >> ex >> ey;

	point ** map = new point*[height];
	for (int i = 0; i < height; i++) {
		map[i] = new point[width];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cin >> map[i][j].weight;
			map[i][j].x = i;
			map[i][j].y = j;
		}
	}

	priority_queue<point, point::compare_p> *paths;
	if (imp.compare("BINARY"))
		path = new binary_heap<point, point::compare_p>();
	else if (imp.compare("UNSORTED"))
		path = new unsorted_heap<point, point::compare_p>();
	else if (imp.compare("FIBONACCI"))
		path = new fib_heap<point, point::compare_p>();
	else return -1;
	// output

	// end
	delete[] map;
}
