// CPP program to implement hashing with chaining
#include <iostream>
#include "hash.hpp"
#include <sstream>

using namespace std;

node *HashTable::createNode(string restaurantName, node *next)
{
    node *newNode = new node();
    newNode->next = next;
    newNode->restaurantName = restaurantName;
    newNode->pq = *(new PriorityQ(50)); //prevents from being an anonymous object, doesn't get destroyed when the function ends
    return newNode;
}

HashTable::HashTable(int bsize)
{
    tableSize = bsize;
    numCollision = 0;
    table = new node *[tableSize];
    for (int i = 0; i < tableSize; i++)
    {
        table[i] = nullptr;
    }
}

HashTable::~HashTable()
{
    for (int i = 0; i < tableSize; i++) {
        node* current = table[i];
        while (current != nullptr) {
            node* next = current->next;
            delete current;
            current = next;
        }
        table[i] = nullptr;
    }
    delete[] table; //max 144 bytes leaked, 9 pointers are being lost (8 bytes), 9 restaurants, and the two ints are 4 bytes each
}

void HashTable::displayTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        cout << i << "|";
        node *current = table[i];
        while (current != nullptr)
        { 
            cout << current->restaurantName << "-->";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
}

unsigned int HashTable::hashFunction(string restaurantName)
{
    int asciiSum = 0;
    int stringLength = restaurantName.length();
    for (int i = 0; i < stringLength; i++)
    {
        asciiSum += restaurantName[i];
    }
    return asciiSum % tableSize;
}

node *HashTable::searchItem(string restaurantName)
{
    int bucket = hashFunction(restaurantName);
    node *current = table[bucket];

    while (current != nullptr)
    {
        if (current->restaurantName == restaurantName)
        {
            return current;
        }
        else
        {
            current = current->next;
        }
    }
    return nullptr;
}

void HashTable::insertItem(ReviewInfo restaurant)
{
    node *checkRest = searchItem(restaurant.restaurantName);

    if (checkRest != nullptr)
    {
        checkRest->pq.insertElement(restaurant);
    }
    else
    {
        node *newRestaurant = createNode(restaurant.restaurantName, nullptr);
        newRestaurant->pq.insertElement(restaurant);

        int bucket = hashFunction(restaurant.restaurantName);
        if (table[bucket] == nullptr)
        {
            table[bucket] = newRestaurant;
        }
        else
        {
            numCollision++;
            newRestaurant->next = table[bucket];
            table[bucket] = newRestaurant;
        }
    }
}

void HashTable::setup(string fname)
{
    ifstream file(fname);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string restaurantName, review, customer, time;
            getline(ss, restaurantName, ';');
            getline(ss, review, ';');
            getline(ss, customer, ';');
            getline(ss, time, ';');

            ReviewInfo restaurant;
            restaurant.restaurantName = restaurantName;
            restaurant.review = review;
            restaurant.customer = customer;
            restaurant.time = stoi(time);

            insertItem(restaurant);
        }
        file.close();
    } else {
        cout << "Unable to open file";
    }
}