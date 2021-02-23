#include "Option.h"

Option::Option(TypeOption optionType, double strikePrice, double maturity)
{  
        _strikePrice = strikePrice;
        _maturity = maturity;
        _type = optionType;
}
Option::~Option()
{
}


double Option::getMaturity()
{
    return _maturity;
}
TypeOption Option::getType()
{
    return _type;
}
double Option::getStrikePrice()
{
    return _strikePrice;
}


