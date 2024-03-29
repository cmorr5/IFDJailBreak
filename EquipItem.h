#include <iostream>
using namespace std;

#ifndef ullItem
#define ullItem
	#include "ull.h"
	#include "Item.h"
#endif
class EquipItem : public Item
{
private:
    vector<Buffs*> buff; // vector of buffs pointers
public:
        virtual void setActiveMessage(string s){
		    activeMessage = s;
		}
		virtual string getActiveMessage(){
            return activeMessage;
		}
		virtual void setActiveArea(int i){
            activeArea = i;
		}
		virtual int getActiveArea(){
            return activeArea;
		}
        virtual void addRule(Rule* temp){
			cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have associated rules."<<endl;
		}
        virtual vector<Rule*> getItemUseRules(){
            //shouldn't ever call this method directly
            vector<Rule*> blank;
			return blank;
		}
		virtual void addEffect(Effect* temp){
			cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have associated effects."<<endl;
		}
        virtual vector<Effect*> getItemConsumeEffects(){
			//shouldn't ever call this method directly
            vector<Effect*> blank;
			return blank;
		}
        virtual void addBuffs(Buffs* temp)
		{
		    buff.push_back(temp);
		}
		virtual vector<Buffs*> getItemBuffEffects()
		{
            return buff;
		}
		friend ostream& operator<<(ostream&, EquipItem&);
};
ostream& operator<<(ostream& osObject, EquipItem& item)
{
	osObject<<"Name: "<<item.getName()<<endl;
	osObject<<"Desc: "<<item.getDesc()<<endl;
	osObject<<"StrtRm: "<<item.getSR()<<endl;
	return osObject;
}
