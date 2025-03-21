#pragma once
#include "domain.h"
#include "repo.h"

class Undo {
public:
	virtual void doUndo() = 0;
	//destructor virtual
	virtual ~Undo() = default;
};

//clasa pentru undo adauga care mosteneste metodele lui Undo
class UndoAdauga :public Undo {
	Locatar locatar_adaugat;
	AbstractRepo* repo;
public:
	UndoAdauga(const Locatar& locatar, AbstractRepo* repo) : repo{ repo }, locatar_adaugat(locatar) {};
	void doUndo() override {
		repo->deletee(locatar_adaugat);
	}
};

class UndoSterge : public Undo {
	Locatar locatar_citit;
	AbstractRepo* repo;
public:
	UndoSterge(AbstractRepo* repo, const Locatar& locatar) : repo{ repo }, locatar_citit{ locatar } {};
	void doUndo() override {
		repo->store(locatar_citit);
	}
};

class UndoModifica : public Undo {
	Locatar locatar;
	AbstractRepo* repo;
public:
	UndoModifica(const Locatar& locatar, AbstractRepo* repo) : repo{ repo }, locatar(locatar) {};
	void doUndo() override {
		repo->modify(locatar);
	}
};