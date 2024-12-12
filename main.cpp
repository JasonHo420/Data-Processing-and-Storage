#include <iostream>
#include <unordered_map>

class InMemoryDB {
private:
    std::unordered_map<std::string, int> DB;
    std::unordered_map<std::string, int> tempDB;
    bool start = false;
public:
    void get(std::string key);
    void commit();
    void rollback();
    void put(std::string key, int val);
    void begin_transaction();
};

void InMemoryDB::get(std::string key) {
    if (DB.find(key) == DB.end()) {
        std::cout << "null" << std::endl;
    }
    else {
        std::cout << DB[key] << std::endl;
    }
}

void InMemoryDB::put(std::string key, int val) {
    if (start) {
        tempDB[key] = val;
    } else {
        std::cout << "Error: No Open Transaction" << std::endl;
    }
}


void InMemoryDB::commit() {
    if (start) {
        for (auto it : tempDB) {
            DB[it.first] = it.second;
        }
        tempDB.clear();
        start = false;
    }
    else {
        std::cout << "Error: No Open Transaction" << std::endl;
    }
}

void InMemoryDB::rollback() {
    if (start) {
        tempDB.clear();
        start = false;
    }
    else {
        std::cout << "Error: No Open Transaction" << std::endl;
    }
}

void InMemoryDB::begin_transaction() {
    start = true;
}



int main() {
    InMemoryDB Database;

    Database.get("A");

    Database.put("A", 5);

    Database.begin_transaction();

    Database.put("A", 5);

    Database.get("A");

    Database.put("A", 6);

    Database.commit();

    Database.get("A");

    Database.commit();

    Database.rollback();

    Database.get("B");

    Database.begin_transaction();

    Database.put("B", 10);

    Database.rollback();

    Database.get("B");

    return 0;
}