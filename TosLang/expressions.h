#ifndef EXPR_H__TOSTITOS
#define EXPR_H__TOSTITOS

#include "ast.h"

/*
* \class Expr
* \brief Node of the AST representing a value or an expression producing a value
*/
class Expr : public ASTNode
{
public:
    Expr(NodeKind kind) : ASTNode(kind) { }
    virtual ~Expr() { }

public:
    bool IsLiteral() const { return mKind == BOOLEAN_EXPR && mKind == NUMBER_EXPR; }
};

/*
* \class NumberExpr
* \brief Node of the AST representing a number literal
*/
class NumberExpr : public Expr
{
public:
    NumberExpr(int value) : Expr(NUMBER_EXPR), mValue{ value } { }
    virtual ~NumberExpr() { }

    const int GetValue() const { return mValue; }

private:
    int mValue;
};

/*
* \class BooleanExpr
* \brief Node of the AST representing a boolean literal
*/
class BooleanExpr : public Expr
{
public:
    BooleanExpr(bool value) : Expr(BOOLEAN_EXPR), mValue{ value } { }
    virtual ~BooleanExpr() { }

    const bool GetValue() const { return mValue; }

private:
    bool mValue;
};

#endif // EXPR_H__TOSTITOS
