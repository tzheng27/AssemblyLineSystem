/*
Name: Tian Zheng
Student Number: 155394174
Email: tzheng26@myseneca.ca
*/

#ifndef CO_SICT_H
#define CO_SICT_H

#include<string>
#include "ItemSet.h"
#include "Utilities.h"

namespace sict {
	class CustomerOrder {
		std::string customerName;
		std::string product;
		struct itemInfoWrapper {
			std::string item;
			size_t serialNum;
			bool fillStatus;
		}* itemInfo = nullptr;
		size_t itemNum{ 0 };
	public:
		static size_t custNameWid;
		CustomerOrder();
		CustomerOrder(const std::string& src);
		~CustomerOrder();
		void fillItem(ItemSet& item, std::ostream& os);
		bool isFilled() const;
		bool isItemFilled(const std::string& item) const;
		std::string getNameProduct() const;
		void display(std::ostream& os, bool showDetail = false) const;

		std::string getName() const;
		std::string getProduct() const;
		void displayItems(std::ostream& os) const;

		CustomerOrder(CustomerOrder&& src);
		CustomerOrder& operator=(CustomerOrder&& src);

		CustomerOrder(const CustomerOrder&) = delete;
		CustomerOrder& operator=(const CustomerOrder&) = delete;
	};
}

#endif // !CO_SICT_H
