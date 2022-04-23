#include <bits/stdc++.h>
#define ll long long int

using namespace std;

class train{
public:
	train();
	train(ll from,ll to,ll departure_t,ll arrival_t,ll num,ll k,bool in_transit,bool givplat,ll platn,ll cnt);
	ll from;
	ll to;
	ll departure_t;
	ll arrival_t;
	ll num;
	ll k;
	ll platn;
	ll cnt;
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
	this->cnt=0;
}

train::train(ll from,ll to,ll departure_t,ll arrival_t,ll num,ll k,bool in_transit,bool givplat,ll platn,ll cnt){
	this->from=from;
	this->to=to;
	this->departure_t=departure_t;
	this->arrival_t=arrival_t;
	this->num=num;
	this->k=k;
	this->in_transit=in_transit;
	this->givplat=givplat;
	this->platn=platn;
	this->cnt=cnt;
}

class station{
public:
	station();
	queue<train *>wait_q;
	train* plat[4];
	ll u;
};

ll k=0;

ll  time_out(ll time){
	ll j=time%100;
	time-=j;
	j*=60;
	j/=100;
	time+=j;
	return time;
}

ll rebound(ll &j){
	return (j<4?j:0);
}

station::station(){
	this->u=0;
}

void remove_train(train *input,station *st){
	train *in=new train(input->from,input->to,input->departure_t,input->arrival_t,input->num,input->k,input->in_transit,input->givplat,input->platn,input->cnt);
	for(ll i = 0; i < 4; i++){
        if(st->plat[i]->num==input->num && input->from!=input->to){
            cout<<"Train "<<st->plat[i]->num<<" is exiting platform "<<i+1<<" at "<<time_out(st->plat[i]->departure_t)<<" at station "<<input->from<<endl<<endl;

            st->plat[i]->from=st->plat[i]->to=st->plat[i]->departure_t=st->plat[i]->arrival_t=st->plat[i]->num=0;
            input->givplat=false;
            break;
        }
    }
}

void time_updation(ll &t,ll k){
	t+=k;
}

bool cmp(train *a,train *b) {
	if(a->departure_t!=b->departure_t) return a->departure_t < b->departure_t;
	return a->num < b->num;
}


void put_train(train *input,station *v, ll beg_time){
	train *in=new train(input->from,input->to,input->departure_t,input->arrival_t,input->num,input->k,input->in_transit,input->givplat,input->platn,input->cnt);
	for(ll i=0;i<4;i++){       							//is there any platform empty?? else go next
		if(v->plat[i]->num==0){
			v->plat[i]=in;
			input->givplat=true;
			input->platn=i+1;
			return;
		}
	}

	v->wait_q.push(in);   								   // all platforms were full!! put in waiting list
	ll depart=INT_MAX;

	for(ll j=0;j<4;j++){
		if(v->plat[j]->num)
			depart=min(depart,v->plat[j]->departure_t);   // this loop find minimum departure time
	}

	for(ll j=k;j<4;j++){
		if(depart==v->plat[j]->departure_t){
			remove_train(v->plat[j],v);						// update departure time due to delay
			v->plat[j]=v->wait_q.front();
			input->platn=j+1;      							//this one finds which platform had minimum departure 
			input->givplat=true;
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
}

bool checkVal(ll trnum,queue<train *>wait_q){
	cout<<"we tried checking for "<<trnum<<endl;
	queue<train *> temp=wait_q;
	while(!temp.empty()){
		if(trnum==temp.front()->num) {
			cout<<"did find "<<trnum<<endl;
			return true;
		}
		temp.pop();
	}
	return false;
}

void transit(train *tr,station *st[],ll beg_time){
	remove_train(tr,st[tr->from-1]);
	if(tr->from<5) put_train(tr,st[tr->from++],beg_time);
}

void solve()
{
	ll t,counter=0,i,j,beg_time=900,from,to,departure_t,arrival_t,num,k;
	station* stat[4];
	train *tra=new train();

	cout<<"Number of trains: ";
	cin>>t;

	ll tempD[t];
	vector<train *>v(t, tra);

	for(i=0;i<4;i++){
		stat[i]=new station();
		for(j=0;j<4;j++){
			stat[i]->plat[j]=new train();
		}
	}

	for(i=0;i<t;i++){
		cout<<"Enter source, destination, incoming time, outgoing time and train number: ";
		cin>>from>>to>>departure_t>>arrival_t>>num;
		k = (arrival_t-departure_t)/(to-from);
		time(k);
		train *tra1=new train(from,to,departure_t,arrival_t,num,k,true,false,0,0);
		v[i]=tra1;
	}
	
	sort(v.begin(),v.end(),cmp);

	for(i=0;i<t;i++)
		tempD[i]=v[i]->departure_t;

	while(beg_time!=2300){
		for(i=0;i<t;i++){
			if(v[i]->departure_t==beg_time){
				if(v[i]->cnt==0){
					put_train(v[i],stat[v[i]->from-1],beg_time);
					v[i]->cnt++;
				}
				else transit(v[i],stat,beg_time);
			
				for(ll j=0;j<4;j++){
					if(v[i]->in_transit && stat[v[i]->from-1]->plat[j]->num!=0 && v[i]->givplat)
						cout<<"Train "<<v[i]->num<<" is entering platform "<<v[i]->platn <<" at "<<time_out(v[i]->departure_t)<<" at station "<<v[i]->from<<" "<<endl<<endl;
					if(v[i]->departure_t>=v[i]->arrival_t) v[i]->in_transit=false;
					break;
				}
			
				if(v[i]->to==v[i]->from){
					cout<<"Train "<<v[i]->num<<" has reached its destination at platform "<<v[i]->platn <<" at "<<time_out(v[i]->departure_t)<<" at station "<<v[i]->from<<endl;
					v[i]=new train(0,0,0,0,0,0,false,false,0,0);
					cout<<"It has now been transferred to the yard"<<endl<<endl;
				}

				time_updation(v[i]->departure_t,v[i]->k);
				time(v[i]->departure_t);
			}
		}

		time_updation(beg_time,10);
		time(beg_time);
	}

}

int main()
{
	solve();

	return 0;
}