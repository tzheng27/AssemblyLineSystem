/*
Name: Tian Zheng
Student Number: 155394174
Email: tzheng26@myseneca.ca
*/


#ifndef LINEMAN_H
#define LINEMAN_H

#include <vector>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace sict {
	class LineManager {
		std::vector<Station*> line;
		std::vector<size_t> nextStation;
		std::deque<CustomerOrder> ordersToFill;
		std::deque<CustomerOrder> completedOrders;
		std::deque<CustomerOrder> incompletedOrders;
		size_t custOrdersNum;
		size_t lastStation;
		size_t startingStationInd;

	public:
		LineManager(std::vector<Station*>&, std::vector<size_t>&, std::vector<CustomerOrder>&, size_t, std::ostream&);
		void display(std::ostream& os) const;
		bool run(std::ostream& os);
	};
}

#endif // !LINEMAN_H
