#include "errorlogger.h"

#include <iostream>

using namespace TosLang::Utils;

std::map<ErrorLogger::ErrorType, std::string> ErrorLogger::mErrorMessages =
{
    // File
    { WRONG_FILE_TYPE,          "FILE ERROR: Wrong file type" },
    { ERROR_OPENING_FILE,       "FILE ERROR: Problem opening the specified file" },

    // Misc
    { MISSING_SEMI_COLON,       "ERROR: Expected a ;" },

    // Var
    { VAR_MISSING_TYPE,         "VAR ERROR: Missing type from variable declaration" },
    { VAR_MISSING_COLON,        "VAR ERROR: Missing : between a variable and its type" },
    { VAR_MISSING_IDENTIFIER,   "VAR ERROR: The var keyword should be followed by an identifier" },

    // Type
    { WRONG_LITERAL_TYPE,       "TYPE ERROR: Trying to instantiate variable with a literal of the wrong type" }
};

void ErrorLogger::PrintError(ErrorType eType)
{
    std::cerr << mErrorMessages[eType] << std::endl;
}
