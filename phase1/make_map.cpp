#include<bits/stdc++.h>
#include "machine_conv.h"
#include "make_map.h"
using namespace std;


make_map:: make_map(){}


string make_map:: bin_to_hex(string sBinary) //copied from stack overflow
{
	string rest("0x"),tmp;
	int len = sBinary.length()/4;
	for (int i=0;i<sBinary.length();i+=4)
	{
		tmp = sBinary.substr(i,4);
		if (!tmp.compare("0000")){rest = rest + "0";}
		else if (!tmp.compare("0001")){rest = rest + "1";}
		else if (!tmp.compare("0010")){rest = rest + "2";}
		else if (!tmp.compare("0011")){rest = rest + "3";}
		else if (!tmp.compare("0100")){rest = rest + "4";}
		else if (!tmp.compare("0101")){rest = rest + "5";}
		else if (!tmp.compare("0110")){rest = rest + "6";}
		else if (!tmp.compare("0111")){rest = rest + "7";}
		else if (!tmp.compare("1000")){rest = rest + "8";}
		else if (!tmp.compare("1001")){rest = rest + "9";}
		else if (!tmp.compare("1010")){rest = rest + "A";}
		else if (!tmp.compare("1011")){rest = rest + "B";}
		else if (!tmp.compare("1100")){rest = rest + "C";}
		else if (!tmp.compare("1101")){rest = rest + "D";}
		else if (!tmp.compare("1110")){rest = rest + "E";}
		else if (!tmp.compare("1111")){rest = rest + "F";}
		else{continue;}
	}
	return rest;
}


string make_map:: reg_to_binary(string s) // eg: x9 => "1001"
{
	int s2;
	if(s.length()==2)
	{
		s2=int(s[1])-48;
	}
	else if(s.length()==3 && s[1]>='0' && s[1]<='9')
	{
		s2=int(s[1])-48;
		s2=s2*10;
		s2=s2+int(s[2])-48;
	}
	bitset<5> res(s2);
	return res.to_string();
}


/*for R type*/
string make_map:: funcR(string ins_name, string rd,string rs1,string rs2)
{
	string opcode = mopcode.find(ins_name)->second;
	string func3 = mfunc3.find(ins_name)->second;
	string func7 = mfunc7.find(ins_name)->second;
	string s2 = reg_to_binary(rs2);
	string s1 = reg_to_binary(rs1);
	string des = reg_to_binary(rd);
	string result = func7;
	result.append(s2);
	result.append(s1);
	result.append(func3);
	result.append(des);
	result.append(opcode);
	result = bin_to_hex(result);
	return result;
}

/*for I type*/
string make_map:: funcI(string ins_name,string rd,string rs1,int imm)
{
	string opcode = mopcode.find(ins_name)->second;
	string func3 = mfunc3.find(ins_name)->second;
	string des = reg_to_binary(rd);
	string s1 = reg_to_binary(rs1);
	bitset<12> res(imm);
	string imm1 = res.to_string();
	string result = imm1;
	result.append(s1);
	result.append(func3);
	result.append(des);
	result.append(opcode);
	result = bin_to_hex(result);
	return result;
}

/*for S type*/
string make_map:: funcS(string ins_name,string rs2,string rs1,int imm)
{
	string opcode = mopcode.find(ins_name)->second;
	string func3 = mfunc3.find(ins_name)->second;
	string s2 = reg_to_binary(rs2);
	string s1 = reg_to_binary(rs1);
	bitset<12> res(imm);
	string imm1 = res.to_string();
	string leftimm=imm1.substr(0, 7);// 0 to 6
	string rightimm=imm1.substr(7, 5);//7 to 11
	string result = leftimm;
	result.append(s2);
	result.append(s1);
	result.append(func3);
	result.append(rightimm);
	result.append(opcode);
	result = bin_to_hex(result);
	return result;
}

/*for SB type*/
string make_map:: funcSB(string ins_name,string rs1,string rs2,int imm)
{
	string opcode = mopcode.find(ins_name)->second;
	string func3 = mfunc3.find(ins_name)->second;
	string s2 = reg_to_binary(rs2);
	string s1 = reg_to_binary(rs1);
	//to make imm of 13 bit and discard LSB of imm
	bitset<13> res(imm);
	string imm1 = res.to_string();
	string leftimm1=imm1.substr(0, 1),leftimm2=imm1.substr(2, 6);// 0 and 2 to 7 =>12|10:5
	string rightimm1=imm1.substr(8, 4),rightimm2=imm1.substr(1, 1);//8 to 11 and 1 =>4:1|11
	string result = leftimm1;
	result.append(leftimm2);
	result.append(s2);
	result.append(s1);
	result.append(func3);
	result.append(rightimm1);
	result.append(rightimm2);
	result.append(opcode);
	result = bin_to_hex(result);
	return result;
}

