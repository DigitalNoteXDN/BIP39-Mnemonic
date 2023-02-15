#ifndef BIP39_ENTROPY_H
#define BIP39_ENTROPY_H

#include <string>
#include <vector>

namespace BIP39
{
	class CheckSum;
	
	class Entropy
	{
		private:
			unsigned char vch[32]; // 256 bits
		
		public:
			Entropy();
			Entropy(const std::vector<unsigned char> &vch);
			
			std::string GetStr();
			void Set(const std::vector<unsigned char> &other_vch);
			
			unsigned int size() const;
			const unsigned char *begin() const;
			const unsigned char *end() const;
			const unsigned char &operator[](unsigned int pos) const;
			
			bool genRandom();
			BIP39::CheckSum genCheckSum();
	};
}

#endif // BIP39_ENTROPY_H
