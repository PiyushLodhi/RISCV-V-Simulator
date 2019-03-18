#include <bits/stdc++.h>
using namespace std;

int RA,RB, signal_memoryaccess=0;
	// signal_memoryaccess = 0 if memmory is not to be accessed else 1
long long int register_file[10000];

int set_signal(int opcode,int funct3,int funct7)
{
	if(opcode == 51 || opcode == 59)
	{
		signal_memoryaccess = 0;
		if(funct7 == 0)
		{
			if(funct3 == 0)
				return 1;
			else if(funct3 == 1)
				return 7;
			else if(funct3 == 2)
				return 5;
			else if(funct3 == 3)
				return 12;
			else if(funct3 == 4)
				return 10;
			else if(funct3 == 5)
				return 6;
			else if(funct3 == 6)
				return 9;
			else if(funct3 == 7)
				return 8;
		}
		else if(funct7 == 32)
		{
			if(funct3 == 0)
				return 2;
			else if(funct3 == 5)
				return 13;
		}
		else if(funct7==1)
		{
			if(funct3==0)
				return 4;
			else if(funct3==4)
				return 3;
		}
	}
	else if(opcode == 3)
	{
		signal_memoryaccess = 1;
		return 0;
	}

	else if(opcode == 19 || opcode == 27)
	{
		if(funct3 == 0)
			return 1;
		else if(funct3 == 1)
			return 7;
		else if(funct3 == 2)
			return 5;
		else if(funct3 == 3)
			return 12;
		else if(funct3 == 4)
			return 10;
		else if(funct3 == 6)
			return 9;
		else if(funct3 == 7)
			return 8;
		else if(funct3 == 5 && funct7 == 0)
			return 6;
		else if(funct3 == 5 && funct7 == 32)
			return 13;
	}

	else if(opcode == 35)
	{
		signal_memoryaccess = 1;
		return 1;
	}

	else if(opcode == 99)
	{
		if(funct3 == 0 || funct3 == 1 || funct3 == 2 || funct3 == 5)
			return 5;
		else if(funct3 == 6 || funct3 == 7)
			return 12;
	}

	else if(opcode == 103)
	{
		signal_memoryaccess = 1;
		return 1;
	}

	return 0;
}

int bintodec(string s)
{
	int value=0,index=0,i;
	for(i=s.length()-1;i>=0;i--)
	{
		if(s[i] == '1')
			value += pow(2,index);
		index++;
	}
	return value;
}

string hextobin(string inst)
{
     stringstream ss;
     ss << hex << inst;
     unsigned n;
     ss >> n;
     bitset<32> b(n);
     string s = b.to_string();
     return s;
}

