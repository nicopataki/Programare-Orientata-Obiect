#include "listaRepo.h"

void ListaRepo::add_apartament(const Locatar& locatar) {
	const int apartament = locatar.get_apartament();
	if (search_apartament_lista(apartament) != -1) {
		throw ListaException("Exista deja un locatar pentru apartamentul dat!");
	}
	else {
		this->Lista.push_back(locatar);
	}
	notify();
}

int ListaRepo::search_apartament_lista(const int apartament) {
	auto it = find_if(this->Lista.begin(), this->Lista.end(), [apartament](const Locatar& locatar) noexcept {
		if (locatar.get_apartament() == apartament)
			return true;
		return false;
		});
	const long long poz = std::distance(this->Lista.begin(), it);
	if (it != this->Lista.end()) {
		return static_cast<int>(poz);
	}
	return -1;
}

void ListaRepo::empty_list() noexcept {
	Lista.clear();
	notify();
}

void ListaRepo::generate_apartamente(int nr_apartamente, const vector<Locatar>& memory) {
	empty_list();
	auto to_list = memory;
	shuffle(to_list.begin(), to_list.end(), std::default_random_engine(static_cast<unsigned int>(time(nullptr))));
	while (nr_apartamente && !to_list.empty()) {
		add_apartament(to_list.back());
		to_list.pop_back();
		nr_apartamente--;
	}
	notify();
}

const vector<Locatar>& ListaRepo::get_Lista() noexcept {
	return Lista;
}

void ListaRepo::export_apartamente(const std::string& file_name) {
	string filename = file_name;
	const auto poz = filename.find_last_of(".");
	if (poz < filename.size()) {
		auto file_extension = file_name.substr(poz);
		if (file_extension != ".html") {
			filename = filename + ".html";
		}
	}
	else {
		filename = filename + ".html";
	}

	std::ofstream fout(filename);
	fout << "<html>\n"
		"<body>\n"
		"<head>\n"
		"    <h3 style=\" font-family: 'Caviar Dreams',serif; color:mediumpurple; \">Lista Apartamente</h3>\n"
		"    </head>\n"
		"<style>\n"
		"   p {\n"
		"    color: #D7BDE2 ;\n"
		"    background-color: #A9CCE3 ;\n"
		"    border: 1px solid black; }\n"
		"   table,th,td{\n"
		"    border: 1px solid black;\n"
		"   }\n"
		"   th{\n"
		"    color: darkviolet;\n"
		"   }\n"
		"   body{\n"
		"    background-color: #CACFD2;\n"
		"   }\n"
		"</style>\n";
	fout << "<table>\n"
		"\n"
		"    <th>Apartament</th>\n"
		"    <th>Nume</th>\n"
		"    <th>Suprafata</th>\n"
		"    <th>Tipul</th>\n";
	for (const Locatar& locatar : get_Lista()) {
		fout << "<tr>\n";
		fout << "<th>" << locatar.get_apartament() << "</th>\n"
			<< "<th>" << locatar.get_nume() << "</th>\n"
			<< "<th>" << locatar.get_suprafata() << "</th>\n"
			<< "<th>" << locatar.get_tip() << "</th>\n"
			<< "</tr>\n";
	}

	fout << "</table>\n"
		"\n"
		"\n"
		"</body>\n"
		"</html>";
}

