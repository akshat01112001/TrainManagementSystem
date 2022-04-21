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
	train(ll from,ll to,ll departure_t,ll arrival_t,ll num,ll k,bool in_transit,bool givplat,ll platn);
	ll from;
	ll to;
	ll departure_t;
	ll arrival_t;
	ll num;
	ll k;
	ll platn;
	bool in_transit;
	bool givplat;
};

train::train(){
	this->from=0;
	this->to=0;
	this->departure_t=0;
	this->arrival_t=0;
	this->num=0;
	this->k=0;
	this->in_transit=true;
	this->givplat=false;
	this->platn=0;
}

train::train(ll from,ll to,ll departure_t,ll arrival_t,ll num,ll k,bool in_transit,bool givplat,ll platn){
	this->from=from;
	this->to=to;
	this->departure_t=departure_t;
	this->arrival_t=arrival_t;
	this->num=num;
	this->k=k;
	this->in_transit=in_transit;
	this->givplat=givplat;
	this->platn=platn;
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

ll k=0;

ll rebound(ll &j){
	return (j<4?j:0);
}

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
	train *in=new train(input->from,input->to,input->departure_t,input->arrival_t,input->num,input->k,input->in_transit,input->givplat,input->platn);
	for(int i = 0; i < 4; i++){
        if(st->plat[i]==input){
            //cout<<"Train "<<st->plat[i]->num<<" is exiting platform "<<i+1<<" at "<<st->plat[i]->departure_t<<" at station "<<input->from<<endl;
            st->plat[i]->from=st->plat[i]->to=st->plat[i]->departure_t=st->plat[i]->arrival_t=st->plat[i]->num=0;
            in->givplat=false;
        }
    }
    input=in;
    
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
bool cmp(train * a,train * b) {
	return a->departure_t < b->departure_t;
}

//make current time dynamic for transit using while loop

void put_train(train *input,station *&v, ll beg_time){
	// cout<<input->num<<" xyz ";
	// for(ll i=0;i<4;i++){
	// 	if(plat[i]->num==0){
	// 		plat[i]=;             //to fimd empty platform
	// 		return;
	// 	}
	// }
	train *in=new train(input->from,input->to,input->departure_t,input->arrival_t,input->num,input->k,input->in_transit,input->givplat,input->platn);
	for(ll i=0;i<4;i++){       //is there any platform empty?? else go next
		if(v->plat[i]->num==0){
			v->plat[i]=in;
			input->givplat=true;
			input->platn=i+1;
			if(v->plat[i]->num) readout_train(in,v);
			return;
		}
		             // all platforms were full!! put in waiting list
	}

	v->wait_q.push(in);
	

	ll depart=INT_MAX;

	for(ll j=0;j<4;j++){
		if(v->plat[j]->num)
			depart=min(depart,v->plat[j]->departure_t);   // this loop find minimum departure time
	}
	// time_updation(input->departure_t,30);
	
	for(ll j=k;j<4;j++){
		if(depart==v->plat[j]->departure_t){
			v->wait_q.front()->departure_t=depart+30;  
			cout<<v->wait_q.front()->departure_t<<endl; // update departure time due to delay
			v->plat[j]=v->wait_q.front();  
			input->platn=j+1;                    //this one finds which platform had minimum departure 
			cout<<v->wait_q.front()->departure_t<<" "<<v->wait_q.front()->num<<" "<<v->plat[j]->num<<" "<<input->platn<<endl;
			v->wait_q.pop();
			k=rebound(j);
			k++;						 // and then puts first waiting list train at that spot
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
bool checkVal(train* tr,queue<train *>wait_q){
	queue<train *>temp=wait_q;
	while(!temp.empty()){
		if(tr==temp.front()) {
			cout<<"did find "<<endl;
			return true;
		}
		temp.pop();
	}
	// cout<<"did not find "<<endl;
	return false;
}



void transit(train *tr,station *st[],ll beg_time){     
	remove_train(tr,st[tr->from++-1]);
	if(tr->from<5){
		
		put_train(tr,st[tr->from-1],beg_time);
	}
}

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
		train *tra1=new train(from,to,departure_t,arrival_t,num,k,true,false,0);
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
				transit(v[i],stat,beg_time);
				//stat[v[i]->from]->readout_train(v[i]);
				time_updation(v[i]->departure_t,v[i]->k);
				time(v[i]->departure_t);
				for(ll j=0;j<4;j++){
					if(v[i]->in_transit && stat[v[i]->from-1]->plat[j]->num!=0 && v[i]->givplat){
						
						cout<<v[i]->num<<" ";
						time_out(v[i]->departure_t);
						cout<<" "<<v[i]->from<<" "<<v[i]->to<<" "<<v[i]->platn<<endl;

						
					}
					if(v[i]->departure_t>=v[i]->arrival_t) v[i]->in_transit=false;
					break;
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
	// fix why station 1 isnt printing
	//find why train isnt coming out from queue.

	return 0;
}