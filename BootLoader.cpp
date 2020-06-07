#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#define LINESZ 1024
#include "BootLoader.h"
#include "InitDataStruct.h"
#include <fstream>
#include <algorithm>

void BootLoader::loadInit(Data* iData)
{	
	std::cout << "loadInit" << std::endl;
	FILE *load;
	char buff[LINESZ];
	char window[100];
	int width=0;
	int height=0;
	bool fullscreen = false;
	load = fopen("init.txt", "r");
	bool s = false;
	
	if (load) {
		while (fgets(buff, LINESZ, load)) {
		if(buff[0] != '#'){
			break;
		}}
		///*
		char tite[100] = "";
		for (int i = 0, z=0,j;i < sizeof(buff);i++) {
			if (buff[i] == '=') {
				s = true;
				j = i;
			}
			if (s && i>=(j+2)) {
				tite[z] = buff[i];
				z++;
			}
			
			if (buff[i] == '\n' && s && i>(j+2)) {
				break;
			}
		}
		//*/
		char map;
		std::cout << "loading load" << std::endl;
		fscanf(load, "Width = %i", &width);
		fscanf(load, " Height = %i", &height);
		fscanf(load, " Fullscreen = %[^\n]", &window);
		//fscanf(load, " Last_map = %[^\n]", &map);
		//std::cout << map;
		fclose(load);
		//std::cout << map << std::endl;
		
		if ( window == "true") {
			fullscreen = true;
		}
		iData->height = height;
		iData->width = width;
		iData->title = tite;
		iData->fullscreen = fullscreen;
		//iData->lastMap = map;
	}
}

void BootLoader::loadInitFile(Data* initData) {
	std::ifstream load;
	load.open("init.txt");
	int width = 800, height = 640;
	std::string title = "Tanks", map;
	bool fullscreen = false;
	if (load.is_open()) {
		while (!load.eof()) {
			std::string temp;
			std::getline(load, temp);
			if (temp[0] != '#') {
				if (temp[0] == 'W' || temp[0] == 'w') {
					std::string temp2 = getStringAfterB("=", temp);
					std::cout << temp2;
					width = std::stoi(temp2);
					initData->width = std::stoi(temp2);
				}
				if (temp[0] == 'H' || temp[0] == 'h') {
					std::string temp2 = getStringAfterB("=", temp);
					height = std::stoi(temp2);
					initData->height = std::stoi(temp2);
				}
				if (temp[0] == 'F' || temp[0] == 'f') {
					std::string temp2 = getStringAfterB("=", temp);
					temp2.erase(remove_if(temp2.begin(), temp2.end(), isspace), temp2.end());
					if (temp2 == "true" || temp2 == "True") {
						fullscreen = true;
						initData->fullscreen = true;
					}
				}
				if (temp[0] == 'L' || temp[0] == 'l') {
					std::string temp2 = getStringAfterB("=", temp);
					temp2.erase(remove_if(temp2.begin(), temp2.end(), isspace), temp2.end());
					map = "Maps/"+temp2+".txt";
					std::cout << map.c_str() << std::endl;
					initData->lastMap = map;
				}
			}
		}
		load.close();
	//	std::cout << width << " " << height << " " << fullscreen << " " << map << std::endl;
	}else {
		std::cout << "Failed to load init.txt /BootLoader";
	}
}

void BootLoader::loadGameObjects()
{
}

std::string BootLoader::getStringBetweenAB(std::string a, std::string b, std::string source) {
	std::string str;
	size_t pos1, pos2, pos3;
	pos1 = source.find(a);
	pos2 = source.find(b);
	pos3 = pos2 - pos1;
	str = source.substr(pos1 + 1, pos3 - 1);
	return str;
}
std::string BootLoader::getStringAfterB(std::string b, std::string source) {
	std::string str;
	size_t pos;
	pos = source.find(b)+1;
	str = source.substr(pos, source.size());
	return str;
}
/*
std::string BootLoader::getStringBeforeB(std::string b, std::string source) {
	std::string str;
	size_t pos;
	pos = source.find(b);
	str = source.substr(0, pos);
	return str;
}*/