#ifndef ERROR_LOGGER_H__TOSTITOS
#define ERROR_LOGGER_H__TOSTITOS

#include <string>
#include <type_traits>
#include <unordered_map>

namespace TosLang
{
    namespace Utils
    {
        /*
        * \class ErrorLogger
        * \brief Singleton class providing error logging services for the whole TosLang compiler
        */
        class ErrorLogger
        {
        public:
            /*
            * \enum     ErrorType
            * \brief    Every type of error that can be logged by the ErrorLogger
            */
            enum class ErrorType : unsigned int
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
                UNCLOSED_ML_COMMENT,
            };

        private:
            // TODO: This shouldn't be necessary with a fully compliant C++14 compiler
            /*
            * \struct   ErrorTypeHash
            * \brief    Functor providing a hash for the ErrorType enum
            */
            struct ErrorTypeHash
            {
                template <typename T>
                std::size_t operator()(T t) const
                {
                    return static_cast<std::size_t>(t);
                }
            };

        public:
            ErrorLogger(const ErrorLogger&) = delete;
            ErrorLogger& operator=(const ErrorLogger&) = delete;
            ~ErrorLogger() = default;

        public:
            /*
            * \fn           PrintError
            * \param eType  Type of error to log
            * \brief        Logs the error of the type eType to the stderr
            */
            static void PrintError(ErrorType eType);
            
            /*
            * \fn           PrintErrorAtLocation
            * \param eType  Type of error to log
            * \param line   Line where the error happened in the source code
            * \param column Column where the error happened in the source code
            * \brief        Logs the error of the type eType with source location information to the stderr
            */
            static void PrintErrorAtLocation(ErrorType eType, unsigned line, unsigned column);

        private:
            ErrorLogger() = default;

        private:
            static std::unordered_map<ErrorType, std::string, ErrorTypeHash> mErrorMessages;    /*!< Maps the error types to the error messages */
            static ErrorLogger mInstance;                                                       /*!< Single instance of the error logger */
        };
    }
}

#endif // ERROR_LOGGER_H__TOSTITOS
