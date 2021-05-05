/**
 * Implementation of the NumberWithUnits class.
 * @author Tzion Beniamonov
 */

#include "NumberWithUnits.hpp"
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <array>

using namespace std;
using namespace ariel;

        /*static data structure, will contain all the given units from txt file*/
        map<std::string , map<std::string , double>> NumberWithUnits:: _unitsConverting;

        /*outLine Constractor*/ 
        NumberWithUnits:: NumberWithUnits (const double& amount,
                            const string& unitType)
                            {
                                _amount = amount;
                                setRigthType(unitType);
                            }

        /*reading the units from a givin file*/
        void NumberWithUnits::read_units(std::ifstream& input)
        {   
            /*store every line in array*/
            array<string, LINE_UNIT_SIZE> inputEachLine{};/*save every line at the input txt file*/

            string line;/*contain each line input*/
            while(!input.eof()){
                double SECOND_UNIT_AMOUMT_input = 0;
                for(u_long i=0 ; i< LINE_UNIT_SIZE ; i++){
                    if(i == SECOND_UNIT_AMOUMT){input >> SECOND_UNIT_AMOUMT_input ;}
                    else {input >> line;}
                    inputEachLine.at(i) = line;
               }
               /*at the map will store unitAmount and 1/unitAmount*/
                _unitsConverting[inputEachLine.at(FIRST_UNIT_TYPE)] [inputEachLine.at(SECOND_UNIT_TYPE)] = SECOND_UNIT_AMOUMT_input;
                _unitsConverting[inputEachLine.at(SECOND_UNIT_TYPE)] [inputEachLine.at(FIRST_UNIT_TYPE)] = 1.0/SECOND_UNIT_AMOUMT_input; 
            }

            /*update the map*/
            for(const auto& it : _unitsConverting){
                for(const auto& it_in : _unitsConverting[it.first]){
                    updataMap(it.first , it_in.first);
                }
            }
        }

        /*discription at hpp file*/
        void NumberWithUnits:: updataMap(const string &firstType , const string &seconfType){
            for(const auto& it : _unitsConverting[firstType]){
        
                if(_unitsConverting[seconfType].count(it.first) == 0  && _unitsConverting[it.first].count(seconfType) == 0){
                    _unitsConverting[seconfType][it.first] = _unitsConverting[seconfType][firstType] * _unitsConverting[firstType][it.first];
                    _unitsConverting[it.first][seconfType] = _unitsConverting[it.first][firstType] * _unitsConverting[firstType][seconfType];
                }
            
                if(_unitsConverting[firstType].count(it.first) == 0  && _unitsConverting[it.first].count(firstType) == 0){
                    for(const auto& it : _unitsConverting[seconfType]){
                        _unitsConverting[firstType][it.first] = _unitsConverting.at(firstType).at(seconfType) * _unitsConverting.at(seconfType).at(it.first);
                        _unitsConverting[it.first][firstType] = _unitsConverting[it.first][seconfType] * _unitsConverting[seconfType][firstType];
                    }
                }
            }
            
        }

        //binary + operetors
        NumberWithUnits ariel::operator+ (const NumberWithUnits& n1, const NumberWithUnits& n2)
        {
            if(n1._unitType == (n2._unitType)){
                return NumberWithUnits((n1._amount+n2._amount) , n1._unitType);
            }

            if(NumberWithUnits::_unitsConverting.count(n1._unitType) > 0 ){ 
                if(NumberWithUnits::_unitsConverting.at(n1._unitType).count(n2._unitType) > 0){
                    double convertWith = NumberWithUnits::_unitsConverting.at(n1._unitType).at(n2._unitType);
                    double newAmount = n1._amount+(n2._amount / convertWith);
                    return NumberWithUnits(newAmount , n1._unitType);
                } 
            }                

            throw "Invalid Unit Type";  
            return NumberWithUnits(0 , " ");
        }

        /*unary +*/
        NumberWithUnits NumberWithUnits:: operator+() const
        {
            return NumberWithUnits(this->_amount, this->_unitType);
        }

        /******************************************************************/
        //binary - operetors
        NumberWithUnits ariel::operator- (const NumberWithUnits& n1, const NumberWithUnits& n2)
        {
           if(n1._unitType == (n2._unitType)){
                return NumberWithUnits((n1._amount - n2._amount) , n1._unitType);
            }
                            
            if(NumberWithUnits::_unitsConverting.count(n1._unitType) > 0 ){ 
                if(NumberWithUnits::_unitsConverting.at(n1._unitType).count(n2._unitType) > 0){
                    double convertWith = NumberWithUnits::_unitsConverting.at(n1._unitType).at(n2._unitType);
                    double newAmount = n1._amount - (n2._amount / convertWith);
                    return NumberWithUnits(newAmount , n1._unitType);
                } 
            }          

            throw "Invalid Unit Type";    
            return NumberWithUnits(0 , " ");
        }
        /*unary -*/
        NumberWithUnits NumberWithUnits:: operator- () const
        {
            return NumberWithUnits(this->_amount*(-1),this->_unitType);
        }

        /******************************************************************/
        // postfix increment:
        NumberWithUnits NumberWithUnits:: operator++(int flag_for_postfix_increment)
        {
            /*create a copy, incremment at origin */
            NumberWithUnits copy = *this;
            this->_amount++;
            return copy; 
        }

        /******************************************************************/
        // postfix decrement:
        NumberWithUnits NumberWithUnits:: operator--(int flag_for_postfix_increment)
        {
            /*create a copy, decrement at origin */\
            NumberWithUnits copy = *this;
            this->_amount--;
            return copy;    
        }

        /******************************************************************/
        /*== operator*/
        bool ariel::operator== (const NumberWithUnits& c1, const NumberWithUnits& c2){
            if(c1._unitType == c2._unitType){
                double diffAmount = abs(c1._amount-c2._amount);
                return diffAmount<EPSILON;
            }
                    
            /*if not found the unit at general map keys, go inside the nested map keys*/
            
            if(NumberWithUnits::_unitsConverting.count(c1._unitType) > 0 ){ 
                if(NumberWithUnits::_unitsConverting.at(c1._unitType).count(c2._unitType) > 0){
                    double convertWith = NumberWithUnits::_unitsConverting.at(c2._unitType).at(c1._unitType);
                    double diffAmount = abs(c1._amount-(c2._amount * convertWith));
                    return diffAmount<EPSILON;
                } 
            }            
           
            throw "Invalid Unit Type";
            return false;
        }

        /******************************************************************/
        /*!= operator*/
        bool ariel::operator!= (const NumberWithUnits& c1, const NumberWithUnits& c2){
            if(c1._unitType == c2._unitType){
                double diffAmount = abs(c1._amount-c2._amount);
                return diffAmount>EPSILON;
            }
                    
            /*if not found the unit at general map keys, go inside the nested map keys*/
            if(NumberWithUnits::_unitsConverting.count(c1._unitType) > 0 ){ 
                if(NumberWithUnits::_unitsConverting.at(c1._unitType).count(c2._unitType) > 0){
                    double convertWith = NumberWithUnits::_unitsConverting.at(c2._unitType).at(c1._unitType);
                    double diffAmount = abs(c1._amount-(c2._amount * convertWith));
                    return diffAmount>EPSILON;
                } 
            }         

            throw "Invalid Unit Type";
            return false;            
        }

        /******************************************************************/
        /*>= operator*/
        bool ariel::operator>= (const NumberWithUnits& c1, const NumberWithUnits& c2){
            if(c1._unitType == c2._unitType){
               return c1._amount>=c2._amount;
            }
                    
            /*if not found the unit at general map keys, go inside the nested map keys*/
            if(NumberWithUnits::_unitsConverting.count(c1._unitType) > 0 ){ 
                if(NumberWithUnits::_unitsConverting.at(c1._unitType).count(c2._unitType) > 0){
                    double convertWith = NumberWithUnits::_unitsConverting.at(c2._unitType).at(c1._unitType);
                    return c1._amount>= c2._amount * convertWith;
                } 
            }         

            throw "Invalid Unit Type";
            return false;
        }

        /******************************************************************/
        /*<= operator*/
        bool ariel::operator<= (const NumberWithUnits& c1, const NumberWithUnits& c2){
            if(c1._unitType == c2._unitType){
                return (c1._amount - c2._amount) <= EPSILON;   
            }
                    
            /*if not found the unit at general map keys, go inside the nested map keys*/
            if(NumberWithUnits::_unitsConverting.count(c1._unitType) > 0 ){ 
                if(NumberWithUnits::_unitsConverting.at(c1._unitType).count(c2._unitType) > 0){
                    double convertWith = NumberWithUnits::_unitsConverting.at(c2._unitType).at(c1._unitType);
                    return (c1._amount - (c2._amount * convertWith)) <= EPSILON;
                } 
            }         

            throw "Invalid Unit Type";
            return false;
        }

        /******************************************************************/
        /*> operator*/
        bool ariel::operator>  (const NumberWithUnits& c1, const NumberWithUnits& c2){
             if(c1._unitType == c2._unitType){
                return (c1._amount - c2._amount) > EPSILON;
            }
                    
            /*if not found the unit at general map keys, go inside the nested map keys*/
            if(NumberWithUnits::_unitsConverting.count(c1._unitType) > 0 ){ 
                if(NumberWithUnits::_unitsConverting.at(c2._unitType).count(c1._unitType) > 0){
                    double convertWith = NumberWithUnits::_unitsConverting.at(c2._unitType).at(c1._unitType);
                    return (c1._amount - (c2._amount * convertWith)) > EPSILON;
                } 
            }         

            throw "Invalid Unit Type";
            return false;
        }

        /******************************************************************/
        /*< operator*/
        bool ariel::operator<  (const NumberWithUnits& c1, const NumberWithUnits& c2){
            
            if(c1._unitType == c2._unitType){
                return c1._amount<c2._amount;
            }
                    
            /*if not found the unit at general map keys, go inside the nested map keys*/
            if(NumberWithUnits::_unitsConverting.count(c1._unitType) > 0 ){ 
                if(NumberWithUnits::_unitsConverting.at(c1._unitType).count(c2._unitType) > 0){
                    double convertWith = NumberWithUnits::_unitsConverting.at(c2._unitType).at(c1._unitType);
                    return c1._amount< (c2._amount * convertWith);
                } 
            }         

            throw "Invalid Unit Type";
            return false;
        }

        //***********************************************************//
        static istream& getAndCheckNextCharIs(istream& input, char expectedChar) {
            char actualChar;
            input >> actualChar;
            if (!input) {return input;}

            if (actualChar!=expectedChar) {
                // failbit is for format error
                input.setstate(ios::failbit);
            }
            return input;
        }

        //----------------------------------
        // friend global IO operators
        //----------------------------------
        /******************************************************************/
        /*output operator*/
        ostream& ariel::operator<< (std::ostream& output, const NumberWithUnits& n) {
            return (output << n._amount << "[" << n._unitType << "]");
        }

        /******************************************************************/
        /*input operator*/
        istream& ariel::operator>> (std::istream& input , NumberWithUnits& n){
            double new_amount = 0; 
            string unitType;
            bool update = false;
            char ch ;

            input >> new_amount;// reading the unit  numbet from the input
            n._amount = new_amount;
            input >> unitType;// reading the next string that have to be that unitType  
           
            if (unitType.length() > 1){
                if(unitType.at(0) == '[' && unitType.at(unitType.length()-1) == ']')
                    {unitType = unitType.substr(1 , unitType.length()-2);}
                else if(unitType.at(0) == '[' )
                    {
                        unitType = unitType.substr(1 , unitType.length());
                        input >> ch; 
                    }
            }
            else if(unitType.length() == 1){
                input >> unitType;// reading the next string that have to be that unitType 
                if(unitType.at(unitType.length() -1 ) != ']' ){input >> ch; } 
            }
                if(unitType.length() > 0){
                    for(auto it = NumberWithUnits::_unitsConverting.begin() ; it != NumberWithUnits::_unitsConverting.end() ; it++){
                        if(unitType == it->first){
                            n._unitType = unitType;
                            update = true;// found the currect unit type
                        }
                    }
                }

            if(!update){throw "Invalid Unit Type";}
            return input;
        }

        //----------------------------------
        // multiplication operators
        //----------------------------------
        NumberWithUnits  ariel::operator* (double var,const NumberWithUnits& n)
        {
            double newAmount = n._amount * var;
            return NumberWithUnits(newAmount, n._unitType);
        }

        NumberWithUnits  ariel::operator* (const NumberWithUnits& n, double var)
        {
            double newAmount = n._amount * var;
            return NumberWithUnits(newAmount, n._unitType);
        }

        /*sets the type if its currect*/
        void NumberWithUnits::setRigthType(const std::string& unitType){
            bool found = false;
            if(_unitsConverting.count(unitType) > 0){
                _unitType = unitType;
                found=true;
            }
            if(!found){throw "Invalid Unit Type";}
        }