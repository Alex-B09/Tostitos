#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#else
#ifndef _WIN32
#   define BOOST_TEST_MODULE SymbolCollector
#endif
#endif

#include <boost/test/unit_test.hpp>

#include "frontend_error_fixture.h"

#include "Parse/parser.h"
#include "Sema/symbolcollector.h"

//////////////////// CORRECT USE CASES ////////////////////

BOOST_FIXTURE_TEST_CASE( CollectSymbolVar, FrontEndErrorFixture )
{
    Parser parser;
    std::unique_ptr<ASTNode> rootNode = parser.ParseProgram("../inputs/var/var_decl.tos");
    BOOST_REQUIRE(rootNode != nullptr);

    auto symbolTable = std::make_shared<TosLang::FrontEnd::SymbolTable>();
    TosLang::FrontEnd::SymbolCollector sCollector{ symbolTable };
    sCollector.Run(rootNode);

    Symbol varSymbol;

    BOOST_REQUIRE(symbolTable->GetSymbol("", "MyIntVar", std::stack<int>{}, varSymbol));
    BOOST_REQUIRE(!varSymbol.IsFunction());
    BOOST_REQUIRE(varSymbol.GetName() == "MyIntVar");
    BOOST_REQUIRE(varSymbol.GetScopeID() == 0); // At global scope
    BOOST_REQUIRE(varSymbol.GetVariableType() == TosLang::Common::Type::NUMBER);

    BOOST_REQUIRE(symbolTable->GetSymbol("", "MyBoolVar", std::stack<int>{}, varSymbol));
    BOOST_REQUIRE(!varSymbol.IsFunction());
    BOOST_REQUIRE(varSymbol.GetName() == "MyBoolVar");
    BOOST_REQUIRE(varSymbol.GetScopeID() == 0); // At global scope
    BOOST_REQUIRE(varSymbol.GetVariableType() == TosLang::Common::Type::BOOL);

    BOOST_REQUIRE(symbolTable->GetSymbol("", "MyStringVar", std::stack<int>{}, varSymbol));
    BOOST_REQUIRE(!varSymbol.IsFunction());
    BOOST_REQUIRE(varSymbol.GetName() == "MyStringVar");
    BOOST_REQUIRE(varSymbol.GetScopeID() == 0); // At global scope
    BOOST_REQUIRE(varSymbol.GetVariableType() == TosLang::Common::Type::STRING);
}

BOOST_FIXTURE_TEST_CASE( CollectSymbolFunctionNoParam, FrontEndErrorFixture )
{
    Parser parser;
    std::unique_ptr<ASTNode> rootNode = parser.ParseProgram("../inputs/function/fn_def_void.tos");
    BOOST_REQUIRE(rootNode != nullptr);

    auto symbolTable = std::make_shared<TosLang::FrontEnd::SymbolTable>();
    TosLang::FrontEnd::SymbolCollector sCollector{ symbolTable };
    sCollector.Run(rootNode);

    Symbol fnSymbol;
    BOOST_REQUIRE(symbolTable->GetSymbol("", "MyFunc", std::stack<int>{}, fnSymbol));
    
    BOOST_REQUIRE(fnSymbol.IsFunction());
    BOOST_REQUIRE(fnSymbol.GetName() == "MyFunc");
    BOOST_REQUIRE(fnSymbol.GetScopeID() == 0); // At global scope
    BOOST_REQUIRE(fnSymbol.GetFunctionParamTypes().size() == 0);
    BOOST_REQUIRE(fnSymbol.GetFunctionReturnType() == TosLang::Common::Type::VOID);
}

