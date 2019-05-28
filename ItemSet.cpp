/*
Name: Tian Zheng
Student Number: 155394174
Email: tzheng26@myseneca.ca
*/

#include <iostream>
#include<string>
#include <iomanip>
#include "ItemSet.h"
#include "Utilities.h"

namespace sict {
	size_t ItemSet::nameWid = 0;

	ItemSet::ItemSet(const std::string& str) {
		size_t pos = 0;
		
		name = tool.extractToken(str, pos);

		if(ItemSet::nameWid < tool.getFieldWidth())
			ItemSet::nameWid = tool.getFieldWidth();

		serialNum = std::stoi(tool.extractToken(str, pos));
		quantity = std::stoi(tool.extractToken(str, pos));
		description = tool.extractToken(str, pos);
		
	}

	ItemSet::ItemSet(ItemSet&& src) {
		if (this != &src) {
			
			name = src.name;
			serialNum = src.serialNum;
			quantity = src.quantity;
			description = src.description;
			tool = src.tool;

			src.name.clear();
			src.serialNum = 0;
			src.quantity = 0;
			src.description.clear();
			src.tool.setFieldWidth(0);
		}
	}

	const std::string& ItemSet::getName() const {
		const std::string& result = name;
		return result;
	}

	const unsigned int ItemSet::getSerialNumber() const {
		return serialNum;
	}

	const unsigned int ItemSet::getQuantity() const {
		return quantity;
	}

	ItemSet& ItemSet::operator--() {
		if (quantity > 0) {
			quantity--;
			serialNum++;
		}
		return *this;
	}

	void ItemSet::display(std::ostream& os, bool full) const {
		os << std::setw(ItemSet::nameWid) << std::setfill(' ') << std::left << name << " "
			<< "[" << std::setw(serNumWid) << std::setfill('0') << std::right << serialNum << "]";

		if (full) {
			os << " " << "Quantity " << std::setw(quanWid) << std::setfill(' ') << std::left << quantity
				<< " Description: " << description;
			os << std::endl;
		}
	}
	
}