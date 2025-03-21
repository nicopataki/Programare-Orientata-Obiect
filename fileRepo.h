#pragma once
#include "repo.h"

class FileRepo : public LocatariRepo {
private:
	string fileName;
public:
	FileRepo() = default;
	//functie pentru preluarea inregistrarilor din fiiser
	void loadRepo();
	//functie pentru salvarea inregistrarilor in fisier
	void saveRepo();
	//functie pentru golirea fisierului
	void emptyFile();
	//constructor
	explicit FileRepo(const string& name);
	//seteaza numele fisierului pe care sa se opereze
	void setPath(const string& name) {
		this->fileName = name;
	}
	//destructor pentru file repo
	~FileRepo() override = default;

	//functie pentru adaugarea unui element nou in fisier
	void store(const Locatar& locatar) override {
		LocatariRepo::store(locatar);
		saveRepo();
	}

	//functie pentru modificarea unui element din fisier
	void update(const Locatar& locatar, const Locatar& locatar_nou) override {
		LocatariRepo::update(locatar, locatar_nou);
		saveRepo();
	}

	//fucntie pentru stergerea unui element din fisier
	void deletee(const Locatar& locatar) override {
		LocatariRepo::deletee(locatar);
		saveRepo();
	}
};