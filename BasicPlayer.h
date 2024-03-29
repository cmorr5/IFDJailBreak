#ifndef PLAYER_H
#define PLAYER_H
    #include "Player.h"
#endif // PLAYER_H

class BasicPlayer : public Player{
    public:
        BasicPlayer() : Player() {
            // Use base constructor
            cout << "Creating Basic Player ... READY!" << endl;
        }
        int isGameOver() {
            if (!(currentLocation->info.getID() || currentLocation->info.getGoal()))
                return 0;
            else if (currentLocation->info.getGoal())
                return 1;
            else
                return 2;
        }
        void resetPlayerStats() {
            // Basic player does not have stats
        }
        void reportStats() {
            // Basic player does not have stats
            cout << "No player statistics to report." << endl;
        }
        void consume(Map* mapptr, string it = "") {
            string n;
            string p;
            if (it.size()) {
                n = it;
            }
            else {
                cout << "Consume what item?" << endl;
                getline(cin, n);
            }
            std::transform(n.begin(), n.end(), n.begin(), ::tolower);
            //cout<<"Looking for item: "<<n<<endl;
                nodeType<Item*>* temp = NULL;
            temp = items.getFirst();
            //cout<<temp<<endl;
            if(temp == nullptr){
                cout << "You have no items in your inventory to consume." << endl;
                return;
            }
            else{
                bool found = false;
                while(temp != nullptr && !found){
                    p = temp->info->getName();
                    std::transform(p.begin(), p.end(), p.begin(), ::tolower);
                    if(n == p){
                        found = true;
                    }
                    else{
                        temp = temp->link;
                    }
                }
                if(!found){
                    cout << "No item by that name in your inventory." << endl;
                    return;
                }
            }
            if (temp->info->getType() != "Consume") {
                cout << "This proves impossible." << endl;
            }
            else if(temp->info->getType() == "basic") {
                cout << "There's no way to use this item." << endl;
            }
            else if(temp->info->getActiveArea() == mapptr->reverseLookUp(currentLocation) || temp->info->getActiveArea() == 0) {
               cout << temp->info->getActiveMessage() << endl;
            }
            else {
                cout << "Can't consume that item here." << endl;
            }

        }
        void use(Map* mapptr, string it = "") {
            string n;
            string p;
            if (it.size()) {
                n = it;
            }
            else {
                cout << "Use what item?" << endl;
                getline(cin, n);
            }
            std::transform(n.begin(), n.end(), n.begin(), ::tolower);
            //cout<<"Looking for item: "<<n<<endl;
                nodeType<Item*>* temp = NULL;
            temp = items.getFirst();
            //cout<<temp<<endl;
            if(temp == nullptr){
                cout << "You have no items in your inventory to use." << endl;
                return;
            }
            else{
                bool found = false;
                while(temp != nullptr && !found){
                    p = temp->info->getName();
                    std::transform(p.begin(), p.end(), p.begin(), ::tolower);
                    if(n == p){
                        found = true;
                    }
                    else{
                        temp = temp->link;
                    }
                }
                if(!found){
                    cout << "No item by that name in your inventory." << endl;
                    return;
                }
            }
            if(temp->info->getType() != "Use") {
                cout << "There's no way to use this item." << endl;
            }
            else if(temp->info->getActiveArea() == mapptr->reverseLookUp(currentLocation) || temp->info->getActiveArea() == 0) {
               cout << temp->info->getActiveMessage() << endl;
               executeRules(temp->info, mapptr);
            }
            else {
                cout << "Can't use that item here." << endl;
            }
        }



        void executeRules(Item* it, Map* mapptr) {
            for(Rule* i: it->getItemUseRules()) {
                areaNode* ptr = mapptr->getAt(i->beginRm-1);
                char c = i->direction;
                if (c == 'u') {
                    ptr->u = mapptr->getAt(i->destRm-1);
                }
                else if (c == 'l') {
                    ptr->l = mapptr->getAt(i->destRm-1);
                }
                else if (c == 'r') {
                    ptr->r = mapptr->getAt(i->destRm-1);
                }
                else if (c == 'd') {
                    ptr->d = mapptr->getAt(i->destRm-1);
                }
                else {
                    cout << "ERROR: Unrecognized direction" << endl;
                }
            }
        }

        void reportLevel()
        {
            cout<<"No level to report. "<<endl;
        }

        void resetPlayerLevel(Map* mapptr)
        {
            //no level to reset
        }

          void equip(Map* mapptr, string it = "") {
            string n;
            string p;
            if (it.size()) {
                n = it;
            }
            else {
                cout << "Equip what item?" << endl;
                getline(cin, n);
            }
            std::transform(n.begin(), n.end(), n.begin(), ::tolower);
            //cout<<"Looking for item: "<<n<<endl;
                nodeType<Item*>* temp = NULL;
            temp = items.getFirst();
            //cout<<temp<<endl;
            if(temp == nullptr){
                cout << "You have no items in your inventory to equip." << endl;
                return;
            }
            else{
                bool found = false;
                while(temp != nullptr && !found){
                    p = temp->info->getName();
                    std::transform(p.begin(), p.end(), p.begin(), ::tolower);
                    if(n == p){
                        found = true;
                    }
                    else{
                        temp = temp->link;
                    }
                }
                if(!found){
                    cout << "No item by that name in your inventory." << endl;
                    return;
                }
            }
            if(temp->info->getType() != "LVL") {
                cout << "There's no way to equip this item." << endl;
            }
            else
            {
               cout << temp->info->getActiveMessage() << endl;

            }

        }

};