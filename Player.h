#ifndef ullItem
#define ullItem
	#include "ull.h"
	#include "Item.h"
	#include "ConsumeItem.h"
	#include "UseItem.h"
	#include "EquipItem.h"
#endif
#include <string>

#include "MapV2.h"


class Player{
  public:
  	uLList<Item*> items;

    	Player(){
		lastLocation = NULL;
		currentLocation = NULL;
	}

	void setCurrent(areaNode* loc){
      		lastLocation = currentLocation;
		currentLocation = loc;
	}

	bool playerMoved(){
		return !(lastLocation == currentLocation);
	}
	areaNode* getCurrent(){
		return currentLocation;
	}

	void inventory(){
		nodeType<Item*>* temp;
      		temp = items.getFirst();
		//cout<<temp<<endl;
		if(temp == NULL){
			cout<<"No items are in your inventory."<<endl;
		}
		else{
			cout<<"You have the following items:"<<endl;
			while(temp != NULL){
				cout<<"\t"<<temp->info->getName()<<endl;
				temp = temp->link;
			}
		}
	}

	void take(string it = ""){
        string n;
        string p;
        if (it.size()) {
            n = it;
        }
        else {
            cout << "Take what item?" << endl;
            getline(cin, n);
        }
        std::transform(n.begin(), n.end(), n.begin(), ::tolower);
            //cout<<"Looking for item: "<<n<<endl;
        nodeType<Item*>* temp = NULL;
        temp = currentLocation->info.items.getFirst();
            //cout<<temp<<endl;
        bool found = false;
        while(temp != nullptr && !found){
            p = temp->info->getName();
            it = p;
            std::transform(p.begin(), p.end(), p.begin(), ::tolower);
            if(n == p){
                found = true;
                items.insertLast(temp->info);
                //delete from room list
                currentLocation->info.items.deleteNode(temp->info);
            }
            else{
                temp = temp->link;
            }
        }
        if(found){
            cout<<"You have taken: "<<it<<endl;
        }
        else{
            cout<<"No item by that name here."<<endl;
        }
    }

	void leave(string it = ""){
            string n;
            string p;
            if (it.size()) {
                n = it;
            }
            else {
                cout << "Leave what item?" << endl;
                getline(cin, n);
            }
            std::transform(n.begin(), n.end(), n.begin(), ::tolower);
            //cout<<"Looking for item: "<<n<<endl;
                nodeType<Item*>* temp = NULL;
            temp = items.getFirst();
            //cout<<temp<<endl;
            if(temp == nullptr){
                cout << "You have no items in your inventory." << endl;
                return;
            }
            else{
                bool found = false;
                while(temp != nullptr && !found){
                    p = temp->info->getName();
                    it = p;
                    std::transform(p.begin(), p.end(), p.begin(), ::tolower);
                    if(n == p){
                        found = true;
                        //add to room list
                        currentLocation->info.items.insertLast(temp->info);
                        //delete from player list
                        items.deleteNode(temp->info);
                    }
                    else{
                        temp = temp->link;
                    }
                }
			if(found){
				cout<<"You have dropped: "<<it<<endl;
			}
			else{
				cout<<"No item by that name in your inventory."<<endl;
			}
		}
	}

	void examine(string it = ""){
            string n;
            string p;
            if (it.size()) {
                n = it;
            }
            else {
                cout << "Examine what item?" << endl;
                getline(cin, n);
            }
            std::transform(n.begin(), n.end(), n.begin(), ::tolower);
            //cout<<"Looking for item: "<<n<<endl;
                nodeType<Item*>* temp = NULL;
            temp = items.getFirst();
            //cout<<temp<<endl;
            if(temp == nullptr){
                cout << "You have no items in your inventory to examine." << endl;
                return;
            }
            else{
                bool found = false;
                while(temp != nullptr && !found){
                    p = temp->info->getName();
                    std::transform(p.begin(), p.end(), p.begin(), ::tolower);
                    if(n == p){
                        found = true;
                        cout<<temp->info->getDesc()<<endl;
                    }
                    else{
                        temp = temp->link;
                    }
                }
			if(!found){
				cout<<"No item by that name in your inventory."<<endl;
			}
		}
	}

	virtual int isGameOver() = 0;
	virtual void resetPlayerStats() = 0;
	virtual void reportStats() = 0;
	virtual void consume(Map* mapptr, string it = "") = 0;
	virtual void use(Map* mapptr, string it = "") = 0;

    virtual void equip(Map* mapptr, string it ="") = 0;
	virtual void  resetPlayerLevel(Map* mapptr) = 0;

	virtual void reportLevel() = 0;


  protected:
		areaNode* currentLocation;
		areaNode* lastLocation;

};
