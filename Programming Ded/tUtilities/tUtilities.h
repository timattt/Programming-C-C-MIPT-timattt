#ifndef T_UTILITIES
#define T_UTILITIES

#include <windows.h>
#include <bits/stdc++.h>

namespace tUtilities {

void tAssert(bool val);
template<typename T> void tWriteBytes(const T &elem, char *dest);
void tThrowException(const char *message);
template<typename T> void tCopyBuffers(const T *from, T *to, unsigned length);
int tSymbolsCount(const char *line, char symb);
int tGetFileSize(const char *name);
int tStrcmp(const char *str1, const char *str2, int size);

template<typename A, typename B> struct tPair {
	A x;
	B y;
};

char tReadCharFromLine() {
	std::cout.flush();
	char c = getchar();
	while (getchar() != '\n')
		;
	return c;
}

template<typename T = int> T tup(T a, T b) {
	return a / b + (a % b == 0 ? 0 : 1);
}

//! Returns minimum of a and b.
template<typename T = int> T tMin(T a, T b) {
	return (a < b ? a : b);
}

//! Returns minimum of a and b.
template<typename T = int> T tMax(T a, T b) {
	return (b < a ? a : b);
}

namespace {

// For the encapsulation!
class _MEM_ {
public:
	void* operator new(size_t s, char *p) {
		return p;
	}
	template<typename T> void __tWriteBytes(const T &elem, char *dest) {
		new (dest) T(elem);
	}
	template<typename T> void __tWriteBytes_rvalue(T &&elem, char *dest) {
		char *beg = (char*) (&elem);
		for (unsigned i = 0; i < sizeof(T); i++) {
			dest[i] = beg[i];
		}
	}
} __mem__;
}

template<typename T = int, typename K = int> T tBinpow(K a, T n) {
	T res = 1;
	while (n) {
		if (n & 1)
			res *= a;
		a *= a;
		n >>= 1;
	}
	return res;
}

double tFloor(double val) {
	return (double) ((long long) (val));
}
unsigned tGetFirstSignificantDecimalPlace(double val) {
	if (val == tFloor(val)) {
		return 0;
	}
	unsigned res = 1;
	long long pow = 10;
	while ((long long) (val * pow) % 10 == 0) {
		res++;
		pow *= 10;
	}

	return res;
}

double tCeiling(double val) {
	double floor = tFloor(val);
	return (val - floor > 0 ? floor + 1 : floor);
}

template<typename T> bool tCompare(const T *a, const T *b, unsigned len) {
	for (unsigned i = 0; i < len; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}

	return true;
}

//! My own realization of assert function.
void tAssert(bool val) {
	if (!val) {
		tThrowException("Assertion error!");
	}
}

template<typename T> void tFill(T *arr, T templ, unsigned len) {
	for (unsigned i = 0; i < len; i++) {
		arr[i] = templ;
	}
}

template<typename T> void tSwap(T &a, T &b) {
	T tmp = a;
	a = b;
	b = tmp;
}

void tSwapBuffers(char *a, char *b, unsigned len) {
	for (unsigned i = 0; i < len; i++) {
		char tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}
}

//! Writes element into given bytes array.
template<typename T> void tWriteBytes(const T &elem, char *dest) {
	__mem__.__tWriteBytes(elem, dest);
}

//! Writes element into given bytes array.
template<typename T> void tWriteBytes_rvalue(T &&elem, char *dest) {
	__mem__.__tWriteBytes_rvalue(elem, dest);
}

//! Converts data from byte array into any element.
template<typename T> T& tConvertBytes(char *data) {
	return (*(T*) (data));
}

//! Copies one buffer to another.
template<typename T> void tCopyBuffers(const T *from, T *to, unsigned length) {
	if (from == NULL || to == NULL) {
		tThrowException("Something is NULL!");
	}
	for (unsigned i = 0; i < length; i++) {
		to[i] = from[i];
	}
}

//! Just throws exception and tells some information about this class.
void tThrowException(const char *message = "tException") {
	std::cout << "!!!EXCEPTION!!!\n";
	//if (file != 0) {
	//	std::cout << "IN FILE " << file << "\n";
	//}
	//if (line != -1) {
	//	std::cout << "IN LINE " << line << "\n";
	//}
	std::cout << message << "\n";
	std::cout << "PROGRAM IS TERMINATED!\n";
	std::cout.flush();
	exit(-1);
}

//!Gives file size in bytes.
int tGetFileSize(const char *name) {
	tAssert(name != NULL);
	WIN32_FIND_DATA data = { };
	FindFirstFileA(name, &data);
	return data.nFileSizeLow;
}

}

#endif
