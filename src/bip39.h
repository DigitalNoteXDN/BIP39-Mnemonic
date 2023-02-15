#ifndef BIP39_H
#define BIP39_H

#include <string>
#include <vector>

namespace BIP39
{
	typedef std::string              Word;
	typedef std::vector<BIP39::Word> Words;
	typedef std::string              LanguageCode;
	
	typedef std::vector<BIP39::Word> Mnemonic;    // 24 words
	typedef unsigned char            Seed[64];    // 512 bits

	bool LoadWords(BIP39::Words& words, const BIP39::LanguageCode& lang_code = "EN");	
}

#endif // BIP39_H
