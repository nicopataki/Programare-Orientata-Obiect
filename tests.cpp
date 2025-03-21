#include "tests.h"
#include "domain.h"
#include "repo.h"
#include "validator.h"
#include "service.h"
#include "cassert"
#include "sstream"

using std::stringstream;

void Tests::runAllTests() {
	LocatarTests();
	RepoTests();
	ValidatorTests();
	ServiceTests();
	testUndo();
	ServiceFileTests();
}

void Tests::LocatarTests() {
	Locatar locatar(1, "Vasile", 20, "normal");
	assert(locatar.get_apartament() == 1);
	assert(locatar.get_nume() == "Vasile");
	assert(locatar.get_suprafata() == 20);
	assert(locatar.get_tip() == "normal");
	Locatar copy = locatar;
	assert(copy == locatar);
	assert(copy.get_apartament() == 1);
	assert(copy.get_nume() == "Vasile");
	Locatar locatar2(2, "Andrei", 22, "normal");
	assert(comparaNume(locatar, locatar2) == 0);
	assert(comparaSuprafata(locatar, locatar2) == 1);
	assert(comparaTip(locatar, locatar2) == 0);
	Locatar loc{};
	assert(loc.get_apartament() == -1);
	assert(loc.get_nume().empty());
	assert(loc.to_string_print() != "");
}

void Tests::RepoTests() {
	vector<Locatar> tests;
	assert(tests.empty() == 1);
	//LocatariRepo repo;
	//AbstractRepo* repo;
	ProbabilityRepo prob(0);
	try {
		prob.store(Locatar{ 1, "Vasile", 12, "normal" });
		assert(false);
	}
	catch (const LocatariRepoException&) {
		assert(true);
	}

	ProbabilityRepo repo(1);
	repo.store(Locatar{ 1, "Vasile", 10, "normal" });
	Locatar locatar(1, "Vasile", 10, "normal");
	assert(repo.getAll().size() == 1);
	assert(repo.find(locatar).get_nume() == "Vasile");

	assert(repo.search_poz(1) == 1);
	assert(repo.getLocatar(1).get_nume() == "Vasile");

	try {
		repo.getLocatar(2);
		assert(false);
	}
	catch (const LocatariRepoException&) {
		assert(true);
	}
	try {
		repo.store(Locatar{ 1, "Vasile", 10, "garsoniera" });
		assert(false);
	}
	catch (const LocatariRepoException&) {
		assert(true);
	}

	assert(repo.search_poz(2) == -1);

	repo.store(Locatar{ 2, "Mihai", 9, "garsoniera" });
	assert(repo.getAll().size() == 2);

	Locatar loc(4, "Mihai", 10, "normal");
	try {
		repo.find(loc);
		assert(false);
	}
	catch (const LocatariRepoException& ex) {
		stringstream os;
		os << ex;
		assert(os.str().find("exista") >= 0);
	}

	try {
		repo.deletee(Locatar{ 3, "Andrei", 10, "normal" });
		assert(false);
	}
	catch (const LocatariRepoException&) {
		assert(true);
	}

	try {
		repo.update(Locatar{ 3, "Andrei", 10, "normal" }, locatar);
		assert(false);
	}
	catch (const LocatariRepoException&) {
		assert(true);
	}

	repo.store(Locatar{ 3, "Andrei", 10, "normal" });
	assert(repo.getAll().size() == 3);
	repo.deletee(Locatar{ 3, "Andrei", 10, "normal" });
	assert(repo.getAll().size() == 2);

	Locatar locatar3(1, "Ana", 10, "garsoniera");
	repo.update(locatar, locatar3);
	assert(repo.find(locatar).get_nume() == "Ana");

	Locatar locatar_1(1, "Mihai", 20, "garsoniera");
	repo.modify(locatar_1);
	assert(repo.getLocatar(1).get_nume() == "Mihai");

	Locatar locatar_2(10, "Ana", 12, "garsoniera");
	try {
		repo.modify(locatar_2);
		assert(false);
	}
	catch (const LocatariRepoException&) {
		assert(true);
	}

	LocatariRepo repo2;
	repo2.store(Locatar{ 1, "Vasile", 10, "normal" });
	Locatar slocatar(1, "Vasile", 10, "normal");
	assert(repo2.getAll().size() == 1);
	assert(repo2.find(slocatar).get_nume() == "Vasile");

	assert(repo2.search_poz(1) == 0);
	assert(repo2.getLocatar(1).get_nume() == "Vasile");

	try {
		repo2.getLocatar(2);
		assert(false);
	}
	catch (const LocatariRepoException&) {
		assert(true);
	}

	assert(repo2.search_poz(2) == -1);

	repo2.store(Locatar{ 2, "Mihai", 9, "garsoniera" });
	assert(repo2.getAll().size() == 2);

	try {
		repo2.store(Locatar{ 1, "Vasile", 10, "garsoniera" });
		assert(false);
	}
	catch (const LocatariRepoException&) {
		assert(true);
	}
	Locatar sloc(4, "Mihai", 10, "normal");
	try {
		repo2.find(sloc);
		assert(false);
	}
	catch (const LocatariRepoException& ex) {
		stringstream os;
		os << ex;
		assert(os.str().find("exista") >= 0);
	}

	try {
		repo2.deletee(Locatar{ 3, "Andrei", 10, "normal" });
		assert(false);
	}
	catch (const LocatariRepoException&) {
		assert(true);
	}

	try {
		repo2.update(Locatar{ 3, "Andrei", 10, "normal" }, locatar);
		assert(false);
	}
	catch (const LocatariRepoException&) {
		assert(true);
	}

	repo2.store(Locatar{ 3, "Andrei", 10, "normal" });
	assert(repo2.getAll().size() == 3);
	repo2.deletee(Locatar{ 3, "Andrei", 10, "normal" });
	assert(repo2.getAll().size() == 2);

	Locatar slocatar3(1, "Ana", 10, "garsoniera");
	repo2.update(slocatar, slocatar3);
	assert(repo2.find(slocatar).get_nume() == "Ana");

	Locatar slocatar_1(1, "Mihai", 20, "garsoniera");
	repo2.modify(slocatar_1);
	assert(repo2.getLocatar(1).get_nume() == "Mihai");

	Locatar slocatar_2(10, "Ana", 12, "garsoniera");
	try {
		repo2.modify(slocatar_2);
		assert(false);
	}
	catch (const LocatariRepoException&) {
		assert(true);
	}
}

