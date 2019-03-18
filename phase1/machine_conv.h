#ifndef MACHINE_CONV_H
#define MACHINE_CONV_H

#include<bits/stdc++.h>
#include "make_map.h"
#include "original_to_basic.h"
using namespace std;

class machinecode : public make_map
{
	string rs1,rs2,rd;
	int imm;
    
	public:
		machinecode();
		void conv_to_mac_code(make_map );
		string discard_zeroes(int);
		~machinecode();
};
#endif