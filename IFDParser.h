#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

#ifndef ullItem
#define ullItem
    #include "ull.h"
    #include "Item.h"
    #include "ConsumeItem.h"
    #include "UseItem.h"
    #include "EquipItem.h"
#endif // ULL_H

#ifndef AREALINK_H
#define AREALINK_H
    #include "LinkData.h"
    #include "Area.h"
#endif

#ifndef AREANODE_H
#define AREANODE_H
    #include "areaNode.h"
#endif // AREANODE_H



using namespace std;

class IFDParser{
	public:
	IFDParser(){
		pos = 0;
		type = 2;
	   	cout << "Please enter the game's file name: ";
	   	getline(cin, gameFile);
	   	ifderr = false;
	}
        // readTokens reads the tokens from the ifd file and creates the map elements
        void readTokens() {
            tokenIt();
            nextToken = getNextToken();
            if(nextToken == "<game>"){
				eatToken();
				nextToken = getNextToken();
				while(nextToken != "</game>"){  //consider what happens when run out of tokens && not error state
					if(nextToken == "<area>"){
						eatToken();
						nextToken = getNextToken();
						makeArea();
					}
					else if(nextToken == "<links>"){
						eatToken();
						nextToken = getNextToken();
						makeLinks();
					}
					else if(nextToken == "<item>") {
                        eatToken();
                        nextToken = getNextToken();
                        makeItem();
					}
					else if(nextToken == "<ptype>") {
                        eatToken();
                        nextToken = getNextToken();
                        playerType();
					}
					else if(nextToken == "<levels>")
                    {
                        eatToken();
                        nextToken = getNextToken();
                        makeLevels();
                    }
					else{
						cout<<"Parse Error Location 1"<<endl;
						ifderr = true;
						break;
					}
					eatToken();
					nextToken = getNextToken();
				}// while !</game>

				if(ifderr){
					cout<<" :: ERROR :: IF Document Formatting Error"<<endl;
					cout<<"Game Loading Failed"<<endl;
					cout<<"General Area of Parsing Failure:"<<endl;
					cout<<"-------------------------------------"<<endl;
					cout<<nextToken<<endl;
					eatToken();
					nextToken = getNextToken();
					cout<<nextToken<<endl;
					eatToken();
					nextToken = getNextToken();
					cout<<nextToken<<endl;
					eatToken();
					nextToken = getNextToken();
					cout<<nextToken<<endl;
					cout<<"-------------------------------------"<<endl;
					return;
				}
				//cout<<"::Found </game>::"<<endl;
			}
			else{
				cout<<" :: ERROR :: No \"<game>\" tag found."<<endl;
				cout<<"Game Loading Failed"<<endl;
			}
		}

	void tokenIt(){
		string token="";
		string nextLine;
		char c;

	   	ifstream inFile;
	   	inFile.open(gameFile.c_str());

	   	// Check file was opened to ensure no user error.
        if (!inFile.is_open()) {
            cout << "ERROR : INVALID FILE NAME" << endl;
            abort();
        }

		while(!inFile.eof()){
			getline(inFile, nextLine);
			trim(nextLine);
		        c=nextLine[0];

			//dump any comment or blank line (all comments exist alone on their lines)
			if(c=='%' || nextLine == ""){
				//do nothing
			}
			else{
				//tokenize the entire line
				//cout<<nextLine<<endl;
				for(int i=0; i<nextLine.length(); i++){
					if(nextLine[i] == '>'){
						token = token + nextLine[i];
						if(token !="\n" && token !="" && token !=" " && token !="\t"){
							tokenVec.push_back(token);
						}
						token = "";
					}
					else if(nextLine[i]=='<'){
						if(token !="\n" && token !="" && token !=" " && token !="\t"){
							tokenVec.push_back(token);
						}
						token = "";
						token = token + nextLine[i];
					}
					else{
						token = token + nextLine[i];
					}
				}
			}
		}//while !eof
		inFile.close();
		return;
	}// end of tokenIt()

	void eatToken(){
		pos++;
	}

	string getNextToken(){
		return tokenVec[pos];
	}

