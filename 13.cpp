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
	station();
	//void readout_train(train *input);
	//void remove_train(train *input);
	//void put_train(train *input,vector<train *>v);
	queue<train *>wait_q;
	train* plat[4];
	ll u;
};

station::station(){
	this->u=0;
}

void readout_train(train *input,station *st){
	for(int i = 0; i < 4; i++){
        if(st->plat[i]->from){
            //this->trains[i]=input;
            //cout<< "Train "<<st->plat[i]->num<<" is entering platform no "<<i + 1<<" at "<<st->plat[i]->departure_t<<" at station "<<input->from<<endl;
        }
    }
}

void remove_train(train *input,station *st){
	for(int i = 0; i < 4; i++){
        if(st->plat[i]==input){
            //cout<<"Train "<<st->plat[i]->num<<" is exiting platform "<<i+1<<" at "<<st->plat[i]->departure_t<<" at station "<<input->from<<endl;
            st->plat[i]->from=st->plat[i]->to=st->plat[i]->departure_t=st->plat[i]->arrival_t=st->plat[i]->num=0;
        }
    }
    
}

bool cmp(train * a,train * b) {
	return a->departure_t < b->departure_t;
}

//make current time dynamic for transit using while loop

void put_train(train *input,station *&v){
	// cout<<input->num<<" xyz ";
	// for(ll i=0;i<4;i++){
	// 	if(plat[i]->num==0){
	// 		plat[i]=;             //to fimd empty platform
	// 		return;
	// 	}
	// }
	train *in=new train(input->from,input->to,input->departure_t,input->arrival_t,input->num,input->k,input->in_transit);
	for(ll i=0;i<4;i++){       //is there any platform empty?? else go next
		if(v->plat[i]->num==0){
			v->plat[i]=in;
			if(v->plat[i]->num) readout_train(in,v);
			return;
		}
		v->wait_q.push(in);             // all platforms were full!! put in waiting list
	}

	ll depart=INT_MAX;

	for(ll j=0;j<4;j++){
		if(v->plat[j]->num)
			depart=min(depart,v->plat[j]->departure_t);   // this loop find minimum departure time
	}

	for(ll j=0;j<4;j++){
		if(depart==v->plat[j]->departure_t){
			v->plat[j]=v->wait_q.front();                      //this one finds which platform had minimum departure 
			v->wait_q.pop();
										 // and then puts first waiting list train at that spot
			break;
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

void  time_out(ll time){
	ll j=time%100;
	time-=j;
	j*=60;
	j/=100;
	time+=j;
	cout<<time<<" ";
}

void time_updation(ll &t,ll k){
	t+=k;
}

void transit(train *tr,station *st[]){     
	remove_train(tr,st[tr->from++-1]);
	if(tr->from<5){
		
		put_train(tr,st[tr->from-1]);
	}
}
oop.
void solve()
{
	//cout<<"Number of trains: ";
	ll t,counter=0,i,j,beg_time=900,from,to,departure_t,arrival_t,num,k;
	station* stat[4];
	cin>>t;
	train *tra=new train();
	vector<train *>v(t, tra);
	for(i=0;i<4;i++){
		stat[i]=new station();
		for(j=0;j<4;j++){
			stat[i]->plat[j]=new train();
		}
	}
	for(i=0;i<t;i++){
		//cout<<"Enter source, destination, incoming time, outgoing time and train number: ";
		cin>>from>>to>>departure_t>>arrival_t>>num;
		k = (arrival_t-departure_t)/(to-from);
		// k /= 100;
		// k*=60;
		// k/=(to - from);

		// k*=100;
		// k/=60;
		time(k);
		train *tra1=new train(from,to,departure_t,arrival_t,num,k,true);
		v[i]=tra1;
	}
	
	cout<<endl;
	sort(v.begin(),v.end(),cmp);
	
	//put_train(v[0],stat[v[0]->from-1]);
	
	cout<<endl;
	while(beg_time!=2300){
		for(i=0;i<t;i++){
			if(v[i]->departure_t==beg_time){
				//if(v[i]->in_transit) cout<<v[i]->num<<" "<<v[i]->departure_t<<" "<<v[i]->from<<" "<<v[i]->to<<endl;
				transit(v[i],stat);
				//stat[v[i]->from]->readout_train(v[i]);
				time_updation(v[i]->departure_t,v[i]->k);
				time(v[i]->departure_t);
				for(ll j=0;j<4;j++){
					if(v[i]->in_transit && stat[v[i]->from-1]->plat[j]->num==v[i]->num){
						cout<<v[i]->num<<" ";
						time_out(v[i]->departure_t);
						cout<<" "<<v[i]->from<<" "<<v[i]->to<<" "<<j+1<<endl;
					}
					if(v[i]->departure_t>=v[i]->arrival_t) v[i]->in_transit=false;
				}
				
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
	//find a way to implement the queue part.

	return 0;
}