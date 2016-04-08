#ifndef BASIC_BLOCK__TOSTITOS
#define BASIC_BLOCK__TOSTITOS

#include "virtualinstruction.h"

#include <memory>
#include <string>
#include <vector>

namespace TosLang
{
    namespace BackEnd
    {
        class BasicBlock;

        using BlockPtr = std::shared_ptr<BasicBlock>;
        using BlockList = std::vector<BlockPtr>;

        /*
        * \class BasicBlock
        * \brief A basic block is a list of instructions having the following properties:
        *        - If one instruction in the basic block is executed, all other instructions 
        *          in the basic block are guaranteed to be executed
        *        - Instructions will be executed sequentially
        *        - The last instruction in a basic block is either a jump or a return
        */
        class BasicBlock
        {
        public:
            /*
            * \fn           BasicBlock
            * \brief        Ctor
            * \param name   Name of the basic block. If none is given, the block will be named 'BlockN' 
            *               where N is a monotonically increasing number
            */
            BasicBlock(const std::string& name = "") : mInstructions{}
            {
                // OK since we won't create multiple blocks in parallel
                static size_t blockNumber = 0;

                if (name.empty())
                    mName = "Block" + std::to_string(blockNumber++);
                else
                    mName = name;
            }

        public:
            using inst_iterator = std::vector<VirtualInstruction>::iterator;
            using inst_const_iterator = std::vector<VirtualInstruction>::const_iterator;

            using bb_iterator = BlockList::iterator;
            using bb_const_iterator = BlockList::const_iterator;

        public:
            inst_iterator inst_begin() { return mInstructions.begin(); }
            inst_iterator inst_end() { return mInstructions.end(); }
            inst_const_iterator inst_begin() const { return mInstructions.begin(); }
            inst_const_iterator inst_end() const { return mInstructions.end(); }

            bb_iterator bb_begin() { return mAdjacentBlocks.begin(); }
            bb_iterator bb_end() { return mAdjacentBlocks.end(); }
            bb_const_iterator bb_begin() const { return mAdjacentBlocks.begin(); }
            bb_const_iterator bb_end() const { return mAdjacentBlocks.end(); }
            
        public:
            /*
            * \fn           InsertBranch
            * \brief        Adds a branch to a basic block. Note that this function 
            *               is not responsible for adding machine instructions to the basic block.
            * \param block  Basic block to branch to 
            */
            void InsertBranch(const BasicBlock* block);

            /*
            * \fn           InsertBranch
            * \brief        Adds a branch to a basic block. Note that this function 
            *               is not responsible for adding machine instructions to the basic block.
            * \param block  Basic block to branch to
            */
            void InsertBranch(const BlockPtr& block);

            /*
            * \fn           InsertInstruction
            * \brief        Appends a virtual instruction to the basic block
            * \param inst   Instruction to be added
            */
            void InsertInstruction(VirtualInstruction&& inst);

            /*
            * \fn           InsertInstruction
            * \brief        Appends a virtual instruction to the basic block
            * \param inst   Instruction to be added
            */
            void InsertInstruction(const VirtualInstruction& inst);

        public:
            /*
            * \fn       GetName
            * \brief    Gives access to the name of the basic block
            */
            const std::string& GetName() const { return mName; }

        private:
            std::vector<VirtualInstruction> mInstructions;  /*!< Instructions making up the basic block */
            BlockList mAdjacentBlocks;                      /*!< List of blocks pointed to by the outgoing edges of the block */
            std::string mName;                              /*<! Name of the basic block. For printing and debugginf purposes */
        };
    }
}

#endif // BASIC_BLOCK__TOSTITOS
