/*
string is "228899"
int array is {9,9,8,8,2,2}

current version is only for integer not for real
*/
#include<iostream>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#define MAX 300//the BigData's max length
using namespace std;
class BigData
{
private:
    string data_str;
public:
  BigData();
    BigData(string str);
  BigData(int num);
  void print();
  int to_int();
    BigData& operator=(const BigData& big);
    string get_data_str();
  bool operator<(const BigData& big) const;
  bool operator<=(const BigData& big) const;
  bool operator>(const BigData& big) const;
  bool operator>=(const BigData& big) const;
  bool operator==(const BigData& big) const;
  bool operator!=(const BigData& big) const;
  BigData operator+(const BigData& big) const;
  BigData operator-(const BigData& big) const;
  BigData operator*(const BigData& big) const;
  BigData* new_sub(const BigData& big) const;
  BigData operator/(const BigData& big) const;
  BigData operator%(const BigData& big) const;
  BigData& operator+=(const BigData& big);
  BigData& operator-=(const BigData& big);
  BigData& operator*=(const BigData& big);
  BigData& operator/=(const BigData& big);
  BigData& operator%=(const BigData& big);
  friend ostream & operator << (ostream& os, const BigData& big);
  friend istream & operator >> (istream& is, const BigData& big);
};

BigData::BigData()
{
  data_str = "0";
}

BigData::BigData(string str)
{
    data_str = str;
  if (data_str.length() > MAX)
  {
    cerr << "sorry,current version did not support the length of" << data_str.length() << endl;
    exit(1);
  }
}

BigData::BigData(int num)
{
  char num_str[100];
  sprintf(num_str, "%d", num);
  data_str = string(num_str);
}

void BigData::print()
{
  cout << data_str << endl;
}

int BigData::to_int()
{
  int ans = -1;
  if (data_str.length() <= 8)
  {
    ans = atoi(data_str.c_str());
  }
  return(ans);
}

BigData& BigData::operator=(const BigData& big)
{
  this->data_str= string(big.data_str);
  if (data_str.length() > MAX)
  {
    cerr << "sorry,current version did not support the length of" << data_str.length() << endl;
    exit(1);
  }
  return(*this);
}

string BigData::get_data_str()
{
    return(data_str);
}

bool BigData::operator<(const BigData& big) const
{
    string s1 = data_str;
    string s2 = big.data_str;
    if(s1[0]=='-'&&s2[0]!='-') {return true;}
    if(s1[0]!='-'&&s2[0]=='-') {return false;}
    if(s1[0]!='-'&&s2[0]!='-')
    {
        if(s1.length()>s2.length()) {return false;}
        else if(s1.length()<s2.length()) {return true;}
        else
        {
      for (int i = 0; i <= (int)s1.length() - 1; i++)
            {
                if(s1[i]<s2[i]) {return true;}
                else if(s1[i]>s2[i]) {return false;}
            }
            return(false);
        }
    }
    if(s1[0]=='-'&&s2[0]=='-')
    {
        if(s1.length()>s2.length()) {return true;}
        else if(s1.length()<s2.length()) {return false;}
        else
        {
      for (int i = 0; i <= (int)s1.length() - 1; i++)
            {
                if(s1[i]<s2[i]) {return false;}
                else if(s1[i]>s2[i]) {return true;}
            }
            return(false);
        }
    }
  return(false);
}

bool BigData::operator<=(const BigData& big) const
{
    if(*this < big || *this == big) return true;
    else return false;
}

bool BigData::operator>(const BigData& big) const 
{
    if(*this < big) return false;
    else if(*this == big) return false;
    else return true;
}

bool BigData::operator>=(const BigData& big) const
{
    if(*this > big || *this == big) return true;
    else return false;
}

bool BigData::operator==(const BigData& big) const
{
    string s1 = data_str;
    string s2 = big.data_str;
    if(s1 == s2) {return true;}
    else {return false;}
}

