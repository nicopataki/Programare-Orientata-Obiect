#include "repo.h"

using std::ostream;

void LocatariRepo::store(const Locatar& locatar) {
	if (exista(locatar)) {
		throw LocatariRepoException("Exista deja un proprietar pentru apartamentul dat");
	}
	this->all.push_back(locatar);
}

bool LocatariRepo::exista(const Locatar& locatar) {
	try {
		find(locatar);
		return true;
	}
	catch (LocatariRepoException&) {
		return false;
	}
}

Locatar& LocatariRepo::find(const Locatar& locatar) {
	auto it = find_if(all.begin(), all.end(), [&locatar](const Locatar& el) noexcept {
		return el.get_apartament() == locatar.get_apartament();
		});
	if (it == all.end()) {
		throw LocatariRepoException("Nu exista locatar la apartamentul dat!");
	}
	return *it;
}

void LocatariRepo::deletee(const Locatar& locatar) {
	if (!exista(locatar)) {
		throw LocatariRepoException("Nu exista apartamentul dat");
	}
	auto it = find_if(all.begin(), all.end(), [&locatar](const Locatar& el) noexcept {
		return el.get_apartament() == locatar.get_apartament();
		});
	all.erase(it);

}

void LocatariRepo::update(const Locatar& locatar, const Locatar& locatar_nou) {
	if (!exista(locatar)) {
		throw LocatariRepoException("Nu exista apartamentul dat");
	}
	auto it = find_if(all.begin(), all.end(), [&locatar](const Locatar& el) noexcept {
		return el.get_apartament() == locatar.get_apartament();
		});
	*it = locatar_nou;
}

vector<Locatar>& LocatariRepo::getAll() {
	return this->all;
}

int LocatariRepo::search_poz(const int apartament) {
	auto it = find_if(this->all.begin(), this->all.end(), [apartament](const Locatar& loc) noexcept {
		if (loc.get_apartament() == apartament)
			return true;
		return false;
		});
	const auto poz = std::distance(this->all.begin(), it);
	if (it != this->all.end())
		return static_cast<int>(poz);
	return -1;
}

Locatar& LocatariRepo::getLocatar(const int apartament) {
	const int index = search_poz(apartament);
	if (index != -1) {
		return this->all[index];
	}
	else {
		throw LocatariRepoException("Nu exista apartamentul!");
	}
}

void LocatariRepo::modify(const Locatar& locatar) {
	const int apartament = locatar.get_apartament();
	const int poz = search_poz(apartament);
	if (poz != -1) {
		this->all[poz] = locatar;
	}
	else {
		throw LocatariRepoException("Nu exista apartamentul dat!");
	}
}

void ProbabilityRepo::store(const Locatar& locatar) {
	det_luck();
	if (exista(locatar)) {
		throw LocatariRepoException("Exista deja un proprietar pentru apartamentul dat");
	}
	elems.insert(make_pair(locatar.get_apartament(), locatar));
}

void ProbabilityRepo::update(const Locatar& locatar, const Locatar& locatar_nou) {
	det_luck();
	if (!exista(locatar)) {
		throw LocatariRepoException("Nu exista apartamentul dat");
	}
	for (auto& it : elems) {
		if (it.first == locatar.get_apartament()) {
			elems.erase(locatar.get_apartament());
			elems.insert(make_pair(locatar_nou.get_apartament(), locatar_nou));
			break;
		}
	}
}

void ProbabilityRepo::deletee(const Locatar& locatar) {
	det_luck();
	if (!exista(locatar)) {
		throw LocatariRepoException("Nu exista apartamentul dat");
	}
	elems.erase(locatar.get_apartament());
	map<int, Locatar> sec;
	sec.clear();
	for (auto& it : elems) {
		sec.insert(make_pair(it.second.get_apartament(), it.second));
	}
}

vector<Locatar> all;
vector<Locatar>& ProbabilityRepo::getAll() {
	det_luck();
	all.clear();
	for (auto& it : elems) {
		all.push_back(it.second);
	}
	return all;
}

ProbabilityRepo::ProbabilityRepo(float chance) {
	prob = chance;
	elems.clear();
}

void ProbabilityRepo::det_luck() {
	auto const probability = int(prob * 10);
	int const nr = rand() % 10 + 1;
	if (nr <= probability) {
		return;
	}
	throw LocatariRepoException("eroare");
}

Locatar& ProbabilityRepo::find(const Locatar& locatar) {
	det_luck();
	for (auto& it : elems) {
		if (it.second.get_apartament() == locatar.get_apartament()) {
			return it.second;
		}
	}
	throw LocatariRepoException("Nu exista locatar la aprtamentul dat!");
}

int ProbabilityRepo::search_poz(const int apartament) {
	det_luck();
	int nr = 0;
	vector<Locatar> locatari = this->getAll();
	nr = static_cast<int>(locatari.size());
	int poz = 0;
	for (auto& it : elems) {
		if (it.second.get_apartament() == apartament)
			return nr - poz;
		poz++;
	}
	return -1;
}

Locatar& ProbabilityRepo::getLocatar(const int apartament) {
	det_luck();
	const int index = search_poz(apartament);
	if (index != -1) {
		return this->elems[index];
	}
	else {
		throw LocatariRepoException("Nu exista apartamentul!");
	}
}

void ProbabilityRepo::modify(const Locatar& locatar) {
	det_luck();
	const int apartament = locatar.get_apartament();
	const int poz = search_poz(apartament);
	if (poz != -1) {
		this->elems[poz] = locatar;
	}
	else {
		throw LocatariRepoException("Nu exista apartamentul dat!");
	}
}

bool ProbabilityRepo::exista(const Locatar& locatar) {
	det_luck();
	try {
		find(locatar);
		return true;
	}
	catch (LocatariRepoException&) {
		return false;
	}
}

ostream& operator<<(ostream& out, const LocatariRepoException& ex) {
	out << ex.msg;
	return out;
}