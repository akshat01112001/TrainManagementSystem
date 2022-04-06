#include <bits/stdc++.h>
#define ll long long int

using namespace std;

//class train and station
//priority queue for every platform
//array of 12 size
//delete this later
class train{
public:
	ll from;
	ll to;
	ll departure_t;
	ll arrival_t;
	ll num;
};

class station{
public:
	priority_queue<ll> plat;
};

station stat_plat[4][4];

void solve()
{
	cout<<"Number of trains: ";
	ll t,counter=0;
	cin>>t;
	vector<train>v(t);
	for(auto& tr:v){
		cout<<"Enter source, destination, incoming time, outgoing time and train number: ";
		cin>>tr.from>>tr.to>>tr.departure_t>>tr.arrival_t>>tr.num;
	}
	sort(v.begin(),v.end());
	for(auto& tr:v){
		ll c=INT_MAX;
		if(tr.from==tr.to) continue;
		ll i=1;
		while(!stat_plat[tr.from][i].empty() && i<5)
			i++;
		cout<<i<<
		if(i==5){
			for(k=1;k<5;k++){
				train tra=stat_plat[tr.from][k].front();
				c=min(c,tra.departure_t);
				if(c==tra.departure_t) i=k;
			}
		}
		stat_plat[tr.from][i].push(tr.num);
		counter++;
		if(counter>=c) stat_plat[tr.from++][i].pop();
	}

}

int main()
{
	solve();

	return 0;
}