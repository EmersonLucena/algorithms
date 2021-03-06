double f(double x) {
	return 4*x*x + 7*x + 8;
}

double integral(double a, double b) {
	double s = 0;
	const int N = 1000000; // #STEPS * 2
	double h = (b - a) / N;

	for(int i=0; i<=N; i++) {
		double x = a + i*h;
		if(i == 0 || i == N) s += f(x);
		else if(i % 2 == 0) s += 2 * f(x);
		else s += 4 * f(x);
	}

	s *= h / 3;
	return s;
}
