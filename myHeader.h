#ifndef MYHEADER_H
#define MYHEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

void swap(int &a, int &b);
int random(int a, int b);
int CharToDec(char c);
void PrintMatrix(const char str[]);
void random_input_salt(int input_size, int salt_size);

void DO_transform_to_matrix(void);
void DO_playCA(void);
void DO_transform_to_string(void);

void myPrint(const char str[], ...);	// Made by DongHwan

constexpr auto PLAYTIME = 100;
constexpr auto HEIGHT = 32;
constexpr auto WIDTH = 23;
constexpr auto IS_SALT = 0;
constexpr auto PRINT_MODE = 0;	// 0: none, 1: stdout, 2: file

extern FILE *logfp;
extern char hashtable[64];
extern char input[96 + 32], salt[32], binary[7];
extern int matrix[HEIGHT][WIDTH], matrix2[HEIGHT][WIDTH];

#endif // MYHEADER_H
