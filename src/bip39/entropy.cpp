#include <string.h>

#include <openssl/rand.h>
#include <openssl/evp.h>

#include "entropy.h"
#include "checksum.h"
#include "../util.h"

BIP39::Entropy::Entropy()
{
	
}

BIP39::Entropy::Entropy(const BIP39::Data &data)
{
	memcpy(this->_vch, const_cast<unsigned char*>(&data.begin()[0]), 32);
}

std::string BIP39::Entropy::GetStr() const
{
	return "0x" + HexStr(*this);
}

void BIP39::Entropy::Set(const BIP39::Data &data)
{
	memcpy(this->_vch, const_cast<unsigned char*>(&data.begin()[0]), 32);
}

unsigned int BIP39::Entropy::size() const
{
	return 32;
}

const unsigned char* BIP39::Entropy::begin() const
{
	return this->_vch;
}

const unsigned char* BIP39::Entropy::end() const
{
	return this->_vch + this->size();
}

const unsigned char& BIP39::Entropy::operator[](unsigned int pos) const
{
	return this->_vch[pos];
}

bool BIP39::Entropy::genRandom()
{
	if(RAND_bytes(this->_vch, this->size()) == 0)
	{
		return false;
	}
	
	return true;
}

BIP39::CheckSum BIP39::Entropy::genCheckSum() const
{
	EVP_MD_CTX* ctx = EVP_MD_CTX_new();
	BIP39::CheckSum checksum;

	if(ctx != NULL)
	{
		if(EVP_DigestInit_ex(ctx, EVP_sha256(), NULL))
		{
			if(EVP_DigestUpdate(ctx, this->begin(), this->size()))
			{
				unsigned char hash[EVP_MAX_MD_SIZE];
				unsigned int lengthOfHash = 0;

				if(EVP_DigestFinal_ex(ctx, hash, &lengthOfHash))
				{
					checksum.Set(static_cast<uint8_t>(hash[0]));
				}
			}
			
			EVP_MD_CTX_free(ctx);
		}
	}
	
	return checksum;
}

BIP39::Data BIP39::Entropy::Raw() const
{
	BIP39::Data data;

	data.insert(data.end(), this->_vch, this->_vch + this->size());

	return data;
}