	//helpre function for trimming a string's white space
	void trim(string& s)
    	{
       	size_t p = s.find_first_not_of(" \t");
       	s.erase(0, p);
    		p = s.find_last_not_of(" \t");
       	if (string::npos != p)
          		s.erase(p+1);
    	}

	void printTokens(){
		cout<<":::Printing the Tokens in Order:::"<<endl;
		for(int i=0; i<tokenVec.size(); i++){
			cout<<i<<": "<<tokenVec[i]<<endl;
		}


	}

        // ---------------------------------------------------------------
        // These functions come from MapV2 and Map. They are what allows IFD Parser to create the map instead of the Map classes.

		void makeArea(){
			int id;
			int goal;
			string xstr;

			areaNode* tempNodePtr = new areaNode;

			while(nextToken != "</area>"){
				if(nextToken == "<desc>"){
					eatToken();
					nextToken = getNextToken();

					tempNodePtr->info.setDescription(nextToken);
				}
				else if(nextToken == "<feats>"){
					eatToken();
					nextToken = getNextToken();

					istringstream ss(nextToken);
          				getline(ss, xstr, ',');
          				tempNodePtr->info.setID(atoi(xstr.c_str()));

          				getline(ss, xstr, ',');
					tempNodePtr->info.setGoal(atoi(xstr.c_str()));
				}
				else if(nextToken == "</desc>" || nextToken == "</feats>"){
				  //do nothing
				}
				else{
					cout<<"Parse Error Location 2"<<endl;
					ifderr = true;
					break;
				}

				eatToken();
				nextToken = getNextToken();
			}//while !</area>

			//add area to vector
			areas.push_back(tempNodePtr);

		}

		void makeLinks(){
			string xstr;
			int u, d, l, r;
			while(nextToken != "</links>"){
				if(nextToken == "<linkset>"){
					eatToken();
			  		nextToken = getNextToken();

					LinkData* tempLDPtr = new LinkData;

					istringstream ss(nextToken);
        				getline(ss, xstr, ',');
        				u = atoi(xstr.c_str());
        				getline(ss, xstr, ',');
        				d = atoi(xstr.c_str());
					getline(ss, xstr, ',');
        				l = atoi(xstr.c_str());
					getline(ss, xstr, ',');
					r = atoi(xstr.c_str());

					tempLDPtr->setDigits(u, d, l, r);
          				links.push_back(tempLDPtr);
				}
				else if(nextToken == "</linkset>"){
					//do nothing
				}
				else{
					cout<<"Parse Error Location 3"<<endl;
					ifderr = true;
					break;
				}
				eatToken();
			  	nextToken = getNextToken();
			}//while !</links>
		}//makeLinks()

		void makeLevels()
		{
		    string xstr;
		    int level;
		    int oldRoom;
		    int newRoom;
		    while(nextToken != "</levels>")
            {
                if(nextToken == "<levelset>")
                {
                    eatToken();
                    nextToken = getNextToken();
                    Levels* levelsPtr = new Levels;

                    istringstream ss(nextToken);
                    getline(ss, xstr, ',');
                    level = atoi(xstr.c_str());

                    getline(ss, xstr, ',');
                    oldRoom = atoi(xstr.c_str());

					getline(ss, xstr, ',');
                    newRoom = atoi(xstr.c_str());

                    levelsPtr->Level = level;
                    levelsPtr->OldRoom = oldRoom;
                    levelsPtr->NewRoom = newRoom;

                    levels.push_back(levelsPtr);

                }
                else if(nextToken == "</levelset>")
                {
                    //do nothing
                }
                else
                {
                    cout<<"Parse Error Location levelsets"<<endl;
					ifderr = true;
					break;
                }
                eatToken();
			  	nextToken = getNextToken();

            }

		}

