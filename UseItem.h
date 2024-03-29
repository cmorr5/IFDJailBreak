#include <iostream>
using namespace std;

#ifndef ullItem
#define ullItem
	#include "ull.h"
	#include "Item.h"
#endif
class UseItem : public Item {
    private:
        vector<Rule*> rules;
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
			rules.push_back(temp);
		}
        virtual vector<Rule*> getItemUseRules(){
			return rules;
		}
		virtual void addEffect(Effect* temp){
			cout<<"DEBUG WARNING: Objects of the UseItem class don't have associated effects."<<endl;
		}
        virtual vector<Effect*> getItemConsumeEffects(){
			//shouldn't ever call this method directly
            vector<Effect*> blank;
			return blank;
		}
        virtual void addBuffs(Buffs* temp)
		{
		    cout<<"DEBUG WARNING: Objects of the Item (use items) class don't have associated buffs."<<endl;
		}
		virtual vector<Buffs*> getItemBuffEffects()
		{
		    vector<Buffs*> blank;
			return blank;
		}
        friend ostream& operator<<(ostream&, UseItem&);
};

ostream& operator<<(ostream& osObject, UseItem& item)
{
	osObject<<"Name: "<<item.getName()<<endl;
	osObject<<"Desc: "<<item.getDesc()<<endl;
	osObject<<"StrtRm: "<<item.getSR()<<endl;
	return osObject;
}
