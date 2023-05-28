/**Yang Zhang 28.05.2023
 * This is a file in the project rational_points_on_EC
 * https://github.com/yang-zhang-math/rational_points_on_EC
 * class of integers and rational numbers of arbitraty length
 * Licensed under GNU General Public License v3.0
 */

#include "rational.h"
#include <iostream>

void bigint::init(long long int number)
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

void bigint::init(std::string hex_number)
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

        //convert to the entry of the bigint
        data.push_back(temp2*16+temp1);
    }

    //in case one inputs 000123, or similar numbers with 0 in front
    for(int i=data.size()-1;i>=0;i--){
        if(data[i]==0)  data.pop_back();
    }
    //in case one inputs -000000 and we get nothing in data but false positivity at last
    if(data.empty())    positivity=true;
}

void bigint::init(bigint a)
{
    positivity=a.is_positive();
    data=a.get_data();
}

//-------------------------------------------------------------------

std::vector<unsigned char> bigint::get_data(void)
{
    return data;
}

bool bigint::is_positive(void)
{
    return positivity;
}

//-------------------------------------------------------------------

void bigint::print_hex(void)
{   
    //print negative sign
    if(!positivity) std::cout<<"-";

    //two temp digits
    unsigned char temp1,temp2;           

    //if is zero, there is no data in array, so print zero
    if(this->is_zero())  std::cout<<'0';

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

void bigint::negate_self(void)
{
    positivity=!positivity;
}

void bigint::absolute_value_self(void)
{
    positivity=true;
}

bigint bigint::negation(void)
{
    bigint ans;
    ans.init(*this);
    ans.negate_self();
    return ans;
}

bigint bigint::absolute_value(void)
{
    bigint ans;
    ans.init(*this);
    ans.absolute_value_self();
    return ans;
}


//-------------------------------------------------------------------

bool bigint::is_zero(void)
{
    return data.empty();
}

bool bigint::larger_than(bigint a)
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

bool bigint::is_equal(bigint a)
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
bool bigint::larger_equal_than(bigint a)
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

bool bigint::smaller_than(bigint a)
{
    return !this->larger_equal_than(a);
}

bool bigint::smaller_equal_than(bigint a)
{
    return !this->larger_than(a);
}

//-------------------------------------------------------------------

void bigint::add_with(bigint a)
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
        if(!data.empty()){
            while(data.back()==0)   data.pop_back();
        }
        
    }

    
}

void bigint::substract_with(bigint a)
{
    this->add_with(a.negation());
}

void bigint::multiply_with_256_power_n(int n)
{
    //if the integer itself is 0 then do nothing
    if(!this->is_zero()){
        //shift every digit by n
        data.insert(data.begin(),n,(unsigned char)0);
    }
}

