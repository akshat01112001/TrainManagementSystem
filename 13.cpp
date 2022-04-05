#include <bits/stdc++.h>
#define ll long long int

using namespace std;

//class train and station
//priority queue for every platform
//array of 12 size

class train{
public:
	ll num;
	ll from;
	ll to;
	ll in;
	ll out;
};

class station{
public:
	priority_queue<ll> plat;
}

station stat_plat[4];

void solve()
{
	ll t;
	cin>>t;
	vector<train>v(t);
	for(auto& tr:v){
		cout<<"Enter train number, source, destination, incoming time and outgoing time: ";
		cin>>tr.num>>tr.from>>tr.to>>tr.in>>tr.out;
	}
	
	

}

int main()
{
	solve();

	return 0;
}