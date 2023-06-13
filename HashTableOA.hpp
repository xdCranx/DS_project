#ifndef HASHTABLE_OA_HPP
#define HASHTABLE_OA_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class HashTableOA
{
private:
    int noe;
    int size;          //- .capacity()
    float load_factor; // noe/size
    typedef pair<int, string> student;
    vector<student *> table;

public:
    void getSize()
    {
        cout << table.capacity() << endl;
    };

    HashTableOA()
    {
        size = 50;
        noe = 0;
        load_factor = 0;

        vector<student *> table1(size, nullptr);
        this->table = table1;
    };

    ~HashTableOA()
    {
        // delete[] table;
        // cout << "\nSpace freed";
    }

    int hashFunc(int sindex)
    {
        return sindex % size;
    };

    void re_hash()
    {
        size += int((noe / 0.6) + 1);
        vector<student *> temp(size);

        for (auto i : table)
        {
            if (i != nullptr)
                temp[hashFunc(i->first)] = i;
        }

        table = temp;
        cout << "\nRehashed\n";
    };

    void add(int sindex, string name)
    {
        student *temp = new student;
        temp->first = sindex;
        temp->second = name;

        int index = hashFunc(temp->first);
        insert(temp, index);
    }

    void insert(student *stu, int index)
    {

        if (table[index] == nullptr)
        {
            table[index] = stu;
            noe++;
            load_factor = noe / size;

            if (load_factor > 0.75)
                re_hash();
        }
        else
        {
            if (table[index]->first == stu->first)
                table[index] = stu;
            else
            {
                index++;
                if (index >= size)
                    table.resize(size++);

                insert(stu, index);
            }
        }
    };

    void show()
    {
        for (int i = 0; i < size; i++)
            if (table[i] != nullptr)
                cout << i << " | "
                     << "Index: " << table[i]->first << " Student: " << table[i]->second << endl;
    };

    void search()
    {
        int sindex;
        cout << "Search for? : [index]" << endl;
        cin >> sindex;

        int index = hashFunc(sindex);
        for (; table[index]->first != sindex; index++)
            ;
        cout << "Index: " << table[index]->first << " Name: " << table[index]->second << endl;
    }
};

#endif