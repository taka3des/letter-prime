// string-prime - search primes based on string map
// (c)2018 Seishi Takamura
#include <iostream>
#include <ctype.h>
#include <gmpxx.h>
//#include "miller-rabin-gmp.h"
using namespace std;

#define Wmax 512
#define Hmax 100
int buf[Hmax][Wmax];
int width, height, maxnum;

// wrapper
bool my_prob_prime(const mpz_class n, const size_t rounds)
{
	return mpz_millerrabin(n.get_mpz_t(), rounds);
}

// 0110022
// 0111020 のような長方形文字列を読み込む
void readmap()
{
	char str[Wmax];
	height = maxnum = 0;
	for (; ;) {
		if (fgets(str, sizeof(str), stdin) == NULL)
			break;
		if (str[0] == '#') //先頭の#は無視する
			continue;
		int l = strlen(str);
		if (l <= 1)
			break;
		width = l - 1; // 改行コードを除く
		if (!isalnum(str[width - 1])) //DOSのように除き切れないとき
			width--;              //再度除く
		for (int i = 0; i < width; i++) {
			char c = str[i];
			int val = (c <= '9') ? c - '0' : c - 'a' + 10;
			if (val > maxnum)
				maxnum = val;
			buf[height][i] = val;
		}
		++height;
	}
}

// if nodup is true, search trans[] s.t. it contains no duplicate entry
void doit(int trans[], int depth, int firstdigit, int lastdigit, bool nodup)
{
	if (depth == maxnum+1) { // do check
		mpz_class a = 0;
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				a = a*10 + trans[buf[j][i]];
			}
		}
		if (my_prob_prime(a, width*height)) {
			cout << a << " prime" << endl;
			for (int j = 0; j < height; j++) {
				for (int i = 0; i < width; i++) {
					printf("%d", trans[buf[j][i]]);
				}
				printf("\n");
			}
			printf("\n");
			// twin-prime check
			if (my_prob_prime(a-2, width*height))
				printf("-2 is twin-prime\n");
			else if (my_prob_prime(a+2, width*height))
				printf("+2 is twin-prime\n");
		}
		return;
	}
	for (int i = 0; i < 10; i++) {
		if (depth == firstdigit && i == 0)
			continue; // 先頭の数字は0にならないようにする
		if (depth == lastdigit && (i%2 == 0 || i%5 == 0))
			continue; // lastdigitは1,3,7,9のみを試す
		if (depth > lastdigit && i == trans[lastdigit])
			continue; // 最後の数字と字面の数字はかぶらないようにする
		if (nodup) {
			bool dupfound = false;
			for (int j = 0; j < depth; j++) {
				if (trans[j] == i) {
					dupfound = true;
				}
			}
			if (dupfound) continue;
		}
		trans[depth] = i;
		doit(trans, depth+1, firstdigit, lastdigit, nodup);
	}
}

int main(int argc, char **argv)
{
	bool nodup = false;
	if (argc > 1 && strcmp(argv[1], "-nodup") == 0) {
		nodup = true;
	}
	readmap();
	printf("%d %d %d\n", width, height, maxnum);
	if (nodup && maxnum > 9) {
		printf("maxnum should be less than 10 when used with -nodup\n");
		return -1;
	}
		
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			printf("%2d", buf[j][i]);
		}
		printf("\n");
	}
	int first = buf[0][0];
	int last = buf[height-1][width-1];
	printf("last digit=%d\n", last);
	int trans[100];
	doit(trans, 0, first, last, nodup);
	return 0;
}
