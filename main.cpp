#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QListWidget>
#include <vector>
#include <string>
#include "GUI.h"
#include "validator.h"
#include "tests.h"

using namespace std;

int main(int argc, char *argv[])
{
    Tests TM;
    TM.runAllTests();
    QApplication a(argc, argv);
    FileRepo* repo = new FileRepo{ "locatari.txt" };
    //ProbabilityRepo* repo =new ProbabilityRepo(1);
    LocatarValidator val;
    ListaRepo lista;
    LocatariService srv{ repo, val, lista };
    AppGUI gui(srv, lista);
    gui.show();
    return QApplication::exec();
}
