#pragma once

#include "string"
#include "iostream"
#include <map>

using std::string;
using std::cout;
using std::map;

class DTO {
	string type;
	int count;
public:
	DTO(const string& type, int count) : type{ type }, count{ count } {};
	DTO(const string& type) : type{ type }, count{ 0 } {};
	DTO() noexcept :type{ "" }, count{ 0 } {};
	const string& get_type() const noexcept {
		return type;
	}
	int get_count() const noexcept {
		return count;
	}
};

class Locatar {
private:
	int apartament;
	string nume;
	int suprafata;
	string tip;
public:
	/*
	* Constructor pentru clasa Locatar
	* @param ap - int, numarul apartamentului
	*		 nume - string, numele locatarului
	*		 suprafata - int, suprafata apartamentului
	*		 tip - string, tipul apartamentului
	*/
	Locatar(int ap, const string& nume, int suprafata, const string& tip);

	//Constructor implicit
	Locatar() noexcept;

	//destructor
	~Locatar();

	/*
	* Copierea unui locatar
	* @param locatar - locatarul ce se doreste a fi copiat
	*/
	Locatar(const Locatar& ot);

	//Retrueaza numarul apartamentului
	int get_apartament() const noexcept;

	//Retruneaza numele locatarului
	const string& get_nume() const noexcept;

	//Retruneaza suprafata apartamentului
	int get_suprafata() const noexcept;

	//Retruneaza tipul aprtamentului
	const string& get_tip() const noexcept;

	//functie de printare
	string to_string_print();

	string print_to_string() const;

	//Operator de asignare - asignarea unui obiect altui obiect
	Locatar& operator=(const Locatar& other);

	//Operator de egalitate intre doua obiecte din clasa
	//Doua obiecte sunt considerate egale daca apartamentele sunt egale
	bool operator==(const Locatar& other) noexcept;

	string l_loc() const;

};
/*
* Functie de comparare a numelor a doi locatari
* @param locatar1 - un locatar
*		 locatar2 - un alt locatar
* @return 1 daca numele locatarilor sunt in ordine alfabetica, 0 altfel
*/
bool comparaNume(const Locatar& locatar1, const Locatar& locatar2) noexcept;
/*
* Functie de comparare a suprafetelo a doua apartamente
* @param locatar1 - un locatar
*		 locatar2 - un alt locatar
* @return 1 daca suprafetele sunt in ordine crescatoare, 0 altfel
*/
bool comparaSuprafata(const Locatar& locatar1, const Locatar& locatar2) noexcept;
/*
* Functie de comparare a tipurilor a doua apartamente
* @param locatar1 - un locatar
*		 locatar2 - un alt locatar
* @return 1 daca tipurile sunt in ordine crescatoare, 0 altfel
*/
bool comparaTip(const Locatar& locatar1, const Locatar& locatar2) noexcept;
