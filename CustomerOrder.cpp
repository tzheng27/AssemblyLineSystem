/*
Name: Tian Zheng
Student Number: 155394174
Email: tzheng26@myseneca.ca
*/

#include<iostream>
#include<string>
#include<iomanip>
#include"CustomerOrder.h"

namespace sict {
	size_t CustomerOrder::custNameWid = 0;

	CustomerOrder::CustomerOrder() {
		customerName = "NA";
		product = "NA";
	}

	CustomerOrder::CustomerOrder(const std::string& src) {
		Utilities tool;
		size_t pos = 0;
		customerName = tool.extractToken(src, pos);
		if (pos == std::string::npos) {
			customerName = "NA";
			product = "NA";
			throw "less than 3 tokens";
		}
		else {
			if (CustomerOrder::custNameWid < tool.getFieldWidth())
				CustomerOrder::custNameWid = tool.getFieldWidth();

			product = tool.extractToken(src, pos);
			if (pos == std::string::npos) {
				customerName = "NA";
				product = "NA";
				throw "less than 3 tokens";
			}
			else {
				std::string restString = src.substr(pos);
				std::string tempString = src.substr(pos);
				std::string tokenholder;
				size_t size = 0, temppos = 0, newpos = 0;
				while (temppos != std::string::npos && temppos < restString.length()) {
					tokenholder = tool.extractToken(tempString, temppos);
					size++;
				}
				itemNum = size;
				itemInfo = nullptr;
				itemInfo = new itemInfoWrapper[itemNum];
				for (size_t i = 0; i < itemNum;i++) {
					itemInfo[i].item = tool.extractToken(restString, newpos);
					itemInfo[i].serialNum = 0;
					itemInfo[i].fillStatus = false;
				}
			}
		}
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) {
		*this = std::move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) {
		if (this != &src) {
			delete[] itemInfo;
			itemInfo = src.itemInfo;
			customerName = src.customerName;
			product = src.product;
			itemNum = src.itemNum;

			src.customerName.clear();
			src.product.clear();
			src.itemInfo = nullptr;
			src.itemNum = 0;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		delete[] itemInfo;
		itemInfo = nullptr;
	}

	void CustomerOrder::fillItem(ItemSet& item, std::ostream& os) {
		for (size_t i = 0; i < itemNum; ++i) {
			if (item.getName() == itemInfo[i].item) {
				if (item.getQuantity() == 0)
					os << " Unable to fill " << customerName << " [" << product << "][" << itemInfo[i].item << "][" << itemInfo[i].serialNum << "] out of stock" << std::endl;
				else
				{
					if (itemInfo[i].fillStatus)
						os << " Unable to fill " << customerName << " [" << product << "][" << itemInfo[i].item << "][" << itemInfo[i].serialNum << "] already filled" << std::endl;
					else
					{
						itemInfo[i].serialNum = item.getSerialNumber();
						itemInfo[i].fillStatus = true;
						item.operator--();
						os << " Filled " << customerName << " [" << product << "][" << itemInfo[i].item << "][" << itemInfo[i].serialNum << "]" << std::endl;
					}
				}
			}
		}
	}

	bool CustomerOrder::isFilled() const {
		bool result = true;
		for (size_t i = 0; i < itemNum;i++) {
			if (!itemInfo[i].fillStatus)
				result = false;
		}
		return result;
	}

	bool CustomerOrder::isItemFilled(const std::string& item) const {
		bool result = true;
		for (size_t i = 0; i < itemNum;i++) {
			if (itemInfo[i].item == item) {
				if (!itemInfo[i].fillStatus)
					result = false;
			}
		}
		return result;
	}

	std::string CustomerOrder::getNameProduct() const {
		std::string result = customerName + " [" + product + "]";
		return result;
	}

	void CustomerOrder::display(std::ostream& os, bool showDetail) const {
		os << std::setw(CustomerOrder::custNameWid) << this->customerName << " " << "[" << this->product << "]" << std::endl;
		if (!showDetail) {
			for (size_t i = 0; i < itemNum;i++) {
				for (size_t space = 0; space < CustomerOrder::custNameWid;space++)
					os << " ";
				os << " " << itemInfo[i].item << std::endl;
			}
		}
		else {
			for (size_t i = 0; i < itemNum;i++) {
				std::string status = itemInfo[i].fillStatus ? "true" : "false";
				os << "[" << itemInfo[i].serialNum << "] " << itemInfo[i].item << " - "
					<< status << std::endl;
			}
		}
	}


	std::string CustomerOrder::getName() const {
		return customerName;
	}

	std::string CustomerOrder::getProduct() const {
		return product;
	}

	void CustomerOrder::displayItems(std::ostream& os) const {
		for (size_t i = 0; i < itemNum;i++) {
			for (size_t space = 0; space < CustomerOrder::custNameWid;space++)
				os << " ";
			std::string status = itemInfo[i].fillStatus ? "FILLED" : "MISSING";
			os << " [" << itemInfo[i].serialNum << "] " << itemInfo[i].item << " - " << status << std::endl;
		}
	}

}