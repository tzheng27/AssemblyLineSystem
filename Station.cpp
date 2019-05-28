/*
Name: Tian Zheng
Student Number: 155394174
Email: tzheng26@myseneca.ca
*/

#include <iostream>
#include <queue>
#include<vector>
#include<string>
#include"Station.h"

namespace sict {
	//Display the item info in one station
	void Station::display(std::ostream& os) const {
		item.display(os, true);
	}

	//fill the orders with the item in one station
	void Station::fill(std::ostream& os) {
		if (!orders.empty()) {
			auto iter = orders.begin();

			if (!(*iter).isFilled())
				(*iter).fillItem(item, os);
		}
	}

	//get the name of the item in one station
	const std::string& Station::getName() const {
		const std::string& result = item.getName();
		return result;
	}

	//Check if an order has been filled or the requested item is out of stock
	bool Station::hasAnOrderToRelease() const {
		bool result = false;
		auto iter = orders.begin();
		if (!orders.empty()) {
			if ((*iter).isItemFilled(item.getName()) || item.getQuantity() <= 0)
				result = true;
		}
		return result;
	}


	Station& Station::operator--() {
		--item;
		return *this;
	}

	Station& Station::operator+=(CustomerOrder&& order) {
		orders.push_back(std::move(order));
		return *this;
	}

	//Check if the first order is filled and return this order
	bool Station::pop(CustomerOrder& ready) {
		auto iter = orders.begin();
		bool result = (*iter).isFilled();

		CustomerOrder tempOrder = std::move((*iter));
		orders.pop_front();
		ready = std::move(tempOrder);

		return result;
	}

	void Station::validate(std::ostream& os) const {
		os << " getName(): " << item.getName() << std::endl;
		os << " getSerialNumber(): " << item.getSerialNumber() << std::endl;
		os << " getQuantity(): " << item.getQuantity() << std::endl;
	}

}