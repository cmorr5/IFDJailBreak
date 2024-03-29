
#ifndef PLAYER_H
#define PLAYER_H
    #include "Player.h"
#endif
#ifndef TYPES_H
#define TYPES_H
    #include "BasicPlayer.h"
    #include "HPSPPlayer.h"
    #include "LVLPlayer.h"
#endif // Player Types TYPES_H
#include <string>

/*#ifndef ullItem
#define ullItem
	#include "ull.h"
	#include "Item.h"
#endif*/

class Game{
	private:
		Player* player1;
		MapV2* map = new MapV2;

  	public:
		Game(){
		    if (map->getPT() == 0) {
                player1 = new BasicPlayer;
		    }
		    else if (map->getPT() == 1) {
                player1 = new HPSPPlayer;
		    }
		    else if(map->getPT() == 2)
            {
                player1 = new LVLPlayer;
            }
		    else {
                cout << "Not sure what type of player that is. Please include a proper player type in IFD file." << endl;
                abort();
		    }
			player1->setCurrent(map->getStart());
		}

  		void play(){
      			string userInput;
      			// These vectors allow all of the words in them to be used for their corresponding function.
                vector<string> take = {"take", "grab", "get", "steal", "grasp", "carry", "hand", "clutch", "bear", "haul", "add"};
      			vector<string> leave = {"leave", "drop", "remove", "throw", "lay", "unhand", "abandon", "desert", "disown"};
      			vector<string> use = {"use", "utilize", "operate", "work", "apply", "implement", "exercise"};
      			vector<string> consume = {"consume", "eat", "drink", "devour", "bite", "ingest", "swallow", "guzzle"};
      			vector<string> examine = {"examine", "look", "view", "peer", "glance", "gaze", "peek", "inspect", "study", "survey"};
			//cin.ignore();
      			while(true){
				//check game status
				if(player1->isGameOver() != 0){
				    if (player1->isGameOver() == 1 || player1->isGameOver() == 2) {
                        player1->getCurrent()->info.displayArea();
                        return;
				    }
				    else if (player1->isGameOver() == 3) {
                        cout << "You DIED OF HP!!!!!!" << endl;
                        return;
				    }
				    else {
                        cout << "You DIED OF SP!!!!!" << endl;
				    }
				}
      				//display area data
				if(player1->playerMoved()){
	    				player1->getCurrent()->info.displayArea();
				}
				else{
					if(userInput != "reset"){
						cout<<"There appears to be no way to go that direction."<<endl;
					}
				}

	  			//get movement selection
	  			cout<<"Which way would you like to go?  Enter u, d, l, or r"<<endl;
				getline(cin, userInput);
				string input2;
				size_t pos = userInput.find(" ");
				if (pos != string::npos)
                input2 = userInput.substr(pos+1, string::npos);
				userInput = userInput.substr(0, pos);

	  			//update area
	  			if(userInput == "u"){
       				player1->setCurrent(player1->getCurrent()->u);
		 		}
				else if(userInput == "d"){
					player1->setCurrent(player1->getCurrent()->d);
				}
				else if(userInput == "l"){
					player1->setCurrent(player1->getCurrent()->l);
				}
				else if(userInput == "r"){
	  				player1->setCurrent(player1->getCurrent()->r);
				}
				else if(userInput == "iseedeadpeople"){ //issdeadpeople cheat code to reveal map
					//map->print();
					cout<<map;
				}
				else if(userInput == "reset"){
					resetGame();
				}
				else if(userInput == "exit"){
					cout<<"Good bye!"<<endl;
					return;
				}
				else if(userInput == "search"){
					player1->getCurrent()->info.search();
				}
				else if(userInput == "inventory"){
					player1->inventory();
				}
				// If user input is in specified vector
				else if(count(take.begin(), take.end(), userInput)){
                    if (input2.size()) {
                        player1->take(input2);
                    }
                    else {
                        player1->take();
                    }
				}
				else if(count(leave.begin(), leave.end(), userInput)){
                    if (input2.size()) {
                        player1->leave(input2);
                    }
                    else {
                        player1->leave();
                    }
				}
				else if(count(examine.begin(), examine.end(), userInput)){
                    if (input2.size()) {
                        player1->examine(input2);
                    }
                    else {
                        player1->examine();
                    }
				}
				else if(userInput == "levels" || userInput == "level" || userInput == "skill")
                {
                    player1->reportLevel();
                }
				else if(userInput == "stats") {
                    player1->reportStats();
				}
				else if(count(use.begin(), use.end(), userInput)) {
                    if (input2.size()) {
                        player1->use(map, input2);
                    }
                    else {
                        player1->use(map);
                    }
				}
				else if(count(consume.begin(), consume.end(), userInput)) {
                    if (input2.size()) {
                        player1->consume(map, input2);
                    }
                    else {
                        player1->consume(map);
                    }
				}
				else if(userInput == "equip" || userInput == "levelup" || userInput == "uselevel" || userInput == "activate")
                {
                    if(input2.size())
                    {
                        player1->equip(map,input2);

                    }
                    else
                    {
                        player1->equip(map);
                    }
                }
				else if(userInput == "help"){
					cout<<"You may type: "<<endl;
					cout<<"\t u, d, l, or r: to move up, down, left or right on the map,"<<endl;
					cout<<"\t search: to search for items in current area,"<<endl;
					cout<<"\t take: to attempt to take an item,"<<endl;
					cout<<"\t leave: to attempt to leave an item,"<<endl;
					cout<<"\t examine: to examine an item in your inventory,"<<endl;
					cout<<"\t stats: see player stats,"<<endl;
					cout<<"\t use: to attempt to use an item,"<<endl;
					cout<<"\t consume: to attempt to consume an item,"<<endl;
					cout <<"\t equip: to equip and item and level up,"<<endl;
					cout<<"\t reset: to reset the game,"<<endl;
					cout<<"\t exit: to exit the game."<<endl;
					cout<<endl;
				}
				else{
					cout<<"I do not understand: "<<userInput<<endl<<endl;
				}


			}//end while
    		}//end play()

		void resetGame(){
			player1->setCurrent(map->getStart());
			//remove item from player list
			player1->items.destroyList();
			//reset player stats to original state
			player1->resetPlayerStats();
			//remove item from each area in turn
			map->resetItems();
			//reset map links to original state
			map->linkLinks();

			player1->resetPlayerLevel(map);
		}
		~Game() {
            delete map;
		}


};
