#ifndef BIP39_H
#define BIP39_H

namespace BIP39
{
	typedef std::vector<unsigned char> Data;
	typedef std::string                Word;
	typedef std::vector<BIP39::Word>   Words;
	typedef std::vector<unsigned int>  Word_indexs;
	typedef std::string                LanguageCode;
	
	//typedef unsigned char            Seed[64];    // 512 bits
}

#endif // BIP39_H
