#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstdlib>
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

class Inventory {
    vector<string> cars = {};
    string name = "";
public:
    Inventory(string new_name) {
        //YOU
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
    vector<Inventory> set;
public:
    SuperSet() : set() {}
    void insert(Inventory &new_inv) {
    }
    //It will return the inventory matching name
    //If ignore_fail is set, then it won't die on a lack of a match
    Inventory* search(string name, bool ignore_fail = false) {
        return nullptr; //STUB
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
        string line;
        getline(cin, line);
        stringstream ss(line);
        string first, second, third, fourth, fifth;
        ss >> first;
        trim(first); //split and trim are two functions badly needed in std
        if (first.size() < 1) break;
        if (!cin) break;
        if (first == "CREATE") {
            //YOU
        } //END CREATE
        else if (first == "INSERT") {
            //YOU
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