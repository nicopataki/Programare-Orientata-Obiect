#include "domain.h"
#include "string"

Locatar::Locatar() noexcept {
	this->apartament = -1;
	this->nume = "";
	this->suprafata = -1;
	this->tip = "";
}

Locatar::Locatar(int ap, const std::string& n, int supraf, const std::string& t) {
	this->apartament = ap;
	this->nume = n;
	this->suprafata = supraf;
	this->tip = t;
}

Locatar::~Locatar() = default;

Locatar::Locatar(const Locatar& locatar) {
	this->apartament = locatar.apartament;
	this->nume = locatar.nume;
	this->suprafata = locatar.suprafata;
	this->tip = locatar.tip;
}

int Locatar::get_apartament() const noexcept {
	return this->apartament;
}

const string& Locatar::get_nume() const noexcept {
	return this->nume;
}

int Locatar::get_suprafata() const noexcept {
	return this->suprafata;
}

const string& Locatar::get_tip() const noexcept {
	return this->tip;
}

string Locatar::to_string_print() {
	return std::to_string(this->apartament) + " " + this->nume + " " + std::to_string(this->suprafata) + " " + this->tip;
}

string Locatar::print_to_string() const{
	return std::to_string(this->apartament) + " " + this->nume + " " + std::to_string(this->suprafata) + " " + this->tip;
}

Locatar& Locatar::operator=(const Locatar& other) = default;

bool Locatar::operator==(const Locatar& other) noexcept {
	return this->apartament == other.apartament;
}

bool comparaNume(const Locatar& locatar1, const Locatar& locatar2) noexcept {
	return locatar1.get_nume() < locatar2.get_nume();
}

bool comparaSuprafata(const Locatar& locatar1, const Locatar& locatar2) noexcept {
	return locatar1.get_suprafata() < locatar2.get_suprafata();
}

bool comparaTip(const Locatar& locatar1, const Locatar& locatar2) noexcept {
	return locatar1.get_tip() < locatar2.get_tip();
}

string Locatar::l_loc() const {
	return std::to_string(apartament) + "," + this->nume + "," + std::to_string(suprafata) + "," + this->tip;
}