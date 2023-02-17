/*
	Reference:
		https://en.bitcoin.it/wiki/BIP_0039
		https://learnmeabitcoin.com/technical/mnemonic
		https://github.com/bitcoin/bips/tree/master/bip-0039
*/

#include <iostream>

#include "bip39/entropy.h"
#include "bip39/checksum.h"
#include "bip39/mnemonic.h"

void test_new_entropy()
{
	BIP39::Entropy entropy;
	
	std::cout << "--- NEW ENTROPY ---" << std::endl;
	
	if(entropy.genRandom())
	{
		std::cout << "Entropy = " << entropy.GetStr() << std::endl;
	}
	else
	{
		std::cout << "Generate Entropy failed :(" << std::endl;
	}
}

void test_new_checksum()
{
	BIP39::Entropy entropy;
	
	std::cout << "--- NEW CHECKSUM ---" << std::endl;
	
	if(!entropy.genRandom())
	{
		std::cout << "Failed to generate new random entropy." << std::endl;
		return;
	}
	
	BIP39::CheckSum checksum = entropy.genCheckSum();
	
	std::cout << "Entropy  = " << entropy.GetStr() << std::endl;
	std::cout << "Checksum = " << checksum.GetStr() << std::endl;
	
	std::cout << "checksum.isValid() = " << std::boolalpha << checksum.isValid(entropy) << std::endl;
	
	checksum.Set(0x0);
	
	std::cout << "checksum.isValid() = " << std::boolalpha << checksum.isValid(entropy) << std::endl;
}

void test_new_mnemonic()
{
	int pos;
	BIP39::Mnemonic mnemonic;
	BIP39::Entropy entropy;
	BIP39::CheckSum checksum;
	
	std::cout << "--- NEW MNEMONIC ---" << std::endl;
	
	if(!mnemonic.LoadLanguage())
	{
		std::cout << "Failed to load language." << std::endl;
		return;
	}
	
	std::cout << "Found " << mnemonic.GetLanguageWords().size() << " total words." << std::endl;
	
	if(mnemonic.Find("acid", &pos))
	{
		std::cout << "Found 'acid' on position " << pos << std::endl;
	}
	
	if(!entropy.genRandom())
	{
		std::cout << "Failed to generate new random entropy." << std::endl;
		return;
	}
	
	checksum = entropy.genCheckSum();
		
	if(mnemonic.Set(entropy, checksum))
	{
		std::cout << "Entropy  = " << entropy.GetStr() << std::endl;
		std::cout << "Checksum = " << checksum.GetStr() << std::endl;
		std::cout << "mnemonic = " << mnemonic.GetStr() << std::endl;
	}
}

int main()
{
	test_new_entropy();
	test_new_checksum();
	test_new_mnemonic();
	
	return 0;
}

