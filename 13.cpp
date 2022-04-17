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
	ll from;
	ll to;
	ll departure_t;
	ll arrival_t;
	ll num;
};

train::train(){
	this->from=0;
	this->to=0;
	this->departure_t=0;
	this->arrival_t=0;
	this->num=0;
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
	for(ll i=0;i<4;i++){
		if(plat[i]->num==0){
			plat[i]=input;
			break;
		}
	}
	for(auto& tr:v){
		ll i=0;
		while(!plat[i]->num && i<4) i++;
		plat[i]=tr;
		if(i==4) wait_q.push(tr);
	}
	ll depart=INT_MAX;
	for(ll j=0;j<4;j++){
		if(plat[j]->num)
			depart=min(depart,plat[j]->departure_t);
	}
	for(ll j=0;j<4;j++){
		if(depart==plat[j]->departure_t){
			plat[j]=wait_q.front();
			wait_q.pop();
		}
	}
}

void time(ll &t){
	if(t%100>59){
		t-=60;
		t+=100;
	}
	if(t>2359) t-=2400;
}

void time_updation(ll &t,double k){
	t+=k;
}

void transit(train *tr,station* stat[],vector<train *>v){
	stat[tr->from++]->remove_train(tr);
	if(tr->from<4) stat[tr->from]->put_train(tr,v);
}

void solve()
{
	cout<<"Number of trains: ";
	ll t,counter=0,i,j,beg_time=900;
	station* stat[4];
	cin>>t;
	vector<train *>v(t);
	for(auto& tr:v){
		cout<<"Enter source, destination, incoming time, outgoing time and train number: ";
		cin>>tr->from>>tr->to>>tr->departure_t>>tr->arrival_t>>tr->num;
	}
	sort(v.begin(),v.end(),cmp);
	while(beg_time!=2300){
		for(auto& tr:v){
			if(tr->departure_t==beg_time){
				stat[tr->from]->put_train(tr,v);
				double k = (tr->arrival_t-tr->departure_t)/(tr->to - tr->from)*1.0;
				transit(tr,stat,v);
				stat[tr->from]->readout_train(tr);
				time_updation(tr->departure_t,k);
			}
			// if(tr->arrival_t==beg_time){
			// 	transit
			// }
		}
		// for(auto& tr:v){

		// }
		time_updation(beg_time,30);
		time(beg_time);
	}
}

int main()
{
	solve();

	return 0;
}