#include <bits/stdc++.h>
using namespace std;

/*
 *	Author timattt
 */

void* operator new(size_t s, char *p) {
	return p;
}

const int total_canaries = 2;
const int canaries_value = 111;

//!Stack created by timattt
//!It is armed with simple memory protection.
//!
template<typename T, int size> struct tStack {
	char mem[size * sizeof(T) + 2 * total_canaries];
	char *begin;
	char *end;
	char *current;

public:
	tStack() :
			begin(mem), end(mem + size * sizeof(T) + total_canaries), current(
					mem) {
		for (int i = 0; i < total_canaries; i++) {
			mem[i] = canaries_value;
			mem[i + size * sizeof(T) + total_canaries] = canaries_value;
		}
	}

private:
	//!This function is not visible. It checks that memory is safe.
	bool checkCanaries() {
		bool result = 0;

		for (int i = 0; i < total_canaries; i++) {
			if (mem[i] != canaries_value
					|| mem[i + size * sizeof(T) + total_canaries]
							!= canaries_value) {
				result = 1;
			}
		}

		if (result) {
			cerr << "Memory broken through!";
			assert(false);
		}

		return result;
	}
public:
	//!Inserts object on the top of this stack.
	void push(const T &el) {
		assert(current + 1 != end);
		checkCanaries();
		current = (char*) new (current) T(el);
		current += sizeof(T);
	}

	//!Delete object from top.
	T pop() {
		assert(current != begin);
		checkCanaries();
		T res = (*(T*) current);
		current -= sizeof(T);
		return res;
	}
};

