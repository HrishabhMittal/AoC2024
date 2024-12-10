#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#define Q2
#ifdef Q2
#define some vals[pos[0]][pos[1]]
#define someline vals=vector(data.size(),vector<int>(data[0].size(),-1));
#else
#define some 0
#define someline
#endif
int calc(vector<int> pos,vector<vector<int>>& vals,vector<string>& data,int preval) {
	if (pos[0]<0 || pos[0]>=data.size() || pos[1]<0 || pos[1]>=data[0].size()) return 0;
	else if (preval+1!=data[pos[0]][pos[1]]) return 0;
	else if (vals[pos[0]][pos[1]]!=-1) return some;
	else if (data[pos[0]][pos[1]]=='9') {
		vals[pos[0]][pos[1]]=1;
		return 1;
	} else {
		char& charat=data[pos[0]][pos[1]];
		int& a=vals[pos[0]][pos[1]];
		a=0;
		a+=calc({pos[0]+1,pos[1]},vals,data,charat);
		a+=calc({pos[0],pos[1]+1},vals,data,charat);
		a+=calc({pos[0]-1,pos[1]},vals,data,charat);
		a+=calc({pos[0],pos[1]-1},vals,data,charat);
		return a;
	}
}
int main(int argc,char**argv) {
	vector<string> data;
	ifstream file(argv[1]);
	while (true) {
		string s;
		getline(file,s);
		if (file.good()) {
			data.push_back(s);
		} else break;
	}
	file.close();
	vector<vector<int>> vals(data.size(),vector<int>(data[0].size(),-1));
	int total=0;
	for (int i=0;i<data.size();i++) {
		for (int j=0;j<data[i].size();j++) {
			if (data[i][j]=='0') {
				total+=calc({i,j},vals,data,'0'-1);
				someline
			}
		}
	}
	//for (int i=0;i<vals.size();i++) {
	//	for (int j=0;j<vals[i].size();j++) {
	//		cout << vals[i][j] << "(" << data[i][j] << ") ";
	//	}
	//	cout << endl;
	//}
	cout << total << endl;
}
