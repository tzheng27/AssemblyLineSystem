/*
Name: Tian Zheng
Student Number: 155394174
Email: tzheng26@myseneca.ca
*/

#include<iostream>
#include<iomanip>
#include "LineManager.h"
#include "CustomerOrder.h"

namespace sict {
	//5 arguments constructor
	LineManager::LineManager(std::vector<Station*>& srcstation, std::vector<size_t>& index, std::vector<CustomerOrder>& srcCustorders, size_t startingStation, std::ostream& os)
		: line(srcstation), nextStation(index), custOrdersNum(srcCustorders.size()), startingStationInd(startingStation) {
		for (size_t o = 0; o < srcCustorders.size();o++) {
			ordersToFill.push_front(std::move(srcCustorders[o]));
		}

		lastStation = startingStation;
		for (size_t s = 0; s < nextStation.size();++s) {
			if (nextStation[lastStation] < line.size())
				lastStation = nextStation[lastStation];
		}
	}

	//display order status
	void LineManager::display(std::ostream& os) const {
		os << "COMPLETED ORDERS" << std::endl;
		for (size_t c = 0; c < completedOrders.size(); c++) {
			os << std::setw(CustomerOrder::custNameWid) << completedOrders[c].getName() << " [" << completedOrders[c].getProduct() << "]" << std::endl;
			completedOrders[c].displayItems(os);
		}

		os << std::endl;
		os << "INCOMPLETE ORDERS" << std::endl;
		for (size_t i; i < incompletedOrders.size(); i++) {
			os << std::setw(CustomerOrder::custNameWid) << incompletedOrders[i].getName() << " [" << incompletedOrders[i].getProduct() << "]" << std::endl;
			incompletedOrders[i].displayItems(os);
		}

	}

	//Allocate the orders to be filled, fill them, and move them to completed or incompleted orders
	bool LineManager::run(std::ostream& os) {
		if (!ordersToFill.empty()) {
			*line[startingStationInd] += std::move(ordersToFill.back());
			ordersToFill.pop_back();
		}

		for (size_t i = 0; i < line.size();i++) {
			line[i]->fill(os);
		}
			

		for (size_t j = 0; j < line.size(); j++) {
			if (line[j]->hasAnOrderToRelease()) {
				CustomerOrder tempOrder;
				bool result = line[j]->pop(tempOrder);
				os << " --> " << tempOrder.getNameProduct() << " moved from " << line[j]->getName() << " to ";
				if (j != lastStation) {
					os << line[nextStation[j]]->getName() << std::endl;
					*line[nextStation[j]] += std::move(tempOrder);
				}
				else if (result) {
					os << "Completed Set" << std::endl;
					completedOrders.push_back(std::move(tempOrder));
				}
				else {
					os << "Incomplete Set" << std::endl;
					incompletedOrders.push_back(std::move(tempOrder));
				}
			}
		}

		bool ifProcessedAll = (completedOrders.size() + incompletedOrders.size()) == custOrdersNum;
		return ifProcessedAll;
	}
}