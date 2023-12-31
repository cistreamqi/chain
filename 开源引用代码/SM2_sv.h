#pragma once
#include<string.h>
#include<malloc.h>
#include "miracl.h"



#define SM2_WORDSIZE 8
#define SM2_n1UMBITS 256
#define SM2_n1UMWORD (SM2_n1UMBITS/SM2_WORDSIZE) //32
#define ERR_ECURVE_INIT 0x00000001
#define ERR_INFINITY_POINT 0x00000002
#define ERR_NOT_VALID_POINT 0x00000003
#define ERR_ORDER 0x00000004
#define ERR_NOT_VALID_ELEMENT 0x00000005
#define ERR_GENERATE_R 0x00000006
#define ERR_GENERATE_S 0x00000007
#define ERR_OUTRANGE_R 0x00000008
#define ERR_OUTRANGE_S 0x00000009
#define ERR_GENERATE_T 0x0000000A
#define ERR_PUBKEY_INIT 0x0000000B
#define ERR_DATA_MEMCMP 0x0000000C

big Gx, Gy, p, a, b, n;
epoint *G, *nG;
int SM2_Init();
int Test_Point(epoint* point);
int Test_PubKey(epoint *pubKey);
int Test_Zero(big x);
int Test_n(big x);
int Test_Range(big x);
int SM2_KeyGeneration(unsigned char PriKey[], unsigned char Px[], unsigned char Py[]);
int SM2_Sign(unsigned char *message, int len, unsigned char ZA[], unsigned char rand[], unsigned
	char d[], unsigned char R[], unsigned char S[]);
int SM2_Verify(unsigned char *message, int len, unsigned char ZA[], unsigned char Px[], unsigned
	char Py[], unsigned char R[], unsigned char S[]);
int SM2_SelfCheck();
int SM2_testSign(char *message, unsigned char r[], unsigned char s[], unsigned char xA[], unsigned char yA[], unsigned char rand[], unsigned char dA[], unsigned char IDA[]);
int SM2_testVerify(char *message, unsigned char r[], unsigned char s[],unsigned char xA[], unsigned char yA[], unsigned char IDA[]);