bool BigData::operator!=(const BigData& big) const
{
    if(*this == big) return(false);
    else return(true);
}

BigData BigData::operator+(const BigData& big) const
{
    BigData zero = BigData("0");
    if(*this >= zero && big >= zero)
    {
        string s1 = string(data_str);
        string s2 = string(big.data_str);
        //get int arr
        int int_arr1[MAX],int_arr2[MAX],int_arr3[MAX];
        for (int i = 0; i <= MAX - 1; i++) { int_arr1[i] = int_arr2[i] = int_arr3[i] = 0; }
        int len_s1=(int)s1.length();
        int len_s2=(int)s2.length();
        int len_s3=len_s1>len_s2 ? len_s1 : len_s2;
        for(int i=len_s1-1,j=0;i>=0;i--,j++) {int_arr1[j]=s1[i]-'0';}
        int_arr1[len_s1]=0;
        for(int i=len_s2-1,j=0;i>=0;i--,j++) {int_arr2[j]=s2[i]-'0';}
        int_arr2[len_s2]=0;
        int carry=0,result=0;
        for(int i=0;i<=len_s3-1;i++)
        {
            result=carry+int_arr1[i]+int_arr2[i];
            carry=result/10;
            int_arr3[i]=result%10;
        }
        if(carry>0)
        {
            int_arr3[len_s3]=carry;
            len_s3++;
        }
        char * char_arr = new char[len_s3 + 10];
        for(int i=len_s3-1,j=0;i>=0;i--,j++) {char_arr[j]=int_arr3[i]+'0';}
        char_arr[len_s3]='\0';
        string s3 = string(char_arr);
        //BigData new_big = BigData(s3);
        BigData * new_p = new BigData(s3);
        return(*new_p);
    }
    else if(*this < zero && big < zero)
    {
        BigData new_this = zero - *this;
        BigData new_big = zero - big;
        BigData res = new_this + new_big;
        res = zero - res;
        return(res);
    }
    else if(*this >= zero)// big < zero
    {
        BigData new_big = zero - big;
        BigData res = *this - new_big;
        return(res);
    }
    else if(big >= zero)//*this  < zero
    {
        BigData new_this = zero - *this;
        BigData res = big - new_this;
        return(res);
    }
    else
    {
        BigData err = BigData("err!!");
        return(err);
    }
}

