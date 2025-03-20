#pragma once
#include <string>
#include <iostream>

class City
{
private:
	int year_;
	std::string name_;
	std::string code_;
	int male_;
	int female_;
	int population_;

public:
	City(int year,std::string name, std::string code, int male, int female, int population);
	int getYear() const;
	std::string getName() const;
	std::string getCode() const;
	int getMale() const;
	int getFemale() const;
	int getPopulation() const;
	void print() const;
};