#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
#include <ostream>
#include <algorithm>
#include <boost/algorithm/string/trim.hpp>
class Inventory;
using namespace boost;
using namespace std;

//Turn on or off all debugging couts
#define DEBUG(X)

//Upper cases a string
void uppercaseify(string &str) {
    for (char &ch : str) ch = toupper(ch);
}

void die() {
    cout << "Invalid Input!\n";
    exit(EXIT_FAILURE);
}

//use after uppercaseify
bool is_valid(const string &str) {
    for (char ch : str) {
        if (!isalnum(static_cast<unsigned char>(ch))) die();

    }
    return true;
}

  struct point {
  string a, b;
     friend ostream& operator<<(ostream &outs, const point &p) {
          return outs << "(" << p.a << ", " << p.b << ")";
     }
 };

// struct print {
//     friend ostream& operator<<(ostream &outs, const Inventory &inv) {
//         outs << inv.name << ": ";
//         for (auto i = inv.cars.begin(); i != inv.cars.end(); ++i) {
//             outs << *i << " ";
//         }
//         return outs;
//     }
// };



class Inventory {
    vector<string> cars = {};
    string name;

public:
    Inventory(const string& new_name) {//
        name = new_name;
    }

    friend ostream& operator<<(ostream &outs, const Inventory &inv) {
        outs << inv.name << ": ";
        for (auto i = inv.cars.begin(); i != inv.cars.end(); ++i) {
            outs << *i << " ";
        }
        return outs;
    }

    bool is_in(const string& search) {
        for (const string &car : cars) {
            if (car == search) return true;
        }
        return false; //Stub
    }

    void insert(const string& new_car) {
        if (!is_in(new_car)) {
            cars.push_back(new_car);
        }
    }

    Inventory intersect(const Inventory& other) {
        Inventory result(name + " INTERSECT " + other.name);
        for (const string &car : cars) {
            if (find(other.cars.begin(), other.cars.end(), car) != other.cars.end()) {
                result.insert(car);
            }
        }
        return result;
    }

    Inventory unionize(const Inventory &other) {
        Inventory result(name + " UNION " + other.name);
        for (const string &car : cars) result.insert(car);
        for (const string &car : other.cars) result.insert(car);
        return result; //Stub
    }
    int size() {
        return cars.size();
    }

    string get_name() {
        return name;
    }
    friend istream& operator>>(istream &ins, Inventory &other);
    friend ostream& operator<<(ostream &outs, Inventory &other);
}; //End of inventory

class SuperSet {
    unordered_map<string, Inventory> set;
public:
    SuperSet() : set() {}
    void insert(Inventory &new_inv) {
        string name = new_inv.get_name();
        if (set.find(name) == set.end()) {
            set.insert(make_pair(name, new_inv));
        }
    }
    //It will return the inventory matching name
    //If ignore_fail is set, then it won't die on a lack of a match
    Inventory* search(string name, bool ignore_fail = false) {
        auto find = set.find(name);
        if (find != set.end()) {
            return &find->second;  }
        if (!ignore_fail) {
            die();
        }

        return nullptr;
    }
    //Prints all inventories in all tables
    void print_all() {
        for (auto i = set.begin(); i != set.end(); ++i) {
            cout << "SET: " << i->first << ", VIN: " << i->second << "\n";
        }
    }

    void poset() {
        for (auto &i : set) {
            for (auto &j : set) {
                if (i.first == j.first) {continue;}
                Inventory *a = &i.second;
                Inventory *b = &j.second;
                if (a->size() < b->size()) {
                    Inventory result = a->intersect(*b);
                    if (result.size() == a->size()) {
                        cout << i.second << " " << j.second << endl;
                    }
                }
            }

        }
    }
} inventories;

//This should read from an instream, parse the input and add the vins to other
//You don't need to write this if you don't want.
istream& operator>>(istream &ins, Inventory &other) {
    string car;
    if (!car.empty()) {
        other.insert(car);
    }
    return ins;
}

int main() {
    while (!cin.eof()) {
        cout << "CREATE TABLE <NAME>\n"
        "INSERT INTO <NAME> VALUES <VIN>, <VIN>, <VIN>,...\n"
        "SELECT FROM <NAME1> UNION <NAME2>\n"
        "SELECT * FROM *\n"
        "SELECT * FROM <NAME1> INNER JOIN <NAME2>\n"
        "IS <NAME1> SUBSET <NAME2>\n"
        "POSET\n" << endl;
        string line;
        getline(cin, line);
        uppercaseify(line);
        stringstream ss(line);
        string first, second, third, fourth, fifth;
        ss >> first;
        trim(first); //split and trim are two functions badly needed in std
        if (first.empty()) break;
        if (!cin) break;
        if (first == "CREATE") {
            string keyword, name;
            ss >> keyword;
            if (keyword != "TABLE" ) die();
            ss >> name;
            if (name.empty()) die();
            is_valid(name);
            if (inventories.search(name, true) != nullptr) die();
            Inventory new_inv(name);
            inventories.insert(new_inv);
        } //END CREATE
        else if (first == "INSERT") {
            string keyword1 , name, keyword2;
            ss >> keyword1;
            if (keyword1 != "INTO") die();
            ss >> name;
            if (name.empty()) die();
            if (inventories.search(name, true) != nullptr) die();
            ss >> keyword2;
            if (keyword2 != "VALUES") die();
            Inventory *target = inventories.search(name);
            getline(ss, line);
            stringstream cars(line);
            string car;
            while (getline(cars, car, ',')) {
                trim(car);
                if (car.empty()) die();
                is_valid(car);
                if (inventories.search(car, true) == nullptr)  die();
                target -> insert(car);
            }
        } //END INSERT
        else if (first == "SELECT") {
            ss >> second;
            if (second == "FROM") {
                string name1, keyword, name2;
                ss >> name1 >> keyword >> name2;
                if (name1.empty() || keyword != "UNION" || name2.empty()) die();
                Inventory *a = inventories.search(name1);
                Inventory *b = inventories.search(name2);
                cout << a->unionize(*b) << "\n";
            }
            else if (second == "*") {
                string keyword;
                ss >> keyword;
                if (keyword != "FROM")die();
                string star_name;
                ss >> star_name;
                if (star_name == "*") {
                    inventories.poset(); }
                else {
                    string name1, keyword1, keyword2, name2;
                    ss >> keyword1 >> keyword2 >> name2;
                    if (keyword1 != "INNER" || keyword2 != "JOIN" || name2.empty())die();
                    Inventory *a = inventories.search(star_name);
                    Inventory *b = inventories.search(name2);
                   // cout << a->intersect(*b) << "\n";
                }
            }
            else die();
        } //END SELECT
        else if (first == "IS") {
            string name1, keyword, name2;
            ss >> name1 >> keyword >> name2;
            if (name1.empty() || keyword != "SUBSET" || name2.empty())  die();
            Inventory *a = inventories.search(name1);
            Inventory *b = inventories.search(name2);
            Inventory result = a->intersect(*b);
            if (result.size() == a->size()) {
                cout << "true" << endl; }
            else {
                cout << "false" << endl;
            }
        } //END ID
        else if (first == "POSET") {
            inventories.poset();
        } //END POSET
        else {
            DEBUG(cout << "COMMAND NOT RECOGNIZED: " << first << endl);
            die();
        }
    }
}