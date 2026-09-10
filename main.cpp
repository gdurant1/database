#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
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
        if (!isalnum(static_cast<unsigned char>(ch))) {
            die();
        }
    }
    return true;
}

class Inventory {
    vector< string> cars = {};
    string name = "";
public:
    Inventory(string new_name) {
        name = new_name;
    }
    bool is_in(string search) {
        //YOU
        return false; //Stub
    }

    void insert(string new_car) {
        //YOU
    }
    Inventory intersect(const Inventory &other) {
        //YOU
        return Inventory("Delete This Line and replace with actual code"); //Stub
    }
    Inventory unionize(const Inventory &other) {
        //YOU
        return Inventory("This also isn't functioning code, so don't leave it in"); //Stub
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
    }
    //It will return the inventory matching name
    //If ignore_fail is set, then it won't die on a lack of a match
    Inventory* search(string name, bool ignore_fail = false) {
        auto it = set.find(name);
        if (it != set.end()) {
            return &it->second;
        }
        return nullptr;
    }
    //Prints all inventories in all tables
    void print_all() {
        //YOU
    }
    void poset() { //Do the partial ordering of the sets here
    }
} inventories;

//This should read from an instream, parse the input and add the vins to other
//You don't need to write this if you don't want.
istream& operator>>(istream &ins, Inventory &other) {
    //YOU
    return ins;
}

//This should output an invntory to outs
ostream& operator<<(ostream &outs, Inventory &other) {
    //YOU
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
            if (keyword != "TABLE" ) break;
            ss >> name;
            if (name.empty()) break;
            is_valid(name);
            if (inventories.search(name, true) == nullptr) break;
            Inventory new_inv(name);
            inventories.insert(new_inv);
        } //END CREATE
        else if (first == "INSERT") {
            string keyword1 , name, keyword2;
            ss >> keyword1;
            if (keyword1 != "INTO") break;
            ss >> name;
            if (name.empty()) break;
            if (inventories.search(name, true) == nullptr) break;
            ss >> keyword2;
            if (keyword2 != "VALUES") break;
            Inventory *target = inventories.search(name);
            getline(ss, line);
            stringstream cars(line);
            string token;
            while (getline(cars, token, ',')) {
                trim(token);
                if (inventories.search(token, true) == nullptr)  break;
                target -> insert(token);
                inventories.insert(token);
            }
        } //END INSERT
        else if (first == "SELECT") {
            //YOU
        } //END SELECT
        else if (first == "IS") {
            //YOU
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