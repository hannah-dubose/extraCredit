#include <iostream>
#include <unordered_map>
#include <stdexcept>

using namespace std;

class Database {
public:
    unordered_map<string, int> overallData;
    unordered_map<string, int> transactionData;
    bool transactionState = false;

    void begin_transaction() {
        //if the database is already in a transaction throw an error
        if (transactionState) {
            throw runtime_error("There is already a transaction happening at this time");
        }
        transactionData.clear();
        transactionState = true;
    }

    void put(string key, int value) {
        //if there is no transaction occurring
        if (!transactionState) {
            throw std::runtime_error("No transaction in progress");
        }
        //put the key/value into the transaction map
        transactionData[key] = value;
    }

    int get(string key) {
        //checking both maps allows up to check if it is in a transaction or not

        //if the key does exist
        if (transactionData.find(key) != transactionData.end()) {
            return transactionData[key];
        }
        //if the key exists in the overall data structure
        if (overallData.find(key) != overallData.end()) {
            return overallData[key];
        }
        //key is not found
        return 0;
    }

    void commit() {
        //throw an error if there is no active transaction
        if (!transactionState) {
            throw runtime_error("No transaction happening");
        }
        //commit the transaction data to the overall data map
        for (const auto& data : transactionData) {
            overallData[data.first] = data.second;
        }
        //clear transaction data
        transactionData.clear();
        //stop the transaction
        transactionState = false;
    }

    void rollback() {
        //throw an error if there is no active transaction
        if (!transactionState) {
            throw runtime_error("No transaction happening");
        }
        //ignore all changes made and stop transaction
        transactionData.clear();
        transactionState = false;
    }
};