void Tests::ValidatorTests() {
	LocatarValidator val;
	Locatar locatar{ -1, "", -1, "" };
	try {
		val.validate(locatar);
	}
	catch (const ValidateException& ex) {
		std::stringstream out;
		out << ex;
		const auto& mesaj = out.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}
}

void Tests::ServiceTests() {
	vector<Locatar> tests;
	LocatariRepo* repo = new LocatariRepo;
	FileRepo* repo3 = new FileRepo{ "teste.txt" };
	//ProbabilityRepo *repo2 = new ProbabilityRepo(1);
	LocatarValidator val;
	ListaRepo lista;
	//LocatariService srv2{ repo2, val, lista };
	LocatariService srv{ repo, val, lista };
	LocatariService srv3{ repo3, val, lista };
	Locatar locatar{ 1, "Vasile", 10, "normal" };
	srv.addLocatar(1, "Vasile", 10, "normal");
	assert(srv.get_All().size() == 1);

	srv.addLocatar(2, "Mihai", 11, "garsoniera");
	srv.addLocatar(3, "Andrei", 20, "normal");
	srv.updateLocatar(2, "Ana", 10, "garsoniera");
	assert(srv.findLocatar(2).get_nume() == "Ana");

	srv.add_to_list(1);
	srv.add_to_list(2);
	srv.add_to_list(3);
	assert(srv.getListaSize() == 3);

	try {
		srv.add_to_list(2);
		assert(false);
	}
	catch (ListaException&) {
		assert(true);
	}

	try {
		srv.add_to_list(4);
		assert(false);
	}
	catch (LocatariRepoException&) {
		assert(true);
	}

	srv.emptyList();
	assert(srv.getListaSize() == 0);

	srv.generateList(1);
	assert(srv.getListaSize() == 1);

	map<string, DTO> raport = srv.raport();
	assert(raport["normal"].get_count() == 2);
	assert(raport["garsoniera"].get_count() == 1);

	const vector<Locatar>& locatari = srv.getAllLista();
	assert(locatari.size() == 1);

	srv.exportList("test.txt");
	srv.exportList("test");


	assert(srv.filtreaza_suprafata(15).size() == 2);
	assert(srv.filtreaza_tip("normal").size() == 2);

	assert(srv.filterByApartament(2).size() == 1);

	auto first = srv.sortByNume()[0];
	assert(first.get_nume() == "Ana");

	first = srv.sortBySuprafata()[0];
	assert(first.get_suprafata() == 10);

	first = srv.sortByTipSuprafata()[1];
	assert(first.get_suprafata() == 10);

	srv.delLocatar(2);
	assert(srv.get_All().size() == 2);

	tests.push_back(first);
	assert(tests.empty() == 0);
}

