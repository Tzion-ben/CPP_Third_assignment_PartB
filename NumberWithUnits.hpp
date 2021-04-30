#pragma once

#include<iostream>
#include <unordered_map>
#include <map>


const int LINE_UNIT_SIZE = 5; 

const float EPSILON = 0.001;
const int FIRST_UNIT_TYPE = 1; 
const int SECOND_UNIT_TYPE = 4; 
const int SECOND_UNIT_AMOUMT = 3;



namespace ariel{

    class NumberWithUnits{

        private :
            double _amount;
            std::string _unitType;
            void setRigthType(const std::string& unitType); 
    

        public:
            static std::map<std::string , std::map<std::string , double>> _unitsConverting;

            /*prametrize constractor*/
            NumberWithUnits (const double& amount,
                            const std::string& unitType);


            /*will read the file with units*/        
            static void read_units(std::ifstream& input);
            /*wil update the map that at every key will contain all the related units*/
            static void updataMap(const std::string &firstType , const std::string &seconfType);


            /*in line implemention */
            NumberWithUnits& operator+= (const NumberWithUnits& other) 
                {
                if(other._unitType.compare(this->_unitType) == 0){
                    this->_amount+=other._amount;
                    return *this;
                }
                    
                /*if not found the unit at general map keys, go inside the nested map keys*/
                               
                    if(_unitsConverting.at(this->_unitType).count(other._unitType) > 0){
                        double otherAmountCopy = other._amount;
                        double convertWith = _unitsConverting.at(this->_unitType).at(other._unitType);
                        this->_amount = this->_amount+(otherAmountCopy / convertWith);
                        return *this;
                   } 
                throw "Invalid Unit Type";
                
                return *this;
            }

            /*unary +*/
            NumberWithUnits operator+() const;

        /******************************************************************/
            
            /*in line implemention */

            NumberWithUnits& operator-= (const NumberWithUnits& other) 
            {
                if(other._unitType.compare(this->_unitType) == 0){
                    this->_amount-=other._amount;
                    return *this;
                }
                /*if not found the unit at general map keys, go inside the nested map keys*/
                               
                    if(_unitsConverting.at(this->_unitType).count(other._unitType) > 0){
                        double otherAmountCopy = other._amount;
                        double convertWith = _unitsConverting.at(this->_unitType).at(other._unitType);
                        this->_amount = this->_amount-(otherAmountCopy / convertWith);
                        return *this;
                   } 
                
                    throw "Invalid Unit Type";
                return *this;
            }
            /*unary -*/
            NumberWithUnits operator- () const;

        /******************************************************************/
            // prefix increment:
            NumberWithUnits& operator++() 
            {
                this->_amount+=1;
                return *this;
            }
            // postfix increment:
            NumberWithUnits operator++(int flag_for_postfix_increment);

        /******************************************************************/
            // prefix decrement:
            NumberWithUnits& operator--()
            {   
                this->_amount-=1;
                return *this;
            }
            // postfix decrement:
            NumberWithUnits operator--(int flag_for_postfix_increment);

        /******************************************************************/
            friend bool operator== (const NumberWithUnits& c1, const NumberWithUnits& c2);
            friend bool operator!= (const NumberWithUnits& c1, const NumberWithUnits& c2);
            friend bool operator>= (const NumberWithUnits& c1, const NumberWithUnits& c2);
            friend bool operator<= (const NumberWithUnits& c1, const NumberWithUnits& c2);
            friend bool operator>  (const NumberWithUnits& c1, const NumberWithUnits& c2);
            friend bool operator<  (const NumberWithUnits& c1, const NumberWithUnits& c2);

            //----------------------------------
            // binary - operetors
            // binary + operetors
            //----------------------------------
            friend NumberWithUnits operator- (const NumberWithUnits& n1, const NumberWithUnits& n2);
            friend NumberWithUnits operator+ (const NumberWithUnits& n1, const NumberWithUnits& n2);

            //----------------------------------
            // friend global IO operators
            //----------------------------------
            friend std::ostream& operator<< (std::ostream& output, const NumberWithUnits& n);
            friend std::istream& operator>> (std::istream& input , NumberWithUnits& n);

            //----------------------------------
            // multiplication operators
            //----------------------------------
            friend NumberWithUnits  operator* (double var,const NumberWithUnits& n);
            friend NumberWithUnits  operator* (const NumberWithUnits& n,double var);
    };
}