#include "cham.h"
#define POWER 1<<=W;

uint16_t ROL(uint16_t input, int k)
{
	uint16_t temp;
	temp = input;
	temp >>= (W - k);
	input <<= k;
	temp |= input;
	return temp;
};

uint16_t ROR(uint16_t input, int k)
{
	uint16_t temp;
	temp = input;
	temp <<= (W - k);
	input >>= k;
	temp |= input;
	return temp;
};

int Power()	
{
	int result = 1;
	result <<= W;
	return result;
};

//---------------------------------------------//
// cipher      |   n     k     r     w    k/w  //
//---------------------------------------------//
//											   //
// CHAM-32/64  |   64    128    80   16    8   //
//											   //
//---------------------------------------------//

void Setkey(void *input, void *output)
{
	int i;
	//input = key    ,    output = RK
	// Round Key setting( w-bit ���� , 2K/W �� )
	for (i = 0; i < KW; i++)
	{
		((uint16_t*)output)[i]				= ((uint16_t*)input)[i] ^ ROL(((uint16_t*)input)[i], 1) ^ ROL(((uint16_t*)input)[i], 8);	// RK[0] ~ RK[7]
		((uint16_t*)output)[(i + KW) ^ 1]	= ((uint16_t*)input)[i] ^ ROL(((uint16_t*)input)[i], 1) ^ ROL(((uint16_t*)input)[i], 11);	// RK[8] ~ RK[15]
	}
};


// PT�� 16bit ������ ���� 4���� �����Ǿ�����
// PT = PT[0] || PT[1] || PT[2] || PT[3]
void Encryption(void *PT, void *CT, void*RK)
{
	int i;
	uint16_t x[4];
	uint16_t x_temp;
	uint16_t a, b, c, d,  f, g, h;
	int e;

	x[0] = ((uint16_t*)PT)[0];
	x[1] = ((uint16_t*)PT)[1];
	x[2] = ((uint16_t*)PT)[2];
	x[3] = ((uint16_t*)PT)[3];

	// ROUND ����
	for (i = 0; i < R; i++)
	{
		if (i % 2 == 0)	// ���� ���尡 ¦�� ���� �̸� (EVEN) -> 0 round ���� ������
			x_temp = ROL((x[0] ^ i) + ((ROL(x[1], 1) ^ ((uint16_t*)RK)[i % (2 * KW)]) % Power()), 8);
		else			// ���� ���尡 Ȧ�� ���� �̸� (ODD)
			x_temp = ROL((x[0] ^ i) + ((ROL(x[1], 8) ^ ((uint16_t*)RK)[i % (2 * KW)]) % Power()), 1);

		x[0] = x[1];
		x[1] = x[2];
		x[2] = x[3];
		x[3] = x_temp;
	}

	((uint16_t*)CT)[0] = x[0];
	((uint16_t*)CT)[1] = x[1];
	((uint16_t*)CT)[2] = x[2];
	((uint16_t*)CT)[3] = x[3];
};


void Decryption(void *CT, void *RCT, void*RK)
{
	int i;
	uint16_t x[4];
	uint16_t x_temp;

	x[0] = ((uint16_t*)CT)[0];
	x[1] = ((uint16_t*)CT)[1];
	x[2] = ((uint16_t*)CT)[2];
	x[3] = ((uint16_t*)CT)[3];

	for (i = R-1; i >=0 ; i--)
	{
		x_temp = x[3];
		x[3] = x[2];
		x[2] = x[1];
		x[1] = x[0];
		
		if (i % 2 == 0)	// ���� ���尡 ¦�� ���� �̸� (EVEN) -> 79 round ���� ������
			x[0] = (ROR(x_temp, 8) - ((ROL(x[1], 1) ^ ((uint16_t*)RK)[i % (2 * KW)]) % Power())) ^ i;
		else			// ���� ���尡 Ȧ�� ���� �̸� (ODD)
			x[0] = (ROR(x_temp, 1) - ((ROL(x[1], 8) ^ ((uint16_t*)RK)[i % (2 * KW)]) % Power())) ^ i;
	}

	((uint16_t*)RCT)[0] = x[0];
	((uint16_t*)RCT)[1] = x[1];
	((uint16_t*)RCT)[2] = x[2];
	((uint16_t*)RCT)[3] = x[3];

};