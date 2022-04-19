#include <bits/stdc++.h>
#define ll long long int

using namespace std;

//class train and station
//priority queue for every platform
//array of 12 size
//delete this later
class train{
public:
	train();
	train(ll from,ll to,ll departure_t,ll arrival_t,ll num,ll k,bool in_transit);
	ll from;
	ll to;
	ll departure_t;
	ll arrival_t;
	ll num;
	ll k;
	bool in_transit;
};

train::train(){
	this->from=0;
	this->to=0;
	this->departure_t=0;
	this->arrival_t=0;
	this->num=0;
	this->k=0;
	this->in_transit=true;
}

train::train(ll from,ll to,ll departure_t,ll arrival_t,ll num,ll k,bool in_transit){
	this->from=from;
	this->to=to;
	this->departure_t=departure_t;
	this->arrival_t=arrival_t;
	this->num=num;
	this->k=k;
	this->in_transit=in_transit;
}

class station{
public:
	void readout_train(train *input);
	void remove_train(train *input);
	void put_train(train *input,vector<train *>v);
	queue<train *>wait_q;
	train* plat[4];
};

void station::readout_train(train *input){
	for(int i = 0; i < 4; i++){
        if(plat[i]->from == 0){
            //this->trains[i]=input;
            cout<< "Train "<<this->plat[i]->num<<" is entering platform no "<<i + 1<<" at "<<this->plat[i]->arrival_t<<" and should leave at "<<this->plat[i]->departure_t<<endl;
        }
    }
}

void station::remove_train(train *input){
	for(int i = 0; i < 4; i++){
        if(plat[i]==input){
            cout<<"Train "<<this->plat[i]->num<<" is exiting platform "<<i+1<<" at "<<this->plat[i]->departure_t<<endl;
            plat[i]->from=plat[i]->to=plat[i]->departure_t=plat[i]->arrival_t=plat[i]->num=0;
        }
    }
}

bool cmp(train * a,train * b) {
	return a->departure_t < b->departure_t;
}

//make current time dynamic for transit using while loop

void station::put_train(train* input,vector<train *>v){
	// for(ll i=0;i<4;i++){
	// 	if(plat[i]->num==0){
	// 		plat[i]=;             //to fimd empty platform
	// 		return;
	// 	}
	// }

	for(auto& tr:v){
		ll i=0;
		while(plat[i]->num && i<4) i++;       //is there any platform empty?? else go next
		if(i<4){
			plat[i]=tr;
			return; 
		}
		if(i==4) wait_q.push(tr);             // all platforms were full!! put in waiting list
		           
	}

	ll depart=INT_MAX;

	for(ll j=0;j<4;j++){
		if(plat[j]->num)
			depart=min(depart,plat[j]->departure_t);   // this loop find minimum departure time
	}

	for(ll j=0;j<4;j++){
		if(depart==plat[j]->departure_t){
			plat[j]=wait_q.front();                      //this one finds which platform had minimum departure 
			wait_q.pop();							 // and then puts first waiting list train at that spot
			return;
		}
	}

	return;
}

void time(ll &t){
	if(t%100>59){
		t-=60;
		t+=100;
	}
	if(t>2359) t-=2400;
}

void time_updation(ll &t,ll k){
	t+=k;
}

void transit(train *tr,station* stat[],vector<train *>v){
	stat[tr->from++]->remove_train(tr);
	if(tr->from<4) stat[tr->from]->put_train(tr,v);
}

void solve()
{
	cout<<"Number of trains: ";
	ll t,counter=0,i,j,beg_time=900,from,to,departure_t,arrival_t,num,k;
	station* stat[4];
	cin>>t;
	train *tra=new train();
	vector<train *>v(t, tra);
	for(i=0;i<t;i++){
		cout<<"Enter source, destination, incoming time, outgoing time and train number: ";
		cin>>from>>to>>departure_t>>arrival_t>>num;
		k = (arrival_t-departure_t)/(to - from);
		// k /= 100;
		time(k);
		train *tra1=new train(from,to,departure_t,arrival_t,num,k,true);
		v[i]=tra1;
	}
	sort(v.begin(),v.end(),cmp);
	for(i=0;i<t;i++){
		cout<<v[i]->from<<" "<<v[i]->to<<" "<<v[i]->departure_t<<" "<<v[i]->arrival_t<<" "<<v[i]->num<<endl;
	}
	while(beg_time!=2300){
		for(i=0;i<t;i++){
			if(v[i]->departure_t==beg_time){
				stat[v[i]->from]->put_train(v[i],v);
				
				//transit(v[i],stat,v);
				//stat[v[i]->from]->readout_train(v[i]);
				time_updation(v[i]->departure_t,v[i]->k);
				time(v[i]->departure_t);
				if(v[i]->in_transit) cout<<v[i]->departure_t<<" "<<v[i]->num<<" "<<v[i]->from<<" "<<v[i]->to<<endl;
				if(v[i]->departure_t>=v[i]->arrival_t) v[i]->in_transit=false;
			}
			// if(tr->arrival_t==beg_time){
			// 	transit
			// }
		}
		// for(auto& tr:v){

		// }
		time_updation(beg_time,10);
		time(beg_time);
	}
}

int main()
{
	solve();

	return 0;
}