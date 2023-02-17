#ifndef BIP39_ENTROPY_H
#define BIP39_ENTROPY_H

#include <string>
#include <vector>
#include "../bip39.h"

namespace BIP39
{
	class CheckSum;
	
	class Entropy
	{
		private:
			unsigned char _vch[32]; // 256 bits
		
		public:
			Entropy();
			Entropy(const BIP39::Data &vch);
			
			std::string GetStr() const;
			void Set(const BIP39::Data &other_vch);
			
			unsigned int size() const;
			const unsigned char *begin() const;
			const unsigned char *end() const;
			const unsigned char &operator[](unsigned int pos) const;
			
			bool genRandom();
			BIP39::CheckSum genCheckSum() const;
			BIP39::Data Raw() const;
	};
}

#endif // BIP39_ENTROPY_H
