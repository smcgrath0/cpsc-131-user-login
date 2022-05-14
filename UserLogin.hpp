#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

class UserLogin {
private:
    
    unordered_map< string, string > table;
    

public:
    UserLogin(); // default constructor

    void readIn(const string& filename); // add data from file to hash table

    size_t numberOfUsers(); // return the number of users

    string passWordCheck(const string& userName); // returns the passWord of the given user

    size_t wordBucketIdMethod1(const string& userName); // return the bucket number where the given user is located

    size_t wordBucketIdMethod2(const string& userName); // another way to find the bucket number where the given user is located

    bool validateUser(const string& userName); // look up given user

    bool authenticateUser(const string& userName, const string& passWord);// authenticate given user and password
       
};

UserLogin::UserLogin() {
}

// COMPLETE THE FOLLOWING FUNCTIONS

void UserLogin::readIn(const string& filename) {
    
    // TO DO

    ifstream myReadFile;
    myReadFile.open(filename);
    char output[100];
    string userName = "^";
    string passWord;

    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {

            myReadFile >> userName;
            myReadFile >> passWord;
            
            if (!validateUser(userName)) {
                table.insert(std::pair<string,string>(userName,passWord));
            } else if (authenticateUser(userName, passWord)) {
                cout << userName << " is authenticated.\n";
            } else {
                cout << userName << " already Exists.\n";
            }
        }
    }

    myReadFile.close();
}

size_t UserLogin::numberOfUsers() {

    // TO DO
    return table.size();
}

string UserLogin::passWordCheck(const string& userName) {

    // TO DO
    if (table.count(userName) == 0) return "Non-existent User";
    return table.at(userName);
}

size_t UserLogin::wordBucketIdMethod1(const string& userName) {

    // TO DO
    if (table.count(userName) == 0) return -1;
    return table.bucket(userName);
}

size_t UserLogin::wordBucketIdMethod2(const string& userName) {
    
    // TO DO
    size_t n = table.bucket_count();
    for (size_t i=0; i<n; ++i) {
        for (auto it = table.begin(i); it!=table.end(i); ++it)
            if (it->first == userName) return i;
    }
    return -1;
}

bool UserLogin::validateUser(const string& userName) {
    
    // TO DO
    if (table.count(userName) == 0) return false;
    return true;
}

bool UserLogin::authenticateUser(const string& userName, const string& passWord) { 
    
    // TO DO
    if (table.count(userName) == 0) return false;
    if (table.at(userName) != passWord) return false;
    return true;
 }