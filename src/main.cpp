/*
	Reference:
		https://en.bitcoin.it/wiki/BIP_0039
		https://learnmeabitcoin.com/technical/mnemonic
		https://github.com/bitcoin/bips/tree/master/bip-0039
*/

#include <iostream>
#include <algorithm>

#include "bip39.h"
#include "bip39/entropy.h"
#include "bip39/checksum.h"

void test_load_languages()
{
	BIP39::Words words;
	BIP39::Words::iterator it;
	
	std::cout << "--- LOAD LANGUAGES ---" << std::endl;
	
	if(BIP39::LoadWords(words))
	{
		std::cout << "Found " << words.size() << " total words." << std::endl;
		
		it = std::find(words.begin(), words.end(), "acid");
		
		if(it != words.end())
		{
			int pos = std::distance(words.begin(), it);
			
			std::cout << "Found '" << *it << "' on position " << pos << std::endl; 
		}
	}
}

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
	
	if(entropy.genRandom())
	{
		BIP39::CheckSum checksum = entropy.genCheckSum();
		
		std::cout << "Entropy  = " << entropy.GetStr() << std::endl;
		std::cout << "Checksum = " << checksum.GetStr() << std::endl;
		
		std::cout << "checksum.isValid() = " << std::boolalpha << checksum.isValid(entropy) << std::endl;
		
		checksum.Set(0x0);
		
		std::cout << "checksum.isValid() = " << std::boolalpha << checksum.isValid(entropy) << std::endl;
	}
}

int main()
{
	test_load_languages();
	test_new_entropy();
	test_new_checksum();
	
	return 0;
}

