#ifndef MAKE_MAP_H
#define MAKE_MAP_H

#include<bits/stdc++.h>
using namespace std;

class make_map
{
	
	public:
		map<string,string> mtype; //for determining format(R,S,I,SB,U,UJ)
		map<string,string> mopcode;
		map<string,string> mfunc3;
		map<string,string> mfunc7;
		make_map();
		void create_map();
		string bin_to_hex(string sBinary);
		string reg_to_binary(string s);
		string funcR(string ins_name, string rd,string rs1,string rs2);
		string funcI(string ins_name,string rd,string rs1,int imm);
		string funcS(string ins_name,string rs2,string rs1,int imm);
		string funcSB(string ins_name,string rs1,string rs2,int imm);
		string funcU(string ins_name,string rd,int imm);
		string funcUJ(string ins_name,string rd,int imm);
		~make_map();
};
#endif