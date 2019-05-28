/*
Name: Tian Zheng
Student Number: 155394174
Email: tzheng26@myseneca.ca
*/

#ifndef STATION_H
#define STATION_H

#include<deque>
#include "CustomerOrder.h"
#include "ItemSet.h"

namespace sict {
	class Station {
		std::deque<CustomerOrder> orders;
		ItemSet item;
	public:
		Station(const std::string& src) : item(src) {}
		void display(std::ostream& os) const;
		void fill(std::ostream& os);
		const std::string& getName() const;
		bool hasAnOrderToRelease() const;
		Station& operator--();
		Station& operator+=(CustomerOrder&& order);
		bool pop(CustomerOrder& ready);
		void validate(std::ostream& os) const;

		Station(Station&&) = delete;
		Station& operator=(Station&&) = delete;
		Station(const Station&) = delete;
		Station& operator=(const Station&) = delete;
	};
}


#endif // !STATION_H
