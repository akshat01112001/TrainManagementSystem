#include <bits/stdc++.h>
#define ll long long int

using namespace std;

//class train and station
//priority queue for every platform
//array of 12 size

class train{
public:
	int num;
	int from;
	int to;
	int in;
	int out;
};

class station{
public:
	int num;
}

int stat_plat[12];

void solve()
{
	int t;
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