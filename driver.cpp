#include <iostream>
#include "hash.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void displayMenu() // do not modify
{
    cout << "------------------" << endl;
    cout << "1: Build the data structure (execute this option one time)" << endl;
    cout << "2: Add a review" << endl;
    cout << "3: Retrieve most recent review for a restaurant" << endl;
    cout << "4: Pop most recent review for a restaurant" << endl;
    cout << "5: Print reviews for a restaurant" << endl;
    cout << "6: Display number of collisions" << endl;
    cout << "7: Display table results" << endl;
    cout << "8: Exit" << endl;
    cout << "------------------" << endl;
}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct number of arguments"<<endl;
    }
	
    string fname = argv[1];
    int tableSize = stoi(argv[2]);
    int ch = 0;
    string chs;
    HashTable ht(5);

    bool hashTableMade = false;
	
    while(ch!=8)
    {
        displayMenu();
        cout << "Enter your choice >>";
        getline(cin, chs);
        ch = stoi(chs);
        switch (ch)
        {
            case 1:
			{
				if(hashTableMade == false){
                    ht.setup(fname);
                    hashTableMade = true;
                } else{
                    cout << "The data structure has already been built." << endl;
                }
				break;
            }
            case 2:
			{
                string restaurantName; 
                cout << "Restaurant Name: ";
                getline(cin, restaurantName);

                string customer;
                cout << "Customer: ";
                getline(cin, customer);

                string review;
                cout << "Review: ";
                getline(cin, review);

                string time;
                cout << "Time: ";
                getline(cin, time);

                ReviewInfo r;
                r.restaurantName = restaurantName;
                r.customer = customer;
                r.review = review;
                r.time = stoi(time);

                ht.insertItem(r);
				break;
            }
            case 3:
			{
                string restaurantName;
                cout << "Restaurant name: ";
                getline(cin, restaurantName);

                node *found = ht.searchItem(restaurantName);
                if(found == nullptr){
                    cout << "no record found" << endl;
                } else{
                    cout << "retrieved result" << endl;
                    found->pq.peek();
                }
               
				break;
            }
            case 4:
			{
                string restaurantName;
                cout << "Restaurant name: ";
                getline(cin, restaurantName);

                node *found = ht.searchItem(restaurantName);
                if(found == nullptr){
                    cout << "no record found" << endl;
                } else{
                    found->pq.pop();
                }
				break;
            }
            case 5:
			{
				string restaurantName;
                cout << "Restaurant name: ";
                getline(cin, restaurantName);

                node *found = ht.searchItem(restaurantName);
                if(found == nullptr){
                    cout << "no record found" << endl;
                } else{
                    found->pq.print();
                }
				break;
			}
            case 6:
                cout << "Number of collisions: " << ht.getNumCollision() << endl;
                break;
            case 7:
                ht.displayTable();
                break;
            case 8:
                cout << "Goodbye!" << endl;
                return 0;
				break;
            default:
                cout << "Enter a valid option." << endl;
                break;
        }
    }
}