BOOST_FIXTURE_TEST_CASE( CollectSymbolFunctionMultiParam, FrontEndErrorFixture )
{
    Parser parser;
    std::unique_ptr<ASTNode> rootNode = parser.ParseProgram("../inputs/function/fn_def_multi_args.tos");
    BOOST_REQUIRE(rootNode != nullptr);

    auto symbolTable = std::make_shared<TosLang::FrontEnd::SymbolTable>();
    TosLang::FrontEnd::SymbolCollector sCollector{ symbolTable };
    sCollector.Run(rootNode);

    Symbol fnSymbol;
    BOOST_REQUIRE(symbolTable->GetSymbol("", "MyFunc", std::stack<int>{}, fnSymbol));

    BOOST_REQUIRE(fnSymbol.IsFunction());
    BOOST_REQUIRE(fnSymbol.GetName() == "MyFunc");
    BOOST_REQUIRE(fnSymbol.GetScopeID() == 0); // At global scope
    BOOST_REQUIRE(fnSymbol.GetFunctionReturnType() == TosLang::Common::Type::NUMBER);

    auto paramTypes = fnSymbol.GetFunctionParamTypes();
    BOOST_REQUIRE(paramTypes.size() == 3);
    BOOST_REQUIRE(std::all_of(paramTypes.begin(), paramTypes.end(), [](const TosLang::Common::Type& t) { return t == TosLang::Common::Type::NUMBER; }));

    std::stack<int> scopeStack;
    scopeStack.push(0);
    scopeStack.push(1);

    for (size_t i = 0; i < 3; ++i)
    {
        Symbol paramSym;
        std::stringstream sStream;
        sStream << "arg";
        sStream << i + 1;
        BOOST_REQUIRE(symbolTable->GetSymbol("MyFunc", sStream.str(), scopeStack, paramSym));
        
        BOOST_REQUIRE(!paramSym.IsFunction());
        BOOST_REQUIRE(paramSym.GetName() == sStream.str());
        BOOST_REQUIRE(paramSym.GetScopeID() == 1); // At function scope
        BOOST_REQUIRE(paramSym.GetVariableType() == TosLang::Common::Type::NUMBER);
    }
}

BOOST_FIXTURE_TEST_CASE( CollectSymbolFunctionWithLocalVar, FrontEndErrorFixture )
{
    Parser parser;
    std::unique_ptr<ASTNode> rootNode = parser.ParseProgram("../inputs/call/call_one_arg.tos");
    BOOST_REQUIRE(rootNode != nullptr);

    auto symbolTable = std::make_shared<TosLang::FrontEnd::SymbolTable>();
    TosLang::FrontEnd::SymbolCollector sCollector{ symbolTable };
    sCollector.Run(rootNode);

    Symbol fnSymbol;
    
    // Validate the identity function symbol
    BOOST_REQUIRE(symbolTable->GetSymbol("", "identity", std::stack<int>{}, fnSymbol));
    BOOST_REQUIRE(fnSymbol.IsFunction());
    BOOST_REQUIRE(fnSymbol.GetName() == "identity");
    BOOST_REQUIRE(fnSymbol.GetScopeID() == 0); // At global scope
    BOOST_REQUIRE(fnSymbol.GetFunctionParamTypes().size() == 1);
    BOOST_REQUIRE(fnSymbol.GetFunctionReturnType() == TosLang::Common::Type::NUMBER);

    Symbol paramSym;
    std::stack<int> scopeStack;
    scopeStack.push(0); // Global scope ID
    scopeStack.push(1); // First defined function scope ID

    // Validate the identity function parameter
    BOOST_REQUIRE(symbolTable->GetSymbol("identity", "i", scopeStack, paramSym));
    BOOST_REQUIRE(!paramSym.IsFunction());
    BOOST_REQUIRE(paramSym.GetName() == "i");
    BOOST_REQUIRE(paramSym.GetScopeID() == 1); // At function scope
    BOOST_REQUIRE(paramSym.GetVariableType() == TosLang::Common::Type::NUMBER);

    // Validate the main function symbol
    BOOST_REQUIRE(symbolTable->GetSymbol("", "main", std::stack<int>{}, fnSymbol));
    BOOST_REQUIRE(fnSymbol.IsFunction());
    BOOST_REQUIRE(fnSymbol.GetName() == "main");
    BOOST_REQUIRE(fnSymbol.GetScopeID() == 0); // At global scope
    BOOST_REQUIRE(fnSymbol.GetFunctionParamTypes().size() == 0);
    BOOST_REQUIRE(fnSymbol.GetFunctionReturnType() == TosLang::Common::Type::VOID);

    scopeStack.pop();   // Getting out of the identity function
    scopeStack.push(2); // Main function scope ID

    // Validate main's local variable
    BOOST_REQUIRE(symbolTable->GetSymbol("main", "MyInt", scopeStack, paramSym));
    BOOST_REQUIRE(!paramSym.IsFunction());
    BOOST_REQUIRE(paramSym.GetName() == "MyInt");
    BOOST_REQUIRE(paramSym.GetScopeID() == 2); // At function scope
    BOOST_REQUIRE(paramSym.GetVariableType() == TosLang::Common::Type::NUMBER);
}

//////////////////// ERROR USE CASES ////////////////////

BOOST_FIXTURE_TEST_CASE( CollectSymbolVarRedefinition, FrontEndErrorFixture )
{

}

BOOST_FIXTURE_TEST_CASE( CollectSymbolFunctionRedefinition, FrontEndErrorFixture )
{

}

BOOST_FIXTURE_TEST_CASE( CollectSymbolFunctionParamRedefinition, FrontEndErrorFixture )
{

}
