#include <fstream>
#include "fileRepo.h"

FileRepo::FileRepo(const std::string& name) {
	this->fileName = name;
	loadRepo();
}

void FileRepo::loadRepo() {
	std::ifstream file(fileName);
	if (!file.is_open()) {
		return;
	}
	Locatar loc{};
	int apartament = 0, suprafata = 0;
	string nume, tip;
	while (file >> apartament && file >> nume && file >> suprafata && file >> tip) {
		Locatar locatar{ apartament, nume, suprafata, tip };
		if (loc.get_apartament() != locatar.get_apartament()) {
			LocatariRepo::store(locatar);
		}
		loc = locatar;
	}
}

void FileRepo::saveRepo() {
	std::ofstream out(fileName);
	for (const auto& locatar : this->getAll()) {
		out << locatar.get_apartament() << " " << locatar.get_nume() << " " << locatar.get_suprafata() << " " << locatar.get_tip() << "\n";
	}
	out.close();
}

void FileRepo::emptyFile() {
	std::ofstream out(fileName);
	out << "";
	out.close();
}