void bigint::multiply_with_char(unsigned char a)
{
    //fast multiplication algorithm
    //I'm not sure whether this is faster than digit multiplication, but I'm too lazy to write digit multiplication
    if(a!=0){
        bigint temp;
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

void bigint::multiply_with(bigint a)
{
    //get the positivity of result and set it at last
    bool result_positivity=!(positivity ^ a.is_positive());

    //save the original number and clean self
    bigint start;
    start.init(*this);
    this->init(0);

    //we do everything on the absolute values and set the positivity at last
    start.absolute_value_self();
    for(int i=0;i<a.get_data().size();i++){
        //multiply by digits
        bigint temp;
        temp.init(start);
        temp.multiply_with_char(a.get_data()[i]);
        temp.multiply_with_256_power_n(i);
        this->add_with(temp);
    }
    positivity= result_positivity;
}

void bigint::divide_with(bigint a)
{
    //if self is zero then do nothing
    //if a is zero then return 0
    if(a.is_zero()){
        this->init(0);
    }else if(!this->is_zero()){
        //get the positivity of final result
        bool result_positivity=!(positivity ^ a.is_positive());

        //take absolute values
        this->absolute_value_self();
        a.absolute_value_self();

        //if this<a output 0
        if(*this< a){
            this->init(0);
        }else{
            //divide by each digit, overdigit is a flag and ans is output
            bool overdigit=0;
            bigint ans(0);
            while(*this>=a){
                //start with a guess by dividing the leading digits
                //say 3456/234, we start then with 3/2*10, where 10 is the difference between the size of self and a.
                //note it is possible like in case 2345/456 that we have to consider the first two digits of self,
                //where we guess it should be around (23/4)
                //we first treat the first case, when we get something left in the leading digit, we set the flag
                //overdigit to be 1 and consider the second case.
                bigint guess;
                if(overdigit){
                    guess.init((((long long)data.back()*256)+(long long)data[data.size()-2])/(long long)a.get_data().back());
                    if(data.size()>a.get_data().size()+1){
                        guess.multiply_with_256_power_n(data.size()-a.get_data().size()-1);
                    }
                }else{
                    guess.init(((long long)data.back())/(long long)a.get_data().back());
                    //if the guess is zero (like for 2345/456 we have 2/4=0) then we set the overdigit flag and go to next round
                    if(guess.is_zero()){
                        overdigit=1;
                        continue;
                    }
                    if(data.size()>a.get_data().size()){
                        guess.multiply_with_256_power_n(data.size()-a.get_data().size());
                    }
                }

                //factor=256^n here
                bigint factor(1);
                factor.multiply_with_256_power_n(data.size()-a.get_data().size()-overdigit);

                //the temps is used to save time
                bigint temp1,temp2;
                temp1.init(guess*a);
                temp2.init(a);
                temp2.multiply_with_256_power_n(data.size()-a.get_data().size()-overdigit);

                //if the guess is too large, reduce each time by 1 (the factor here)
                if(guess*a>*this){
                    /*we use temp1 to substitute guess*a and temp2 to substitute factor*a
                    this is equivalent to

                    while(guess*a>*this){
                        guess.substract_with(factor);
                    }

                    since when guess get substracted with factor, guess*a get substracted with factor*a,
                    but we do not need to do multiplication every time
                    */
                    while(temp1>*this){
                        guess.substract_with(factor);
                        temp1.substract_with(temp2);
                    }

                //if the guess is too small, add each time by 1 (the factor here)
                }else if(guess*a<*this){
                    /*we use temp1 to substitute guess*a and temp2 to substitute factor*a
                    this is equivalent to

                    while(guess*a<*this){
                        guess.add_with(factor);
                    }

                    since when guess get added with factor, guess*a get added with factor*a,
                    but we do not need to do multiplication every time
                    */
                    while(temp1<*this){
                        guess.add_with(factor);
                        temp1.add_with(temp2);
                    }
                    //at last temp1 will exceed self, so as the guess, so we neew to substract once
                    guess.substract_with(factor);
                    temp1.substract_with(temp2);
                }

                //get the size of the current data
                int previous_datasize=data.size();
                //take this substracted with temp1, which is guess*a, and let ans get added with guess
                this->substract_with(temp1);
                ans.add_with(guess);

                //if the new size is the same, which means that there are something left in the leading digit
                //then we set overdigit to be 1
                if(data.size()==previous_datasize){
                    overdigit=1;
                }else{
                    overdigit=0;
                }
            }
            //take the result
            this->init(ans);
            positivity=result_positivity;
        }
    }
}

void bigint::mod_with(bigint a)
{
    if(!this->is_zero())
    {
        this->substract_with((*this/a)*a);
        if (*this<0)    this->add_with(a);
    }
}

void bigint::exp_with(int n)
{
    //fast exponential algorithm
    if(n!=1){
        bigint temp;
        temp.init(*this);
        this->exp_with(n/2);
        this->multiply_with(*this);
        if(n%2)
            this->multiply_with(temp);
    }
}

//-------------------------------------------------------------------

void bigint::operator=(bigint a)
{
    this->init(a);
}

bigint bigint::operator+(bigint a)
{
    bigint ans;
    ans.init(*this);
    ans.add_with(a);
    return ans;
}

bigint bigint::operator-(bigint a)
{
    bigint ans;
    ans.init(*this);
    ans.substract_with(a);
    return ans;
}

bigint bigint::operator*(bigint a)
{
    bigint ans;
    ans.init(*this);
    ans.multiply_with(a);
    return ans;
}

bigint bigint::operator/(bigint a){
    bigint ans;
    ans.init(*this);
    ans.divide_with(a);
    return ans;
}

bigint bigint::operator%(bigint a){
    bigint ans;
    ans.init(*this);
    ans.mod_with(a);
    return ans;
}

bool bigint::operator>(bigint a)
{
    return this->larger_than(a);
}

bool bigint::operator<(bigint a)
{
    return this->smaller_than(a);
}

bool bigint::operator==(bigint a)
{
    return this->is_equal(a);
}

bool bigint::operator!=(bigint a)
{
    return !this->is_equal(a);
}

bool bigint::operator>=(bigint a)
{
    return this->larger_equal_than(a);
}

bool bigint::operator<=(bigint a)
{
    return this->smaller_equal_than(a);
}

//-------------------------------------------------------------------

bigint bigint_gcd(bigint a, bigint b)
{
    a.absolute_value_self();
    b.absolute_value_self();

    //Euclidean 
    if (a<b) std::swap(a,b);
    if(b.is_zero())     return a;
    bigint c;
    c.init(a%b);
    if (c.is_zero())    return b;
    return bigint_gcd(b, c);
}

bigint bigint_lcm(bigint a, bigint b)
{
    return a*b/bigint_gcd(a,b);
}

bigint bigint_a_exp_with_n(bigint a, int n)
{
    bigint ans;
    ans.init(a);
    ans.exp_with(n);
    return ans;
}



//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------

void bigrat::init(void)
{
    numerator.init(0);
    denominator.init(1);
}

void bigrat::init(int num, int denom)
{
    numerator.init(num);
    denominator.init(denom);

    if(denominator.is_zero())
        denominator.init(1);
    
    if(!denominator.is_positive()){
        denominator.negate_self();
        numerator.negate_self();
    }

    this->reduce_fraction();
}

void bigrat::init(bigint num, bigint denom)
{
    numerator.init(num);
    denominator.init(denom);

    if(denominator.is_zero())
        denominator.init(1);
    
    if(!denominator.is_positive()){
        denominator.negate_self();
        numerator.negate_self();
    }

    this->reduce_fraction();
}

void bigrat::init(std::string num, std::string denom){
    numerator.init(num);
    denominator.init(denom);

    if(denominator.is_zero())
        denominator.init(1);
    
    if(!denominator.is_positive()){
        denominator.negate_self();
        numerator.negate_self();
    }

    this->reduce_fraction();
}

void bigrat::init(bigrat a)
{
    numerator=a.get_numerator();
    denominator=a.get_denominator();
}

//-------------------------------------------------------------------

bigint bigrat::get_numerator(void)
{
    return numerator;
}

bigint bigrat::get_denominator(void)
{
    return denominator;
}

//-------------------------------------------------------------------

void bigrat::print_hex(void)
{
    std::cout << "Numerator:" << std::endl;
    numerator.print_hex();
    std::cout << std::endl << "Denominator:" << std::endl;
    denominator.print_hex();
    std::cout << std::endl;
}

void bigrat::reduce_fraction(void)
{
    bigint gcd=bigint_gcd(numerator,denominator);
    numerator.divide_with(gcd);
    denominator.divide_with(gcd);
}

void bigrat::negate_self(void)
{
    numerator.negate_self();
}

void bigrat::absolute_value_self(void)
{
    numerator.absolute_value_self();
}

void bigrat::invert_self(void)
{
    if(!this->is_zero()){
        std::swap(numerator,denominator);

        if(!denominator.is_positive()){
            denominator.negate_self();
            numerator.negate_self();
        }
    }
}

bigrat bigrat::negation(void)
{
    bigrat ans;
    ans.init(*this);
    ans.negate_self();
    return ans;
}

bigrat bigrat::absolute_value(void)
{
    bigrat ans;
    ans.init(*this);
    ans.absolute_value_self();
    return ans;
}

bigrat bigrat::inverse(void)
{
    bigrat ans;
    ans.init(*this);
    ans.invert_self();
    return ans;
}

//-------------------------------------------------------------------

bool bigrat::is_zero(void)
{
    return numerator.is_zero();
}

bool bigrat::is_one(void)
{
    return (numerator==denominator);
}

bool bigrat::larger_than(bigrat a)
{
    return (numerator*a.get_denominator()) > (denominator*a.get_numerator());
}

bool bigrat::is_equal(bigrat a)
{
    return (numerator==a.get_numerator()) and (denominator==a.get_denominator());
}

bool bigrat::larger_equal_than(bigrat a)
{
    return (numerator*a.get_denominator()) >= (denominator*a.get_numerator());
}

bool bigrat::smaller_than(bigrat a)
{
    return !this->larger_equal_than(a);
}

bool bigrat::smaller_equal_than(bigrat a)
{
    return !this->larger_than(a);
}

//-------------------------------------------------------------------

void bigrat::add_with(bigrat a)
{
    numerator.multiply_with(a.get_denominator());
    numerator.add_with(a.get_numerator()*denominator);
    denominator.multiply_with(a.get_denominator());
    this->reduce_fraction();
}

void bigrat::substract_with(bigrat a)
{
    this->add_with(a.negation());
}

void bigrat::multiply_with(bigrat a)
{
    numerator.multiply_with(a.get_numerator());
    denominator.multiply_with(a.get_denominator());
    this->reduce_fraction();
}

void bigrat::divide_with(bigrat a)
{
    if(!a.is_zero()){
        this->multiply_with(a.inverse());
    }
}

void bigrat::exp_with(int n)
{
    numerator.exp_with(n);
    denominator.exp_with(n);
}

void bigrat::operator=(bigrat a)
{
    this->init(a);
}

bigrat bigrat::operator+(bigrat a)
{
    bigrat ans;
    ans.init(*this);
    ans.add_with(a);
    return ans;
}

bigrat bigrat::operator-(bigrat a)
{
    bigrat ans;
    ans.init(*this);
    ans.substract_with(a);
    return ans;
}

bigrat bigrat::operator*(bigrat a)
{
    bigrat ans;
    ans.init(*this);
    ans.multiply_with(a);
    return ans;
}

bigrat bigrat::operator/(bigrat a)
{
    bigrat ans;
    ans.init(*this);
    ans.divide_with(a);
    return ans;
}

bool bigrat::operator>(bigrat a)
{
    return this->larger_than(a);
}

bool bigrat::operator<(bigrat a)
{
    return this->smaller_than(a);
}

bool bigrat::operator==(bigrat a)
{
    return this->is_equal(a);
}

bool bigrat::operator!=(bigrat a)
{
    return !this->is_equal(a);
}

bool bigrat::operator>=(bigrat a)
{
    return this->larger_equal_than(a);
}

bool bigrat::operator<=(bigrat a)
{
    return this->smaller_equal_than(a);
}

//-------------------------------------------------------------------

bigrat bigrat_a_exp_with_n(bigrat a, int n)
{
    bigrat ans;
    ans.init(a);
    ans.exp_with(n);
    return ans;
}