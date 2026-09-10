#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
#include <ostream>
#include <boost/algorithm/string/trim.hpp>
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

class Inventory {
    vector< string> cars = {};
    string name = "";
public:
    Inventory(string new_name) {//
        name = new_name;
    }
    bool is_in(string search) {
        for (const string &car : cars) {
            if (car == search) return true;
        }
        return false; //Stub
    }

    void insert(string new_car) {
        if (!is_in(new_car)) {
            cars.push_back(new_car);
        }
    }
    Inventory intersect(const Inventory &other) {
        Inventory result(name + " INTERSECT " + other.name);
        for (const string &car : cars) {
            if (cars == other.cars) {
                result.insert(car);
                break;
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
        for (const auto &pair : set) {
            cout << pair.first << ": " << pair.second << "\n" << endl;
             //total = total.unionize(*inv);
        }
    }
    void poset() { //Do the partial ordering of the sets here
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

//This should output an invntory to outs
ostream& operator<<(ostream &outs, Inventory &other) {
    for (size_t i = 0; i < other.cars.size(); i++) {
        outs << other.cars[i] << " ";
        if (i +1 < other.cars.size()) {outs << ", "; }
    }
    return outs;
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
            if (inventories.search(name, true) == nullptr) break;
            Inventory new_inv(name);
            inventories.insert(new_inv);
        } //END CREATE
        else if (first == "INSERT") {
            string keyword1 , name, keyword2;
            ss >> keyword1;
            if (keyword1 != "INTO") die();
            ss >> name;
            if (name.empty()) die();
            if (inventories.search(name, true) == nullptr) die();
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
                if (inventories.search(car, true) == nullptr)  break;
                target -> insert(car);
                inventories.insert(car);
            }
        } //END INSERT
        else if (first == "SELECT") {
            ss >> second;
            if (second == "FROM") {
                string name1, keyword, name2;
                ss >> name1 >> keyword >> name2;
                if (name1.empty() || keyword == "UNION" || name2.empty()) die();
                inventories.search(name1);
                inventories.search(name2);
                Inventory *a = inventories.search(name1);
                Inventory *b = inventories.search(name2);
                cout << a->unionize(*b) << endl;
            }
            else if (second == "*") {
                string keyword;
                ss >> keyword;
                if (keyword != "FROM")die();
                string start_name;
                ss >> start_name;
                if (start_name == "*") {
                    inventories.poset(); }
                else {
                    string name1 = start_name, keyword1, keyword2, name2;
                    ss >> keyword1 >> keyword2 >> name2;
                    if (keyword1 != "INNER" || keyword2 != "JOIN" || name2.empty())die();
                    Inventory *a = inventories.search(start_name);
                    Inventory *b = inventories.search(name2);
                    cout << a->intersect(*b) << "\n" << endl;
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
            //YOU
        } //END POSET
        else {
            DEBUG(cout << "COMMAND NOT RECOGNIZED: " << first << endl);
            die();
        }
    }
}