/*for U type*/
string make_map:: funcU(string ins_name,string rd,int imm)
{
	string opcode = mopcode.find(ins_name)->second;
	string des = reg_to_binary(rd);
	bitset<20> res(imm);
	string imm1 = res.to_string();
	string result = imm1;
	result.append(des);
	result.append(opcode);
	result = bin_to_hex(result);
	return result;
}

/*for UJ type*/
string make_map:: funcUJ(string ins_name,string rd,int imm)
{
	string opcode = mopcode.find(ins_name)->second;
	string des = reg_to_binary(rd);
	//to make imm of 21 bit and discard LSB of imm
	bitset<21> res(imm);
	string imm1 = res.to_string();
	string first=imm1.substr(0, 1),second=imm1.substr(10, 10);// 0 and 10 to 19 =>20|10:1
	string third=imm1.substr(9, 1),fourth=imm1.substr(1, 8);// 9 and 1 to 8 =>11|19:12
	string result = first;
	result.append(second);
	result.append(third);
	result.append(fourth);
	result.append(des);
	result.append(opcode);
	result = bin_to_hex(result);
	return result;
}

void make_map:: create_map()
{
	/*for R type*/
	ifstream Rfp("R_instructions.txt",ios::in);
	string ins_name,rs2,rs1,rd,f7,f3,opcode,type;
	int imm;
	if(!Rfp)
		cout<<"R_instructions txt not readed"<<endl;
	else
	{
		while(Rfp>>ins_name>>opcode>>f3>>f7)
		{
			type="R";
			mtype.insert( pair<string,string>(ins_name,type) );
			mopcode.insert( pair<string,string>(ins_name,opcode) );
			mfunc7.insert( pair<string,string>(ins_name,f7) );
			mfunc3.insert( pair<string,string>(ins_name,f3) );
		}
	}
	Rfp.close();

	/*for I type*/
	ifstream Ifp("I_instructions.txt",ios::in);
	if(!Ifp)
		cout<<"I_instructions txt not readed"<<endl;
	else
	{
		while(Ifp>>ins_name>>opcode>>f3)
		{
			type="I";
			mtype.insert( pair<string,string>(ins_name,type) );
			mopcode.insert( pair<string,string>(ins_name,opcode) );
			mfunc3.insert( pair<string,string>(ins_name,f3) );
		}
	}
	Ifp.close();

	/*for S type*/
	ifstream Sfp("S_instructions.txt",ios::in);
	if(!Sfp)
		cout<<"S_instructions txt not readed"<<endl;
	else
	{
		while(Sfp>>ins_name>>opcode>>f3)
		{
			type="S";
			mtype.insert( pair<string,string>(ins_name,type) );
			mopcode.insert( pair<string,string>(ins_name,opcode) );
			mfunc3.insert( pair<string,string>(ins_name,f3) );
		}
	}
	Sfp.close();

	/*for SB type*/
	ifstream SBfp("SB_instructions.txt",ios::in);
	if(!SBfp)
		cout<<"SB_instructions txt not readed"<<endl;
	else
	{
		while(SBfp>>ins_name>>opcode>>f3)
		{
			type="SB";
			mtype.insert( pair<string,string>(ins_name,type) );
			mopcode.insert( pair<string,string>(ins_name,opcode) );
			mfunc3.insert( pair<string,string>(ins_name,f3) );
		}
	}
	SBfp.close();

	/*for U type*/
	ifstream Ufp("U_instructions.txt",ios::in);
	if(!Ufp)
		cout<<"U_instructions txt not readed"<<endl;
	else
	{
		while(Ufp>>ins_name>>opcode)
		{
			type="U";
			mtype.insert( pair<string,string>(ins_name,type) );
			mopcode.insert( pair<string,string>(ins_name,opcode) );
		}
	}
	Ufp.close();

	/*for UJ type*/
	ifstream UJfp("UJ_instructions.txt",ios::in);
	if(!UJfp)
		cout<<"UJ_instructions txt not readed"<<endl;
	else
	{
		while(UJfp>>ins_name>>opcode)
		{
			type="UJ";
			mtype.insert( pair<string,string>(ins_name,type) );
			mopcode.insert( pair<string,string>(ins_name,opcode) );
		}
	}
	UJfp.close();

}

make_map:: ~make_map(){}