#ifndef HASHTABLE_OA_HPP
#define HASHTABLE_OA_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class HashTableOA 
{
private:
    //noe - .size()
    //size - .capacity()
    float load_factor; // noe/size
    typedef pair<int, string> student;
    vector<student>* table = new vector<student>;

public:

    void getSize()
    {
        cout << table.capacity() << endl;
    };

    HashTableOA()
    {
        load_factor = 0;
    };

    ~HashTableOA(){
        delete[] table;
        cout << "\nSpace freed";
    }

    int hashFunc(int index) 
    {
        return index%size;
    };

    void add(int index, string name)
    {
        student temp;
        // cout << "Index: ";
        // cin >> temp -> first;
        // cout << "\nName: ";
        // cin >> temp -> second;
        // cout <<"\n";

        temp -> first = index;
        temp -> second = name;

        insert(temp);
    }

    void insert(student stu)
    {
        int index = hashFunc(stu->first);

        if(table[index] == )
        {
            table[index] = stu;
            noe++;
        }
        else 
        {
            int i = index+1;
            int temp_size = size;
            for(; i < temp_size; i++)
            {
                if(table[i] == nullptr)
                    table[i] = stu;
                else if(i==size-1) {
                    size++;
                    table[i+1] = stu;
                }
            }
            
        }

        load_factor = noe / size;
        if(load_factor > 0.75)
            size+= int((noe/0.6)+1);
    };

    void show()
    {
        for(int i = 0; i < size; i++)
            cout << "Index: " << table[i]->first << " Student: " << table[i]->second << endl;
    };

    void search() 
    {
        int sindex;
        cout << "Search for? : [index]" << endl;
        cin >> sindex;

        int index = hashFunc(sindex);
        for(;table[index]->first!=sindex;index++);
        cout << "Index: " << table[index]->first << " Name: " << table[index] -> second << endl;
    }
};

#endif