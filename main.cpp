#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include "CPUheader.h"
#include <string.h>
#include <string>
#include <string.h>
#define Nb 4 
#define KeySize  240

using namespace std;

//======================================================================================================
//											COMMON VARIABLES
//======================================================================================================
int Nr = 0;
int Nk = 0;

string str_in;
char *tempt, *a, *b;
char *source, *dest;
unsigned char Key[32] =
{ 'a', 'b', 'c', 'd',
'e', 'f', 'g', 'h',
'i', 'j', 'k', 'l',
'm', 'n', 'o', 'p',
'a', 'b', 'c', 'd',
'e', 'f', 'g', 'h',
'i', 'j', 'k', 'l',
'm', 'n', 'o', 'p' };

unsigned char RoundKey[240];
int Isbox[256] = {
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	/*1*/  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	/*2*/  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	/*3*/  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	/*4*/  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	/*5*/  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	/*6*/  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	/*7*/  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	/*8*/  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	/*9*/  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	/*a*/  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	/*b*/  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	/*c*/  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	/*d*/  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	/*e*/  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	/*f*/  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};
int Sbox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};
int Rcon[255] = {
	0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
	0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
	0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
	0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
	0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
	0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
	0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
	0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
	0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
	0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
	0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
	0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
	0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
	0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
	0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
	0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb };


//======================================================================================================
//											CPU VARIABLES
//======================================================================================================
unsigned char State_CPU[4][4];
FILE *in_file_CPU, *input_file_CPU, *output_file_CPU;
LARGE_INTEGER start_CPU, end_CPU, frequency_CPU;
double processingTimeCPU;






//======================================================================================================
//										     CPU METHODS
//======================================================================================================
char* CreatText(char type[])
{
	int length = str_in.length();
	char *tempt = (char *)malloc(length*sizeof(char));
	char  *a = (char *)malloc(length*sizeof(char));
	char  *b = (char *)malloc(length*sizeof(char));

	for (int i = 0; i < length + 1; i++)
		tempt[i] = str_in[i];


	for (int i = 0; i < strlen(tempt); i++)
	{
		if (tempt[i] == '.')
		{
			a[i] = '\0'; break;
		}
		a[i] = tempt[i];
	}

	for (int i = strlen(a); i < strlen(tempt) + 1; i++)
		b[i - strlen(a)] = tempt[i];

	char* str_ou = (char *)malloc((length + strlen(type))*sizeof(char));
	for (int i = 0; i < strlen(a); i++)
		str_ou[i] = a[i];
	for (int i = strlen(a); i < strlen(a) + strlen(type) + 1; i++)
		str_ou[i] = type[i - strlen(a)];

	for (int i = strlen(a) + strlen(type); i < strlen(a) + strlen(type) + strlen(b) + 1; i++)
		str_ou[i] = b[i - strlen(a) - strlen(type)];

	return str_ou;
}

int getSBoxValue(int num)
{
	return Sbox[num];
}

int get_ISBoxValue(int num)
{
	return Isbox[num];
}

unsigned char gf_mult(unsigned char a, unsigned char b) {
	int i;
	int retval;

	retval = a * b;
	if (retval < 128)
		return retval;
	else
		retval = 0;

	for (i = 0; i < 8; i++) {
		if ((b & 1) == 1)
			retval ^= a;

		if ((a & 0x80) == 0x80) {
			a <<= 1;
			a ^= 0x1b;
		}
		else {
			a <<= 1;
		}

		b >>= 1;
	}

	return (unsigned char)retval;
}

