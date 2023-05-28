/**Yang Zhang 28.05.2023
 * This is a file in the project rational_points_on_EC
 * https://github.com/yang-zhang-math/rational_points_on_EC
 * class of integers and rational numbers of arbitraty length
 * Licensed under GNU v3.0
 */

#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <vector>
#include <string>


//class of integers
//use vector of char to save the data

class bigint{

    private:

        //the array to save the data
        //unlike writing a number, we store the digits conversely
        //namely higher the index, higher the digit
        std::vector<unsigned char> data;

        //whether the number is larger **equal** 0
        bool positivity=true;

    public:
        //initialize as 0
        bigint(void){
            positivity=true;
        }

        //initialize with long long
        bigint(long long int number){

            //test the positivity
            if(number<0){
                positivity=false;
                number*=-1;
            }else{
                positivity=true;
            }

            //transfer into data
            while(number!=0){
                data.push_back(number % 256);
                number /=256;
            }
        }


        //initialize with hex strings, every entry has to be between 0-9, a-f!
        bigint(std::string hex_number){

            //if the first char is negative sign then delete it and set positivity to be false
            if(hex_number[0]=='-'){
                positivity=false;
                hex_number.erase(0,1);
            }
            //if the length is odd then add a 0 in front
            if(hex_number.length() %2)  hex_number="0"+hex_number;

            //convert to array of unsigned char
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
                if(data[i]==0){
                    data.pop_back();
                }else{
                    break;
                }     
            }
            //in case one inputs -000000 and we get nothing in data but false positivity at last
            if(data.empty())    positivity=true;
        }

        //initializing function, the same as the init in header but clear the data and positivity at first

        void init(long long int number);

        void init(std::string hex_number);

        //initialize with another bigint
        void init(bigint a);

        //-------------------------------------------------------------------
        //get the data

        //the array saving every digit
        std::vector<unsigned char> get_data(void);

        //is_positive returns positivity, namely whether larger **equal** 0
        bool is_positive(void);

        //-------------------------------------------------------------------
        //print the number in hex
        void print_hex(void);

        //make self to be the negation
        void negate_self(void);

        //make self to be the absolute value
        void absolute_value_self(void);

        //take negation, does not change self data
        bigint negation(void);

        //take absolute value, does not change self data
        bigint absolute_value(void);

        //-------------------------------------------------------------------
        //compare two numbers

        bool is_zero(void);

        bool larger_than(bigint a);

        bool is_equal(bigint a);

        bool larger_equal_than(bigint a);

        bool smaller_than(bigint a);

        bool smaller_equal_than(bigint a);

        //-------------------------------------------------------------------
        //algebraic operations
        //the operations will cover the original data, e.g. this->add_with(a) is the same as this+=a

        void add_with(bigint a);

        void substract_with(bigint a);

        //multiplication with 256^n
        void multiply_with_256_power_n(int n);

        //multiply with an unsigned char, considered as a positive bigint with single digit
        void multiply_with_char(unsigned char a);

        void multiply_with(bigint a);

        //this acts like division of int, returns only bigint
        //example for negative division: 10/4=-10/-4=2, -10/4=10/-4=-2
        //return 0 if a==0, do not throw any error here!!!
        void divide_with(bigint a);

        //this modulo returns only nonnegative bigint!
        //example: 13%4=1, -13%4=3
        void mod_with(bigint a);

        //let self get exponentiated with power n
        void exp_with(int n);

        //-------------------------------------------------------------------
        //reload operators
        //do not provide += and similar things, for this please use the algebraic operations above;

        void operator=(bigint a);

        bigint operator+(bigint a);

        bigint operator-(bigint a);

        bigint operator*(bigint a);

        bigint operator/(bigint a);

        bigint operator%(bigint a);

        bool operator>(bigint a);

        bool operator<(bigint a);

        bool operator==(bigint a);

        bool operator!=(bigint a);

        bool operator>=(bigint a);

        bool operator<=(bigint a);

};

//further operations

//greatest common divisor of the *ABSOLUTE VALUE* of a and b
bigint bigint_gcd(bigint a, bigint b);

//least common multiplier of the *ABSOLUTE VALUE* of a and b
bigint bigint_lcm(bigint a, bigint b);

/** exponential, return a^n
 *  \param a the base
 *  \param n the exponent
 */
bigint bigint_a_exp_with_n(bigint a, int n);



//class of rational numbers
//the positivity is saved in numerator, and denominator should be always positive

class bigrat{

    private:

        //the numerator
        bigint numerator;

        //the denominator
        bigint denominator;

    public:
        
        //initialize as zero
        bigrat(void){
            numerator.init(0);
            denominator.init(1);
        }

        //initialize with integer numerator and denominator
        //if input denom=0, we set denominator to be 1
        bigrat(int num, int denom){
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

        //initialize with bigint numerator and denominator
        //if input denom=0, we set denominator to be 1
        bigrat(bigint num, bigint denom){
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

        //initializing functions, the same as the init functions in the header but clear all data at first

        void init(void);

        void init(int num, int denom);

        void init(bigint num, bigint denom);

        //init with another bigrat number
        void init(bigrat a);

        //-------------------------------------------------------------------
        //get the data

        //get the numerator
        bigint get_numerator(void);

        //get the denominator
        bigint get_denominator(void);

        //-------------------------------------------------------------------
        //print the number in hex
        void print_hex(void);

        //let the numerator and denominator divided by their gcd
        void reduce_fraction(void);

        //make self to be the negation
        void negate_self(void);

        //make self to be the absolute value
        void absolute_value_self(void);

        //make self to be the multiplicative inverse, if self is zero, return zero
        void invert_self(void);

        //take negation, does not change self data
        bigrat negation(void);

        //take absolute value, does not change self data
        bigrat absolute_value(void);

        //take multiplicative inverse, does not change self data, if self is zero, return zero
        bigrat inverse(void);

        //-------------------------------------------------------------------
        //compare two numbers

        bool is_zero(void);

        bool is_one(void);

        bool larger_than(bigrat a);

        bool is_equal(bigrat a);

        bool larger_equal_than(bigrat a);

        bool smaller_than(bigrat a);

        bool smaller_equal_than(bigrat a);

        //-------------------------------------------------------------------
        //algebraic operations
        //the operations will cover the original data, e.g. this->add_with(a) is the same as this+=a

        void add_with(bigrat a);

        void substract_with(bigrat a);

        void multiply_with(bigrat a);

        //this will do nothing if a==0;
        void divide_with(bigrat a);

        //let self get exponentiated with power n
        void exp_with(int n);

        //-------------------------------------------------------------------
        //reload operators
        //do not provide += and similar things, for this please use the algebraic operations above;

        void operator=(bigrat a);

        bigrat operator+(bigrat a);

        bigrat operator-(bigrat a);

        bigrat operator*(bigrat a);

        bigrat operator/(bigrat a);

        bool operator>(bigrat a);

        bool operator<(bigrat a);

        bool operator==(bigrat a);

        bool operator!=(bigrat a);

        bool operator>=(bigrat a);

        bool operator<=(bigrat a);
};

//further operations

/** exponential, return a^n
 *  \param a the base
 *  \param n the exponent
 */
bigrat bigrat_a_exp_with_n(bigrat a, int n);

#endif