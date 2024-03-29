#ifndef PLAYER_H
#define PLAYER_H
    #include "Player.h"
#endif

class LVLPlayer : public Player
{
private:
    int level; //players level
    vector<Levels*> levelPtr; // vector to store levels pointers in
    vector<Area> originals; // vector to store original areas in
    vector<Item*> originItems; // vector to store item pointers in
public:
    LVLPlayer() : Player ()
    {
        cout<<"Creating LVL Player...READY!"<<endl;
        level = 1;
    }
    int getLevel()
    {
        return level;
    }
    void setLevel(int temp)
    {
        level = temp;
    }
    int isGameOver()
    {
        if (!(currentLocation->info.getID() || currentLocation->info.getGoal()))
            return 0;
        else if (currentLocation->info.getGoal())
            return 1;
        else
            return 2;
    }
    void resetPlayerLevel(Map* mapptr)
    {

        level = 1; //make the players level 1 again

        vector<Levels*> check = mapptr->getLevels(); // get all level sets

        for(int i = 0; i < originals.size(); i++)
        {
            int oldRoom = check[i]->OldRoom; //get the number of the changed area

            areaNode* oldR = mapptr->getAt(oldRoom - 1); // get the area node of the changed area
            oldR->info = originals[i]; // set that area node to the original area

        }
        for(int i = 0; i < originItems.size(); i++)
        {
            vector<Buffs*> temp = originItems[i]->getItemBuffEffects(); // get the vector of item pointers we equipped
            temp[i]->status = 1; // change their status to un used
        }

    }
    void reportLevel()
    {
        cout<<"Players current level: "<<level<<endl;
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

    ///------
    //Name: Equip
    //Description: equip an item and execute buffs
    //---------------
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
            if(temp->info->getType() != "Equip") {                    //equip item if it is equipable
                cout << "There's no way to equip this item." << endl;
            }
            else
            {
                vector<Buffs*> buffPtr = temp->info->getItemBuffEffects(); //get the items buff vector
                if(buffPtr[0]->status == 0) //make sure it has not been use
                {
                    cout<<"Cannot equip item. Item has already been equipped. "<<endl;
                }
                else
                {
                   executeBuffs(temp->info, mapptr); // execute buffs
                }

            }

        }

        //------------
        //Name:execute Buffs
        // Description: make needed changes for equipping an item
        //-------------------------

    void executeBuffs(Item* it,Map* mapptr)
    {
        int temp = 0;
        vector<Buffs*> buffPtr = it->getItemBuffEffects(); //get items buff effects

            cout << it->getActiveMessage() << endl; //display active message
            temp = temp + buffPtr[0]->Buffamt; // create updated level
            buffPtr[0]->status = 0; // set status to equipped
            level =  level + temp; // update level
            originItems.push_back(it); // push item into vector of equipped items

        vector<Levels*> check = mapptr->getLevels(); // get linksets

        for(int i = 0; i < check.size(); i++)
        {
            if(level >= check[i]->Level)
            {
                int oldRoom = check[i]->OldRoom; // get old room number
                int newRoom = check[i]->NewRoom; // get new room number

                areaNode* oldR = mapptr->getAt(oldRoom - 1); // get old room area node

                originals.push_back(oldR->info); // push the older room into our changed area vectors

                areaNode*  newR = mapptr->getAt(newRoom - 1); // get new room area node

                oldR->info.setDescription(newR->info.getDescription()); // change old rooms description
                oldR->info.setGoal(newR->info.getGoal()); // change old rooms goal
                oldR->info.setID(newR->info.getID()); // change old rooms ID

            }
        }

    }

    void resetPlayerStats() {
            // Basic player does not have stats
        }
    void reportStats() {
            // Basic player does not have stats
            cout << "No player statistics to report." << endl;
        }

};
