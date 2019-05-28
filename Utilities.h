/*
Name: Tian Zheng
Student Number: 155394174
Email: tzheng26@myseneca.ca
*/

#ifndef UTI_H
#define UTI_H

namespace sict {
	class Utilities {
		static char delimiter;
	public:
		Utilities();
		size_t fieldwidth;
		const std::string extractToken(const std::string& str, size_t& next_pos);
		const char getDelimiter() const;
		size_t getFieldWidth() const;
		static void setDelimiter(const char d);
		void setFieldWidth(size_t);
	};
}


#endif // !UTI_H
