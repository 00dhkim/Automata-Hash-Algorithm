#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <string.h>

#define PLAYTIME 100
#define HEIGHT 32
#define WIDTH 23
#define IS_SALT 0
#define IS_FILE_PRINT 1

FILE *logfp = fopen("PrintLog.txt", "a+");

char hashtable[64] = {
						'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
						'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
						'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
						'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F',
						'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
						'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
						'W', 'X', 'Y', 'Z', '0', '1', '2', '3',
						'4', '5', '6', '7', '8', '9', '+', '-'
};
//BASE64 table
char input[96 + 32], salt[32], binary[7];
int matrix[HEIGHT][WIDTH] = { 0, }, matrix2[HEIGHT][WIDTH] = { 0, };

void swap(int &a, int &b);
int random(int a, int b);
int CharToDec(char c);
void PrintMatrix(const char str[]);
void random_input_salt(int input_size, int salt_size);

void DO_transform_to_matrix(void);
void DO_playCA(void);
void DO_transform_to_string(void);

int main()
{
	srand((int)time(NULL));

	printf("input: ");
	scanf("%s", input);
	if (IS_FILE_PRINT) fprintf(logfp, "input: %s\n", input);
	if (IS_SALT) {
		printf("salt: ");
		scanf("%s", salt);
		strcat(input, salt);
		if (IS_FILE_PRINT) fprintf(logfp, "salt: %s\n", salt);
	}
	if (!IS_FILE_PRINT) {
		system("pause"); system("cls");
	}

//	random_input_salt(20, 5);

	DO_transform_to_matrix();	// 격자로 변환

	DO_playCA();	// 세포 자동자 실행

	DO_transform_to_string();	// 문자로 변환

	if (IS_FILE_PRINT) fprintf(logfp, "\n==========================\n\n");
	else system("pause");
	

	return 0;
}

void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

int random(int a, int b)
{
	return a + rand() % (b - a + 1);
}

int CharToDec(char c)
{
	int i = 0;
	while (hashtable[i] != c)
		i++;
	return i;
}

void PrintMatrix(const char str[])
{
	if (IS_FILE_PRINT) fprintf(logfp, "%s\n", str);
	else printf("%s\n", str);
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (IS_FILE_PRINT) {
				fprintf(logfp, "%d", matrix[i][j]);
			}
			else {
				if (matrix[i][j]) printf("■");
				else printf("□");
				// if (!((j+1) % 6)) printf(" ");
			}
		}
		if (IS_FILE_PRINT) fprintf(logfp, "\n");
		else printf("\n");
	}
	if (!IS_FILE_PRINT) {
		system("pause");
		system("cls");
	}
}

void random_input_salt(int input_size, int salt_size) {
	for (int i = 0; i < input_size; i++)
		input[i] = hashtable[random(0, 63)];
	for (int i = 0; i < salt_size; i++)
		salt[i] = hashtable[random(0, 63)];
}

void DO_transform_to_matrix(void) {	//격자로 변환
	int t = 0, i = 0, j = 0, k, num;

	while (!(i == HEIGHT - 1 && j + 6 > WIDTH - 1))	//matrix다 채우면 탈출하기
	{
		num = CharToDec(input[t++]);
		strcpy(binary, "000000");
		for (k = 5; k >= 0; k--)	// 문자를 2진수로 만들기
		{
			if (num % 2 == 1) binary[k] = '1';
			num /= 2;
		}
		if (t == strlen(input)) t = 0;

		// 2진수를 matrix[][]안에 담기
		if (j + 5 >= WIDTH) {	// 내림 해야하면
			for (k = 0; k < WIDTH - j; k++) {
				matrix[i][j + k] = (binary[k] == '1' ? 1 : 0);
			}
			i++; j = 0;
			for (; k < 6; k++, j++) {
				matrix[i][j] = (binary[k] == '1' ? 1 : 0);
			}
		}
		else {	// 바로 넣을 수 있으면
			for (k = 0; k < 6; k++) {
				matrix[i][j + k] = (binary[k] == '1' ? 1 : 0);
			}
			j += 6;
		}
	}

	for (k = 0; k < WIDTH - j; k++) { //남은 0~5칸 채우기
		matrix[i][j + k] = (binary[k] == '1' ? 1 : 0);
	}
	//	PrintMatrix(":INIT_MATRIX");
}

void DO_playCA(void) {
	int i, j, k, t;
	int dx[8] = { -1,0,1,-1,1,-1,0,1 }, dy[8] = { 1,1,1,0,0,-1,-1,-1 };

	for (t = 0; t < PLAYTIME; t++)
	{
		//주위 개수 계산
		for (i = 0; i < HEIGHT; i++)
			for (j = 0; j < WIDTH; j++)
				for (k = 0; k < 8; k++)
					if (matrix[(i + dx[k] + HEIGHT) % HEIGHT][(j + dy[k] + WIDTH) % WIDTH]) matrix2[i][j]++;	//토러스형 격자

		//규칙 판단
		for (i = 0; i < HEIGHT; i++)
		{
			for (j = 0; j < WIDTH; j++)
			{
				if ((matrix2[i][j] == 1 || matrix2[i][j] == 2 || matrix2[i][j] == 3 || matrix2[i][j] == 7) && !matrix[i][j]) matrix[i][j] = 1;
				else if ((matrix2[i][j] == 1 || matrix2[i][j] == 5 || matrix2[i][j] == 7) && matrix[i][j]) matrix[i][j] = 1;
				else matrix[i][j] = 0;
			}
		}

		memset(matrix2, 0, sizeof(matrix2));

		//		printf(":%d ", t); PrintMatrix("PLAYING");
	}
}

void DO_transform_to_string(void) {
	int i = 0, j = 0, t, k, num = 0;
	
	PrintMatrix(":END_PLAY");
	if (IS_FILE_PRINT) fprintf(logfp, "Hash Code:\n");
	else printf("Hash Code:\n");

	while (!(i == HEIGHT - 1 && j + 5 >= WIDTH))
	{
		num = 0;
		for (t = 0; t < 6; t++, j++) {
			if (j == WIDTH) {
				i++; j = 0;
			}
			num += matrix[i][j];
			num *= 2;
		}
		num /= 2;
		if (IS_FILE_PRINT) fprintf(logfp, "%c", hashtable[num]);
		else printf("%c", hashtable[num]);
	}

	// 0~5(WIDTH-j)개의 값을 matrix에서 가져오기
	num = 0;
	for (k = 0; k < WIDTH - j; k++) {
		num += matrix[i][j + k];
		num *= 2;
	}
	num /= 2;
	if (IS_FILE_PRINT) fprintf(logfp, "%c\n", hashtable[num]);
	else printf("%c\n", hashtable[num]);
}

