#include <string>
#include <iostream>
using namespace std;
#ifndef ullItem
#define ullItem
    #include "ull.h"
    #include "Item.h"
    #include "ConsumeItem.h"
    #include "UseItem.h"
    #include "EquipItem.h"
#endif // ULL_H


class Area{
  public:
    void setDescription (string desc){
    	description = desc;
    }
    void setGoal(bool g){
	goal = g;
    }
    void setID(bool id){
	instadeath = id;
    }
    string getDescription(){
    	return description;
    }
    bool getID(){
    	return instadeath;
    }
    bool getGoal(){
	return goal;
    }
    void displayArea(){
	cout<<description<<endl;
    }

    uLList<Item*> items;

    void search() {
        if(items.isEmptyList()) {
            cout << "No items are in this area." << endl;
        }
        else {
            nodeType<Item*>* traverse = items.getFirst();
            cout << "The following items are in this area:" << endl;
            for (int i = 0; i < items.length(); i++) {
                cout << "\t" << traverse->info->getName() << endl;
                traverse = traverse->link;
            }
        }
    }
  private:
     string description;
     bool instadeath;
     bool goal;
};