BigData BigData::operator-(const BigData& big) const
{
    BigData zero = BigData("0");
    if(*this >= zero && big >= zero)
    {
        if(*this > big)
        {
            string s1 = string(data_str);
            string s2 = string(big.data_str);
            //get int arr
            int int_arr1[MAX],int_arr2[MAX],int_arr3[MAX];
      for (int i = 0; i <= MAX - 1; i++) { int_arr1[i] = int_arr2[i] = int_arr3[i] = 0; }
            int len_s1=(int)s1.length();
            int len_s2=(int)s2.length();
            int len_s3=len_s1>len_s2 ? len_s1 : len_s2;//not must be this value
            for(int i=len_s1-1,j=0;i>=0;i--,j++) {int_arr1[j]=s1[i]-'0';}
            int_arr1[len_s1]=0;
            for(int i=len_s2-1,j=0;i>=0;i--,j++) {int_arr2[j]=s2[i]-'0';}
            int_arr2[len_s2]=0;
            for(int i=0;i<=len_s3-1;i++)//from low bit to high bit
            {
                if(int_arr1[i]<int_arr2[i])//borrow 1 bit from higher bit
                {
                    int j=0;
                    for(j=i+1;j<=len_s3-1;j++)
                    {
                        if(int_arr1[j]>0)
                        {
                            break;
                        }
                    }
                    int_arr1[j]--;//borrow 1 bit
                    for(int k=j-1;k>=i+1;k--)//if it has 0 bit during find high bit , this 0 bit will be 9 bit
                    {
                        if(int_arr1[k]==0)
                        {
                            int_arr1[k]=9;
                        }
                    }
                    int_arr3[i]=10+int_arr1[i]-int_arr2[i];//sub the current bit
                }
                else
                {
                    int_arr3[i]=int_arr1[i]-int_arr2[i];
                }
            }
            char * char_arr = new char[len_s3 + 10];
            int i=0;
            for(i=len_s3-1;i>=0;i--) {if(int_arr3[i]>0) {len_s3=i+1; break;}}//111111 - 111110 = 1
            if(i<0) {len_s3=1;}
            for(int i=len_s3-1,j=0;i>=0;i--,j++) {char_arr[j]=int_arr3[i]+'0';}
            char_arr[len_s3]='\0';
            string s3 = string(char_arr);
            BigData new_big = BigData(s3);
            return(new_big);
        }
        else if(*this < big)
        {
            if(*this == zero)
            {
                string ss = string(big.data_str);
                string res_ss = "-" + ss;
                BigData res = BigData(res_ss);
                return(res);
            }
            else
            {
                BigData new_big = big - *this;
                new_big = zero - new_big;
                return(new_big);
            }
        }
        else
        {
            return(zero);
        }
    }
    else if(*this < zero && big < zero)
    {
        BigData new_this = zero - *this;
        BigData new_big = zero - big;
        BigData res = new_big - new_this;
    return(res);
    }
    else if(*this >= zero)//big < zero
    {
        if(*this == zero)
        {
            string str_big = string(big.data_str);
            string res_ss = str_big.substr(1,str_big.length()-1);
            BigData res = BigData(res_ss);
            return(res);
        }
        else
        {
            BigData new_big = zero - big;
            BigData res = *this + new_big;
            return(res);
        }
    }
    else if(big >= zero)
    {
        BigData new_this = zero -*this;
        BigData res = new_this + big;
        res = zero - res;
        return(res);
    }
    else
    {
        BigData err = BigData("err!!");
        return(err);
    }
}

