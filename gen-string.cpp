// gen-string - generate string map
// (c)2018 Seishi Takamura

/* ./string-prime 4x6.bdf Taka
11100000300000000000000000000000099000000b000000d0000e00
0100022030300440505060607070088090000a0000000cc0dd000000
010020203300404055506060770080800900a0a0bb00cc00d0d0ee00
010020203030404050506060700080800090aa000b0000c0d0d00e00
0100022030300440505006607000088099000aa0bbb0cc00d0d0eee0
00000000000000000000000000000000000000000000000000000000
*/

#include "readbdf.cpp"
// ”wŒi‚Í'0', ‘OŒi(•¶Žš)‚Í1,2,3,...‚Æ‚µ‚ÄƒŒƒ“ƒ_ƒŠƒ“ƒO
void setfont2(char *s, int pos, int len, unsigned char *img, int width, int height, int blk)
{
	s += width * pos;
	char blk_c = (blk >= 10) ? blk - 10 + 'a' : blk + '0'; // 012..789abcde...
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			s[w + h*(width*len)] = (*img++ == 0) ? blk_c : '0';
		}
	}
}

int main(int argc, char **argv)
{
	int width, height, cnum;
	int *codes;
	if (argc < 3) {
		printf("usage: gen-string bdf_file [ascii-string | -j file]\n");
		return -1;
	}
	unsigned char *image = bdf_load(argv[1], &width, &height, &cnum, &codes);
	int len = 0, intstr[100];
	if (strcmp(argv[2], "-j") == 0) {
		FILE *fp = fopen(argv[3], "r");
		if (fp == NULL) {
			printf("cannot open file %s\n", argv[3]);
			return -1;
		}
		int ch;
		while ((ch = fgetc(fp)) != EOF) {
			if (ch == '\e') {
				ch = fgetc(fp); // '$'
				ch = fgetc(fp); // 'B'
			} else if (ch == '\n' || ch == '\r') {
				continue;
			} else {
				int ch2 = fgetc(fp);
			//	printf("<%c %c>", ch, ch2);
				intstr[len++] = ch*256 + ch2;
			//	printf("%d ", intstr[len-1]);
			}
		}
	} else {
		len = strlen(argv[2]);
		for (int i = 0; i < len; i++)
			intstr[i] = (int)argv[2][i];
		printf("#string=<%s>, length=%d\n", argv[2], len);
	}

	char s[width * len * height + 1];
	for (int pos = 0; pos < len; pos++) {
		int ch;
		for (ch = 0; ch < cnum; ch++) {
			if (codes[ch] == intstr[pos])
				break;
		}
		if (ch == cnum) {
			printf("the character (%c) not found in bdf file.\n", intstr[pos]);
			return -1;
		}
		setfont2(s, pos, len, &image[ch*width*height], width, height, pos+1);
	}
	s[width * len * height] = '\0';
	for (int i = 0; i < width*len*height; i++) {
		putchar(s[i]);
		if ((i+1) % (width*len) == 0)
			putchar('\n');
	}
	fflush(stdout);
	delete image;
	delete codes;
	return 0;
}
