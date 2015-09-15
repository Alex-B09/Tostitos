#ifndef ERROR_LOGGER_H__TOSTITOS
#define ERROR_LOGGER_H__TOSTITOS

#include <map>
#include <string>

namespace TosLang
{
    namespace Utils
    {
        class ErrorLogger
        {
        public:
            enum ErrorType
            {
                // File
                WRONG_FILE_TYPE,
                ERROR_OPENING_FILE,

                // Literal
                NEW_LINE_IN_LITERAL,
                NUMBER_BAD_SUFFIX,

                // Type
                WRONG_LITERAL_TYPE,
                WRONG_VARIABLE_TYPE,

                // Var
                VAR_MISSING_TYPE,
                VAR_MISSING_COLON,
                VAR_MISSING_IDENTIFIER,
                VAR_REDEFINITION,
                VAR_UNDECLARED_IDENTIFIER,

                // Misc
                MISSING_SEMI_COLON,
            };

        public:
            ErrorLogger(const ErrorLogger&) = delete;
            ErrorLogger& operator=(const ErrorLogger&) = delete;
            ~ErrorLogger() = default;

        public:
            static void PrintError(ErrorType eType);
            static void PrintErrorAtLocation(ErrorType eType, unsigned line, unsigned column);

        private:
            ErrorLogger() = default;

        private:
            static std::map<ErrorType, std::string> mErrorMessages;
            static ErrorLogger mInstance;
        };
    }
}

#endif // ERROR_LOGGER_H__TOSTITOS
