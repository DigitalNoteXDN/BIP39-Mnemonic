/*
	Reference:
		https://en.bitcoin.it/wiki/BIP_0039
		https://learnmeabitcoin.com/technical/mnemonic
		https://github.com/bitcoin/bips/tree/master/bip-0039
		https://pypi.org/project/bip-utils/2.3.0/#files
*/

#include <iostream>

#include "bip39/entropy.h"
#include "bip39/checksum.h"
#include "bip39/mnemonic.h"

void test_new_entropy()
{
	BIP39::Entropy entropy;
	
	std::cout << "--- NEW ENTROPY ---" << std::endl;
	
	// Generate random entropy
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
	BIP39::CheckSum checksum;
	
	std::cout << "--- NEW CHECKSUM ---" << std::endl;
	
	// Generate random entropy
	if(!entropy.genRandom())
	{
		std::cout << "Failed to generate new random entropy." << std::endl;
		return;
	}
	
	// Generate checksum
	if(!entropy.genCheckSum(&checksum))
	{
		std::cout << "Failed to generate checksum." << std::endl;
		return;
	}
	
	// Test newly generated entropy and checksum
	std::cout << "Entropy  = " << entropy.GetStr() << std::endl;
	std::cout << "Checksum = " << checksum.GetStr() << std::endl;
	std::cout << "checksum.isValid() = " << std::boolalpha << checksum.isValid(entropy) << std::endl;
	
	// Test modified checksum
	checksum.Set(0x0);
	std::cout << "checksum.isValid() = " << std::boolalpha << checksum.isValid(entropy) << std::endl;
}

void test_new_mnemonic()
{
	int index;
	BIP39::Mnemonic mnemonic, mnemonic2;
	BIP39::Entropy entropy;
	BIP39::CheckSum checksum;
	
	std::cout << "--- NEW MNEMONIC ---" << std::endl;
	
	// Load the english words database
	if(!mnemonic.LoadLanguage() || !mnemonic2.LoadLanguage())
	{
		std::cout << "Failed to load language." << std::endl;
		return;
	}
	
	std::cout << "Found " << mnemonic.GetLanguageWords().size() << " total words." << std::endl;
	
	// Check if searching through database works
	if(mnemonic.Find("acid", &index))
	{
		std::cout << "Found 'acid' on position " << index << std::endl;
	}
	
	// Generate random entropy
	if(!entropy.genRandom())
	{
		std::cout << "Failed to generate new random entropy." << std::endl;
		return;
	}
	
	// Generate checksum
	if(!entropy.genCheckSum(&checksum))
	{
		std::cout << "Failed to generate checksum." << std::endl;
		return;
	}
	
	// Generate mnemonic
	if(mnemonic.Set(entropy, checksum))
	{
		mnemonic2.Set(mnemonic.GetStr());
		
		mnemonic.Debug();
		mnemonic2.Debug();
	}
}

int main()
{
	test_new_entropy();
	test_new_checksum();
	test_new_mnemonic();
	
	return 0;
}

