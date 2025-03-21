#pragma once
#include "service.h"
#include "observer.h"
#include "listaRepo.h"
#include <QPaintEvent>
#include <QPainter>
#include <QMessageBox>
#include <QWidget>
#include <QVBoxLayout>
#include<QLayoutItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QDebug>
#include <QListWidget>
#include <QTableWidget>
#include <QRadioButton>
#include <QHeaderView>
#include <QSplitter>
#include "MyTableModel.h"
#include <QHeaderView>
using std::pair;

class ContractReadOnlyGUI;

class Contract :public QWidget, public Observable, public Observer {
	//friend class LocatariService;
	friend class AppGUI;
	//friend class ContractReadOnlyGUI;
private:
	ListaRepo& locatari;
	LocatariService& srv;
	QListWidget* locat = new QListWidget();
	//buttons
	QPushButton* refreshL = new QPushButton{ "&REFRESH LIST" };
	QPushButton* add_contract = new QPushButton{ "&ADD TO CONTRACT" };
	QPushButton* empty_contract = new QPushButton{ "&EMPTY CONTRACT" };
	QPushButton* generate_contract = new QPushButton{ "&GENERATE CONTRACT" };
	QPushButton* export_contract = new QPushButton{ "&EXPORT TO CONTRACT" };
	QPushButton* exit_contract = new QPushButton{ "&EXIT" };
	//text fields
	QLineEdit* txtListApartament = new QLineEdit;
	QLineEdit* txtListNumber = new QLineEdit;
	QLineEdit* txtListFile = new QLineEdit;
	void ui_addContract();
public:
	explicit Contract(ListaRepo& locatari, LocatariService& srv) :locatari{ locatari }, srv(srv) {};
	void init_contract();
	void connectSignalContract();
	void reloadList();
	void update() override {
		reloadList();
	}
};

class ContractReadOnlyGUI : public QWidget, public Observer {
	//friend class Contract;
	//Contract* contr;
	//QListWidget* lista_obj;
private:
	ListaRepo& locatar;
public:
	ContractReadOnlyGUI(ListaRepo& locatar) : locatar{ locatar } {
		locatar.addObs(this);
		connect();
	}
	/*explicit ContractReadOnlyGUI(Contract* c) : contr(c) {
		contr->addObs(this);
	}
	void initContract() {
		lista_obj = new QListWidget();
		QHBoxLayout* main = new QHBoxLayout;
		main->addWidget(lista_obj);
		this->setLayout(main);
	}*/
	void update() override {
		this->repaint();
	}

	void connect() {
		QObject::connect(this, &QWidget::close, this, [&]() {
			locatar.removeObs(this);
			});
	}
	/*void reload() {
		lista_obj->clear();
		for (const auto& e : contr->srv.getAllLista()) {
			lista_obj->addItem(QString::fromStdString(e.print_to_string()));
		}
	}*/

	void paintEvent(QPaintEvent* e) override {
		QPainter p(this);
		p.drawImage(0, 0, QImage("poza.jpg"));
		srand(time(0));
		int x = -20;
		const auto& loc = locatar.get_Lista();
		int size = (int)loc.size();
		for (int i = 0; i < size;i++) {
			x += 40;
			int forma = rand() % 4;
			int inaltime = rand() % 130;
			int start_y = rand() % 60;
			QColor color;

			int color_num = rand() % 5;
			switch (color_num) {
			case 0:
				color = Qt::red;
				break;
			case 1:
				color = Qt::green;
				break;
			case 2:
				color = Qt::black;
				break;
			case 3:
				color = Qt::blue;
				break;
			case 4:
				color = Qt::lightGray;
				break;
			default:
				break;
			}

			switch (forma) {
			case 0:
				p.drawRect(x, start_y, 20, inaltime);
				break;
			case 1:
				p.drawEllipse(x, start_y, 20, inaltime);
				break;
			case 2:
				p.fillRect(x, start_y, 20, inaltime, color);
				break;
			default:
				p.fillRect(x, start_y, 20, inaltime, color);
				break;
			}
		}
	}

