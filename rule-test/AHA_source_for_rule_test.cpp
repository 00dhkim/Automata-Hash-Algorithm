#include <Windows.h>
#include "myHeader.h"

FILE *fp = fopen("rt_pair.txt", "a+");

void fPrintMatrix_rt()	// rt_pair.txt에 matrix 쌓는 함수
{
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			fprintf(fp, "%d", matrix[i][j]);
		}
		fprintf(fp, "\n");
	}
}

void decToBinary(int n)
{
	int binaryNum[32] = { 0, };
	int i = 0;
	while (n > 0) {
		binaryNum[i] = n % 2;
		n = n / 2;
		i++;
	}
	for (int j = 5; j >= 0; j--)
		fprintf(fp, "%d", binaryNum[j]);
	fprintf(fp, "\n");
}

// 모든 input bits에 대해서 matrix 출력하기
int main()
{
	srand((int)time(NULL));

	for (int num = 0; num < 64; num++) {
		decToBinary(num);
		input[0] = hashtable[num];

		/*	buf = fgetc(stdin);
			while (buf != 10 && buf != EOF) {
				if (buf == ' ') {
					buf = fgetc(stdin);
					continue;
				}
				num += (buf == '1' ? 1 : 0);
				num *= 2;
				if (++cnt == 6) {
					cnt = 0;
					input[i++] = hashtable[num / 2];
					num = 0;
				}
				buf = fgetc(stdin);
			}
		//	puts(input);
		*/

		DO_transform_to_matrix();	// 격자로 변환

		DO_playCA();	// 세포 자동자 실행

		fPrintMatrix_rt();
	}

	fclose(fp);
	return 0;
}

