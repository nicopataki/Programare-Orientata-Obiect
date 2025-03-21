#pragma once
#include "domain.h"
#include "vector"
#include "string"

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
	vector<string> msgs;
public:
	ValidateException(const vector<string>& errors) :msgs{ errors } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class LocatarValidator {
public:
	/*
	* Functie de validare a unui locatar
	* @param locatar - un locatar
	* @raises ValidateException daca locatar are campuri invalide
	*/
	void validate(const Locatar& locatar);
};