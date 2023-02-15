#include <string>
#include <fstream>
#include <map>

#include "bip39.h"

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

bool BIP39::LoadWords(BIP39::Words& words, const BIP39::LanguageCode& lang_code)
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
	words.clear();
	
	// Iterate through the words inside the input file
	for (std::string word; std::getline(ifs, word); ) 
	{
		// Debug
		//std::cout << word << std::endl;
		
		words.push_back(word);
	}
	
	// Close input file
	ifs.close();
	
	return true;
}