BigData BigData::operator*(const BigData& big) const
{
    BigData zero = BigData("0");
    if(*this > zero && big > zero)
    {
        string s1 = string(data_str);
        string s2 = string(big.data_str);
        //get int arr
        int int_arr1[MAX],int_arr2[MAX],int_arr3[MAX];
        for (int i = 0; i <= MAX - 1; i++) { int_arr1[i] = int_arr2[i] = int_arr3[i] = 0; }
        int len_s1=(int)s1.length();
        int len_s2=(int)s2.length();
        int len_s3=len_s1+len_s2-1;//may not be current
        for(int i=len_s1-1,j=0;i>=0;i--,j++) {int_arr1[j]=s1[i]-'0';}
        int_arr1[len_s1]=0;
        for(int i=len_s2-1,j=0;i>=0;i--,j++) {int_arr2[j]=s2[i]-'0';}
        int_arr2[len_s2]=0;
        int carry=0,result=0;
        int carry_arr3=0,result_arr3=0;
        int i=0,j=0;
        for(j=0;j<=len_s2-1;j++)
        {
            for(i=0;i<=len_s1-1;i++)
            {
                result=carry+int_arr2[j]*int_arr1[i];
                carry=result/10;
                result=result%10;
                result_arr3=carry_arr3+int_arr3[i+j]+result;
                carry_arr3=result_arr3/10;
                result_arr3=result_arr3%10;
                int_arr3[i+j]=result_arr3;
            }
            //deal with carry or carry_arr3 cases
            result=carry;
            result_arr3=carry_arr3+int_arr3[i+j]+result;
            carry_arr3=result_arr3/10;
            result_arr3=result_arr3%10;
            int_arr3[i+j]=result_arr3;
            carry=0;
            //deal with carry_arr3 cases
            result=carry;
            result_arr3=carry_arr3+int_arr3[i+j]+result;
            carry_arr3=result_arr3/10;
            result_arr3=result_arr3%10;
            int_arr3[i+j]=result_arr3;
            carry_arr3=0;
        }
        if(int_arr3[len_s1+len_s2-1]>0) {len_s3=len_s1+len_s2;}
        else {len_s3=len_s1+len_s2-1;}
        char * char_arr = new char[len_s3 + 10];
        for(int i=len_s3-1,j=0;i>=0;i--,j++) {char_arr[j]=int_arr3[i]+'0';}
        char_arr[len_s3]='\0';
        string s3 = string(char_arr);
        BigData new_big = BigData(s3);
        return(new_big);
    }
  else if (*this < zero && big < zero)
  {
    BigData new_this = zero - *this;
    BigData new_big = zero - big;
    BigData res = new_this * new_big;
    return(res);
  }
    else if(*this == zero || big ==zero)
    {
        return(zero);
    }
    else if(*this < zero)//big > zero
    {
        BigData new_this = zero - *this;
        BigData res = new_this * big;
        res = zero - res;
        return(zero);
    }
    else if(big < zero)//*this > zero
    {
        BigData new_big = zero - big;
        BigData res = *this * new_big;
        res = zero - res;
        return(zero);
    }
    else
    {
        BigData err = BigData("err!!");
        return(err);
    }
}
//return the list of the BigData, first is quotinet ,the second is remainder, this is new_sub function, will be use to operator/ and operator%
BigData* BigData::new_sub(const BigData& big) const
{
  BigData * ans_list = new BigData[2];
  BigData zero = BigData("0");
  if (*this > zero && big > zero)
  {
    //construct divisor and dividend
    BigData dived_num = BigData(data_str);
    BigData div_num = BigData(big.data_str);
    BigData quo_num = BigData("0");//summation
    BigData rem_num = BigData("0");
    string s1, s2, s3, s4;//s1 is dived  s2 is div  s3 is result s4 is remainder
    while (div_num <= dived_num)
    {
      s1 = string(dived_num.get_data_str());
      s2 = string(div_num.get_data_str());
      int bit_len = s1.length() - s2.length();
      int bit_num = 1;//1 * (10 ^ bit_len)
      string by_str = "1";//s2 * by_str  compare with s1
      for (int i = 1; i <= bit_len; i++){by_str += "0";}
      BigData by_num = BigData(by_str);
      if (div_num * by_num < dived_num)
      {
        bit_num = 9;
        by_str = "9";
        for (int i = 1; i <= bit_len; i++){ by_str += "0"; }
        by_num = BigData(by_str);// div * by_num must > dived_nums
      }
      while (div_num * by_num > dived_num)
      {
        bit_num--;
        if (bit_num == 0)
        {
          bit_num = 9;
          bit_len--;
          if (bit_len < 0){ bit_len = 0; }
        }
        char cstr[2];
        cstr[0] = bit_num + 48;
        cstr[1] = '\0';
        by_str = string(cstr);
        for (int i = 1; i <= bit_len; i++){ by_str += "0"; }
        by_num = BigData(by_str);
      }
      dived_num = dived_num - (div_num * by_num);//div_num * by_num <= dived_num, dived_num = dived_num - (div_num * by_num)
      quo_num = quo_num + by_num;//record the quotient
    }
    //dived_num < div_num,make it to the remainder
    rem_num = dived_num;
    ans_list[0] = quo_num;
    ans_list[1] = rem_num;
    return(ans_list);
  }
  else if (*this < zero && big < zero)
  {
    BigData new_this = zero - *this;
    BigData new_big = zero - big;
    BigData* res = new_this.new_sub( new_big);
    return(res);
  }
  else if (big == zero)
  {
    //throw exception("error divide zero");
    return(NULL);
  }
  else if (*this == zero)
  {
    ans_list[0] = zero;
    ans_list[1] = zero;
    return(ans_list);
  }
  else if (*this < zero)//big > zero
  {
    BigData new_this = zero - *this;
    BigData * res = new_this.new_sub(big);
    res[0] = zero - res[0];
    return(res);
  }
  else if (big < zero)//*this  > zero
  {
    BigData new_big = zero - big;
    BigData * res = new_sub(new_big);
    res[0] = zero - res[0];
    return(res);
  }
  else//error
  {
    BigData err = BigData("err!!");
    return(NULL);
  }
}
//integer's divede not save the remainder
BigData BigData::operator/(const BigData& big) const
{
  BigData * ans = new_sub(big);
  BigData quo_num = ans[0];
  return(quo_num);
}

