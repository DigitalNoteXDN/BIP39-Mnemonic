#ifndef BIP39_CHECKSUM_H
#define BIP39_CHECKSUM_H

#include <cstdint>
#include <string>

namespace BIP39
{
	class Entropy;
	
	class CheckSum
	{
		private:
			uint8_t sum; // 8 bits
		
		public:
			CheckSum();
			CheckSum(const uint8_t sum);
			
			void Set(const uint8_t sum);
			uint8_t Get();
			std::string GetStr();
			
			bool isValid(BIP39::Entropy& entropy);
	};
}

#endif // BIP39_CHECKSUM_H
