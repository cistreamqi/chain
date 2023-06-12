#include"pch.h"
#include <iostream>
#include<winsock2.h>
#include <Ws2tcpip.h>
#include<tchar.h>
#include"CliFunction.h"
#include"io.h"
#include"vector"
#include <cstdio>
#include<fstream>
#include<iostream>
#include<string>
#pragma comment(lib,"ws2_32.lib")
extern "C"
{
#include <stdlib.h>
#include<time.h>
#include".\cli-rc\key.h"
#include".\cli-rc\SM2_sv.h"
}
//将16进制字符串转换为2进制字符串
void HextoTwo(unsigned char num[], char sum[][5])
{
	int res;
	int i = 0;
	int t = 0;
	char buf[BUFSIZ][5] = { "0000" };
	char reference[16][5] = { "0000", "0001", "0010", "0011",
		"0100", "0101", "0110", "0111",
		"1000", "1001", "1010", "1011",
		"1100", "1101", "1110", "1111" };
	for (int j = 0; j < 32; j++)
	{
		int s = (int)num[j];
		while (s / 16 != 0)
		{
			res = s % 16;
			strcpy_s(buf[i++], sizeof(buf[i++]), reference[res]);
			s = s / 16;
		}
		res = s % 16;
		strcpy_s(buf[i++], sizeof(buf[i++]), reference[res]);
		if (i == 1)
		{
			i = 2;
			strcpy_s(buf[1], sizeof(buf[1]), reference[0]);
		}
		strcpy_s(sum[t], sizeof(sum[t]), buf[1]);
		t++;
		strcpy_s(sum[t], sizeof(sum[t]), buf[0]);
		t++;
		i = 0;
	}
}
//输入用户标识符IDA，生成密钥dk
/*void Two_Put(unsigned char IDA2[], unsigned char dk[])
{
	char n[64][5];
	miracl* mip = mirsys(10000, 16);
	mip->IOBASE = 16;
	GetKey(IDA2, dk);//生成私钥
	printf("\n{");

	for (int i = 0; i < 32; i++)
	{
		printf("0x");
		printf("%02x ", dk[i]);
		if (i != 31)
			printf(",");
		else printf("}");
	}
	printf("\n转换为二进制: ");
	HextoTwo(dk, n);
	for (int i = 0; i < 64; i++)
	{
		printf("%s ", n[i]);
	}
	printf("\n");
}//可删私钥由sever提供*/
//签名函数
void sign_t(char message[], unsigned char sum[], unsigned char dk[], unsigned  char x[],
	unsigned  char y[], unsigned char IDA[])
{
	miracl* mip = mirsys(10000, 16);
	mip->IOBASE = 16;
	//引入时间
	irand((unsigned int)time(NULL));
	big x1, x2;
	x1 = mirvar(0);
	x2 = mirvar(0);
	bigdig(64, 16, x1);//可用来Cpk的n
	//输出随机大数
	printf("随机数: ");
	cotnum(x1, stdout);
	unsigned char* rand[32];
	big_to_bytes(SM2_n1UMWORD, x1, (char*)rand, TRUE);
	unsigned char r[32];
	unsigned char s[32];

	int testRand = 0;

	do {
		bigdig(64, 16, x1);
		char rand[32] = "";
		big_to_bytes(SM2_n1UMWORD, x1, rand, TRUE);
		testRand = SM2_testSign(message, r, s, x, y, (unsigned char*)rand, dk, IDA);

		for (int i = 0; i < 32; i++)
		{
			sum[i] = r[i];
			sum[i + 32] = s[i];
			sum[i + 64] = x[i];
			sum[i + 96] = y[i];
		}
		printf("\n");

	} while (testRand);
	mirkill(x1);
	mirexit();
}
void join(unsigned char num[32], unsigned char orc[32], char info[257])
{
	char n1[64][5], n2[64][5];
	HextoTwo(num, n1);
	HextoTwo(orc, n2);
	int s = 0;
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 4; j++)
			info[s++] = n1[i][j];
	}
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 4; j++)
			info[s++] = n2[i][j];
	}
}