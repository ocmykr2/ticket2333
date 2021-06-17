#ifndef Hash
#define Hash

#include "includes.hpp"
#include "FileOperator.hpp"
#include <bits/stdc++.h>

const int MAXSTR = N * 29;
const int Base = 111111;
const int mod = 1e9 + 7;

map <int, int> Stations;

fstream StationsGO;

struct Stationfuck {
	map <int, int> Map;
	Stationfuck() {
		
		StationsGO.open("StationsGO", ios::in|ios::out|ios::binary);
		int now = FileOperator.getend(StationsGO), a[1], b[1];
		Map.clear();
//		cerr << "sdasjdlkajsdlajsdljasdljasdlkasjdlkjasdlkajsdlasjdlaksjdlaskjdaskljdaskljdaskldjlkasjasdkjlsadjklljadsk" << endl; 
		for(int i = 0; i < now; i += sizeof(int)) {
			FileOperator.get(StationsGO, i, 1, a);
			i += sizeof(int);
			FileOperator.get(StationsGO, i, 1, b);
			Map[a[0]] = b[0];
		}
		swap(Map, Stations);
		StationsGO.close();
	}
	~Stationfuck() {
		FileOperator.NewFile("StationsGO");
		StationsGO.open("StationsGO", ios::in|ios::out|ios::binary);
		int a[1], b[1];
		int pos = 0;
		for(auto V : Stations) {
			a[0] = V.first;
			FileOperator.write(StationsGO, pos, 1, a);
			pos += sizeof(int);
			b[0] = V.second;
			FileOperator.write(StationsGO, pos, 1, b);
			pos += sizeof(int);
		}
		StationsGO.close();
	}
}tuile;

fstream rtGO, chGO, szGO, UserGO, TrainGO, StaGO, TraGO, cntAllGO;

class Has {
	public: 
	int rt, ch[MAXSTR][2], sz, User[MAXSTR], Train[MAXSTR];
	char Sta[1000005][35], Tra[N][35];
	int cntAll = 0;
	
	void init() {
		Stations.clear();
		rt = sz = 1;
		memset(ch, 0, sizeof(ch));
		memset(User, 0, sizeof(User));
		memset(Train, 0, sizeof(Train));
		memset(Sta, 0, sizeof(Sta));
		memset(Tra, 0, sizeof(Tra));
		cntAll = 0;
	}
	
	Has() {
		rtGO.open("rtGO", ios::binary|ios::out|ios::in);
		UserGO.open("UserGO", ios::binary|ios::out|ios::in);
		chGO.open("chGO", ios::binary|ios::out|ios::in);
		int tmp[3];
		if(FileOperator.getend(rtGO) == -1) {
			sz = rt = 1;
			rtGO.close();  UserGO.close(); chGO.close();
			return;
		}
		
		FileOperator.get(rtGO, 0, 3, tmp);
		rt = tmp[0]; sz = tmp[1]; cntAll = tmp[2];
		
		if(!rt) {
			rt = sz = 1;
			cntAll = 0;
			rtGO.close();  UserGO.close(); chGO.close();
			return;
		}
		FileOperator.get(UserGO, 0, sz, User + 1);
		FileOperator.get(UserGO, sz * sizeof(int), sz, Train + 1);
		
		int pos = 0;
		for(int i = 1; i <= sz; ++ i) {
			FileOperator.get(chGO, pos, 2, ch[i]);
			pos += sizeof(int) * 2;
		}
		
		for(int i = 1; i <= cntAll; ++ i) {
			FileOperator.get(chGO, pos, 35, Sta[i]);
			pos += sizeof(char) * 35;
		}
		
		for(int i = 1; i < N; ++ i) {
			FileOperator.get(chGO, pos, 35, Tra[i]);
			pos += sizeof(char) * 35;
		}

			
		rtGO.close();  UserGO.close(); chGO.close();
		
	}
	
	~Has() {
		FileOperator.NewFile("rtGO");
		FileOperator.NewFile("UserGO");
		FileOperator.NewFile("chGO");
		rtGO.open("rtGO", ios::binary|ios::out|ios::in);
		UserGO.open("UserGO", ios::binary|ios::out|ios::in);
		chGO.open("chGO", ios::binary|ios::out|ios::in);
		int tmp[3];
		tmp[0] = rt; tmp[1] = sz; tmp[2] = cntAll;
		FileOperator.write(rtGO, 0, 3, tmp);
		FileOperator.write(UserGO, 0, sz, User + 1);
		FileOperator.write(UserGO, sz * sizeof(int), sz, Train + 1);
		
		int pos = 0;
		for(int i = 1; i <= sz; ++ i) {
			FileOperator.write(chGO, pos, 2, ch[i]);
			pos += sizeof(int) * 2;
		}
		
		
		for(int i = 1; i <= cntAll; ++ i) {
			FileOperator.write(chGO, pos, 35, Sta[i]);
			pos += sizeof(char) * 35;
		}
		
		for(int i = 1; i < N; ++ i) {
			FileOperator.write(chGO, pos, 35, Tra[i]);
			pos += sizeof(char) * 35;
		}
				
		rtGO.close(); UserGO.close();chGO.close();
	}
	
	int HashS(char *s) {
		int l = 0, ans = 0;
		l = strlen(s);
		for(int i = 0; i < l; ++ i) {
			ans = 1LL * ans * Base % mod + s[i];
		}
		if(ans >= mod) ans -= mod;
		return ans;
	}
	
	int ConvertToNum(char c) {
		return(int)c;
	}
	
	void addUser(char *s, int user) {
		int x = HashS(s);
		int now = rt;
		for(int i = 0; i < 31; ++ i) {
			int &it = ch[now][(x >> i) & 1];
			if(!it) it = ++ sz;
			now = ch[now][(x >> i) & 1];
		}
		User[now] = user;
	}
	
	void addTrain(char *s, int train) {
		int x = HashS(s);
		int now = rt;
		for(int i = 0; i < 31; ++ i) {
			int &it = ch[now][(x >> i) & 1];
			if(!it) it = ++ sz;
			now = ch[now][(x >> i) & 1];
		}
		Train[now] = train;
		strcpy(Tra[train], s);
	}
	
	int getUser(char *s) {
		int x = HashS(s), now = rt;
		for(int i = 0; i < 31; ++ i) 
		now = ch[now][(x >> i) & 1];
		return User[now];
	}
	
	int getTrain(char *s) {
		int x = HashS(s), now = rt;
		for(int i = 0; i < 31; ++ i) {
			now = ch[now][(x >> i) & 1];
		}
		return Train[now];
	}
	
	int HashStation(char *opt) {
		int now = HashS(opt);
		
		if(!Stations[now]) {
			Stations[now] = ++ cntAll;
			strcpy(Sta[cntAll], opt);
		}
		
		if(strcmp(opt, Sta[Stations[now]])) throw;
		
		return Stations[now];
	}
	
	int QueryStation(char *opt) {
		int now = HashS(opt);
		if(Stations.count(now)) return Stations[now];
		else return 0;
	}
	
	void getStation(int Id, char *opt) {
		strcpy(opt, Sta[Id]);
	}
}IdGetter;

#endif
