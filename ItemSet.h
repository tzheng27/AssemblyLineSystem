/*
Name: Tian Zheng
Student Number: 155394174
Email: tzheng26@myseneca.ca
*/

#ifndef ITEMSET_H
#define ITEMSET_H

#include<string>
#include<vector>
#include"Utilities.h"

namespace sict {
	const int serNumWid = 5;
	const int quanWid = 3;


	class ItemSet {
		std::string name;
		size_t serialNum;
		size_t quantity;
		std::string description;
		Utilities tool;
	public:
		static size_t nameWid;
		ItemSet(const std::string&);
		const std::string& getName() const;
		const unsigned int getSerialNumber() const;
		const unsigned int getQuantity() const;
		ItemSet& operator--();
		void display(std::ostream& os, bool full) const;
		ItemSet(ItemSet&& );
	

		ItemSet& operator=(const ItemSet&) = delete;
		ItemSet& operator=(ItemSet&&) = delete;
		ItemSet(const ItemSet&) = delete;
	};
}


#endif // !ITENSET_H
