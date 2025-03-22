#include <string>
#include "Loader.h"
#include <Windows.h>
#include "Algoritmus.h"
#include "Predicates.h"


int main() {
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);

	Loader loader;
	std::string filename1 = "2020.csv";
	std::string filename2 = "2021.csv";
	std::string filename3 = "2022.csv";
	std::string filename4 = "2023.csv";
	std::string filename5 = "2024.csv";

	std::vector<std::string> filenames = { filename1, filename2, filename3, filename4, filename5 };

	loader.loadCsv(filenames);

	std::vector<Village> Villages = loader.getVillages();
	Algoritmus algo;


	// CUI
	std::cout << "Vitajte v CLI, vyberte si z mo�nost�:" << '\n';
	while (true) {
		std::cout << "\n1. [PREDIK�T 1 - N�ZOV DANEJ OBCE OBSAHUJE ZADAN� RE�AZEC] | [re�azec]" << '\n';
		std::cout << "2. [PREDIK�T 2 - CELKOV� PO�ET OBYVATE�OV V ZADANOM ROKU BOL <= ZADAN�MU PO�TU] | [rok] + [po�et obyvate�ov]" << '\n';
		std::cout << "3. [PREDIK�T 3 - CELKOV� PO�ET OBYVATE�OV V ZADANOM ROKU BOL >= ZADAN�MU PO�TU] | [rok] + [po�et obyvate�ov]" << '\n';
		std::cout << "4. [VYP͊ V�ETKY OBCE]" << '\n';
		std::cout << "5. [VYP͊ OBCE V ZADANOM ROKU] | [rok]" << '\n';
		std::cout << "6. [KONIEC]" << '\n';
		std::cout << "Va�a mo�nos�:" << '\n';
		int choice;
		std::cin >> choice;

		switch (choice) {
		case 1: {
			std::cout << "Zadajte h�adan� re�azec:" << '\n';
			std::string str;
			std::cin >> str;
			std::cout << "Chcete filtrova� aj pod�a roka? [ano / nie]" << '\n';
			std::string volba;
			std::cin >> volba;
			if (volba == "ano") {
				std::cout << "Zadajte rok:" << '\n';
				int year;
				std::cin >> year;
				std::cout << "Zoznam obc�, ktor� obsahuj� re�azec [" << str << "] a s� z roku [" << year << "]:" << '\n';

				std::vector<Village> filteredVillage = algo.FilterWithContainsStr(Villages, str, year);
				algo.PrintItems(filteredVillage.begin(), filteredVillage.end());
				size_t size = filteredVillage.size();
				std::cout << "Obce boli vyp�san�. Po�et: [" << size << "] " << '\n';
				break;
			}
			if (volba == "nie") {
				std::cout << "Zoznam obc�, ktor� obsahuj� re�azec [" << str << "]:" << '\n';

				std::vector<Village> filteredVillage = algo.FilterWithContainsStr(Villages, str);
				algo.PrintItems(filteredVillage.begin(), filteredVillage.end());
				size_t size = filteredVillage.size();

				std::cout << "Obce boli vyp�san�. Po�et: [" << size << "] " << '\n';
				break;
			}
			std::cout << "Nespr�vna vo�ba." << '\n';
			break;
		}

		case 2: {
			std::cout << "Zadajte rok:" << '\n';
			int year;
			std::cin >> year;
			std::cout << "Zadajte maxim�lny po�et obyvate�ov:" << '\n';
			int maxResidents;
			std::cin >> maxResidents;
			std::cout << "Zoznam obc�, ktor� v roku [" << year << "] maj� <= [" << maxResidents << "] obyvate�ov:" << '\n';

			std::vector<Village> filteredVillage = algo.FilterWithHasMaxResidents(Villages, year, maxResidents);
			algo.PrintItems(filteredVillage.begin(), filteredVillage.end());
			size_t size = filteredVillage.size();

			std::cout << "Obce boli vyp�san�. Po�et: [" << size << "] " << '\n';
			break;

		}
		case 3: {
			std::cout << "Zadajte rok:" << '\n';
			int year;
			std::cin >> year;
			std::cout << "Zadajte minim�lny po�et obyvate�ov:" << '\n';
			int minResidents;
			std::cin >> minResidents;
			std::cout << "Zoznam obc�, ktor� v roku [" << year << "] maj� >= [" << minResidents << "] obyvate�ov:" << '\n';

			std::vector<Village> filteredVillage = algo.FilterWithHasMinResidents(Villages, year, minResidents);
			algo.PrintItems(filteredVillage.begin(), filteredVillage.end());
			size_t size = filteredVillage.size();

			std::cout << "Obce boli vyp�san�. Po�et: [" << size << "] " << '\n';
			break;
		}
		case 4: {
			std::cout << "V�etky obce:" << '\n';
			loader.printVillages();

			size_t size = loader.getSize();
			std::cout << "Obce boli vyp�san�. Po�et: [" << size << "] " << '\n';
			break;
		}
		case 5: {
			std::cout << "Zadajte rok:" << '\n';
			int year;
			std::cin >> year;
			std::cout << "Obce v roku [" << year << "]:" << '\n';
			loader.printVillages(year);

			size_t size = loader.getSize(year);
			std::cout << "Obce boli vyp�san�. Po�et: [" << size << "] " << '\n';
			break;
		}
		case 6: {
			std::cout << "Ukon�ujem program." << '\n';
			return 0;
		}
		default:
			std::cout << "Ukon�ujem program,\n";
		}
		
	}
}
