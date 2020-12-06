#ifndef GRAPHER_H
#define GRAPHER_H

#include "pch.h"

#include "astexpression.h"

//@EZ TODO: put .h and .cpp outsde the Parser folder

//Does the graphviz of a node. We might decide against this because maintaining
//it is too much work, but honestly is *really* hard to visualize tagged union
//in this debugger so we will see

//We will use std::string and a billion string reallocs for now because this should
//only be used for debugging and I dont want to spend too much time in this code

struct GraphvizNode {
    std::string name;
    std::string code;
};

namespace Grapher{
    GraphvizNode graphExpression(AstExpression* expr);
};

#endif // GRAPHER_H
