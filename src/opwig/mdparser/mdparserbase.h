// Generated by Bisonc++ V4.01.00 on Mon, 11 Mar 2013 15:52:45 -0300

#ifndef MDParserBase_h_included
#define MDParserBase_h_included

#include <vector>
#include <iostream>

// $insert preincludes
#include "iostream"

namespace // anonymous
{
    struct PI__;
}

// $insert namespace-open
namespace opwig
{


class MDParserBase
{
    public:
// $insert tokens

    // Symbolic tokens:
    enum Tokens__
    {
        IDENTIFIER = 257,
        KEYWORD,
        STRING_LITERAL,
        CHARACTER_LITERAL,
        INTEGER_LITERAL,
        HEXADECIMAL_LITERAL,
        OCTAL_LITERAL,
        FLOAT_LITERAL,
    };

// $insert STYPE
typedef int STYPE__;

    private:
        int d_stackIdx__;
        std::vector<size_t>   d_stateStack__;
        std::vector<STYPE__>  d_valueStack__;

    protected:
        enum Return__
        {
            PARSE_ACCEPT__ = 0,   // values used as parse()'s return values
            PARSE_ABORT__  = 1
        };
        enum ErrorRecovery__
        {
            DEFAULT_RECOVERY_MODE__,
            UNEXPECTED_TOKEN__,
        };
        bool        d_debug__;
        size_t      d_nErrors__;
        size_t      d_requiredTokens__;
        size_t      d_acceptedTokens__;
        int         d_token__;
        int         d_nextToken__;
        size_t      d_state__;
        STYPE__    *d_vsp__;
        STYPE__     d_val__;
        STYPE__     d_nextVal__;

        MDParserBase();

        void ABORT() const;
        void ACCEPT() const;
        void ERROR() const;
        void clearin();
        bool debug() const;
        void pop__(size_t count = 1);
        void push__(size_t nextState);
        void popToken__();
        void pushToken__(int token);
        void reduce__(PI__ const &productionInfo);
        void errorVerbose__();
        size_t top__() const;

    public:
        void setDebug(bool mode);
}; 

inline bool MDParserBase::debug() const
{
    return d_debug__;
}

inline void MDParserBase::setDebug(bool mode)
{
    d_debug__ = mode;
}

inline void MDParserBase::ABORT() const
{
    throw PARSE_ABORT__;
}

inline void MDParserBase::ACCEPT() const
{
    throw PARSE_ACCEPT__;
}

inline void MDParserBase::ERROR() const
{
    throw UNEXPECTED_TOKEN__;
}


// As a convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define MDParser MDParserBase

// $insert namespace-close
}

#endif


