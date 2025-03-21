#pragma once
#include <vector>
#include <random>
#include <fstream>
#include <algorithm>
#include "domain.h"
#include <ostream>
#include <exception>
#include "observer.h"

using std::vector;
using std::shuffle;
using std::ostream;
using std::exception;

class ListaRepo: public Observable {
private:
	vector<Locatar> Lista;
public:
	//goleste lista
	void empty_list() noexcept;

	//adauga un apartament in lista
	void add_apartament(const Locatar& locatar);

	//genereaza apartamente
	void generate_apartamente(int nr_apartamente, const vector<Locatar>& memory);

	//exporta apartamente
	void export_apartamente(const string& file_name);

	//returneaza lista cu apartamente
	const vector<Locatar>& get_Lista() noexcept;

	//cauta un apartament in lista
	int search_apartament_lista(const int apartament);
};

class ListaException : public exception {
	string mesaj;
public:
	explicit ListaException(string mesaj) noexcept : mesaj(move(mesaj)) {};
	string get_mesaj() { return this->mesaj; }
};