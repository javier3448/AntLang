#include "./grapher.h"


GraphvizNode Grapher::graphExpression(AstExpression *expr)
{
    static int exprId = 0;

    std::string name = "\"expr" +std::to_string(exprId++) + "\"";

    std::string label;
    switch (expr->kind) {
        case NumberLiteral:
            label = expr->numberLiteral.string.toStdString();
        break;
        case BinaryExpression:
            label = std::string(expr->binaryForm._operator.stringRepresentation());
        case CastExpression:
            //[!] Only works for nativeTypes
            label = std::string("Cast expression ") + expr->castForm.typeExpression._type.stringRepresentation();
        break;
    }

    //Node declaration
    std::string code = name + " [\n" +
                              "label = \"" + label + "\",\n"
                              "shape = \"box\",\n" +
                              "];\n";

    switch (expr->kind) {
        case NumberLiteral:
            return GraphvizNode{name, code};
        break;

        case BinaryExpression:{
            auto leftNode = graphExpression(expr->binaryForm.left);
            auto rightNode = graphExpression(expr->binaryForm.right);

            code += leftNode.code + rightNode.code;

            code += name + "->" + leftNode.name + ";\n" +
                    name + "->" + rightNode.name + ";\n";

            return GraphvizNode{name, code};
        }break;

        case CastExpression:{
            auto expNode = graphExpression(expr->castForm.expression);

            code += expNode.code;

            code += name + "->" + expNode.name + ";\n";

            return GraphvizNode{name, code};
        }break;
    }

    assert(false && "Grapher not implemented for that expression kind yet!");
    //@Bodge: just to make clang shut up about not return. I am asserting
    //false, so we are never gonna get to this code (in debug mode)
    return GraphvizNode{name, code};
}

