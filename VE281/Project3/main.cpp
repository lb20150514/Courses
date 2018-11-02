#include <deque>
#include <getopt>
#include <list>
#include <string>
#include <vector>

#include 'binary_heap.h'
#include 'fib_heap.h'
#include 'unsorted_heap.h'

char* const short_op = "vi:";
static const option long_op[] = {
	{"implementation", required_argument, NULL, "i"},
	{"verbose", no_argument, NULL, "v"},
	{NULL, no_argument, NULL, 0}
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

	if (imp.compare("BINARY"))
	else if (imp.compare("UNSORTED"))
	else if (imp.compare("FIBONACCI"))
	else return -1;
	// output
}
