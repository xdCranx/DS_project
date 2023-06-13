#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>
#include <list>
#include <cstring>
#include <cmath>
#include <chrono>

// using namespace std::chrono;
using namespace std;

class HashTable {
    private:
        static const int ht_size = 10;
        list<pair<int, string>> table[ht_size];
        

    public:
        bool is_empty();
        void print_isempty();
        int hash_func(int index);
        void add_element(int index, string student);
        void remove_element(int index);
        void show();
        void search(int index);
};

bool HashTable::is_empty() {
    for(int i = 0 ; i < ht_size ; i++)
    {
        if(table[i].size()!=0)
            return true;
        else
            continue;
    }
    return false;
}

void HashTable::print_isempty() {
    if(is_empty()) {
        cout<<"HashTable contains elements"<<endl;
        cout<<endl;
    }
    else {
        cout<<"HashTable is empty"<<endl;
        cout<<endl;
    }
}

// int HashTable::hash_func(int index) {
//     int sum = 0;
//     int num = index;
//     for(int i = 0; i < 6; i++) {
//         sum += num % 10;
//         num /= 10;
//     }
//     while(sum>ht_size-1) {
//         sum /= 2;
//         ceil(sum);
//     }
//     return sum;
// }


int HashTable::hash_func(int index) {
    return index%ht_size;
}


void HashTable::add_element(int index, string student) {
    int Hash = hash_func(index);
    auto& indeks = table[Hash];
    auto iterator = begin(indeks);
    bool index_exists = false;
    for(; iterator != end(indeks); iterator++) {
        if(iterator->first == index) {
            index_exists = true;
            iterator->second = student;
            break;
        }
    }

    if(!index_exists) {
        indeks.emplace_back(index, student);
    }
    return;
}

void HashTable::remove_element(int index) {
    int Hash = hash_func(index);
    auto& indeks = table[Hash];
    auto iterator = begin(indeks);
    for(; iterator != end(indeks); iterator++) {
        if(iterator->first == index) {
            iterator = indeks.erase(iterator);
            break;
        }
        else continue;
    }
    return;
}

void HashTable::show() {
    for(int i=0; i<ht_size; i++) {
        if(table[i].size() == 0) continue;

        auto iterator = table[i].begin();
        for(; iterator != table[i].end(); iterator++) {
            cout<<"Numer Albumu: "<< iterator->first << endl;
            cout <<"Generated Hash:" << hash_func(iterator -> first) << endl;
            cout<<"student: "<< iterator->second << endl;
            cout << endl;
        }
    }
}

void HashTable::search(int index) {
    auto start = chrono::high_resolution_clock::now();
    int Hash = hash_func(index);
    auto& indeks = table[Hash];
    auto iterator = begin(indeks);
    for(; iterator != end(indeks); iterator++) {
        if(iterator->first == index) {
            cout<<"Podany numer albumu "<<iterator->first<<" jest przypisany do: "<<iterator->second<<endl;
            break;
        } 
        else {
            continue;
        }
    }
    if(iterator->first != index)
        cout << "Not found" << endl;

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "[Czas wykonania funkcji: "<< duration.count() << " mikrosekund]" << endl;
    return;
}

#endif