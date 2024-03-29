#include <iostream>
using namespace std;

#ifndef ullItem
#define ullItem
	#include "ull.h"
	#include "Item.h"
#endif

class ConsumeItem : public Item {
    private:
        vector<Effect*> fx;
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
			cout<<"DEBUG WARNING: Objects of the ConsumeItem class don't have associated rules."<<endl;
		}
        virtual vector<Rule*> getItemUseRules(){
            //shouldn't ever call this method directly
            vector<Rule*> blank;
			return blank;
		}
		virtual void addEffect(Effect* temp){
            fx.push_back(temp);
		}
        virtual vector<Effect*> getItemConsumeEffects(){
            return fx;
		}
        virtual void addBuffs(Buffs* temp)
		{
		    cout<<"DEBUG WARNING: Objects of the Item (consume items) class don't have associated buffs."<<endl;
		}
		virtual vector<Buffs*> getItemBuffEffects()
		{
		    vector<Buffs*> blank;
			return blank;
		}
        friend ostream& operator<<(ostream&, ConsumeItem&);
};
ostream& operator<<(ostream& osObject, ConsumeItem& item)
{
	osObject<<"Name: "<<item.getName()<<endl;
	osObject<<"Desc: "<<item.getDesc()<<endl;
	osObject<<"StrtRm: "<<item.getSR()<<endl;
	return osObject;
}