		void makeConsumeItem(Item*& newItem) {
		    newItem->setType("Consume");
		    string xstr;
            eatToken();
            nextToken = getNextToken();
            while(nextToken != "</item>") {

                //cout << "CURRENT TOKEN  "  << nextToken << endl << endl;
                if(nextToken == "<name>") {
                    eatToken();
                    nextToken = getNextToken();

                    newItem->setName(nextToken);
                    //cout << "NAME HERE: " << newItem->getName() << endl;
                }
                else if (nextToken == "<desc>") {
                    eatToken();
                    nextToken = getNextToken();

                    newItem->setDesc(nextToken);
                    //cout << "DESC HERE: " << newItem->getDesc() << endl;
                }
                else if (nextToken == "<star>") {
                    eatToken();
                    nextToken = getNextToken();

                    newItem->setSR(stoi(nextToken));
                    //cout << "ITEM AREA: " << newItem->getSR() << endl;
                }
                else if (nextToken == "<actmess>") {
                    eatToken();
                    nextToken = getNextToken();
                    newItem->setActiveMessage(nextToken);
                }
                else if (nextToken == "<actar>") {
                    eatToken();
                    nextToken = getNextToken();
                    newItem->setActiveArea(stoi(nextToken));
                }
                else if (nextToken == "<effect>") {
                    eatToken();
                    nextToken = getNextToken();

                    Effect* effect = new Effect;
                    istringstream ss(nextToken);
                    getline(ss, xstr, ',');
                    effect->effectID = stoi(xstr);
                    getline(ss, xstr, ',');
                    effect->effectAmt = stoi(xstr);
                    newItem->addEffect(effect);
                }
                else if (nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>"
                        || nextToken == "</consume>" || nextToken == "</actmess>" || nextToken == "</actar>"
                        || nextToken == "</effect>") {
                    // do nothing
                    //cout << "I AM GOING TO DO ABSOLUTELY NOTHING !!!" << endl;
                }
                else {
                    cout << "Parse Error Location 4" << endl;
                    ifderr = true;
                    break;
                }
                eatToken();
                nextToken = getNextToken();
            } // while not to the end of the item tokens
		}
		void makeUseItem(Item*& newItem) {
		    newItem->setType("Use");
		    string xstr;
            eatToken();
            nextToken = getNextToken();
            while(nextToken != "</item>") {
                if(nextToken == "<name>") {
                    eatToken();
                    nextToken = getNextToken();

                    newItem->setName(nextToken);
                    //cout << "NAME HERE: " << newItem->getName() << endl;
                }
                else if (nextToken == "<desc>") {
                    eatToken();
                    nextToken = getNextToken();

                    newItem->setDesc(nextToken);
                    //cout << "DESC HERE: " << newItem->getDesc() << endl;
                }
                else if (nextToken == "<star>") {
                    eatToken();
                    nextToken = getNextToken();

                    newItem->setSR(stoi(nextToken));
                    //cout << "ITEM AREA: " << newItem->getSR() << endl;
                }
                else if (nextToken == "<actmess>") {
                    eatToken();
                    nextToken = getNextToken();
                    newItem->setActiveMessage(nextToken);
                }
                else if (nextToken == "<actar>") {
                    eatToken();
                    nextToken = getNextToken();
                    newItem->setActiveArea(stoi(nextToken));
                }
                else if (nextToken == "<rule>") {
                    eatToken();
                    nextToken = getNextToken();

                    Rule* rule = new Rule;
                    istringstream ss(nextToken);
                    getline(ss, xstr, ',');
                    rule->beginRm = atoi(xstr.c_str());
                    getline(ss, xstr, ',');
                    char* ptr = const_cast<char*>(xstr.c_str());
                    char letter = *ptr;
                    rule->direction = letter;
                    getline(ss, xstr, ',');
                    rule->destRm = atoi(xstr.c_str());
                    newItem->addRule(rule);
                }
                else if (nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>"
                        || nextToken == "</use>" || nextToken == "</actmess>" || nextToken == "</actar>"
                        || nextToken == "</rule>") {
                    // do nothing
                    //cout << "I AM GOING TO DO ABSOLUTELY NOTHING !!!" << endl;
                }
                else {
                    cout << "Parse Error Location 4" << endl;
                    ifderr = true;
                    break;
                }
                eatToken();
                nextToken = getNextToken();
            } // while not to the end of the item tokens
		}