void KeyExpansion()
{
	int i, j;
	unsigned char temp[4], k;


	for (i = 0; i<Nk; i++)
	{
		RoundKey[i * 4] = Key[i * 4];
		RoundKey[i * 4 + 1] = Key[i * 4 + 1];
		RoundKey[i * 4 + 2] = Key[i * 4 + 2];
		RoundKey[i * 4 + 3] = Key[i * 4 + 3];
	}


	while (i < (Nb * (Nr + 1)))
	{
		for (j = 0; j<4; j++)   // chép 4 word trước đó lại 
		{// i = 8 
			temp[j] = RoundKey[(i - 1) * 4 + j];   // 28 29 30 31
		}
		if (i % Nk == 0)  // các w số 8  16  24 ... 
		{
			//  RotWord()
			{
				k = temp[0];
				temp[0] = temp[1];
				temp[1] = temp[2];
				temp[2] = temp[3];
				temp[3] = k;
			}

			//  Subword()
			{
				temp[0] = getSBoxValue(temp[0]);
				temp[1] = getSBoxValue(temp[1]);
				temp[2] = getSBoxValue(temp[2]);
				temp[3] = getSBoxValue(temp[3]);
			}
			// Xor RCON
			temp[0] = temp[0] ^ Rcon[i / Nk];
		}
		else if (Nk > 6 && i % Nk == 4) //  Nk = 8  i = 12  20  28   36   44   52  60  
		{
			//  Subword()
			{
				temp[0] = getSBoxValue(temp[0]);
				temp[1] = getSBoxValue(temp[1]);
				temp[2] = getSBoxValue(temp[2]);
				temp[3] = getSBoxValue(temp[3]);
			}
		}
		RoundKey[i * 4 + 0] = RoundKey[(i - Nk) * 4 + 0] ^ temp[0];
		RoundKey[i * 4 + 1] = RoundKey[(i - Nk) * 4 + 1] ^ temp[1];
		RoundKey[i * 4 + 2] = RoundKey[(i - Nk) * 4 + 2] ^ temp[2];
		RoundKey[i * 4 + 3] = RoundKey[(i - Nk) * 4 + 3] ^ temp[3];
		i++;
	}
}

void AddRoundKey(int round)
{
	int i, j;
	for (i = 0; i<4; i++)
		for (j = 0; j<4; j++)
			State_CPU[j][i] ^= RoundKey[round * Nb * 4 + i * Nb + j];

}

void SubBytes()
{
	int i, j;
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			State_CPU[i][j] = getSBoxValue(State_CPU[i][j]);

		}
	}
}

void Inv_SubBytes()
{
	int i, j;
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			State_CPU[i][j] = get_ISBoxValue(State_CPU[i][j]);

		}
	}
}

void ShiftRows()
{
	unsigned char temp;

	temp = State_CPU[1][0];
	State_CPU[1][0] = State_CPU[1][1];
	State_CPU[1][1] = State_CPU[1][2];
	State_CPU[1][2] = State_CPU[1][3];
	State_CPU[1][3] = temp;

	temp = State_CPU[2][0];
	State_CPU[2][0] = State_CPU[2][2];
	State_CPU[2][2] = temp;

	temp = State_CPU[2][1];
	State_CPU[2][1] = State_CPU[2][3];
	State_CPU[2][3] = temp;

	temp = State_CPU[3][0];
	State_CPU[3][0] = State_CPU[3][3];
	State_CPU[3][3] = State_CPU[3][2];
	State_CPU[3][2] = State_CPU[3][1];
	State_CPU[3][1] = temp;
}

void Inv_ShiftRows()
{
	unsigned char temp;

	temp = State_CPU[1][3];
	State_CPU[1][3] = State_CPU[1][2];
	State_CPU[1][2] = State_CPU[1][1];
	State_CPU[1][1] = State_CPU[1][0];
	State_CPU[1][0] = temp;

	temp = State_CPU[2][2];
	State_CPU[2][2] = State_CPU[2][0];
	State_CPU[2][0] = temp;

	temp = State_CPU[2][3];
	State_CPU[2][3] = State_CPU[2][1];
	State_CPU[2][1] = temp;

	temp = State_CPU[3][1];
	State_CPU[3][1] = State_CPU[3][2];
	State_CPU[3][2] = State_CPU[3][3];
	State_CPU[3][3] = State_CPU[3][0];
	State_CPU[3][0] = temp;
}

int gfmultby01(int b)
{
	return (b % 256);
}

int gfmultby02(int b)
{
	if (b < 0x80) // nếu b7 =0
		return ((b << 1) % 256);
	else // nếu b7 =1
		return (((b << 1) % 256 ^ (int)(0x1b))); // 0x1b = 00011011 ; b7b6b5b4b3b2b1b0 << 1 = b6b5b4b3b2b1b00 (dịch bít trái)
}

