
#include "GUI.h"

	void AppGUI::init_gui() {
		this->setWindowTitle("Locatari App");
		QPalette palette = QPalette();
		palette.setColor(QPalette::Window, "#FAE381");
		QFont font("Caviar Dreams", 12);
		this->setAutoFillBackground(true);
		this->setPalette(palette);
		this->setFont(font);
		auto* lymain = new QHBoxLayout;
		setLayout(lymain);

		//List layout
		auto* left_layout = new QVBoxLayout;
		lymain->addLayout(left_layout, 9);
		//now i am gonna populate it
		//Adding the label for the table
		left_layout->addWidget(new QLabel{ "Table" });
		tableV->resizeColumnsToContents();
		left_layout->addWidget(tableV);
		left_layout->addWidget(undo);
		left_layout->addWidget(open_contract);

		//Right Layout
		QVBoxLayout* right_layout = new QVBoxLayout;
		//lymain->stretch(30);
		lymain->addLayout(right_layout, 30);
		//operations
		QFormLayout* data_layout = new QFormLayout;
		right_layout->addLayout(data_layout);
		data_layout->addRow(new QLabel{ "APARTAMENT:" }, txtApartament);
		data_layout->addRow(new QLabel{ "NUME:" }, txtName);
		data_layout->addRow(new QLabel{ "SUPRAFATA:" }, txtSuprafata);
		data_layout->addRow(new QLabel{ "TIP:" }, txtTip);
		data_layout->addRow(new QLabel{ "NUMARUL APARTAMENTELOR:" }, txtListNumber);
		data_layout->addRow(new QLabel{ "NUMELE FISIERULUI:" }, txtListFile);
		data_layout->addRow(new QLabel{ "LISTA:" });
		right_layout->addWidget(list);

		QHBoxLayout* actions = new QHBoxLayout;
		right_layout->addLayout(actions);
		actions->addWidget(add);
		actions->addWidget(modify);
		actions->addWidget(del);
		actions->addWidget(find);

		actions->addWidget(add_contract);
		actions->addWidget(empty_contract);
		actions->addWidget(generate_contract);
		actions->addWidget(export_contract);

		QVBoxLayout* sflayer = new QVBoxLayout;
		right_layout->addLayout(sflayer);
		sflayer->addWidget(new QLabel{ "SORT TYPE" });
		sflayer->addWidget(sort_name);
		sflayer->addWidget(sort_sup);
		sflayer->addWidget(sort_ts);
		sflayer->addWidget(new QLabel{ "FILTER" });
		QHBoxLayout* filterlayer = new QHBoxLayout;
		right_layout->addLayout(type);
		right_layout->addLayout(filterlayer);
		filterlayer->addWidget(filter_type);
		filterlayer->addWidget(filter_sup);
		right_layout->addWidget(txtfilter);
		left_layout->addWidget(load);
		left_layout->addWidget(loadlist);
		right_layout->addWidget(exit);
		right_layout->addWidget(open_roc);
	}

	void AppGUI::ui_generatetypebuttons() {
		set<string> types_from_service = service.number_of_types();

		for (const auto& t : types_from_service)
		{
			auto it = find_if(this->buttons_types.begin(),
				buttons_types.end(),
				[t](const pair<QPushButton*, string>& but)
				{
					if (but.second == t)
						return true;
					else
						return false;
				});

			if (it != this->buttons_types.end())
			{
				continue;
			}
			else {
				std::cout << t << "\n";


				QPushButton* button = new QPushButton{ QString::fromStdString(t) };
				buttons_types.push_back(std::make_pair(button, t));
				type->addWidget(button);

				QObject::connect(button, &QPushButton::clicked, [this, t]() {
					map<string, DTO> m = service.raport();
					int nr = m[t].get_count();
					QString mes = "Number is:";
					mes += QString::number(nr);
					QMessageBox::information(nullptr, "Info", mes);
					});

			}
		}
		vector<string> toremove;
		for (const auto& pair : buttons_types)
		{
			if (std::find(types_from_service.begin(), types_from_service.end(), pair.second) == types_from_service.end())
			{
				toremove.push_back(pair.second);
				std::cout << pair.second << " HERE";
			}
		}

		for (const auto& type_to_remove : toremove)
		{
			auto it = find_if(this->buttons_types.begin(),
				buttons_types.end(),
				[type_to_remove](const pair<QPushButton*, string>& but)
				{
					if (but.second == type_to_remove)
						return true;
					else
						return false;
				});
			int poz = (int)std::distance(this->buttons_types.begin(), it);
			delete this->buttons_types[poz].first;
			this->buttons_types.erase(it);
		}
	}

	/*void AppGUI::listaGUI() {
		lista->setWindowTitle("Set Contract");
		QPalette second_pal = QPalette();
		second_pal.setColor(QPalette::Window, "#81FADD");
		QFont font2("Comic Sans", 12);
		lista->setPalette(second_pal);
		lista->setFont(font2);
		QHBoxLayout* lysecond = new QHBoxLayout;
		lista->setLayout(lysecond);
		QVBoxLayout* l_lay = new QVBoxLayout;
		lysecond->addLayout(l_lay);
		l_lay->addWidget(new QLabel{ "LISTA" });
		l_lay->addWidget(empty_list);
		QFormLayout* l_form = new QFormLayout;
		l_lay->addLayout(l_form);
		l_form->addRow(new QLabel{ "Apartament:" }, txtListApartament);
		l_lay->addWidget(add_list);
		l_lay->addWidget(new QLabel{ "GENERATE" });
		QFormLayout* gen_layout = new QFormLayout;
		l_lay->addLayout(gen_layout);
		gen_layout->addRow(new QLabel{ "How many:" }, txtListNumber);
		l_lay->addWidget(generate_list);
		l_lay->addWidget(new QLabel{ "Export" });
		QFormLayout* export_layout = new QFormLayout;
		l_lay->addLayout(export_layout);
		export_layout->addRow(new QLabel{ "FILE:" }, txtListFile);
		l_lay->addWidget(export_list);
		QVBoxLayout* r_layout = new QVBoxLayout;
		lysecond->addLayout(r_layout);
		r_layout->addWidget(lista_list);
		r_layout->addWidget(exit_list);
	}*/

	void Contract::reloadList() {
		const auto& loc = locatari.get_Lista();
		locat->clear();
		for (const auto& locatar : loc) {
			locat->addItem(QString::fromStdString(locatar.l_loc()));
		}
	}

	/*void AppGUI::ui_reloadList(const vector<Locatar>& locatari) {
		contract->contract_list->clear();
		for (const auto& loc : locatari) {
			contract->contract_list->addItem(QString::fromStdString(loc.l_loc()));
		}
	}*/

	void Contract::ui_addContract() {
		string apartament = txtListApartament->text().toStdString();
		int a;
		try {
			a = stoi(apartament);
		}
		catch (LocatariRepoException) {
			QMessageBox::warning(this, "WARNING", "Invalid data!");
			return;
		}
		auto found = srv.filterByApartament(a);
		if (found.empty()) {
			QMessageBox::warning(this, "1", "Nu exista locatar pentru apartamentul dat!");
			return;
		}
		else
			try {
			srv.add_to_list(a);
		}
		catch (LocatariRepoException) {
			QMessageBox::warning(this, "WARNING", "Exista deja un locatar pentru apartamentul dat!");
		}
		reloadList();
		notify();
	}

	void Contract::init_contract() {
		locatari.addObs(this);
		setWindowTitle("Set Contract");
		QPalette second_pal = QPalette();
		second_pal.setColor(QPalette::Window, "#81FADD");
		QFont font2("Comic Sans", 12);
		setPalette(second_pal);
		setFont(font2);
		QHBoxLayout* lysecond = new QHBoxLayout;
		setLayout(lysecond);
		QVBoxLayout* l_lay = new QVBoxLayout;
		//lysecond->addWidget(locatari);
		lysecond->addLayout(l_lay);
		l_lay->addWidget(new QLabel{ "LISTA" });
		//l_lay->addWidget(refreshL);
		l_lay->addWidget(empty_contract);
		QFormLayout* l_form = new QFormLayout;
		l_lay->addLayout(l_form);
		/*l_form->addRow(new QLabel{"Apartament:"}, txtListApartament);
		l_lay->addWidget(add_contract);*/
		l_lay->addWidget(new QLabel{ "GENERATE" });
		QFormLayout* gen_layout = new QFormLayout;
		l_lay->addLayout(gen_layout);
		gen_layout->addRow(new QLabel{ "How many:" }, txtListNumber);
		l_lay->addWidget(generate_contract);
		/*l_lay->addWidget(new QLabel{"Export"});
		QFormLayout* export_layout = new QFormLayout;
		l_lay->addLayout(export_layout);
		export_layout->addRow(new QLabel{ "FILE:" }, txtListFile);
		l_lay->addWidget(export_contract);*/
		QVBoxLayout* r_layout = new QVBoxLayout;
		lysecond->addLayout(r_layout);
		r_layout->addWidget(locat);
		r_layout->addWidget(exit_contract);
	}

	void Contract::connectSignalContract() {
		this->reloadList();
		QObject::connect(refreshL, &QPushButton::clicked, [&]() {
			reloadList();
			});
		QObject::connect(exit_contract, &QPushButton::clicked, [&]() {
			this->notify();
			close();
			});
		QObject::connect(empty_contract, &QPushButton::clicked, [&]() {
			srv.emptyList();
			reloadList();
			notify();
			});
		QObject::connect(generate_contract, &QPushButton::clicked, [&]() {
			string n = txtListNumber->text().toStdString();
			int nr;
			try {
				nr = stoi(n);
			}
			catch (std::invalid_argument& m) {
				QMessageBox::warning(nullptr, "!", "INVALID ARGUMENT");
			}
			srv.generateList(nr);

			reloadList();
			notify();
			txtListNumber->clear();
			});
		/*QObject::connect(add_contract, &QPushButton::clicked, this, &Contract::ui_addContract);
		QObject::connect(export_contract, &QPushButton::clicked, [&]() {
			string file = txtListFile->text().toStdString();
			srv.exportList(file);
			});*/
	}




	void AppGUI::loadTable(const vector<Locatar>&locatari) {
		/*this->table_main->clearContents();
		this->table_main->setColumnCount(5);
		// this->table_main->setRowCount(subject.size()+1);
		this->table_main->setRowCount(int(locatari.size()) + 1);
		int line_nr = 0;
		table_main->setItem(line_nr, 0, new QTableWidgetItem("NR"));
		table_main->setItem(line_nr, 1, new QTableWidgetItem("APARTAMENT"));
		table_main->setItem(line_nr, 2, new QTableWidgetItem("NUME"));
		table_main->setItem(line_nr, 3, new QTableWidgetItem("SUPRAFATA"));
		table_main->setItem(line_nr, 4, new QTableWidgetItem("TIP"));
		line_nr++;
		for (const auto& Locatar : locatari)
		{
			table_main->setItem(line_nr, 0, new QTableWidgetItem(QString::number(line_nr)));
			table_main->setItem(line_nr, 1, new QTableWidgetItem(QString::number(Locatar.get_apartament())));
			table_main->setItem(line_nr, 2, new QTableWidgetItem(QString::fromStdString(Locatar.get_nume())));
			table_main->setItem(line_nr, 3, new QTableWidgetItem(QString::number(Locatar.get_suprafata())));
			table_main->setItem(line_nr, 4, new QTableWidgetItem(QString::fromStdString(Locatar.get_tip())));
			line_nr++;
		}
		ui_generatetypebuttons();*/
		modelTable = new MyTableModel{ locatari };
		tableV->setModel(modelTable);
		tableV->setSelectionMode(QAbstractItemView::ExtendedSelection);
	}

	void AppGUI::afisare(const vector<Locatar>& locatari) {
		list->clear();
		for (Locatar l: locatari) {
			list->addItem(QString::fromStdString(l.to_string_print()));
		}
	}

	void AppGUI::ui_add() {
		string apartament = txtApartament->text().toStdString();
		string nume = txtName->text().toStdString();
		string suprafata = txtSuprafata->text().toStdString();
		string tip = txtTip->text().toStdString();
		qDebug() << nume;
		int h, k;
		try {
			h = stoi(apartament);
			k = stoi(suprafata);
		}
		catch (std::invalid_argument)
		{
			QMessageBox::warning(this, "WARNING", "INVALID DATA");
			return;
		}
		try
		{
			service.addLocatar(h, nume, k, tip);
		}
		catch (LocatariRepoException)
		{
			QMessageBox::warning(this, "WARNING", "Camp invalid");
		}
		catch (ValidateException)
		{
			QMessageBox::warning(this, "WARNING", "Camp invalid");
		}
		loadTable(service.get_All());
		afisare(service.get_All());
		curataFielduri();
	}

	void AppGUI::ui_delete() {
		string apartament = txtApartament->text().toStdString();
		int h;
		try {
			h = stoi(apartament);
		}
		catch (std::invalid_argument)
		{
			QMessageBox::warning(this, "WARNING", "INVALID DATA");
			return;
		}
		try {
			service.delLocatar(h);
		}
		catch (LocatariRepoException) {
			QMessageBox::warning(this, "WARNING", "Nu exista locatar pentru apartamentul dat");
		}
		loadTable(service.get_All());
		afisare(service.get_All());
		curataFielduri();
	}

	void AppGUI::ui_find() {
		string apartament = txtApartament->text().toStdString();
		vector<Locatar> loc;
		int h;
		try {
			h = stoi(apartament);
		}
		catch (std::invalid_argument)
		{
			QMessageBox::warning(this, "WARNING", "INVALID DATA");
			return;
		}
		try {
			loc.push_back(service.findLocatar(h));
		}
		catch (LocatariRepoException) {
			QMessageBox::warning(this, "WARNING", "Nu exista locatar pentru apartamentul dat");
		}
		loadTable(loc);
		afisare(loc);
		curataFielduri();
	}

	void AppGUI::ui_modify() {
		string apartament = txtApartament->text().toStdString();
		string nume = txtName->text().toStdString();
		string suprafata = txtSuprafata->text().toStdString();
		string tip = txtTip->text().toStdString();
		qDebug() << apartament;
		int h, k;
		try {
			h = stoi(apartament);
			k = stoi(suprafata);
		}
		catch (std::invalid_argument) {
			QMessageBox::warning(this, "WARNING", "INVALID DATA");
			return;
		}
		try {
			service.updateLocatar(h, nume, k, tip);
		}
		catch (LocatariRepoException) {
			QMessageBox::warning(this, "WARNING", "Nu exista locatar pentru apartamentul dat!");
		}
		loadTable(service.get_All());
		afisare(service.get_All());
	}

	void AppGUI::ui_filter_t() {
		string tip = txtfilter->text().toStdString();
		qDebug() << tip;
		vector<Locatar> loc = service.filtreaza_tip(tip);
		for (Locatar i : loc) {
			qDebug() << i.to_string_print();
		}
		loadTable(loc);
		afisare(loc);
	}

	void AppGUI::ui_filter_s() {
		string s = txtfilter->text().toStdString();
		int suprafata;
		try {
			suprafata = stoi(s);
		}
		catch (std::invalid_argument) {
			QMessageBox::warning(nullptr, "!", "Invalid input");
			return;
		}
		vector<Locatar> loc = service.filtreaza_suprafata(suprafata);
		for (Locatar i : loc) {
			qDebug() << i.to_string_print();
		}
		loadTable(loc);
		afisare(loc);
	}

	void AppGUI::ui_sort() {
		vector<Locatar> l = service.sortByNume();
		loadTable(l);
		afisare(l);
	}

	void AppGUI::loadList(const vector<Locatar>&locatari) {
		lista_list->clear();
		for (Locatar l : locatari) {
			lista_list->addItem(QString::fromStdString(l.to_string_print()));
		}
	}

	/*void AppGUI::ui_addList() {
		string apartament = txtListApartament->text().toStdString();
		int a;
		try {
			a = stoi(apartament);
		}
		catch (LocatariRepoException) {
			QMessageBox::warning(this, "WARNING", "Invalid data!");
			return;
		}
		auto found = service.filterByApartament(a);
		if (found.empty()) {
			QMessageBox::warning(this, "1", "Nu exista locatar pentru apartamentul dat!");
			return;
		}
		else
			try {
			service.add_to_list(a);
		}
		catch (LocatariRepoException) {
			QMessageBox::warning(this, "WARNING", "Exista deja un locatar pentru apartamentul dat!");
		}
		loadList(service.getAllLista());
	}*/

	void AppGUI::connectSignalSlots() {
		QObject::connect(exit, &QPushButton::clicked, [&]() {
			this->close();
			//contract->close();
			QMessageBox::information(nullptr, "!", "Closing app");
			});
		QObject::connect(add, &QPushButton::clicked, this, &AppGUI::ui_add);
		QObject::connect(del, &QPushButton::clicked, this, &AppGUI::ui_delete);
		QObject::connect(find, &QPushButton::clicked, this, &AppGUI::ui_find);
		QObject::connect(modify, &QPushButton::clicked, this, &AppGUI::ui_modify);
		QObject::connect(filter_type, &QPushButton::clicked, this, &AppGUI::ui_filter_t);
		QObject::connect(filter_sup, &QPushButton::clicked, this, &AppGUI::ui_filter_s);
		QObject::connect(load, &QPushButton::clicked, [&]() {
			this->loadTable(service.get_All());
			});
		QObject::connect(loadlist, &QPushButton::clicked, [&]() {
			this->afisare(service.get_All());
			});
		QObject::connect(sort_name, &QPushButton::toggled, this, &AppGUI::ui_sort);
		QObject::connect(sort_sup, &QPushButton::toggled, [&]() {
			loadTable(service.sortBySuprafata());
			afisare(service.sortBySuprafata());
			});
		QObject::connect(sort_ts, &QPushButton::toggled, [&]() {
			loadTable(service.sortByTipSuprafata());
			afisare(service.sortByTipSuprafata());
			});
		QObject::connect(undo, &QPushButton::clicked, [&]() {
			try {
				service.Undo();
			}
			catch (LocatariRepoException) {
				QMessageBox::warning(nullptr, "!", "Nu se mai poate face undo!");
			}
			loadTable(service.get_All());
			afisare(service.get_All());
			});
		QObject::connect(open_contract, &QPushButton::clicked, [&]() {
			auto contract_n = new Contract{ locatari, service };
			contract_n->init_contract();
			contract_n->connectSignalContract();
			contract_n->show();
			contract_n->addObs(contract_n);
			});

		QObject::connect(open_roc, &QPushButton::clicked, [&]() {
			auto contractRO = new ContractReadOnlyGUI(locatari);
			contractRO->show();
			});

		QObject::connect(add_contract, &QPushButton::clicked, [&]() {
			auto ap = stoi(txtApartament->text().toStdString());
			const auto& nume = txtName->text().toStdString();
			auto sup = stoi(txtSuprafata->text().toStdString());
			const auto& tip = txtTip->text().toStdString();
			Locatar loc{ ap, nume, sup, tip };
			locatari.add_apartament(loc);
			curataFielduri();
			});

		QObject::connect(empty_contract, &QPushButton::clicked, [&]() {
			locatari.empty_list();
			});

		QObject::connect(generate_contract, &QPushButton::clicked, [&]() {
			int n = stoi(txtListNumber->text().toStdString());
			locatari.generate_apartamente(n, service.get_All());
			txtListNumber->clear();
			});
		QObject::connect(export_contract, &QPushButton::clicked, [&]() {
			string name = txtListFile->text().toStdString();
			locatari.export_apartamente(name);
			txtListFile->clear();
			});

		/*QObject::connect(open_list, &QPushButton::clicked, [&]() {
			lista->show();
			});
		QObject::connect(exit_list, &QPushButton::clicked, [&]() {
			lista->close();
			});
		QObject::connect(empty_list, &QPushButton::clicked, [&]() {
			service.emptyList();
			loadList(service.getAllLista());
			});
		QObject::connect(generate_list, &QPushButton::clicked, [&]() {
			string n = txtListNumber->text().toStdString();
			int nr;
			try {
				nr = stoi(n);
			}
			catch (std::invalid_argument) {
				QMessageBox::warning(nullptr, "!", "Invalid argument");
				return;
			}
			service.generateList(nr);
			loadList(service.getAllLista());
			});
		QObject::connect(add_list, &QPushButton::clicked, this, &AppGUI::ui_addList);
		QObject::connect(export_list, &QPushButton::clicked, [&]() {
			string file = txtListFile->text().toStdString();
			service.exportList(file);
			});*/

		QObject::connect(tableV, &QTableView::pressed, [&]() {
			auto sel = tableV->selectionModel();

			if (sel->selectedRows().size() > 0) {
				std::cout << "HERE";
				QModelIndex index = sel->selectedRows().at(0);
				QAbstractItemModel* model = tableV->model();

				QVariant apartamentVariant = model->data(model->index(index.row(), 0));
				QVariant numeVariant = model->data(model->index(index.row(), 1));
				QVariant suprafataVariant = model->data(model->index(index.row(), 2));
				QVariant tipVariant = model->data(model->index(index.row(), 3));
				std::cout << apartamentVariant.toString().toStdString();
				txtApartament->setText(apartamentVariant.toString());
				txtName->setText(numeVariant.toString());
				txtSuprafata->setText(suprafataVariant.toString());
				txtTip->setText(tipVariant.toString());
			}

			/*txtApartament->setText(sel->selectedRows(1).value(0).data().toString());
			txtName->setText(sel->selectedRows(2).value(0).data().toString());
			txtSuprafata->setText(sel->selectedRows(3).value(0).data().toString());
			txtTip->setText(sel->selectedRows(4).value(0).data().toString());*/
			});
	}

void AppGUI::curataFielduri() {
	txtApartament->clear();
	txtName->clear();
	txtSuprafata->clear();
	txtTip->clear();
}
	