//Yang Zhang 17.05.2023
//class of integers and rational numbers of arbitraty length

#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <vector>
#include <string>


//class of integers
//use vector of char to save the data

class integer{

    private:

        //the array to save the data
        //unlike writing a number, we store the digits conversely
        //namely higher the index, higher the digit
        std::vector<unsigned char> data;

        //whether the number is larger **equal** 0
        bool positivity=true;

    public:
        //initialize as 0
        integer(void){
            positivity=true;
        }

        //initialize with long long
        integer(long long int number){

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
        integer(std::string hex_number){

            //if the first char is negative sign then delete it and set positivity to be false
            if(hex_number[0]=='-'){
                positivity=false;
                hex_number.erase(0,1);
            }
            //if the length is odd then add a 0 in front
            if(hex_number.length() %2)  hex_number="0"+hex_number;

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
                if(data[i]==0){
                    data.pop_back();
                }else{
                    break;
                }     
            }
            //in case one inputs -000000 and we get nothing in data but false positivity at last
            if(data.empty())    positivity=true;
        }


        //initializing function, the same as the init in header
        void init(long long int number);

        void init(std::string hex_number);

        //initialize with another integer
        void init(integer a);

        //-------------------------------------------------------------------
        //get the data
        //the numbers
        std::vector<unsigned char> get_data(void);

        //is_positive returns positivity, namely whether larger **equal** 0
        bool is_positive(void);

        //-------------------------------------------------------------------
        //print the number in hex
        void print_hex();

        //make self to be the negation
        void negate_self();

        //make self to be the absolute value
        void absolute_value_self();

        //take negation, does not change self data
        integer negation(void);

        //take absolute value, does not change self data
        integer absolute_value(void);

        //-------------------------------------------------------------------
        //compare two numbers

        bool larger_than(integer a);

        bool is_equal(integer a);

        bool larger_equal_than(integer a);

        bool smaller_than(integer a);

        bool smaller_equal_than(integer a);

        //-------------------------------------------------------------------
        //algebraic operations
        //the operations will cover the original data, e.g. this->add_with(a) is the same as this+=a
        void add_with(integer a);

        void substract_with(integer a);

        void multiply_with(integer a);

        //this acts like division of int, returns only integer
        void divide_with(integer a);

        void mod_with(integer a);

        //multiplication with 256
        void multiply_with_256(void);

        //-------------------------------------------------------------------
        //reload operators
        //do not provide += and similar things, for this please use the algebraic operations below;
        void operator=(integer a);

        integer operator+(integer a);

        integer operator-(integer a);

        integer operator*(integer a);

        integer operator/(integer a);

        integer operator%(integer a);

        bool operator>(integer a);

        bool operator<(integer a);

        bool operator==(integer a);

        bool operator>=(integer a);

        bool operator<=(integer a);

};

//further operations
integer gcd(integer a, integer b);

integer lcm(integer a, integer b);


#endif