int gfmultby03(int b)
{
	return ((gfmultby02(b) ^ b) % 256);
}

int gfmultby09(int b)
{
	return ((gfmultby02(gfmultby02(gfmultby02(b))) ^ b) % 256);
}

int gfmultby0b(int b)
{
	return ((gfmultby02(gfmultby02(gfmultby02(b))) ^ gfmultby02(b) ^ b) % 256);
}

int gfmultby0d(int b)
{
	return ((gfmultby02(gfmultby02(gfmultby02(b))) ^ gfmultby02(gfmultby02(b)) ^ b) % 256);
}

int gfmultby0e(int b)
{
	return ((gfmultby02(gfmultby02(gfmultby02(b))) ^ gfmultby02(gfmultby02(b)) ^ gfmultby02(b)) % 256);
}

void MixColumns()
{
	int temp[4][4];
	for (int r = 0; r < 4; ++r)  // copy State_CPU into temp[]
	{
		for (int c = 0; c < 4; ++c)
		{
			temp[r][c] = State_CPU[r][c];
		}
	}

	for (int c = 0; c < 4; ++c)
	{
		State_CPU[0][c] = ((int)gfmultby02(temp[0][c]) ^ (int)gfmultby03(temp[1][c]) ^
			(int)gfmultby01(temp[2][c]) ^ (int)gfmultby01(temp[3][c]));
		State_CPU[1][c] = ((int)gfmultby01(temp[0][c]) ^ (int)gfmultby02(temp[1][c]) ^
			(int)gfmultby03(temp[2][c]) ^ (int)gfmultby01(temp[3][c]));
		State_CPU[2][c] = ((int)gfmultby01(temp[0][c]) ^ (int)gfmultby01(temp[1][c]) ^
			(int)gfmultby02(temp[2][c]) ^ (int)gfmultby03(temp[3][c]));
		State_CPU[3][c] = ((int)gfmultby03(temp[0][c]) ^ (int)gfmultby01(temp[1][c]) ^
			(int)gfmultby01(temp[2][c]) ^ (int)gfmultby02(temp[3][c]));
	}
}  // MixColumns

void InvMixCoLumns()
{
	int temp[4][4];
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			temp[r][c] = State_CPU[r][c];

	for (int c = 0; c < 4; ++c)
	{
		State_CPU[0][c] = (gfmultby0e(temp[0][c]) ^ gfmultby0b(temp[1][c]) ^
			gfmultby0d(temp[2][c]) ^ gfmultby09(temp[3][c]));
		State_CPU[1][c] = (gfmultby09(temp[0][c]) ^ gfmultby0e(temp[1][c]) ^
			gfmultby0b(temp[2][c]) ^ gfmultby0d(temp[3][c]));
		State_CPU[2][c] = (gfmultby0d(temp[0][c]) ^ gfmultby09(temp[1][c]) ^
			gfmultby0e(temp[2][c]) ^ gfmultby0b(temp[3][c]));
		State_CPU[3][c] = (gfmultby0b(temp[0][c]) ^ gfmultby0d(temp[1][c]) ^
			gfmultby09(temp[2][c]) ^ gfmultby0e(temp[3][c]));
	}
}

void Cipher()
{
	int i, j, round = 0;

	AddRoundKey(0);

	for (round = 1; round<Nr; round++)
	{
		SubBytes();
		ShiftRows();
		MixColumns();
		AddRoundKey(round);
	}

	SubBytes();
	ShiftRows();
	AddRoundKey(Nr);
}

void Inv_Cipher()
{
	int i, j, round = 0;

	AddRoundKey(Nr);

	for (round = Nr - 1; round>0; round--)
	{
		Inv_ShiftRows();
		Inv_SubBytes();
		AddRoundKey(round);
		InvMixCoLumns();

	}

	Inv_ShiftRows();
	Inv_SubBytes();
	AddRoundKey(0);

}

//======================================================================================================
//											MAIN FUNCTION
//======================================================================================================

