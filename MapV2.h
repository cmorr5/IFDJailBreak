#include <iostream>
#include <vector>
#include <string>
#include "Map.h"
#include <algorithm>

class MapV2: public Map {
    private:
        vector<Item*> itemsVec;
        int pType;
    public:
        MapV2(){
            //parseIFD();
            parser.readTokens();
            pType = parser.getPlayerType();
            for (int i = 0; i < parser.areas.size(); i++) {
                areasVec.push_back(parser.areas.at(i));
            }
            for (int i = 0; i < parser.items.size(); i++) {
                itemsVec.push_back(parser.items.at(i));
            }
            for (int i = 0; i < parser.links.size(); i++) {
                linkVec.push_back(parser.links.at(i));
            }
            for (int i = 0; i < parser.levels.size(); i++) {
                levelsVec.push_back(parser.levels.at(i));
            }
			linkLinks();
            insertItems();
            //lowercaseItems(itemsVec);
		}//constructor


		void insertItems() {
            for(Item* i: itemsVec) {
                areasVec[i->getSR() - 1]->info.items.insertFirst(i);
            }
		}

		void resetItems() {
            for(areaNode* i: areasVec) {
                i->info.items.destroyList();
            }
            insertItems();
		}

		int getPT() {
            return pType;
		}

        friend ostream& operator<<(ostream& out, MapV2*& outMap);
};

ostream& operator<<(ostream& out, MapV2*& outMap) {
    out<<"******************************************************************"<<endl;
    out<<"CHEATING!!!! Printing the set of areas and connections on the map."<<endl;
    out<<"******************************************************************"<<endl;
    for(int i=0; i<outMap->areasVec.size(); i++) {
        out << "This is area: " << i+1 << endl;
        out<<outMap->areasVec[i]->info.getDescription()<<endl;
        if(outMap->areasVec[i]->info.getID() == 1){
            out<<"Area is INSTADEATH."<<endl;
        }
        if(outMap->areasVec[i]->info.getGoal() == 1){
            out<<"Area is GOAL."<<endl;
        }
        out<<"Connections:"<<endl;
        out<<"\t u: Area #"<<outMap->reverseLookUp(outMap->areasVec[i]->u)<<endl;
        out<<"\t d: Area #"<<outMap->reverseLookUp(outMap->areasVec[i]->d)<<endl;
        out<<"\t l: Area #"<<outMap->reverseLookUp(outMap->areasVec[i]->l)<<endl;
        out<<"\t r: Area #"<<outMap->reverseLookUp(outMap->areasVec[i]->r)<<endl;
    }

    out<<"******************************************************************"<<endl;
    out<<"CHEATING!!!! ITEM LOCATIONS FOR ALL NON-INVENTORY ITEMS."<<endl;
    out<<"******************************************************************"<<endl;

    for (int i = 0; i < outMap->areasVec.size(); i++) {
        cout << "Items for area " << i << ": " << outMap->areasVec[i]->info.getDescription() << endl;
        nodeType<Item*>* traverse = outMap->areasVec[i]->info.items.getFirst();
        if (traverse == nullptr) {
            cout << "No items in list." << endl;
        }
        else {
            while (traverse != nullptr) {
                cout << "\t" << traverse->info->getName() << endl;
                traverse = traverse->link;
            }
        }
    }
    return out;
}
