#include <stdio.h>
#include <map>
#include <iostream>
#include <string>
using namespace std;
map<int,string> tzolkin_map;
int len = 1000;
int main()
{
	tzolkin_map[1]="imix"; //day begin with 1 number is from 1 to 13 cycle  name is 1 to 20 cycle
    tzolkin_map[2]="ik";
    tzolkin_map[3]="akbal";
    tzolkin_map[4]="kan";
    tzolkin_map[5]="chicchan";
    tzolkin_map[6]="cimi";
    tzolkin_map[7]="manik";
    tzolkin_map[8]="lamat";
    tzolkin_map[9]="muluk";
    tzolkin_map[10]="ok";
    tzolkin_map[11]="chuen";
    tzolkin_map[12]="eb";
    tzolkin_map[13]="ben";
    tzolkin_map[14]="ix";
    tzolkin_map[15]="mem";
    tzolkin_map[16]="cib";
    tzolkin_map[17]="caban";
    tzolkin_map[18]="eznab";
    tzolkin_map[19]="canac";
    tzolkin_map[20]="ahau";

    for(int i=1,k=1,t=1;i<=len;i++,k++,t++)
    {
    	printf("%d %s\n", t, tzolkin_map[k].c_str());
    	if(k==20) k=0;
    	if(t==13) t=0;
    }
	return(0);
}