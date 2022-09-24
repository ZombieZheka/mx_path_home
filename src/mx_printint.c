void mx_printchar(char);

void mx_printint(int n) {
	int i = 1;

	if (n < 0) {
		mx_printchar('-');
		n *= -1;
	}

	for (; i <= n / 10; i *= 10);

	for (; i >= 1; i /= 10) {
		int num = (n / i) % 10;
		mx_printchar(num + '0');
	}
}