	/*~ContractReadOnlyGUI() {
		contr->removeObs(this);
	}*/
};

class AppGUI :public QWidget {
	friend class Contract;
private:
	LocatariService& service;
	ListaRepo& locatari;
	//QWidget* lista = new QWidget;
	//QTableWidget* table_main = new QTableWidget;
	MyTableModel* modelTable;
	QTableView* tableV = new QTableView;

	QListWidget* lista_list = new QListWidget;
	QListWidget* list = new QListWidget;

	//Buttons
	QPushButton* add = new QPushButton{ "&ADD" };
	QPushButton* del = new QPushButton{ "&DELETE" };
	QPushButton* find = new QPushButton{ "&FIND" };
	QPushButton* modify = new QPushButton{ "&MODIFY" };
	QPushButton* undo = new QPushButton{ "&UNDO" };
	//QPushButton* open_list = new QPushButton{ "&OPEN LIST" };
	QRadioButton* sort_name = new QRadioButton{ "&SORT NAME" };
	QRadioButton* sort_sup = new QRadioButton{ "&SORT SUP" };
	QRadioButton* sort_ts = new QRadioButton{ "&SORT T+S" };
	QPushButton* filter_type = new QPushButton{ "&FILTER TYPE" };
	QPushButton* filter_sup = new QPushButton{ "&FILTER SUP" };
	QLineEdit* txtfilter = new QLineEdit;
	QPushButton* exit = new QPushButton{ "&EXIT" };
	QPushButton* load = new QPushButton{ "&LOAD" };
	QPushButton* loadlist = new QPushButton{ "&LOADLIST" };
	QHBoxLayout* type = new QHBoxLayout;
	vector<pair<QPushButton*, string>> buttons_types;

	QPushButton* add_contract = new QPushButton{ "&ADD TO CONTRACT" };
	QPushButton* empty_contract = new QPushButton{ "&EMPTY CONTRACT" };
	QPushButton* generate_contract = new QPushButton{ "&GENERATE CONTRACT" };
	QPushButton* export_contract = new QPushButton{ "&EXPORT TO CONTRACT" };

	//List Buttons
	/*QPushButton* add_list = new QPushButton{ "&ADD TO LIST" };
	QPushButton* empty_list = new QPushButton{ "&EMPTY LIST" };
	QPushButton* generate_list = new QPushButton{ "&GENERATE LIST" };
	QPushButton* export_list = new QPushButton{ "&EXPORT LIST" };
	QPushButton* exit_list = new QPushButton{ "&EXIT LIST" };*/

	//contract
	QPushButton* open_contract = new QPushButton{ "&OPEN CONTRACT" };
	QPushButton* open_roc = new QPushButton{ "Open read only contract" };

	//Form Layout
	QLineEdit* txtApartament = new QLineEdit;
	QLineEdit* txtName = new QLineEdit;
	QLineEdit* txtSuprafata = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;

	QLineEdit* txtListNumber = new QLineEdit;
	QLineEdit* txtListFile = new QLineEdit;

	//Main list

	void loadList(const vector<Locatar>& locatari);
	void loadTable(const vector<Locatar>& locatari);
	void afisare(const vector<Locatar>& locatari);
	//void listaGUI();
	void connectSignalSlots();
	void init_gui();
	void ui_add();
	void ui_delete();
	void ui_find();
	void ui_modify();
	void ui_filter_t();
	void ui_filter_s();
	void ui_sort();
	//void ui_addList();
	void ui_generatetypebuttons();
	//void ui_cout_map(const map<string, vector<Locatar>> mapFiltered, const string& type);

	void curataFielduri();

public:
	AppGUI(LocatariService& srv, ListaRepo& locatari) : service{ srv }, locatari{locatari} {
		init_gui();
		//listaGUI();
		loadTable(srv.get_All());
		afisare(srv.get_All());
		//this->contract = new Contract(srv);
		//cont.init_contract();
		//cont.connectSignalContract();
		connectSignalSlots();
	}
};