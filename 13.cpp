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
	this.from=0;
	this.to=0;
	this.departure_t=0;
	this.arrival_t=0;
	this.num=0;
}

void time(ll &t){
	if(t%100>59){
		t-=60;
		t+=100;
	}
	if(t>2359) t-=2400;
}

void time_updation(ll &t){
	t+=30;
}

class station{
public:
	void put_train(train *input);
	void remove_train(train *input);
private:
	train* trains[4];
};

void station::put_train(train *input){
	for(int i = 0; i < 4; i++){
        if(trains[i].from == 0){
            this->trains[i]=input;
            cout<< "Train "<<this->trains[i]->num<<" is entering platform no "<<i + 1<<" at "<<this->trains[i]->arrival_t<<" and should leave at "<<this->trains[i]->departure_t<<endl;
        }
    }
}

void Station::remove_train(train *input){
	for(int i = 0; i < 4; i++){
        if(trains[i]==input){
            cout<<"Train "<<this->trains[i]->num<<" is exiting platform "<<i+1<<" at "<<this->trains[i]->departure_t<<endl;
            trains[i]->from=trains[i]->to=trains[i]->departure_t=trains[i]->arrival_t=trains[i]->num=0;
        }
    }
}

void solve()
{
	cout<<"Number of trains: ";
	ll t,counter=0;
	cin>>t;
	vector<train *>v(t);
	for(auto& tr:v){
		cout<<"Enter source, destination, incoming time, outgoing time and train number: ";
		cin>>tr.from>>tr.to>>tr.departure_t>>tr.arrival_t>>tr.num;
	}
	sort(v.begin(),v.end());


}

int main()
{
	solve();

	return 0;
}