#include "checksum.h"

#include "../util.h"
#include "entropy.h"

BIP39::CheckSum::CheckSum()
{
	
}

BIP39::CheckSum::CheckSum(const uint8_t sum)
{
	this->_sum = sum;
}

void BIP39::CheckSum::Set(const uint8_t sum)
{
	this->_sum = sum;
}

uint8_t BIP39::CheckSum::Get() const
{
	return this->_sum;
}

std::string BIP39::CheckSum::GetStr() const
{	
	return "0x" + HexStr(&this->_sum, &this->_sum + 1);
}

bool BIP39::CheckSum::isValid(const BIP39::Entropy& entropy) const
{
	return this->_sum == entropy.genCheckSum().Get();
}

