#include<iostream>
#include<vector>
using namespace std;
#include<stdlib.h>
#include<time.h>
int capacity;
#define size 10

class node{
	public:
		int cwnd;
		int accepted,dropped;
		int cost,g,a,b;
		void utility();
		node(){
			g=2;
			a=1;b=2;
		}
		void assign()
		{
			cwnd=rand()%capacity+1;
			cout<<cwnd<<endl;
		}
}nodes[size];

void node::utility(){
	dropped=cwnd-accepted;
	cost=cwnd-g*dropped;
	if(dropped==0){
		cwnd+=a;}
	else{
		cwnd/=b;}
}

class router{
public:
	vector <int> q;
	vector <int> n_index;
	int sum,sum_after,i;
	router(){
		sum=0;
		sum_after=0;		
	}
	void rq(int index);
	void display();
	void sum_and_acknowledge();
};

void router::rq(int index){
	q.push_back(nodes[index].cwnd);
	n_index.push_back(index);
}

void router::display(){
		for(int i=0;i<size;i++){
			cout<< "Node "<<n_index[i]<<" has a cwnd of size "<<q[i]<<endl;
		}
	}
	
void router::sum_and_acknowledge()
{
	sum=0;sum_after=0;
	int c;
	i=0;
	while(1){
		sum=sum+q[i];
		if(sum<=capacity)
		i++;
		else{
			sum=sum-q[i];
			i--;
			
		break;}
	}
	for(c=i+1;c<size;c++)
	sum_after+=q[c];


if(i<size)
{
	int tsum=sum+sum_after;
do{
		int max = 0,indexj;
		for(c=0;c<size;c++)
		if(max<q[c]){
			max=q[c];
			indexj=c;
		}
		do{
			q[indexj]--;
			tsum--;
		}while(q[indexj]!=0&&tsum>capacity);
}while(tsum>capacity);
}
cout<<"New arrangement"<<endl;
	display();

for(i=0;i<size;i++)
{
	nodes[n_index[i]].accepted=q[i];
	nodes[n_index[i]].utility();
}
for(i=0;i<size;i++)
{
	n_index.pop_back();
	q.pop_back();
}
}

int dorepeat(){
	int flag=0;
	for(int u=0;u<size;u++)
	 {
	 	if(nodes[u].dropped>0)flag++;
	 }
	 if(flag==0)return 0;
	 else return 1;
}
int main(int argc,char* argv[])
{
	
	int y=1,seed=25;
	capacity=atoi(*(argv+1));
	//capacity=300;
	int i;
	router r;
 	for(i=0;i<size;i++)
	 {
 		cout<<"Node "<<i<<" has chosen the cwnd size of ";
		nodes[i].assign();
	 }
	 
	
	do{
		cout<<endl<<endl<<"ITERATION "<<y<<endl<<endl;
		srand(seed);
 int a[size]={-1},j=0,k;
	while(j<size)
 	{	
	int k=rand()%size;
	for(i=0;i<j;i++)
	{
			if(a[i]==k)break;
	}
	if(i==j)
		{
			a[j++]=k;
			r.rq(k);
		}
	}
	cout<<"Old arrangement"<<endl;
	r.display();
	r.sum_and_acknowledge();
	y++;
	seed=seed+5;
	cout<<"The utility values of each node are as follows:"<<endl;
	for(int o=0;o<size;o++)
	{
		cout<<endl;
		cout<<" Node "<<o<<" has utility value = "<<nodes[o].cost<<endl;
	}
	}while(dorepeat()==1&&y<=15);
	return 0;
}

