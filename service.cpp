#include "service.h"


/*vector<Locatar> LocatariService::generalSort(bool(*maiMicF)(const Locatar&, const Locatar&)) {
	if (maiMicF == nullptr) {
		return { };
	}
	vector<Locatar> v{ repo.getAll() };//fac o copie
	for (int i = 0; i < v.size(); i++) {
		for (int j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v[i], v[j])) {
				//interschimbam
				Locatar aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}*/

const vector<Locatar>& LocatariService::getAllLista() noexcept {
	return lista.get_Lista();
}

void LocatariService::generateList(int nrApartamente) {
	lista.generate_apartamente(nrApartamente, repo->getAll());
}

void LocatariService::exportList(const std::string& name) {
	lista.export_apartamente(name);
}

void LocatariService::emptyList() noexcept {
	lista.empty_list();
}

void LocatariService::add_to_list(const int apartament) {
	const auto found = repo->search_poz(apartament);
	if (found != -1) {
		auto loc = repo->getLocatar(apartament);
		lista.add_apartament(loc);
	}
	else if (found == -1) {
		throw LocatariRepoException("Apartamentul nu exista");
	}
}

int LocatariService::getListaSize() noexcept {
	return static_cast<int>(lista.get_Lista().size());
}

map<string, DTO> LocatariService::raport() {
	map<string, DTO> raport;
	auto locatari = repo->getAll();
	for (const auto& loc : locatari) {
		DTO tip(loc.get_tip());
		raport[loc.get_tip()] = tip;
	}

	for (const auto& loc : locatari) {
		const int nr = raport[loc.get_tip()].get_count() + 1;
		DTO new_val(loc.get_tip(), nr);
		raport[loc.get_tip()] = new_val;
	}
	return raport;
}

/*LocatariService::LocatariService(AbstractRepo* repo, LocatarValidator& val, ListaRepo& lista) {
	repo = repo;
	val = val;
	lista = lista;
	undoActions.clear();
}*/


void LocatariService::addLocatar(int apartament, const string& nume, int suprafata, const string& tip) {
	Locatar locatar{ apartament, nume, suprafata, tip };
	val.validate(locatar);
	repo->store(locatar);

	undoActions.push_back(std::make_unique<UndoAdauga>(locatar, repo));
	//repo.saveRepo();
}

Locatar LocatariService::findLocatar(int apartament) {
	Locatar locatar{ apartament, "nume", 5, "tip" };
	val.validate(locatar);
	return repo->find(locatar);
}

void LocatariService::delLocatar(int apartament) {
	vector<Locatar> locatari = get_All();
	Locatar locatar;
	for (Locatar i : locatari) {
		if (i.get_apartament() == apartament) {
			locatar = i;
		}
	}
	val.validate(locatar);
	repo->deletee(locatar);

	undoActions.push_back(std::make_unique<UndoSterge>(repo, locatar));
	//repo.saveRepo();
}

void LocatariService::updateLocatar(int apartament, const string& nume, int suprafata, const string& tip) {
	Locatar locatar = repo->getLocatar(apartament);
	Locatar locatar_nou{ apartament, nume, suprafata, tip };
	val.validate(locatar);
	val.validate(locatar_nou);
	repo->update(locatar, locatar_nou);

	undoActions.push_back(std::make_unique<UndoModifica>(locatar, repo));
	//repo.saveRepo();
}

/*vector<Locatar> LocatariService::filtru(function<bool(const Locatar)> functie) {
	vector<Locatar> rez;
	for (const auto& loc : repo.getAll()) {
		if (functie(loc)) {
			rez.push_back(loc);
		}
	}
	return rez;
}*/


vector<Locatar> LocatariService::filtreaza_tip(const string& tip) {
	vector<Locatar> filtrat;
	copy_if(repo->getAll().begin(), repo->getAll().end(), std::back_inserter(filtrat), [tip](const Locatar& locatar) noexcept {
		return locatar.get_tip() == tip;
		});
	return filtrat;
}

vector<Locatar> LocatariService::filtreaza_suprafata(int suprafata) {
	vector<Locatar> filtrat;
	copy_if(repo->getAll().begin(), repo->getAll().end(), std::back_inserter(filtrat), [suprafata](const Locatar& locatar) noexcept {
		return locatar.get_suprafata() < suprafata;
		});
	return filtrat;
}

vector<Locatar> LocatariService::filterByApartament(int apartament) {
	vector<Locatar> filtrat;
	copy_if(repo->getAll().begin(), repo->getAll().end(), std::back_inserter(filtrat), [apartament](const Locatar& locatar) noexcept {
		return locatar.get_apartament() == apartament;
		});
	return filtrat;
}

vector<Locatar> LocatariService::sortByNume() {
	auto sortat = repo->getAll();
	sort(sortat.begin(), sortat.end(), comparaNume);
	return sortat;
}

vector<Locatar> LocatariService::sortBySuprafata() {
	auto sortat = repo->getAll();
	sort(sortat.begin(), sortat.end(), comparaSuprafata);
	return sortat;
}

vector<Locatar> LocatariService::sortByTipSuprafata() {
	auto sortat = repo->getAll();
	sort(sortat.begin(), sortat.end(), comparaSuprafata);
	sort(sortat.begin(), sortat.end(), comparaTip);
	return sortat;
}


void LocatariService::Undo() {
	if (undoActions.empty()) {
		throw LocatariRepoException("Nu se mai poate face undo!");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
	//repo->saveRepo();
}

set<string> LocatariService::number_of_types() {
	set<string> types;
	vector <Locatar> locatari = get_All();
	for (const auto& i : locatari) {
		types.insert(i.get_tip());
	}
	return types;
}