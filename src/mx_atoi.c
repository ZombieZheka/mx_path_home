//#include <stdio.h>
#include <stdbool.h>

bool mx_isspace(char);
bool mx_isdigit(char);

int mx_atoi(const char *str) {
	int number = 0;
	bool negative = false;
	
	while (mx_isspace(*str))
			str++;
	if (*str == '+'
	|| *str == '-') {
		if (*str == '-')
			negative = !negative;
		str++;
	}
	while (*str != '\0') {
		if (mx_isspace(*str)) {
			str++;
			continue;
		}
		if (!mx_isdigit(*str))
			return 0;
		number *= 10;
		number += *str - '0';
		str++;
	}
	if (negative)
		number *= -1;
	return number;
}

/*int main(void) {
	char num_str[] = "144";
	int number = mx_atoi(num_str);
	printf("%d\n", number);
}*/

