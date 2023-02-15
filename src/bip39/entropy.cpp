#include <string.h>

#include <openssl/rand.h>
#include <openssl/evp.h>

#include "entropy.h"
#include "checksum.h"
#include "../util.h"

BIP39::Entropy::Entropy()
{
	
}

BIP39::Entropy::Entropy(const std::vector<unsigned char> &other_vch)
{
	memcpy(this->vch, (unsigned char*)&other_vch.begin()[0], 32);
}

std::string BIP39::Entropy::GetStr()
{
	return "0x" + HexStr(*this);
}

void BIP39::Entropy::Set(const std::vector<unsigned char> &other_vch)
{
	memcpy(this->vch, (unsigned char*)&other_vch.begin()[0], 32);
}

unsigned int BIP39::Entropy::size() const
{
	return 32;
}

const unsigned char* BIP39::Entropy::begin() const
{
	return this->vch;
}

const unsigned char* BIP39::Entropy::end() const
{
	return this->vch + this->size();
}

const unsigned char& BIP39::Entropy::operator[](unsigned int pos) const
{
	return this->vch[pos];
}

bool BIP39::Entropy::genRandom()
{
	if(RAND_bytes(this->vch, this->size()) == 0)
	{
		return false;
	}
	
	return true;
}

BIP39::CheckSum BIP39::Entropy::genCheckSum()
{
	EVP_MD_CTX* context = EVP_MD_CTX_new();
	BIP39::CheckSum checksum;
	
    if(context != NULL)
    {
        if(EVP_DigestInit_ex(context, EVP_sha256(), NULL))
        {
            if(EVP_DigestUpdate(context, this->begin(), this->size()))
			{
				unsigned char hash[EVP_MAX_MD_SIZE];
                unsigned int lengthOfHash = 0;

                if(EVP_DigestFinal_ex(context, hash, &lengthOfHash))
                {
					checksum.Set(static_cast<uint8_t>(hash[0]));
				}
			}
		}
	}
	
	return checksum;
}