int main()
{
	register_file[0]=0;
	vector<string> program_counter;
	vector<string> instructions_hexa;
	vector<string> instructions_bin;
	vector<int> program_counter_deci;
	string s1,s2;
	ifstream input("phase1.txt");
	while(input>>s1>>s2)
	{
	   
	     cout<<s1<<" "<<s2<<endl;
	     if((s1[0] == '\0') || (s2[0] == '\0'))
	     break;
	     program_counter.push_back(s1);
	     instructions_hexa.push_back(s2);
	}

	for(int i=0;i<program_counter.size();i++)
	{
		string s = hextobin(instructions_hexa[i]);
		//cout<<s<<endl;
		instructions_bin.push_back(s);			//array of instruction  in binary string form
		string s1 = hextobin(program_counter[i]);
		int a = bintodec(s1);
		//cout<<a<<endl;
		program_counter_deci.push_back(a);		//array of program counter in decimal form
	}

/*-----------------------------------------------*/
	int k=0;
	while(k<instructions_bin.size())
	{
	string test_inst = instructions_bin[k];	

	string op_str,rd_str,funct3_str,rs1_str,rs2_str,funct7_str,immi_s_sb_str,immu_str,immuj_str;
	op_str = test_inst.substr(25,31);
	//cout<<op_str<<endl;
	int opcode,rd,funct3,rs1,rs2,funct7,immi_s_sb,immu,immuj;
	opcode = bintodec(op_str);		//opcode in decimal form

	int ALU_input1,ALU_input2;		//ALU inputs
	int  signal_ALU = 0;
	/*
		0. Default NOthing to do.
		1. Add
		2. Subtract
		3. Divide
		4. Multiply
		5. Compare (Set result value:- -1 for input1 < input2; 1 for input1 > input2; 2 for input1 = input2)
		6. Shift bits right
		7. Shift bits left
		8. AND
		9. OR
		10. XOR
		11. NOT
		12. Unsigned comparison
		13. Arithmetic Shift Right
	*/
	
	if(opcode == 51 || opcode == 59) //R
	{
		rd_str = test_inst.substr(20,5);
		rs1_str = test_inst.substr(12,5);
		rs2_str = test_inst.substr(7,5);
		funct7_str = test_inst.substr(0,7);
		funct3_str = test_inst.substr(17,3);

		rd = bintodec(rd_str);
		funct3 = bintodec(funct3_str);
		rs1 = bintodec(rs1_str);
		rs2 = bintodec(rs2_str);
		funct7 = bintodec(funct7_str);

		RA = rs1;
		RB = rs2;
		ALU_input1 = RA;
		ALU_input2 = RB;
	//	cout<<funct3<<" "<<funct7<<" "<<RA<<" "<<RB<<endl;
		signal_ALU = set_signal(opcode,funct3,funct7);		//arithmetic operator
	
	}

	else if(opcode == 3 || opcode == 15 || opcode == 19 || opcode == 27 || opcode == 103)//I
	{
		rd_str = test_inst.substr(20,5);
		funct3_str = test_inst.substr(17,3);
		rs1_str = test_inst.substr(12,5);
		immi_s_sb_str = test_inst.substr(0,12);

		rd = bintodec(rd_str);
		funct3 = bintodec(funct3_str);
		rs1 = bintodec(rs1_str);
		immi_s_sb = bintodec(immi_s_sb_str);

		RA = rs1;
		ALU_input2 = immi_s_sb;
		ALU_input1 = RA;
	//	cout<<funct3<<" "<<funct7<<" "<<RA<<" "<<immi_s_sb<<endl;
		signal_ALU = set_signal(opcode,funct3,funct7);		//arithmetic operator

	}

	else if(opcode == 35)//S
	{
		funct3_str = test_inst.substr(17,3);
		rs1_str = test_inst.substr(12,5);
		rs2_str = test_inst.substr(7,5);
		string temp,temp1;
		temp = test_inst.substr(20,5);
		temp1 = test_inst.substr(0,7);
		immi_s_sb_str = temp1 + temp;

		funct3 = bintodec(funct3_str);
		rs1 = bintodec(rs1_str);
		rs2 = bintodec(rs2_str);
		immi_s_sb = bintodec(immi_s_sb_str);

		RB = rs2;
		RA = rs1;
		ALU_input1 = RA;
		ALU_input2 = immi_s_sb;
		signal_ALU = set_signal(opcode,funct3,funct7);		//arithmetic operator
	}

	else if(opcode == 99)//SB
	{
		funct3_str = test_inst.substr(17,3);
		rs1_str = test_inst.substr(12,5);
		rs2_str = test_inst.substr(7,5);

		string temp,temp1,temp2,temp3;
		temp = test_inst.substr(0,1);
		temp1 = test_inst.substr(1,6);
		temp2 = test_inst.substr(24,1);
		temp3 = test_inst.substr(20,4);
		immi_s_sb_str = temp + temp2 + temp1 + temp3;

		funct3 = bintodec(funct3_str);
		rs1 = bintodec(rs1_str);
		rs2 = bintodec(rs2_str);
		immi_s_sb = bintodec(immi_s_sb_str);

		RA = rs1;
		RB = rs2;
		ALU_input1 = RA;
		ALU_input2 = RB;
		signal_ALU = set_signal(opcode,funct3,funct7);		//arithmetic operator
	}

	else if(opcode == 55)//U
	{
		rd_str = test_inst.substr(20,5);
		immu_str = test_inst.substr(0,20);

		rd = bintodec(rd_str);
		immu = bintodec(immu_str);
		immu *= 4096;
		signal_memoryaccess = 1;		//access to memory
	}

	else if(opcode == 111)//UJ
	{
		rd_str = test_inst.substr(20,5);
		string temp,temp1,temp2,temp3;
		temp = test_inst.substr(0,1);
		temp1 = test_inst.substr(1,10);
		temp2 = test_inst.substr(11,1);
		temp3 = test_inst.substr(12,8);
		immuj_str = temp + temp3 + temp2 + temp1;

		rd = bintodec(rd_str);
		immuj = bintodec(immuj_str);
		signal_ALU = set_signal(opcode,funct3,funct7);		//arithmetic operator
	}
	cout<<opcode<<" "<<ALU_input1<<" "<<ALU_input2<<" "<<signal_ALU<<endl;
	k++;
	}
}
