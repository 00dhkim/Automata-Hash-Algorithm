#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define PLAYTIME 100

char hashtable[64] = {
						'~', '!', '@', '#', '$', '%', '^', '&', '*', '_', '+', '|', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
						};
char input[96], salt[32], output[128];
int matrix[32][24] = { 9, }, inputsize = 0, saltsize = 0;

void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

int random(int a, int b)
{
	return a + rand() % (b - a);
}

int CharToDec(char c)
{
	int i = 0;
	while (hashtable[i] != c)
		i++;
	return i;
}

void PrintMatrix()
{
	system("cls");
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			if (matrix[i][j]) printf("■");
			else printf("□");
		}
		printf("\n");
	}
	system("pause");
}

int main()
{
	int i, j, k, num;

	printf("input: ");
	scanf("%s", input);
	printf("salt: ");
	scanf("%s", salt);

	while (input[inputsize] != 0)
		inputsize++;

	while (salt[saltsize] != 0)
		saltsize++;

	//======================================================
	//====================격자로 변환=======================

	int t = 0;	//t는 매트릭스에 값 넣을때 첫째 라인에서 둘째 라인으로 넘어가는 과정에서 문자가 부드럽게 지속적으로 들어가도록 하기 위한 변수임. 이 값은 계속 1씩 더해지고 t를 inputzise로 나눈 나머지 값에 해당하는 input값을 2진수로 변환하면 됨. 따라서 t는 종료시 96임. (j는 0~32를 3번 반복하는 반면에)
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 32; j++)
		{
			num = CharToDec(input[t%inputsize]);

			for (k = 5; k >= 0; k--)
			{
				matrix[j][8 * i + k] = num % 2;
				num /= 2;
			}
			t++;
		}
	}

	//salt 첨가
	for (i = 0; i < 32; i++)
	{
		int num = CharToDec(salt[i%saltsize]);
		matrix[i][23] = num % 2;
		num /= 2;
		matrix[i][22] = num % 2;
		num /= 2;
		matrix[i][15] = num % 2;
		num /= 2;
		matrix[i][14] = num % 2;
		num /= 2;
		matrix[i][7] = num % 2;
		num /= 2;
		matrix[i][6] = num % 2;
	}
	//PrintMatrix();
	//====================격자로 변환=======================
	//======================================================
	//=================세포 자동자 실행=====================
	
	int matrix2[32][24] = { 0, };
	int dx[8] = { -1,0,1,-1,1,-1,0,1 }, dy[8] = { 1,1,1,0,0,-1,-1,-1 };

	//PrintMatrix();
	for (int q = 0; q < PLAYTIME; q++)
	{
		//주위 개수 계산
		for (i = 0; i < 32; i++)
			for (j = 0; j < 24; j++)
				for (k = 0; k < 8; k++)
					if (matrix[(i + dx[k]+32)%32][(j + dy[k]+24)%24]) matrix2[i][j]++;	//토러스형 격자

		//규칙 판단
		for (i = 0; i < 32; i++)
		{
			for (j = 0; j < 24; j++)
			{
				if ((matrix2[i][j] == 1 || matrix2[i][j] == 2 || matrix2[i][j] == 3 || matrix2[i][j] == 7) && !matrix[i][j]) matrix[i][j] = 1;
				else if ((matrix2[i][j] == 1 || matrix2[i][j] == 5 || matrix2[i][j] == 7) && matrix[i][j]) matrix[i][j] = 1;
				else matrix[i][j] = 0;
			}
		}

		for (i = 0; i < 32; i++)
			for (j = 0; j < 24; j++)
				matrix2[i][j] = 0;

		//PrintMatrix();
	}
	//PrintMatrix();
	
	//=================세포 자동자 실행=====================
	//======================================================
	//====================문자로 변환=======================

	for (i = 0; i < 32; i++)
	{
		for (j = 0; j < 4; j++)
		{
			num = 0;

			for (k = 0; k < 6; k++)
			{
				num += matrix[i][6 * j + k];
				num *= 2;
			}
			num /= 2;
			printf("%c", hashtable[num]);
		}
	}
	printf("\n");

	//====================문자로 변환=======================
	//======================================================

	system("pause");
	return 0;
}