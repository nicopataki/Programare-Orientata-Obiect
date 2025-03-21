#pragma once
#include "domain.h"

#include "string"
#include "ostream"
#include <vector>
#include <map>

using std::string;
using std::ostream;
using std::vector;
using std::find_if;
using std::map;
using std::make_pair;

class AbstractRepo {
public:
	virtual void store(const Locatar& locatar) = 0;
	virtual Locatar& find(const Locatar& locatar) = 0;
	virtual void deletee(const Locatar& locatar) = 0;
	virtual void update(const Locatar& locatar, const Locatar& locatar_nou) = 0;
	virtual vector<Locatar>& getAll() = 0;
	virtual int search_poz(const int apartament) = 0;
	virtual Locatar& getLocatar(const int apartament) = 0;
	virtual void modify(const Locatar& locatar) = 0;
	virtual bool exista(const Locatar& locatar) = 0;
	virtual ~AbstractRepo() = default;
};

class LocatariRepo : public AbstractRepo {
private:
	vector<Locatar> all;

public:
	LocatariRepo() = default;

	//we do not permit to copy the objects
	//LocatariRepo(const LocatariRepo& ot) = delete;

	//explicit LocatariRepo(const Vector<Locatar>& locatari) :all{locatari} {};
	//LocatariRepo() = default;
	//nu permitem copierea de obiecte
	//LocatariRepo(const LocatariRepo& copy) = delete;

	/*
	Salvare locatar
	@param locatar - locatarul ce se doreste a fi salvat in repo
	arunca exceptie daca mai exista un locatar cu acelasi apartament
	*/
	virtual void store(const Locatar& locatar) override;


	/*
	* Sterge un locatar
	* @param locatar - locatarul ce se doreste a fi sters
	* arunca exceptie daca nu exista locatarul dat la apartamentul dat
	*/
	virtual void deletee(const Locatar& locatar) override;

	/*
	* Modifica un locatar
	* @param locatar - locatarul ce se doreste a fi modificat
	*		 locatar_nou - locatarul cu care se inlocuieste
	* arunca exceptie daca nu exista locatarul dat la apartamentul dat
	*/
	virtual void update(const Locatar& locatar, const Locatar& locatar_nou) override;

	/*
	returneaza toti locatarii salvati
	*/
	vector<Locatar>& getAll() override;

	/*
	Cauta un locatar
	@param apartament - apartamentul locatarului
		   nume - numele locatarului
	arunca exceptie daca nu exista locatar
	*/
	virtual Locatar& find(const Locatar& locatar) override;

	/*
	* Cauta pozitia pe care se afla locatarul cu apartamentul dat
	* @param apartament - apartamentul locatarului
	* @return int - pozitia pe care se gaseste locatarul in lista
	*/
	virtual int search_poz(const int apartament) override;

	/*
	* Getter pentru returnarea locatarului de la apartamentul dat
	* @param apartament - apartamentul al carui locatar este cautat
	* @return Locatar - locatarul de la apartamentul dat
	*/
	Locatar& getLocatar(const int apartament) override;

	void modify(const Locatar& locatar) override;

	/*
	* Functia privata verifica daca locatarul exista deja in repository
	* @param locatar - locatarul cautat
	*/
	virtual bool exista(const Locatar& locatar) override;

	virtual ~LocatariRepo() = default;
};

class ProbabilityRepo : public AbstractRepo {
private:
	float prob;
	map<int, Locatar> elems;
	void det_luck();
public:
	ProbabilityRepo() = default;
	explicit ProbabilityRepo(float chance);

	void store(const Locatar& locatar) override;

	void deletee(const Locatar& locatar) override;

	void update(const Locatar& locatar, const Locatar& locatar_nou) override;

	vector<Locatar>& getAll() override;

	virtual Locatar& find(const Locatar& locatar) override;

	virtual int search_poz(const int apartament) override;

	virtual Locatar& getLocatar(const int apartament) override;

	virtual void modify(const Locatar& locatar) override;

	virtual bool exista(const Locatar& locatar) override;
};



/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class LocatariRepoException {
	string msg;
public:
	LocatariRepoException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const LocatariRepoException& ex);
	string get_mesaj() { return this->msg; }
};

ostream& operator<<(ostream& out, const LocatariRepoException& ex);