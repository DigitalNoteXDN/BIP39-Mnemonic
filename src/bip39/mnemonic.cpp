#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <bitset>

#include "mnemonic.h"

std::map<BIP39::LanguageCode, std::string> lang_code_filepath = {
	{ "zh-CN",  "../data/chinese_simplified.txt" },
	{ "zh-CHT", "../data/chinese_traditional.txt" },
	{ "CZ",     "../data/czech.txt" },
	{ "EN",     "../data/english.txt" },
	{ "FR",     "../data/french.txt" },
	{ "IT",     "../data/italian.txt" },
	{ "JP",     "../data/japanese.txt" },
	{ "PT",     "../data/portuguese.txt" },
	{ "ES",     "../data/spanish.txt" }
};

bool BIP39::Mnemonic::_isReady() const
{
	return this->_lang_words.size() == 2048;
}

BIP39::Mnemonic::Mnemonic()
{
	
}

bool BIP39::Mnemonic::Set(const BIP39::Entropy& entropy, const BIP39::CheckSum& checksum)
{
	if(!this->_isReady() || !checksum.isValid(entropy))
	{
		return false;
	}
	
	BIP39::Data data = entropy.Raw();
	
	// Collect word indexs
	BIP39::Word_indexs word_indexs = {
		( static_cast<unsigned int>(data[ 0])         <<  3) + ((static_cast<unsigned int>(data[ 1]) & 0xE0) >> 5),
		((static_cast<unsigned int>(data[ 1]) & 0x1F) <<  6) + ((static_cast<unsigned int>(data[ 2]) & 0xFC) >> 2),
		((static_cast<unsigned int>(data[ 2]) & 0x03) <<  9) + ( static_cast<unsigned int>(data[ 3])         << 1) + ((static_cast<uint16_t>(data[4]) & 0x80) >> 7),
		((static_cast<unsigned int>(data[ 4]) & 0x7F) <<  4) + ((static_cast<unsigned int>(data[ 5]) & 0xF0) >> 4),
		((static_cast<unsigned int>(data[ 5]) & 0x0F) <<  7) + ((static_cast<unsigned int>(data[ 6]) & 0xFE) >> 1),
		((static_cast<unsigned int>(data[ 6]) & 0x01) << 10) + ((static_cast<unsigned int>(data[ 7])       ) << 2) + ((static_cast<uint16_t>(data[8]) & 0xC0) >> 6),
		((static_cast<unsigned int>(data[ 8]) & 0x3F) <<  5) + ((static_cast<unsigned int>(data[ 9]) & 0xF8) >> 3),
		((static_cast<unsigned int>(data[ 9]) & 0x07) <<  8) + ( static_cast<unsigned int>(data[10])             ),
		( static_cast<unsigned int>(data[11])         <<  3) + ((static_cast<unsigned int>(data[12]) & 0xE0) >> 5),
		((static_cast<unsigned int>(data[12]) & 0x1F) <<  6) + ((static_cast<unsigned int>(data[13]) & 0xFC) >> 2),
		((static_cast<unsigned int>(data[13]) & 0x03) <<  9) + ( static_cast<unsigned int>(data[14])         << 1) + ((static_cast<uint16_t>(data[15]) & 0x80) >> 7),
		((static_cast<unsigned int>(data[15]) & 0x7F) <<  4) + ((static_cast<unsigned int>(data[16]) & 0xF0) >> 4),
		((static_cast<unsigned int>(data[16]) & 0x0F) <<  7) + ((static_cast<unsigned int>(data[17]) & 0xFE) >> 1),
		((static_cast<unsigned int>(data[17]) & 0x01) << 10) + ((static_cast<unsigned int>(data[18])       ) << 2) + ((static_cast<uint16_t>(data[19]) & 0xC0) >> 6),
		((static_cast<unsigned int>(data[19]) & 0x3F) <<  5) + ((static_cast<unsigned int>(data[20]) & 0xF8) >> 3),
		((static_cast<unsigned int>(data[20]) & 0x07) <<  8) + ( static_cast<unsigned int>(data[21])             ),
		( static_cast<unsigned int>(data[22])         <<  3) + ((static_cast<unsigned int>(data[23]) & 0xE0) >> 5),
		((static_cast<unsigned int>(data[23]) & 0x1F) <<  6) + ((static_cast<unsigned int>(data[24]) & 0xFC) >> 2),
		((static_cast<unsigned int>(data[24]) & 0x03) <<  9) + ( static_cast<unsigned int>(data[25])         << 1) + ((static_cast<uint16_t>(data[26]) & 0x80) >> 7),
		((static_cast<unsigned int>(data[26]) & 0x7F) <<  4) + ((static_cast<unsigned int>(data[27]) & 0xF0) >> 4),
		((static_cast<unsigned int>(data[27]) & 0x0F) <<  7) + ((static_cast<unsigned int>(data[28]) & 0xFE) >> 1),
		((static_cast<unsigned int>(data[28]) & 0x01) << 10) + ((static_cast<unsigned int>(data[29])       ) << 2) + ((static_cast<uint16_t>(data[30]) & 0xC0) >> 6),
		((static_cast<unsigned int>(data[30]) & 0x3F) <<  5) + ((static_cast<unsigned int>(data[31]) & 0xF8) >> 3),
		((static_cast<unsigned int>(data[31]) & 0x07) <<  8) +   static_cast<unsigned int>(checksum.Get())
	};
	
	// Collect words
	this->_words.clear();
	for(unsigned int index : word_indexs)
	{
		this->_words.push_back(this->_lang_words[index]);
	}
	
	return true;
}

std::string BIP39::Mnemonic::GetStr() const
{
	std::string v;
	
	for(std::string word : this->_words)
	{
		v += word + " ";
	}
	
	return v;
}

bool BIP39::Mnemonic::LoadLanguage(const BIP39::LanguageCode& lang_code)
{
	std::string filepath;
	std::ifstream ifs;
	
	// Get language file path
	filepath = lang_code_filepath[lang_code];
	
	// Open input file
	ifs.open(filepath, std::ifstream::in);
	if(!ifs.is_open())
	{
		return false;
	}
	
	// Clear words
	this->_lang_words.clear();
	
	// Iterate through the words inside the input file
	for (std::string word; std::getline(ifs, word); ) 
	{
		// Debug
		//std::cout << word << std::endl;
		
		this->_lang_words.push_back(word);
	}
	
	// Close input file
	ifs.close();
	
	return true;
}

BIP39::Words BIP39::Mnemonic::GetLanguageWords() const
{
	return this->_lang_words;
}

bool BIP39::Mnemonic::Find(const BIP39::Word& word, int* position) const
{
	BIP39::Words::const_iterator found, begin, end;
	
	if(!this->_isReady())
	{
		*position = -1;
		return false;
	}
	
	begin = this->_lang_words.begin();
	end = this->_lang_words.end();
	
	found = std::find(begin, end, word.c_str());
		
	if(found != end)
	{
		*position = std::distance(begin, found);
		
		return true;
	}
	
	*position = -1;
	return false;
}

