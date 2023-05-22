//Yang Zhang 22.05.2023

#include "rational.h"
#include <iostream>

void integer::init(long long int number)
{
    //test the positivity
    if(number<0){
        positivity=false;
        number*=-1;
    }else{
        positivity=true;
    }

    //transfer into data
    data.clear();
    while(number!=0){
        data.push_back(number % 256);
        number /=256;
    }
}

void integer::init(std::string hex_number)
{
    //if the first char is negative sign then delete it and set positivity to be false
    positivity=true;
    if(hex_number[0]=='-'){
        positivity=false;
        hex_number.erase(0,1);
    }

    //if the length is odd then add a 0 in front
    if(hex_number.length() %2)  hex_number="0"+hex_number;

    //convert to array of unsigned char
    data.clear();
    for(int i=hex_number.length()-1;i>=0;i-=2){
        //change the char in every entry into right hex number
        unsigned char temp1;
        if(hex_number[i]>='0' && hex_number[i]<='9'){
            temp1=hex_number[i]-'0';
        }else{
            temp1=hex_number[i]-'a'+10;
        }

        unsigned char temp2;
        if(hex_number[i-1]>='0' && hex_number[i-1]<='9'){
            temp2=hex_number[i-1]-'0';
        }else{
            temp2=hex_number[i-1]-'a'+10;
        }

        //convert to the entry of the integer
        data.push_back(temp2*16+temp1);
    }

    //in case one inputs 000123, or similar numbers with 0 in front
    for(int i=data.size()-1;i>=0;i--){
        if(data[i]==0)  data.pop_back();
    }
    //in case one inputs -000000 and we get nothing in data but false positivity at last
    if(data.empty())    positivity=true;
}

void integer::init(integer a)
{
    positivity=a.is_positive();
    data=a.get_data();
}

//-------------------------------------------------------------------
std::vector<unsigned char> integer::get_data(void)
{
    return data;
}

bool integer::is_positive(void)
{
    return positivity;
}

//-------------------------------------------------------------------
void integer::print_hex(void)
{   
    //print negative sign
    if(!positivity) std::cout<<"-";

    //two temp digits
    unsigned char temp1,temp2;           

    //if is zero, print zero
    if(data.size()==0)  std::cout<<'0';

    //print every digit in hex
    for(int i=data.size()-1;i>=0;i--){
        temp1=data[i]/16;
        temp2=data[i]%16;
        if(temp1<10){
            temp1+='0';
        }else{
            temp1=temp1-10+'a';
        }
        if(temp2<10){
            temp2+='0';
        }else{
            temp2=temp2-10+'a';
        }

        //in case the first digit is 0
        if(i==data.size()-1 and temp1=='0'){
            std::cout<<temp2;
        }else{
            std::cout<<temp1<<temp2;
        }
    }
}

void integer::negate_self(void)
{
    positivity=!positivity;
}

void integer::absolute_value_self(void)
{
    positivity=true;
}

integer integer::negation(void)
{
    integer ans;
    ans.init(*this);
    ans.negate_self();
    return ans;
}

integer integer::absolute_value(void)
{
    integer ans;
    ans.init(*this);
    ans.absolute_value_self();
    return ans;
}


//-------------------------------------------------------------------
bool integer::larger_than(integer a)
{

    //this>=0, a<0
    if(positivity && !a.is_positive())  return true;

    //this<0, a>0
    if( !positivity && a.is_positive())  return false;

    //this, a >=0
    if( positivity && a.is_positive()){

        std::vector<unsigned char> a_data=a.get_data();
        
        //if one number has more digits
        if(data.size()> a_data.size())    return true;
        if(data.size()< a_data.size())    return false;
        
        //compare each digit
        for(int i=data.size()-1;i>=0;i--){
            if(data[i]>a_data[i])   return true;
            if(data[i]<a_data[i])   return false;
        }
    }

    //this, a <0
    if( (!positivity) && (!a.is_positive())){

        std::vector<unsigned char> a_data=a.get_data();
        
        //if one number has more digits
        if(data.size()> a_data.size())    return false;
        if(data.size()< a_data.size())    return true;
        
        //compare each digit
        for(int i=data.size()-1;i>=0;i--){
            if(data[i]>a_data[i])   return false;
            if(data[i]<a_data[i])   return true;
        }
    }

    //if they are equal;
    return false;
}

bool integer::is_equal(integer a)
{
    //if the positivity are different;
    if(positivity!= a.is_positive())    return false;

    std::vector<unsigned char> a_data=a.get_data();
    //if have different size of digits
    if(data.size() != a_data.size())    return false;

     //compare each digit
    for(int i=data.size()-1;i>=0;i--){
        if(data[i]!=a_data[i])   return false;
    }

    return true;
}

//we can combine the former two functions, but rewriting it again can save operating time
bool integer::larger_equal_than(integer a)
{
    //this>=0, a<0
    if(positivity && !a.is_positive())  return true;

    //this<0, a>0
    if( !positivity && a.is_positive())  return false;

    //this, a >=0
    if( positivity && a.is_positive()){

        std::vector<unsigned char> a_data=a.get_data();
        
        //if one number has more digits
        if(data.size()> a_data.size())    return true;
        if(data.size()< a_data.size())    return false;
        
        //compare each digit
        for(int i=data.size()-1;i>=0;i--){
            if(data[i]>a_data[i])   return true;
            if(data[i]<a_data[i])   return false;
        }
    }

    //this, a <0
    if( (!positivity) && (!a.is_positive())){

        std::vector<unsigned char> a_data=a.get_data();
        
        //if one number has more digits
        if(data.size()> a_data.size())    return false;
        if(data.size()< a_data.size())    return true;
        
        //compare each digit
        for(int i=data.size()-1;i>=0;i--){
            if(data[i]>a_data[i])   return false;
            if(data[i]<a_data[i])   return true;
        }
    }

    //if they are equal;
    return true;
}