		void makeEquipItem(Item*& newItem) {
		    newItem->setType("Equip");
		    string xstr;
            eatToken();
            nextToken = getNextToken();
            while(nextToken != "</item>") {
                if(nextToken == "<name>") {
                    eatToken();
                    nextToken = getNextToken();

                    newItem->setName(nextToken);
                    //cout << "NAME HERE: " << newItem->getName() << endl;
                }
                else if (nextToken == "<desc>") {
                    eatToken();
                    nextToken = getNextToken();

                    newItem->setDesc(nextToken);
                    //cout << "DESC HERE: " << newItem->getDesc() << endl;
                }
                else if (nextToken == "<star>") {
                    eatToken();
                    nextToken = getNextToken();

                    newItem->setSR(stoi(nextToken));
                    //cout << "ITEM AREA: " << newItem->getSR() << endl;
                }
                else if (nextToken == "<actmess>") {
                    eatToken();
                    nextToken = getNextToken();
                    newItem->setActiveMessage(nextToken);
                }
                else if (nextToken == "<actar>") {
                    eatToken();
                    nextToken = getNextToken();
                    newItem->setActiveArea(stoi(nextToken));
                }
                else if (nextToken == "<buff>") {

                    eatToken();
					nextToken = getNextToken();
                    Buffs* temp = new Buffs;

					istringstream ss(nextToken);
                    getline(ss, xstr, ',');
                    temp->Buffamt = atoi(xstr.c_str());

                    getline(ss, xstr, ',');
					temp->status = atoi(xstr.c_str());
					newItem->addBuffs(temp);

                }
                else if (nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>"
                        || nextToken == "</use>" || nextToken == "</actmess>" || nextToken == "</actar>"
                        || nextToken == "</buff>" || nextToken == "</rule>" || nextToken == "</equip>") {
                    // do nothing
                    //cout << "I AM GOING TO DO ABSOLUTELY NOTHING !!!" << endl;
                }
                else {
                    cout << "Parse Error Location 4: equip item" << endl;
                    ifderr = true;
                    break;
                }
                eatToken();
                nextToken = getNextToken();
            } // while not to the end of the item tokens
		}

		void makeItem() {
            Item* newItem;

            // Determine item type
            if (nextToken == "<consume>") {
                newItem = new ConsumeItem;
                makeConsumeItem(newItem);
            }
            else if (nextToken == "<use>") {
                newItem = new UseItem;
                makeUseItem(newItem);
            }
            else if(nextToken == "<equip>")
            {
                newItem = new EquipItem;
                makeEquipItem(newItem);
            }
            else {
                newItem = new Item;
                newItem->setType("Basic");
                eatToken();
                nextToken = getNextToken();
                while(nextToken != "</item>") {

                    //cout << "CURRENT TOKEN  "  << nextToken << endl << endl;
                    if(nextToken == "<name>") {
                        eatToken();
                        nextToken = getNextToken();

                        newItem->setName(nextToken);
                        //cout << "NAME HERE: " << newItem->getName() << endl;
                    }
                    else if (nextToken == "<desc>") {
                        eatToken();
                        nextToken = getNextToken();

                        newItem->setDesc(nextToken);
                        //cout << "DESC HERE: " << newItem->getDesc() << endl;
                    }
                    else if (nextToken == "<star>") {
                        eatToken();
                        nextToken = getNextToken();

                        newItem->setSR(stoi(nextToken));
                        //cout << "ITEM AREA: " << newItem->getSR() << endl;
                    }
                    else if (nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>"
                             || nextToken == "</basic>") {
                        // do nothing
                        //cout << "I AM GOING TO DO ABSOLUTELY NOTHING !!!" << endl;
                    }
                    else {
                        cout << "Parse Error Location 4" << endl;
                        ifderr = true;
                        break;
                    }
                    eatToken();
                    nextToken = getNextToken();
                } // while not to the end of the item tokens
            }
            items.push_back(newItem);
		}

		void playerType() {
            if(nextToken == "basic") {
                type = 0;
            }
            else if(nextToken == "hpsp") {
                type = 1;
            }
            else if(nextToken == "lvl")
            {
                type = 2;
            }
            else {
                cout << "ERROR: Player type not recognized." << endl;
                ifderr = true;
                type = 3;
            }
            eatToken();
            nextToken = getNextToken();
		}

		int getPlayerType() {
            return type;
		}

        vector<areaNode*> areas;
        vector<LinkData*> links;
        vector<Item*> items;
        vector<Levels*> levels;
	private:
		int pos;
		string gameFile;
        vector<string> tokenVec;
        string nextToken;
        int type;
        bool ifderr;
};

