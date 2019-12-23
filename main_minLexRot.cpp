#include <bits/stdc++.h>

using namespace std;

#define MAX 100007
#define f first
#define s second
// #define s.f second.first
// #define s.s second.second
#define fo(i,a,b) for(int i=a;i<b;i++)
#define fo2(i,a,b) for(int i=a;i<b;i*=2)



int buildSuffArr(char txt[MAX], int n);
int comp(pair<int,pair<int,int> > a, pair<int,pair<int,int> > b);
vector<pair<int,pair<int,int>>> radixSort(vector<pair<int,pair<int,int>>>& arr);
void sortByIndex(vector<pair<int,pair<int,int>>>& arr,int c);

int main(){
	int n;
	cin>>n;
	char txt[n];   
    cin >> txt ;
    // int n = strlen(txt);
    // cout << buildSuffArr(txt, n)<< endl;

    int idx=buildSuffArr(txt, n);
    // cout<<idx<<endl;
    string lexo="";
    fo(i,idx,n){
    	lexo+=txt[i];
    }
    fo(i,0,idx){
    	lexo+=txt[i];
    }
    cout<<lexo<<endl;
	return 0 ;
}

int buildSuffArr(char txt[MAX], int n){
	/*Each elem of suff vector has 3 things(in the foll order:
	1- index (of substring in the text string)
	2- rank
	3- next rank
	*/
	vector<pair<int,pair<int,int> > > suff(n);

	// suff[0].f=1;
	// suff[0].s.f=2;
	// suff[0].s.s=3;

	// cout<<suff[0].f<<endl;
	// cout<<suff[0].s.f<<endl;

	int idx[n];

	/*For a string of length n, n suffixes are possible*/

	fo(i,0,n-1){
		suff[i].f=i;
		suff[i].s.f=(int)txt[i];
		suff[i].s.s=(int)txt[i+1];
		// suff[i].s.f=txt[i]-'a';
		// suff[i].s.s=txt[i+1]-'a';
	}

	//For the last suffix(of length 1), the next rank is that of the first char in the text, coz of lexicographic "rotation" requirement
	suff[n-1].f=n-1;
	suff[n-1].s.f=(int)txt[n-1];
	suff[n-1].s.s=(int)txt[0];
	// suff[n-1].s.f=txt[n-1]-'a';
	// suff[n-1].s.s=txt[0]-'a';

	/*The above computes rank and nextRank as per the 1st and the 2nd characters (2^0 and 2^1) in each of the suffixes*/

	// stable_sort(suff.begin(), suff.end(), comp);
	suff=radixSort(suff);

	// fo(i,)


	int lim=2*n;
	fo2(k,4,lim){
		int temprank=suff[0].s.f;
		suff[0].s.f=0;//Need to store the rank coz it'll get updated with a new rank; no need to store nextRank, as it doesn't get overwritten

		//updating ranks of each suffix
		fo(i,1,n){
			if(suff[i].s.f == temprank && suff[i].s.s == suff[i-1].s.s){
				suff[i].s.f=suff[i-1].s.f;//assigning i the same rank as that of i-1, coz both rank and nextRank are same for ith and i-1th suffix
			}
			else{
				temprank=suff[i].s.f;
				suff[i].s.f=suff[i-1].s.f+1;//suffix at i greater than suffix at i-1, hence adding 1 to the rank of i-1th suffix
			}
		}

		/*This stores where each "index" of a suffix can be found in the suff vector*/
		fo(i,0,n){
			idx[suff[i].f]=i;
		}

		//updating nextRanks of each suffix
		fo(i,0,n){
			int nextidx=suff[i].f+k/2;//giving rank as per 2^2, 2^4 ann so on characters
			int id;
			if(nextidx<n){
				suff[i].s.s=suff[idx[nextidx]].s.f;
			}
			else{
				suff[i].s.s=suff[idx[nextidx%n]].s.f;// Imp step for lexicographic "rotation"
			}
		}

		// stable_sort(suff.begin(), suff.end(), comp);
		suff=radixSort(suff);
	}

	return suff[0].f;
	//The lexicographically smallest suffix comes to the front of suff[], and that suffix's "index" gives us the minimum rotations reqd to obtain that suffix



}

int comp(pair<int,pair<int,int> > a, pair<int,pair<int,int> > b){
	if(a.s.f == b.s.f){
		return a.s.s<b.s.s;
	}
	else{
		return a.s.f<b.s.f;
	}
}


void sortByIndex(vector<pair<int,pair<int,int>>>& arr,int c){
	int count[MAX]={0};
	
	for(int j=0; j<arr.size(); j++){
		switch(c){
			case 1:
				count[arr[j].second.first+1]++;
				break;
			case 2:
				count[arr[j].second.second+1]++;
				break;
		}
		
	}
	for(int j=1; j<=MAX; j++)
		count[j] += count[j-1];
	vector<pair<int,pair<int,int>>> sorted(arr.size());
	for(int j=(arr.size()-1); j>=0; j--){
		switch(c){
			case 1:
				sorted[count[arr[j].second.first+1]-1]=arr[j];
				count[arr[j].second.first+1]--;
				break;
			case 2:
				sorted[count[arr[j].second.second+1]-1]=arr[j];
				count[arr[j].second.second+1]--;
				break;
		}
	}
	arr=sorted;
}


vector<pair<int,pair<int,int>>> radixSort(vector<pair<int,pair<int,int>>>& arr){
	int c=2;
	while(c)
	{	sortByIndex(arr,c);
		c--;
	}
	return arr;
}



