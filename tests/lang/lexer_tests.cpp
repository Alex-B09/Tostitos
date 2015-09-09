#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#else
#ifndef _WIN32
#   define BOOST_TEST_MODULE Lexer
#endif
#endif

#include <boost/test/unit_test.hpp>

#include "Parse/lexer.h"

using namespace TosLang::FrontEnd;

BOOST_AUTO_TEST_CASE( LexerInitTest )
{
    Lexer lex;
    BOOST_REQUIRE(!lex.Init("BadFile.tos"));
	BOOST_REQUIRE_EQUAL(lex.GetCurrentLine(), 0);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentColumn(), 0);

	BOOST_REQUIRE(lex.Init("../inputs/var_init_bool.tos"));
	BOOST_REQUIRE_EQUAL(lex.GetCurrentLine(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentColumn(), 1);
}

BOOST_AUTO_TEST_CASE( LexerVarDeclTest )
{
    Lexer lex;
    BOOST_REQUIRE(lex.Init("../inputs/vardecl.tos"));
	BOOST_REQUIRE_EQUAL(lex.GetCurrentLine(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentColumn(), 1);

    // var MyIntVar : Int;
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
    BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "MyIntVar");
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

    //var MyBoolVar : Bool;    
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
    BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "MyBoolVar");
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

    // End of file
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TOK_EOF);
}

BOOST_AUTO_TEST_CASE( LexerVarInitBoolTest )
{
    Lexer lex;
    BOOST_REQUIRE(lex.Init("../inputs/var_init_bool.tos"));
	BOOST_REQUIRE_EQUAL(lex.GetCurrentLine(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentColumn(), 1);

    //var MyTrueVar : Bool = True;    
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
    BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "MyTrueVar");
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TRUE);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

    //var MyFalseVar : Bool = False;
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
    BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "MyFalseVar");
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::FALSE);
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

    // End of file
    BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TOK_EOF);
}

BOOST_AUTO_TEST_CASE( LexerVarInitIntTest )
{
	Lexer lex;
	BOOST_REQUIRE(lex.Init("../inputs/var_init_int.tos"));
	BOOST_REQUIRE_EQUAL(lex.GetCurrentLine(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentColumn(), 1);

	// var MyIntVar : Int = 42;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "MyIntVar");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 42);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);
}

BOOST_AUTO_TEST_CASE( LexerVarInitIdentifierTest )
{
	Lexer lex;
	BOOST_REQUIRE(lex.Init("../inputs/var_init_identifier.tos"));
	BOOST_REQUIRE_EQUAL(lex.GetCurrentLine(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentColumn(), 1);

	// var MyIntVar : Int = 42;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "MyIntVar");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 42);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

	// var MyIntVar2 : Int = MyIntVar;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "MyIntVar2");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "MyIntVar");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);
}

BOOST_AUTO_TEST_CASE( LexerVarInitBinOpIntTest )
{
	Lexer lex;
	BOOST_REQUIRE(lex.Init("../inputs/binary_op_int.tos"));
	BOOST_REQUIRE_EQUAL(lex.GetCurrentLine(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentColumn(), 1);

	// var V1 : Int = 1 + 1;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "V1");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::PLUS);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

	// var V2 : Int = 1 - 1;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "V2");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::MINUS);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

	// var V3 : Int = 1 * 1;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "V3");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::MULT);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

	// var V4 : Int = 1 / 1;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "V4");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::DIVIDE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

	// var V5 : Int = 1 % 1;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "V5");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::MODULO);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

	// var V6 : Int = 1 & 1;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "V6");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::AND_INT);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

	// var V7 : Int = 1 | 1;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "V7");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::OR_INT);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

	// var V8 : Int = 1 >> 1;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "V8");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::RIGHT_SHIFT);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

	// var V9 : Int = 1 % 1;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "V9");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::LEFT_SHIFT);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentNumber(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);
}

BOOST_AUTO_TEST_CASE( LexerVarInitBinOpBoolTest )
{
	Lexer lex;
	BOOST_REQUIRE(lex.Init("../inputs/binary_op_bool.tos"));
	BOOST_REQUIRE_EQUAL(lex.GetCurrentLine(), 1);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentColumn(), 1);

	// var V1 : Bool = True && False;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "V1");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TRUE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::AND_BOOL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::FALSE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

	// var V2 : Bool = True || False;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "V2");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TRUE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::OR_BOOL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::FALSE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

	// var V3 : Bool = 1 > 2;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "V3");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::GREATER_THAN);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);

	// var V4 : Bool = 1 < 2;
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::VAR);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::IDENTIFIER);
	BOOST_REQUIRE_EQUAL(lex.GetCurrentStr(), "V4");
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::COLON);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::TYPE);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::EQUAL);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::LESS_THAN);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::NUMBER);
	BOOST_REQUIRE_EQUAL(lex.GetNextToken(), Lexer::Token::SEMI_COLON);
}