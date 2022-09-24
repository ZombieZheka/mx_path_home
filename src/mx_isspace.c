#include <stdbool.h>

bool mx_isspace(char c) {
	switch (c)
	case ' ':
	case '\t':
	case '\n':
	case '\v':
	case '\f':
	case '\r':
		return true;
	return false;
}

/*int main(void) {
	printf("%d\n", mx_isspace('	'));
	printf("%d\n", mx_isspace('a'));
}*/

