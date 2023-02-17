#ifndef BIP39_MNEMONIC_H
#define BIP39_MNEMONIC_H

#include <string>
#include <vector>

#include "checksum.h"
#include "entropy.h"
#include "../bip39.h"

namespace BIP39
{	
	class Mnemonic
	{
		private:
			BIP39::Words       _lang_words;
			BIP39::Words       _words;
			BIP39::CheckSum    _checksum;
			BIP39::Entropy     _entropy;
			
			bool _isReady() const;
			
		public:
			Mnemonic();
			
			bool Set(const std::string& mnemonic_str);
			bool Set(const std::vector<BIP39::Word>& word);
			bool Set(const BIP39::Entropy& entropy, const BIP39::CheckSum& checksum);
			
			std::string GetStr() const;
			
			bool LoadLanguage(const BIP39::LanguageCode& lang_code = "EN");
			BIP39::Words GetLanguageWords() const;
			bool Find(const BIP39::Word& word, int* position) const;
	};
}

#endif // BIP39_MNEMONIC_H
