/*
Name: Tian Zheng
Student Number: 155394174
Email: tzheng26@myseneca.ca
*/

#include <iostream>
#include <string>
#include"Utilities.h"

namespace sict {
	char Utilities::delimiter = ' ';

	Utilities::Utilities() {
		fieldwidth = 0;
	}

	const std::string Utilities::extractToken(const std::string& str, size_t& next_pos) {
		std::string token;
		size_t searchDelimiter = str.find_first_of(delimiter, next_pos);

		if (searchDelimiter != std::string::npos) {
			token = str.substr(next_pos, searchDelimiter - next_pos);
			next_pos = searchDelimiter + 1;
		}
		else {
			token = str.substr(next_pos);
			next_pos = str.length() + 1;
		}

		if ((token.empty()) && (next_pos != str.length() + 1)) {
			next_pos = std::string::npos;
			throw "unable to read token";
		}

		if (fieldwidth < token.length())
			fieldwidth = token.length();

		if (!(next_pos <= str.length()))
			next_pos = std::string::npos;
		
		return token;
	}

	const char Utilities::getDelimiter() const {
		return delimiter;
	}

	size_t Utilities::getFieldWidth() const {
		return fieldwidth;
	}

	
	void Utilities::setFieldWidth(size_t f) {
		fieldwidth = f;
	}

	void Utilities::setDelimiter(const char d) {
		delimiter = d;
	}
}