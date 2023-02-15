#include "checksum.h"

#include "../util.h"
#include "entropy.h"

BIP39::CheckSum::CheckSum()
{
	
}

BIP39::CheckSum::CheckSum(const uint8_t sum)
{
	this->sum = sum;
}

void BIP39::CheckSum::Set(const uint8_t sum)
{
	this->sum = sum;
}

uint8_t BIP39::CheckSum::Get()
{
	return this->sum;
}

std::string BIP39::CheckSum::GetStr()
{	
	return "0x" + HexStr(&this->sum, &this->sum + 1);
}

bool BIP39::CheckSum::isValid(BIP39::Entropy& entropy)
{
	return this->sum == entropy.genCheckSum().Get();
}