BigData BigData::operator%(const BigData& big) const
{
  BigData * ans = new_sub(big);
  BigData rem_num = ans[1];
  return(rem_num);
}

BigData& BigData::operator+=(const BigData& big) 
{
  (*this) = (*this) + big;
  return(*this);
}

BigData& BigData::operator-=(const BigData& big) 
{
  (*this) = (*this) - big;
  return(*this);
}

BigData& BigData::operator*=(const BigData& big) 
{ 
  (*this) = (*this) * big;
  return(*this);
}

BigData& BigData::operator/=(const BigData& big) 
{
  (*this) = (*this) / big;
  return(*this);
}

BigData& BigData::operator%=(const BigData& big) 
{
  (*this) = (*this) % big;
  return(*this);
}

ostream& operator <<(ostream& os, const BigData& big)
{
  os << big.data_str;
  return(os);
}

istream& operator >>(istream& is, const BigData& big)
{
  is >> big.data_str;
  if (!is)
  {
    cerr << "incurrent input!" << endl;
  }
  return(is);
}
#include<stdio.h>
#include<string.h>
#include<string>
using namespace std;
#define CL 22
char in_str[100];
int main()
{
    while(scanf("%s",in_str)!=EOF&&in_str[0]!='*')
    {
        int len = strlen(in_str);
        string strs = "";//output string
		BigData sum = BigData("0");//output number
		BigData add_num = BigData("0");
		BigData by_num = BigData("1");
		BigData bit_num = BigData("26");
		if (in_str[0] >= '0' && in_str[0] <= '9')//number to string
		{
			sum = BigData(string(in_str));
			char temp_str[100];
			int temp_len = 0;
			BigData zero = BigData("0");
			BigData tsum = BigData(sum);
			while (tsum >= bit_num)
			{
				BigData rem_num = tsum % bit_num;
				tsum /= bit_num;
				if(rem_num == zero) tsum-=BigData("1");
				temp_str[temp_len++] = rem_num.to_int() - 1 + 'a';
			}
			if(tsum > zero)
            {
                temp_str[temp_len++] = tsum.to_int() - 1 + 'a';
            }
            char reverse_str[100];
            for(int i=0,j=temp_len-1;j>=0;j--,i++)
            {
                reverse_str[i] = temp_str[j];
            }
            reverse_str[temp_len] = '\0';
            strs = string(reverse_str);
		}
		else//string to number
		{
			int char_rank = in_str[len - 1] - 'a' + 1;
			add_num = BigData(char_rank);
			sum += add_num;
			for (int i = len - 2; i >= 0; i--)
			{
				char_rank = in_str[i] - 'a' + 1;
				by_num *= bit_num;
				add_num = BigData(char_rank) * by_num;
				sum += add_num;
			}
			strs = string(in_str);
		}
		printf("%s",strs.c_str());
		for(int i=1;i<=CL-(int)strs.length();i++) printf(" ");
		string ostr = string(sum.get_data_str());
		int first_len=ostr.length()%3;
		if(first_len==0) first_len=3;
		int i=0;
		for(i=0;i<=first_len-1;i++) printf("%c",ostr[i]);
		for(;i<=(int)ostr.length()-1;i+=3) printf(",%c%c%c",ostr[i],ostr[i+1],ostr[i+2]);
		printf("\n");
    }
    return(0);
}
