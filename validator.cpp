#include "validator.h"
#include "sstream"

void LocatarValidator::validate(const Locatar& locatar) {
	vector<string> msg;
	if (locatar.get_apartament() <= 0) {
		msg.push_back("Apartament invalid!");
	}
	if (locatar.get_nume().size() == 0) {
		msg.push_back("Numele nu poate fi vid!");
	}
	if (locatar.get_suprafata() <= 0) {
		msg.push_back("Suprafata invalida!");
	}
	if (locatar.get_tip().size() == 0) {
		msg.push_back("Tipul nu poate fi vid!");
	}
	if (msg.size() > 0) {
		throw ValidateException(msg);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}