bool integer::smaller_than(integer a)
{
    return !this->larger_equal_than(a);
}

bool integer::smaller_equal_than(integer a)
{
    return !this->larger_than(a);
}

//-------------------------------------------------------------------
void integer::add_with(integer a)
{
    std::vector<unsigned char> a_data=a.get_data();

    //make two numbers to be the same size
    if(data.size() < a_data.size()){
        data.insert(data.end(), a_data.size()-data.size(), 0);
    }
    if(a_data.size() < data.size()){
        a_data.insert(a_data.end(), data.size()-a_data.size(), 0);
    }

    bool carry_bit=0;
    //if the positivities are the same
    if( ! (positivity ^ a.is_positive())){
        for(int i=0;i<data.size();i++){
            unsigned char temp=(data[i]+a_data[i]+(unsigned char)carry_bit) % 256;
            carry_bit= ((unsigned int)data[i]+(unsigned int)a_data[i]+(unsigned int)carry_bit)/256;
            data[i]=temp;
        }
        //add carry bit
        if(carry_bit)   data.push_back(1);
    }else{
    //if the positivities are different
        //get the new positivity
        if(positivity){
            positivity= (this->absolute_value()>= a.absolute_value());
        }else{
            positivity= (this->absolute_value()<= a.absolute_value());
        }

        //computations, we substract from the one with larger norm
        if(this->absolute_value()>= a.absolute_value()){
            for(int i=0;i<data.size();i++){
                unsigned char temp=(data[i]-a_data[i]-(unsigned char)carry_bit) % 256;
                //the carry_bit will be one if we have to take a one from higher digit
                //the part after "or" happens if there is already a one token from the lower bit and we have to substract 255
                //in this case the sum of the digit and carry_bit will be 0 in unsigned char, but we indeed want to substract one
                carry_bit= (data[i]<a_data[i]+(unsigned char) carry_bit) or (carry_bit and a_data[i]==255);
                data[i]=temp;
            }
        }else{
            for(int i=0;i<data.size();i++){
                unsigned char temp=(a_data[i]-data[i]-(unsigned char)carry_bit) % 256;
                //the carry_bit will be one if we have to take a one from higher digit
                //the part after "or" happens if there is already a one token from the lower bit and we have to substract 255
                //in this case the sum of the digit and carry_bit will be 0 in unsigned char, but we indeed want to substract one
                carry_bit= (a_data[i]<data[i]+(unsigned char) carry_bit) or (carry_bit and data[i]==255);
                data[i]=temp;
            }
        }
        //remove all 0 digits
        while(data.back()==0)   data.pop_back();
        
    }

    
}

void integer::substract_with(integer a)
{
    this->add_with(a.negation());
}

void integer::multiply_with_256_power_n(int n)
{
    //shift every digit by n
    data.insert(data.begin(),n,(unsigned char)0);
}

void integer::multiply_with_char(unsigned char a)
{
    //fast multiplication algorithm
    if(a!=0){
        integer temp;
        temp.init(*this);   //copy the current number
        if(a>1){
            //this=this*(a/2)+this*(a/2)+this*(a%2)
            this->multiply_with_char(a/2);
            this->add_with(*this);
            if(a%2) this->add_with(temp);
        }
    }else{  //if a==0
        this->init(0);
    }
}

void integer::multiply_with(integer a)
{
    //get the positivity of result and set it at last
    bool result_positivity=!(positivity ^ a.is_positive());

    //save the original number and clean self
    integer start;
    start.init(*this);
    this->init(0);

    //we do everything on the absolute values and set the positivity at last
    start.absolute_value_self();
    for(int i=0;i<a.get_data().size();i++){
        //multiply by digits
        integer temp;
        temp.init(start);
        temp.multiply_with_char(a.get_data()[i]);
        temp.multiply_with_256_power_n(i);
        this->add_with(temp);
    }
    positivity= result_positivity;
}

void integer::operator=(integer a)
{
    this->data=a.get_data();
    this->positivity=a.is_positive();
}

integer integer::operator+(integer a)
{
    integer ans;
    ans.init(*this);
    ans.add_with(a);
    return ans;
}

integer integer::operator-(integer a)
{
    integer ans;
    ans.init(*this);
    ans.substract_with(a);
    return ans;
}

integer integer::operator*(integer a)
{
    integer ans;
    ans.init(*this);
    ans.multiply_with(a);
    return ans;
}

/*

integer operator/(integer a);

integer operator%(integer a);
*/

bool integer::operator>(integer a)
{
    return this->larger_than(a);
}

bool integer::operator<(integer a)
{
    return this->smaller_than(a);
}

bool integer::operator==(integer a)
{
    return this->is_equal(a);
}

bool integer::operator>=(integer a)
{
    return this->larger_equal_than(a);
}

bool integer::operator<=(integer a)
{
    return this->smaller_equal_than(a);
}
