#include <vector>
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>


#include "IFDParser.h"
#ifndef AREALINK_H
#define AREALINK_H
    #include "LinkData.h"
    #include "Area.h"
#endif


/*struct areaNode
{
	Area info;
	areaNode *u;
	areaNode *d;
	areaNode *l;
	areaNode *r;
}; */

class Map{
	protected:
		vector<areaNode*> areasVec;
		int areacnt;

		//Here is the instance of IFDParser
	  	IFDParser parser;

		//Some additional class attributes here
        vector<LinkData*> linkVec;
		string nextToken;

		bool ifderr;
		vector<Levels*> levelsVec; // vector of level pointers
	public:
		vector<Levels*>getLevels()
		{
		    return levelsVec; // return the levels pointer vector
		}



		void linkLinks(){
			for(int i=0; i<linkVec.size(); i++){
					areasVec[i]->u = areasVec[(linkVec[i]->getDigit(0))-1];
					areasVec[i]->d = areasVec[(linkVec[i]->getDigit(1))-1];
					areasVec[i]->l = areasVec[(linkVec[i]->getDigit(2))-1];
					areasVec[i]->r = areasVec[(linkVec[i]->getDigit(3))-1];
			}
		}


		areaNode* getStart(){
			return areasVec[0];  //returns a pointer to the first area listed
		}
		areaNode* getAt(int i) {
            return areasVec[i];
		}

		void print(){
			cout<<"******************************************************************"<<endl;
			cout<<"CHEATING!!!! Printing the set of areas and connections on the map."<<endl;
			cout<<"******************************************************************"<<endl;
			for(int i=0; i<areasVec.size(); i++){
				cout<<"This is area: "<<i+1<<endl;
				cout<<areasVec[i]->info.getDescription()<<endl;
				if(areasVec[i]->info.getID() == 1){
					cout<<"Area is INSTADEATH."<<endl;
				}
				if(areasVec[i]->info.getGoal() == 1){
					cout<<"Area is GOAL."<<endl;
				}
				cout<<"Connections:"<<endl;
				cout<<"\t u: Area #"<<reverseLookUp(areasVec[i]->u)<<endl;
				cout<<"\t d: Area #"<<reverseLookUp(areasVec[i]->d)<<endl;
				cout<<"\t l: Area #"<<reverseLookUp(areasVec[i]->l)<<endl;
				cout<<"\t r: Area #"<<reverseLookUp(areasVec[i]->r)<<endl;
			}
		}

		int reverseLookUp(areaNode* addy){
			for(int i=0; i<areasVec.size(); i++){
				if(areasVec[i] == addy){
					return i+1;
				}
			}
			//this should not happen
			return -1;
		}
        //virtual void parseIFD() = 0;
        friend ostream& operator<<(ostream& out, Map& outMap);
};

ostream& operator<<(ostream& out, Map& outMap) {
    out<<"******************************************************************"<<endl;
    out<<"CHEATING!!!! Printing the set of areas and connections on the map."<<endl;
    out<<"******************************************************************"<<endl;
    for(int i=0; i<outMap.areasVec.size(); i++) {
        out << "This is area: " << i+1 << endl;
        out<<outMap.areasVec[i]->info.getDescription()<<endl;
        if(outMap.areasVec[i]->info.getID() == 1){
            out<<"Area is INSTADEATH."<<endl;
        }
        if(outMap.areasVec[i]->info.getGoal() == 1){
            out<<"Area is GOAL."<<endl;
        }
        out<<"Connections:"<<endl;
        out<<"\t u: Area #"<<outMap.reverseLookUp(outMap.areasVec[i]->u)<<endl;
        out<<"\t d: Area #"<<outMap.reverseLookUp(outMap.areasVec[i]->d)<<endl;
        out<<"\t l: Area #"<<outMap.reverseLookUp(outMap.areasVec[i]->l)<<endl;
        out<<"\t r: Area #"<<outMap.reverseLookUp(outMap.areasVec[i]->r)<<endl;
    }
    return out;
}
