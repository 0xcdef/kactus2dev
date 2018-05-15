//-----------------------------------------------------------------------------
// File: NullParser.cpp
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Esko Pekkarinen
// Date: 02.02.2015
//
// Description:
// Expression parser implementation that does nothing.
//-----------------------------------------------------------------------------

#include "NullParser.h"

//-----------------------------------------------------------------------------
// Function: NullParser::()
//-----------------------------------------------------------------------------
NullParser::NullParser() : ExpressionParser()
{

}

//-----------------------------------------------------------------------------
// Function: NullParser::()
//-----------------------------------------------------------------------------
NullParser::~NullParser()
{

}

//-----------------------------------------------------------------------------
// Function: NullParser::parseExpression()
//-----------------------------------------------------------------------------
QString NullParser::parseExpression(QString const& expression, bool* /*isValidExpression*/) const
{
    return expression;
}

//-----------------------------------------------------------------------------
// Function: NullParser::isPlainValue()
//-----------------------------------------------------------------------------
bool NullParser::isPlainValue(QString const& /*expression*/) const
{
    return true;
}

//-----------------------------------------------------------------------------
// Function: NullParser::baseForExpression()
//-----------------------------------------------------------------------------
int NullParser::baseForExpression(QString const& /*expression*/) const
{
    return 0;
}