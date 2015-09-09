#ifndef AST_VISITOR_H__TOSTITOS
#define AST_VISITOR_H__TOSTITOS

#include "../AST/ast.h"

namespace TosLang
{
    namespace Utils
    {
        /*
        * \class ASTVisitor
        * \brief Tree visitor that does a traversal of the AST.
        *        It is based of CRTP, so any derived class should provide itself as the template argument
        */
        template <typename Derived>
        class ASTVisitor
        {
        public:
            ASTVisitor() : mCurrentLevel(0), mCurrentNode(nullptr) { }
            ~ASTVisitor() = default;

        protected:
            /*
            * \fn VisitPostOrder
            * \param root   Root node of the tree to visit
            * \brief        Visit the tree rooted at root by doing a post-order traversal
            */
            void VisitPostOrder(const std::unique_ptr<FrontEnd::ASTNode>& root)
            {
                if (root != nullptr)
                {
                    ++mCurrentLevel;

                    for (auto& childNode : root->GetChildrenNodes())
                        VisitPostOrder(childNode);

                    --mCurrentLevel;
                    mCurrentNode = root.get();

                    DispatchNode(root.get());
                }
            }

            /*
            * \fn VisitPreOrder
            * \param root   Root node of the tree to visit
            * \brief        Visit the tree rooted at root by doing a pre-order traversal
            */
            void VisitPreOrder(const std::unique_ptr<FrontEnd::ASTNode>& root)
            {
                if (root != nullptr)
                {
                    mCurrentNode = root.get();
                    DispatchNode(root.get());

                    ++mCurrentLevel;

                    for (auto& childNode : root->GetChildrenNodes())
                        VisitPreOrder(childNode);

                    --mCurrentLevel;
                }
            }

        protected:  // Declarations
            /*
            * \fn       HandleProgramDecl
            * \brief    Handle a node of the PROGRAM_DECL kind
            */
            void HandleProgramDecl() { }

            /*
            * \fn       HandleVarDecl
            * \brief    Handle a node of the VAR_DECL kind
            */
            void HandleVarDecl() { }

        protected:  // Expressions
            /*
            * \fn       HandleBooleanExpr
            * \brief    Handle a node of the BOOLEAN_EXPR kind
            */
            void HandleBooleanExpr() { }

            /*
            * \fn       HandleNumberExpr
            * \brief    Handle a node of the NUMBER_EXPR kind
            */
            void HandleNumberExpr() { }

        private:
            /*
            * \fn       GetDerived
            * \brief    Gets a reference to the current derived class of ASTVisitor
            * \return   Reference to the current derived class of ASTVisitor
            */
            Derived& GetDerived()
            {
                return *static_cast<Derived*>(this);
            }

            /*
            * \fn           DispatchNode
            * \param node   AST node to dispatch
            * \brief        Dispatch the handling of given node to the correct method of the correct derived class
            */
            void DispatchNode(const FrontEnd::ASTNode* node)
            {
                switch (node->GetKind())
                {
                case FrontEnd::ASTNode::PROGRAM_DECL:
                    GetDerived().HandleProgramDecl();
                    break;
                case FrontEnd::ASTNode::VAR_DECL:
                    GetDerived().HandleVarDecl();
                    break;
                case FrontEnd::ASTNode::BOOLEAN_EXPR:
                    GetDerived().HandleBooleanExpr();
                    break;
                case FrontEnd::ASTNode::NUMBER_EXPR:
                    GetDerived().HandleNumberExpr();
                    break;
                default:
                    break;
                }
            }

        protected:
            unsigned int mCurrentLevel; /*!< Current tree level of the traversal */
            FrontEnd::ASTNode* mCurrentNode;      /*!< Current node being handled in the traversal */
        };
    }
}

#endif // AST_VISITOR_H__TOSTITOS