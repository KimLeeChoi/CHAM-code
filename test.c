#include "cham.h"
using namespace std;

int main()
{
	uint16_t key[8] = { 0x0100, 0x0302, 0x0504, 0x0706, 0x0908, 0x0b0a, 0x0d0c, 0x0f0e};
	uint16_t RK[16];
	uint16_t PT[4] = {0x1100, 0x3322, 0x5544, 0x7766};
	uint16_t CT[4];
	uint16_t RCT[4];

	int i = 0;

	Setkey(key, RK);
	Encryption(PT, CT, RK);
	Decryption(CT, RCT, RK);

	cout << "PT  : " << PT[0]<< PT[1]<< PT[2]<< PT[3]<<endl;
	cout << "CT  : " << CT[0]<< CT[1]<< CT[2]<< CT[3]<<endl;
	cout << "RCT  : " << RCT[0]<< RCT[1]<< RCT[2]<< RCT[3]<<endl;

} 
