#pragma once
#include <vector>
#include <algorithm>
using namespace std;

class Observer {
public:
	virtual void update() = 0;
};

class Observable {
private:
	std::vector<Observer*> obs;
public:
	void addObs(Observer* ob) {
		obs.push_back(ob);
	}

	void removeObs(Observer* ob) {
		obs.erase(remove(obs.begin(), obs.end(), ob), obs.end());
	}

	void notify() {
		for (auto it : obs) {
			it->update();
		}
	}
};