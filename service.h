#pragma once
#include "domain.h"
#include "validator.h"
#include "repo.h"
#include "vector"
#include "string"
#include "listaRepo.h"
#include "functional"
#include"undo.h"
#include <algorithm>
#include <map>
#include "undo.h"
#include "fileRepo.h"
#include <set>

using std::set;
using std::vector;
using std::function;
using std::map;
using std::copy_if;
using std::shuffle;
using std::string;
using std::shared_ptr;

class LocatariService {
private:
	AbstractRepo* repo;
	//LocatariRepo& repo;
	//FileRepo& repo;
	LocatarValidator& val;
	ListaRepo& lista;
	std::vector<shared_ptr<Undo>> undoActions;

	/*
	* Functie de sortare generala
	* maiMicF - functie care compara 2 Locatari, verifica daca are loc relatia mai mare
	*		 - poate fi orice functie care respecta signatura(realizeaza bool, are 2 parametrii Locatar)
	*		 - poate fi functie lambda
	* returneaza o lista sortata dupa criteriu dat ca parametru
	*/
	//vector<Locatar> generalSort(bool (*maiMicF)(const Locatar&, const Locatar&));

	/*
	* Functie generala de filtrare
	* functie - poate fi o functie
	* functie - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
	* returneaza doar locatarii care trec prin filtru
	*/
	//vector<Locatar> filtru(function<bool(const Locatar)> functie);

public:
	//get lista apartamente
	const vector<Locatar>& getAllLista() noexcept;

	//afiseaza numarul de elemente din lista
	int getListaSize() noexcept;

	//adauga un nou element in lista
	void add_to_list(const int apartament);

	//genereaza apartamente aleator
	void generateList(int nrApartamente);

	//exporta lista intr-un fisier html
	void exportList(const string& name);

	//goleste lista
	void emptyList() noexcept;

	map<string, DTO> raport();

	//LocatariService(AbstractRepo* repo, LocatarValidator& val, ListaRepo& lista);

	LocatariService(AbstractRepo* repo, LocatarValidator& val, ListaRepo& lista) noexcept : repo{ repo }, val{ val }, lista{ lista } {}
	//nu permitem copierea de obiecte LocatariService
	//LocatariService(const LocatariService& copy) noexcept = delete;
	/*
	 returneaza toti locatarii in ordinea in care au fost adaugati
	*/
	vector<Locatar>& get_All() {
		return repo->getAll();
	}
	/*
	Adauga un nou locatar
	arunca exceptie daca: nu se poate salva, nu este valid
	*/
	void addLocatar(int apartament, const string& nume, int suprafata, const string& tip);

	/*
	* Cauta un locatar dupa apartament si nume
	* arunca exceptie daca nu exista un locatar la apartamentul dat
	*/
	Locatar findLocatar(int apartament);

	/*
	* Sterge un locatar dupa apartament
	* arunca exceptie daca nu exista un locatar la apartamentul dat
	*/
	void delLocatar(int apartament);

	/*
	* Modifica un locatar
	* arunca exceptie daca nu exista un locatar la apartamentul dat
	*/
	void updateLocatar(int apartament, const string& nume, int suprafata, const string& tip);

	/*
	* Filtreaza locatarii dupa tipul apartamentului
	*/
	vector<Locatar> filtreaza_tip(const string& tip);

	/*
	* Filtreaza locatarii dupa suprafata apartamentului
	*/
	vector<Locatar> filtreaza_suprafata(int suprafata);

	/*
	* Filtreaza locatarii dupa numarul apartamentului
	*/
	vector<Locatar> filterByApartament(int apartament);

	/*
	* Sorteaza locatarii dupa nume
	*/
	vector<Locatar> sortByNume();

	/*
	* Sorteaza locatarii dupa suprafata
	*/
	vector<Locatar> sortBySuprafata();

	/*
	* Sorteaza locatarii dupa tip si suprafata
	*/
	vector<Locatar> sortByTipSuprafata();

	/*
	* Sorteaza locatarii dupa apartament
	*/
	vector<Locatar> sortByApartament();

	//reface ultima operatie
	void Undo();

	set<string> number_of_types();
};