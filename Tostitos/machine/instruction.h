#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "utils.h"

using MachineEngine::ProcessorSpace::Utils::UInt8;
using MachineEngine::ProcessorSpace::Utils::UInt16;
using MachineEngine::ProcessorSpace::Utils::UInt32;

namespace MachineEngine
{
    namespace ProcessorSpace
    {
        /**
        * \class Instruction
        * \brief Abstraction over a Chip16 instruction
        */
        class Instruction
        {
        public:
            /**
            * \fn           Instruction
            * \brief        Default constructor
            * \param value  Value of the instruction. 0 by default.
            */
            explicit Instruction(const UInt32 value = 0);

            /**
            * \fn           Instruction
            * \brief        Constructor
            * \param value  Value of the instruction. 0 by default.
            */
			//explicit Instruction(InstructionOpCode iType);

            /**
            * \fn       Instruction
            * \brief    Destructor
            */
            ~Instruction() = default;

        public:
            /**
            * \fn       GetOpcode
            * \brief    Fetch the instruction opcode
            * \return   The instruction opcode
            */
            UInt8 GetOpcode() const;

            /**
            * \fn       GetFirstOperand
            * \brief    Fetch the first operand of the instruction
            * \return   The first operand of the instruction
            */
            UInt8 GetFirstOperand() const;

            /**
            * \fn       GetSecondOperand
            * \brief    Fetch the second operand of the instruction when the instruction
            *           doesn't use an immediate value
            * \return   The second operand of the instruction or pure garbage
            */
            UInt8 GetSecondOperand() const;

            /**
            * \fn       GetThirdOperand
            * \brief    Fetch the third operand of the instruction when the instruction
            *           doesn't use an immediate value or isn't inplace
            * \return   The third operand of the instruction or pure garbage
            */
            UInt8 GetThirdOperand() const;

            /**
            * \fn       GetImmediateValue
            * \brief    Fetch the immediate value contained in the instruction
            * \return   The immediate value contained in the instruction
            */
            UInt16 GetImmediateValue() const;

            /**
            * \fn           SetFirstOperand
            * \brief        Set the first operand of the instruction
            * \param value  The value to assign to the first operand
            */
            void SetFirstOperand(UInt8 value);

            /**
            * \fn           SetSecondOperand
            * \brief        Set the second operand of the instruction when the instruction
            *               doesn't use an immediate value
            * \param value  The value to assign to the second operand
            */
            void SetSecondOperand(UInt8 value);

            /**
            * \fn           SetThirdOperand
            * \brief        Set the third operand of the instruction when the instruction
            *               doesn't use an immediate value or isn't inplace
            * \param value  The value to assign to the third operand
            */
            void SetThirdOperand(UInt8 value);

            /**
            * \fn           SetImmediateValue
            * \brief        Set the immediate value contained in the instruction if it uses an immediate value
            * \param value  The value to assign to the immediate value of the instruction
            */
            void SetImmediateValue(UInt16 value);

            /**
            * \fn       GetType
            * \brief    Fetch the type of the instruction
            * \return   The type of the instruction
            */
            UInt8 GetType() const;

        public:
            /*
            * \fn       IsArithmeticInstruction
            * \brief    Indicates if the instruction is an arithmetic operation
            * \return   Boolean indicating if the instruction is an arithmetic operation
            */
            bool IsArithmeticInstruction() const;

            /**
            * \fn       IsInplace
            * \brief    Indicates if the instruction is an inplace operation
            * \return   Boolean indicating if the instruction us an inplace operation
            */
            bool IsInplace() const;

            /**
            * \fn       UseImmediateValue
            * \brief    Indicates if the instruction make use of an immediate value
            * \return   Boolean indicating the use of an immediate value
            */
            bool UseImmediateValue() const;

            /*
            * \fn       UseSecondOperand
            * \brief    Indicates if the instruction uses of a second operand
            * \return   Boolean indicating the use of a second operand
            */
            bool UseSecondOperand() const;

            /*
            * \fn       UseThirdOperand
            * \brief    Indicates if the instruction uses of a third operand
            * \return   Boolean indicating the use of a third operand
            */
            bool UseThirdOperand() const;

        private:
            UInt32 mValue;		    /*!< 4 byte value of the instruction */
        };
    }
}

#endif // INSTRUCTION_H
