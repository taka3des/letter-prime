// readbdf - simple BDF reader
// (c)2018 Seishi Takamura
#include <stdio.h>
#include <string.h>

unsigned char *bdf_load(char *name, int *width, int *height, int *cnum, int **codes)
{
	FILE *fp = fopen(name, "r");
	if (fp == NULL) return NULL;
	char buf[512];
	while (!feof(fp)) {
		fgets(buf, sizeof(buf), fp);
		if (strncmp(buf, "FONTBOUNDINGBOX ", 16) == 0) {
			sscanf(buf+16, "%d%d", width, height);
			printf("#%dx%d\n", *width, *height);
			break;
		}
	}
	while (!feof(fp)) {
		fgets(buf, sizeof(buf), fp);
		if (strncmp(buf, "CHARS ", 6) == 0) {
			sscanf(buf+6, "%d", cnum);
			printf("#cnum %d\n", *cnum);
			break;
		}
	}
	int chars = (*width + 3) / 4;
	unsigned char *p, *image = new unsigned char[*width * *height * *cnum];
	p = image;
	int *c = *codes = new int[*cnum];
	for (int i = 0; i < *cnum; i++) {
		while (!feof(fp)) {
			fgets(buf, sizeof(buf), fp);
			if (strncmp(buf, "ENCODING ", 9) == 0) {
				sscanf(buf+9, "%d", &*c++);
			}
			if (strncmp(buf, "BITMAP", 6) == 0)
				break;
		}
		for (int j = 0; j < *height; j++) {
			fgets(buf, sizeof(buf), fp);
			for (int c = 0, pos = 0; c < chars; c++) {
				int val;
				sscanf(buf+c, "%1x", &val);
				for (int m = 8; m > 0 && pos < *width; m /= 2, pos++) {
					*p++ = (val & m) ? 0 : 255;
				}
			}
		}
	}
	return image;
}
