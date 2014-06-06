using namespace std;

const int MAX_VALUE = 1 << 21;
const double pi = acos(-1.0);

namespace FFT2 {
	class complex {
	public:
		double a, b;
		complex() {
		}
		;
		complex(double _a, double _b) {
			a = _a;
			b = _b;
		}
	};

	const int maxn = MAX_VALUE + 5;

	int L1, L2;
	int s1[maxn], s2[maxn];
	int n, id;
	int A[maxn];
	complex tmp[maxn], P[maxn], PB[maxn];

	int lowbit(int n) {
		return (n ^ (n - 1)) & n;
	}
	int getnumber(int s[], int L, int id) {
		if (id > L)
			return 0;
		return s[L - id] - 48;
	}
	void Fill(int s[], int L, int m, int d) {
		if (m == n)
			P[d] = complex(s[id++], 0);
		else {
			Fill(s, L, m * 2, d);
			Fill(s, L, m * 2, d + m);
		}
	}
	void Fill2(int m, int d) {
		if (m == n)
			P[d] = tmp[id++];
		else {
			Fill2(m * 2, d);
			Fill2(m * 2, d + m);
		}
	}
	void FFT(int oper) {
		for (int d = 0; (1 << d) < n; d++) {
			int i, m = (1 << d);
			double p0 = 2 * pi / double(m * 2) * double(oper);
			double sinp0 = sin(p0);
			double cosp0 = cos(p0);
			for (i = 0; i < n; i += (m * 2)) {
				double sinp = 0;
				double cosp = 1;
				for (int j = 0; j < m; j++) {
					double ta = cosp * P[i + j + m].a - sinp * P[i + j + m].b;
					double tb = cosp * P[i + j + m].b + sinp * P[i + j + m].a;
					P[i + j + m].a = P[i + j].a - ta;
					P[i + j + m].b = P[i + j].b - tb;
					P[i + j].a += ta;
					P[i + j].b += tb;
					double tsinp = sinp;
					sinp = sinp * cosp0 + cosp * sinp0;
					cosp = cosp * cosp0 - tsinp * sinp0;
				}
			}
		}
	}

	void multiply(int a[], int b[], int ret[]) {
		int L = MAX_VALUE / 2;
		n = MAX_VALUE;
		for (int i = 0; i < n; ++i) {
			s1[i] = a[i], s2[i] = b[i];
		}
		id = 0;
		Fill(s1, L, 1, 0);
		FFT(1);
		for (int i = 0; i < n; i++) {
			tmp[i].a = P[i].a * P[i].a - P[i].b * P[i].b;
			tmp[i].b = P[i].a * P[i].b + P[i].b * P[i].a;
		}
		id = 0;
		Fill2(1, 0);
		FFT(-1);
		for (int i = 0; i < n; ++i) {
			ret[i] = int(P[i].a / n + 0.1);
		}
	}
}
