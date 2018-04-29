#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define K 128
#define N 64
#define R 80
#define W 16
#define KW K/W

//---------------------------------------------//
// cipher      |   n     k     r     w    k/w  //
//---------------------------------------------//
//											   //
// CHAM-32/64  |   64    128    80   16    8   //
//											   //
//---------------------------------------------//

uint16_t ROL(uint16_t , int );
uint16_t ROR(uint16_t, int);
int Power();
void Setkey(void*, void*);
void Encryption(void*, void*, void*);
void Decryption(void*, void*, void*);