int main(int argc, char ** argv)
{

	cout << "                       Encryption with AES-CPU                           " << endl;

	cout << "\n Input file :  ";
	getline(cin, str_in);

	int length = str_in.length();

	char *source = (char *)malloc(length*sizeof(char));
	for (int i = 0; i < length + 1; i++)
		source[i] = str_in[i];

	int ch;
	int countchar = 0;
	int element = 0;
	bool Lack = false;
	Nr = 256;
	Nk = Nr / 32;
	Nr = Nk + 6;


	int code_order;
	cout << "\n\n";
	cout << " CHOISE :\n";
	cout << " 0. encryption\n\n";
	cout << " 1. decryption\n\n";

	while (1)
	{
		cout << " THE CHOICE IS : ";
		cin >> code_order;
		if ((code_order == 0) || (code_order == 1))
			break;
		cout << "\n ----------------->>> Unvalid number ! \n\n";
	}
	if (code_order == 0)
	{
		dest = CreatText("_CIPHER");
		cout << "\n Output file is :  " << dest << "\n";
		char *str_in_Result;
		char *str_out_Result;

		str_in_Result = source;
		str_out_Result = dest;
		// đọc và ghi dữ liệu

		in_file_CPU = fopen(str_in_Result, "rb");
		input_file_CPU = fopen(str_in_Result, "rb");
		output_file_CPU = fopen(str_out_Result, "wb");

	}

	if (code_order == 1)
	{
		dest = CreatText("_INVERT");
		cout << "\n Output file is :  " << dest << "\n";
		char *str_in_Result = source;
		char *str_out_Result = dest;

		in_file_CPU = fopen(str_in_Result, "rb");
		input_file_CPU = fopen(str_in_Result, "rb");
		output_file_CPU = fopen(str_out_Result, "wb");

	}
	cout << "\n\n ------------------------ BEGIN ------------------------\n";
	while (1)
	{
		ch = fgetc(in_file_CPU);
		if (ch == EOF)
			break;
		++countchar;
	}
	cout << "\n Total size : " << countchar / 1000 << " Kb\n";

	if (code_order == 0)
		cout << "\n CPU Encryption start ...";
	else
		cout << "\n CPU Decryption start ...";

	::QueryPerformanceFrequency(&frequency_CPU);

	QueryPerformanceCounter(&start_CPU);


	KeyExpansion();

	while (element < countchar)
	{
		int count = 0;
		unsigned char c;
		for (count = 0; count < 16; count++)
		{
			element++;
			if (code_order == 0)
				if (element == (countchar + 1))
				{
					State_CPU[count % 4][count / 4] = 170;
					for (int i = count + 1; i < 16; i++)
						State_CPU[i % 4][i / 4] = 0;
					goto cycle;
				}
			if (code_order == 1)
				if (element == countchar)
					Lack = true;
			c = fgetc(input_file_CPU);
			State_CPU[count % 4][count / 4] = c;
		}

	cycle:
		if (code_order == 0)
			Cipher();
		if (code_order == 1)
			Inv_Cipher();

		int dele = 16;
		if (code_order == 1)
			for (int i = 0; i < dele; i++)
			{
				unsigned char x = State_CPU[i % 4][i / 4];
				if ((State_CPU[i % 4][i / 4] == 170) && (Lack))
					break;
				fputc(x, output_file_CPU);
			}
		if (code_order == 0)
			for (int i = 0; i < dele; i++)
			{
				unsigned char x = State_CPU[i % 4][i / 4];
				fputc(x, output_file_CPU);
			}
	}

	cout << "\n\n Complete !";
	::QueryPerformanceCounter(&end_CPU);
	processingTimeCPU = (double)(end_CPU.QuadPart - start_CPU.QuadPart) / frequency_CPU.QuadPart;

	printf("\n\n Total encryption time CPU : %.3f (s)\n\n\n", processingTimeCPU);

	for (int i = 0; i < 240; i++)
		RoundKey[i] = 0;
	
	fclose(output_file_CPU);
	fclose(input_file_CPU);
	fclose(in_file_CPU);

	//===========================================End CPU Encryption=========================================

	double SpeedCPU;
	SpeedCPU = countchar / processingTimeCPU / 1000000;
	printf("\n\n\n Speed of CPU %.3f Mb/s ", SpeedCPU);

	//End:
	cout << "\n\n ------------------------- END -------------------------\n";

	getchar();
	getchar();
	return 0;
}