void Tests::testUndo() {
	vector<Locatar> tests;
	//LocatariRepo repo;
	FileRepo* repo = new FileRepo{ "testeundo.txt" };
	LocatarValidator val;
	ListaRepo lista;
	LocatariService srv{ repo, val, lista };
	srv.addLocatar(1, "mihai", 12, "normal");
	srv.addLocatar(2, "andrei", 13, "normal");
	srv.addLocatar(3, "ana", 20, "normal");
	srv.addLocatar(4, "maria", 10, "garsoniera");
	assert(srv.get_All().size() == 4);
	srv.Undo();
	try {
		srv.findLocatar(4);
		assert(false);
	}
	catch (LocatariRepoException&) {
		assert(true);
	}

	srv.delLocatar(2);
	assert(srv.get_All().size() == 2);

	srv.Undo();
	assert(srv.get_All().size() == 3);

	srv.updateLocatar(1, "vasile", 12, "2camere");
	srv.Undo();
	assert(srv.findLocatar(1).get_nume() == "mihai");

	srv.Undo();
	srv.Undo();
	srv.Undo();
	try {
		srv.Undo();
		assert(false);
	}
	catch (const LocatariRepoException&) {
		assert(true);
	}

	repo->emptyFile();
}

void Tests::ServiceFileTests() {
	vector<Locatar> tests;
	FileRepo* repo = new FileRepo{ "test_nou.txt" };
	LocatarValidator val;
	ListaRepo lista;
	LocatariService srv{ repo, val, lista };
	srv.addLocatar(1, "Vasile", 10, "normal");
	assert(srv.get_All().size() == 1);
	srv.addLocatar(2, "Mihai", 11, "garsoniera");
	srv.addLocatar(3, "Andrei", 20, "normal");
	srv.updateLocatar(2, "Ana", 10, "garsoniera");
	assert(srv.findLocatar(2).get_nume() == "Ana");

	srv.delLocatar(2);
	assert(srv.get_All().size() == 2);
	srv.addLocatar(2, "Ana", 10, "garsoniera");

	srv.add_to_list(1);
	srv.add_to_list(2);
	srv.add_to_list(3);
	assert(srv.getListaSize() == 3);

	try {
		srv.add_to_list(2);
		assert(false);
	}
	catch (ListaException&) {
		assert(true);
	}

	try {
		srv.add_to_list(4);
		assert(false);
	}
	catch (LocatariRepoException&) {
		assert(true);
	}

	assert(srv.filtreaza_suprafata(15).size() == 2);
	assert(srv.filtreaza_tip("normal").size() == 2);

	assert(srv.filterByApartament(2).size() == 1);

	auto first = srv.sortByNume()[0];
	assert(first.get_nume() == "Ana");

	first = srv.sortBySuprafata()[0];
	assert(first.get_suprafata() == 10);

	first = srv.sortByTipSuprafata()[1];
	assert(first.get_suprafata() == 10);

	srv.delLocatar(2);
	assert(srv.get_All().size() == 2);

	tests.push_back(first);
	assert(tests.empty() == 0);

	repo->emptyFile();
}