#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

struct Company
{
	string name;
	string profit_tax;
	string address;
};
struct HashTable {
	vector<Company> table[2000];
};
vector<Company> readCompanyList(string file_name) {
	vector<Company> comp;
	ifstream ifs(file_name);
	if (!ifs.is_open()) {
		cout << "Cannot open the input file." << endl;
	}
	char s[1000];
	ifs.getline(s, 256, '\n');

	while (!ifs.eof()) {
		Company current;
		ifs.getline(s, 256, '|');
		for (int i = 0; i < strlen(s); i++) {
			current.name = current.name + s[i];
		}
		ifs.getline(s, 256, '|');

		for (int i = 0; i < strlen(s); i++) {
			current.profit_tax = current.profit_tax + s[i];
		}
		ifs.getline(s, 256, '\n');
		for (int i = 0; i < strlen(s); i++) {
			current.address = current.address + s[i];
		}
		comp.push_back(current);
	}
	return comp;
}
long long hashString(string company_name) {
	long long sum = 0;
	long long ppow = 1;
	string hash = "";
	if (company_name.length() < 20) {
		hash = company_name;
	}
	else {
		for (int i = company_name.length(); i > company_name.length() - 20; i--) {
			hash = company_name[i-1] + hash;
		}
	}
	for (int i = 0; i < hash.length(); i++) {
		int k = hash[i];
		sum = sum + (k * ppow)%2000;
		ppow = (ppow * 31) %2000;
	}
	sum = sum % 2000;
	return sum;
}

HashTable* createHashTable(vector<Company> list_company) {
	HashTable* Hashtable = new HashTable;
	for (Company x : list_company) {
		long long index = hashString(x.name);
		Hashtable->table[index].push_back(x);
	}

	return Hashtable;
}

void insert(HashTable* hash_table, Company company) {
	long long index = hashString(company.name);
	hash_table->table[index].push_back(company);
}
Company* search(HashTable* hash_table, string company_name) {
	bool found = false;
	Company * comp = new Company;
	long long index = hashString(company_name);
	for (Company x : hash_table->table[index]) {
		if (x.name == company_name) {
			*comp = x;
			found = true;
		}
	}
	if (!found) {
		return nullptr;
	}
	return comp;
}
void perform(string path1, string path2, HashTable* hash_table) {
	ifstream ifs(path1);
	while (ifs.is_open() == false) {
		cout << "Cannot open the input file" << endl;
		return;
	}
	ofstream ofs(path2);
	while (ofs.is_open() == false) {
		cout << "Cannot open the output file" << endl;
		return;
	}
	string name;
	while (!ifs.eof()) {
		getline(ifs, name);
		Company* comp = search(hash_table,name);
		if (comp == nullptr) {
			ofs << "Not found" << endl;
			continue;
		}
		ofs << comp->name << "|";
		ofs << comp->profit_tax << "|";
		ofs << comp->address << endl;
	}
	return;
}
int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "Error!" << endl;
		return -1;
	}
	string path1 = argv[2];
	string path2 = argv[3];
	string file_name = argv[1];
	vector <Company > companyList = readCompanyList(file_name);
	HashTable* hash_table = createHashTable(companyList);
	perform(path1, path2, hash_table);
	delete[] hash_table;
}
