#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
using namespace std;
int main(int argc, char *argv[]) {
	float x,y,z,r,diff;
	cout<<"Enter radius of the sphere"<<endl;
	cin>>r;
	ofstream outfile;
	ofstream outfile2;
	outfile.open("SphereLearnSet.txt",ios::trunc);
	outfile2.open("SphereTestSet.txt",ios::trunc);
	int random;
	srand(time(NULL));
	for(int i=0;i<900;i++)
	{
		random=rand();
		cout<<"Random value : "<<random<<endl;
		x=-r+static_cast <float> (random) / (static_cast <float> (RAND_MAX/(2*r)));
		diff=sqrt(r*r-x*x);
		random=rand();
		y=-diff+static_cast <float> (random) / (static_cast <float> (RAND_MAX/(2*diff)));
		int sign=pow(-1,rand()%2);
		z=sqrt(r*r-x*x-y*y)*sign;
		cout<<x<<"\t"<<y<<"\t"<<z<<endl;
		outfile<<abs(x)<<" "<<abs(y)<<" "<<abs(z)<<"\n";
	}
	for(int i=0;i<100;i++)
	{
		random=rand();
		cout<<"Random value : "<<random<<endl;
		x=-r+static_cast <float> (random) / (static_cast <float> (RAND_MAX/(2*r)));
		diff=sqrt(r*r-x*x);
		random=rand();
		y=-diff+static_cast <float> (random) / (static_cast <float> (RAND_MAX/(2*diff)));
		int sign=pow(-1,rand()%2);
		z=sqrt(r*r-x*x-y*y)*sign;
		cout<<x<<"\t"<<y<<"\t"<<z<<endl;
		outfile2<<abs(x)<<" "<<abs(y)<<" "<<abs(z)<<"\n";
	}
	outfile.close();
	outfile2.close();
	return 0;
}
