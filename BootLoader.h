#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "InitDataStruct.h"
#include <stdio.h>

class BootLoader
{
public:
	BootLoader() {}
	~BootLoader();
	void loadInit(Data* initData);
	void loadInitFile(Data * initData);
	void loadGameObjects();
	std::string getStringBetweenAB(std::string a, std::string b, std::string source);
	std::string getStringAfterB(std::string b, std::string source);
	std::string getStringBeforeB(std::string b, std::string source);
private:

};
