#pragma once

class Tests {
private:
	//teste pentru domain
	void LocatarTests();

	//teste pentru repo
	void RepoTests();

	//teste pentru validator
	void ValidatorTests();

	//teste pentru service
	void ServiceTests();

	//test pentru undo
	void testUndo();

	//test pentru service cu FileRepo
	void ServiceFileTests();
public:
	void runAllTests();
};