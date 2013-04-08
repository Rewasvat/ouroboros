// Generated by Flexc++ V1.02.00 on Mon, 08 Apr 2013 20:24:21 -0300

#ifndef MDScannerBASE_H_INCLUDED
#define MDScannerBASE_H_INCLUDED

#include <limits>
#include <iostream>
#include <deque>
#include <string>
#include <vector>
#include <memory>


// $insert namespace-open
namespace opwig
{

class MDScannerBase
{
                // idx: rule, value: tail length (NO_INCREMENTS if no tail)
    typedef std::vector<int> VectorInt;

    enum        // RuleFlagsCount Indices, see s_rfc__[]
    {
        RULE = 0,
        FLAGS,
        ACCCOUNT,
    };

    enum
    {
        FINAL = 1,
        INCREMENT = 2,
        COUNT = 4,
        BOL = 8
    };

    enum 
    {
        AT_EOF = -1
    };

protected:
    enum Leave__
    {};

    enum class ActionType__
    {
        CONTINUE,               // transition succeeded, go on
        ECHO_CH,                // echo ch itself (d_matched empty)
        ECHO_FIRST,             // echo d_matched[0], push back the rest
        MATCH,                  // matched a rule
        RETURN,                 // no further continuation, lex returns 0.
    };

public:
    enum class StartCondition__ {
        // $insert startCondNames
        INITIAL,
        string
    };

private:
    struct FinData            // Info about intermediate matched rules while
    {                           // traversing the DFA
        size_t rule;
        size_t matchLen;
        size_t tailCount;
    };

    struct Final
    {
        FinData atBOL;
        FinData notAtBOL;
    };

        // class Input encapsulates all input operations. 
        // Its member get() returns the next input character
// $insert inputInterface
    class Input
    {
        std::deque<unsigned char> d_deque;  // pending input chars
        std::istream *d_in;                 // ptr for easy streamswitching
        size_t d_lineNr;                    // line count

        public:
            Input();
                                       // iStream: dynamically allocated
            Input(std::istream *iStream, size_t lineNr = 1);
            size_t get();                   // the next range
            void reRead(size_t ch);         // push back 'ch' (if < 0x100)
                                            // push back str from idx 'fmIdx'
            void reRead(std::string const &str, size_t fmIdx);
            size_t lineNr() const
            {
                return d_lineNr;
            }
            void close()                    // force closing the stream
            {
                delete d_in;
                d_in = 0;                   // switchStreams also closes
            }

        private:
            size_t next();                  // obtain the next character
    };

protected:

    struct StreamStruct
    {
        std::string pushedName;
        Input pushedInput;
    };

private:

    std::vector<StreamStruct>    d_streamStack;

    std::string     d_filename;             // name of the currently processed
    static size_t   s_istreamNr;            // file. With istreams it receives
                                            // the name "<istream #>", where
                                            // # is the sequence number of the 
                                            // istream (starting at 1)
    StartCondition__  d_startCondition;
    size_t          d_state;
    int             d_nextState;
    std::shared_ptr<std::ostream> d_out;
    bool            d_sawEOF;               // saw EOF: ignore tailCount
    bool            d_atBOL;                // the matched text starts at BOL
    std::vector<size_t> d_tailCount;         
    Final d_final;                          // 1st for BOL rules
                                            
                                            // only used interactively:
    std::istream *d_in;                     // points to the input stream
    std::shared_ptr<std::istringstream> d_line; // holds line fm d_in
    
    Input           d_input;
    std::string     d_matched;              // matched characters
    bool            d_return;               // return after a rule's action 
    bool            d_more;                 // set to true by more()

protected:
    std::istream   *d_in__;
    int d_token__;                          // returned by lex__



    int     const (*d_dfaBase__)[65];

    static int     const s_dfa__[][65];
    static int     const (*s_dfaBase__[])[65];
    enum: bool { s_interactive__ = false };
    enum: size_t {
        s_rangeOfEOF__           = 62,
        s_finacIdx__             = 63,
        s_nRules__               = 52,
        s_maxSizeofStreamStack__ = 10
    };
    static size_t  const s_ranges__[];
    static size_t  const s_rfc__[][3];

public:
    MDScannerBase(MDScannerBase const &other)             = delete;
    MDScannerBase &operator=(MDScannerBase const &rhs)    = delete;

    bool                debug()     const;
    std::string const  &filename()  const;
    std::string const  &matched()   const;

    size_t              length()    const;
    size_t              lineNr()    const;

    void                setDebug(bool onOff);

    void                switchOstream(std::ostream &out);
    void                switchOstream(std::string const &outfilename);


    void                switchStreams(std::istream &in,
                                      std::ostream &out = std::cout);

    void                switchIstream(std::string const &infilename);
    void                switchStreams(std::string const &infilename,
                                      std::string const &outfilename);


protected:
    MDScannerBase(std::istream &in, std::ostream &out);
    MDScannerBase(std::string const &infilename, std::string const &outfilename);

    StartCondition__  startCondition() const;   // current start condition
    bool            popStream();
    std::ostream   &out();
    void            begin(StartCondition__ startCondition);
    void            echo() const;
    void            leave(int retValue) const;

//    `accept(n)' returns all but the first `n' characters of the current
// token back to the input stream, where they will be rescanned when the
// scanner looks for the next match.
//  So, it matches n of the characters in the input buffer, and so it accepts
//  n characters, rescanning the rest. 
    void            accept(size_t nChars = 0);      // former: less
    void            redo(size_t nChars = 0);        // rescan the last nChar
                                                    // characters, reducing
                                                    // length() by nChars
    void            more();
    void            push(size_t ch);                // push char to Input
    void            push(std::string const &txt);   // same: chars


    std::vector<StreamStruct> const &streamStack() const;

    void            pushStream(std::istream &curStream);
    void            pushStream(std::string const &curName);


    void            setFilename(std::string const &name);
    void            setMatched(std::string const &text);

    static std::string istreamName__();
        
        // members used by lex__(): they end in __ and should not be used
        // otherwise.

    ActionType__    actionType__(size_t range); // next action
    bool            interactiveLine__();        // refresh an interactive line
    bool            return__();                 // 'return' from codeblock
    size_t          matched__(size_t ch);       // handles a matched rule
    size_t          getRange__(int ch);         // convert char to range
    size_t          get__();                    // next character
    size_t          state__() const;            // current state 
    void            continue__(int ch);         // handles a transition
    void            echoCh__(size_t ch);        // echoes ch, sets d_atBOL
    void            echoFirst__(size_t ch);     // handles unknown input
    void            inspectRFCs__();            // update d_tailCount
    void            noReturn__();               // d_return to false
    void            print__() const;            // optionally print token
    void            pushFront__(size_t ch);     // return char to Input
    void            reset__();                  // prepare for new cycle
                                                // next input stream:
    void            switchStream__(std::istream &in, size_t lineNr);   

private:
    void p_pushStream(std::string const &name, std::istream *streamPtr);
    void determineMatchedSize(FinData const &final);
    bool atFinalState();
};

inline std::ostream &MDScannerBase::out()
{
    return *d_out;
}

inline void MDScannerBase::push(size_t ch)
{
    d_input.reRead(ch);
}

inline void MDScannerBase::push(std::string const &str)
{
    d_input.reRead(str, 0);
}

inline bool MDScannerBase::atFinalState()
{
    return d_final.notAtBOL.rule != std::numeric_limits<size_t>::max() || 
            (d_atBOL && d_final.atBOL.rule != std::numeric_limits<size_t>::max());
}

inline void MDScannerBase::setFilename(std::string const &name)
{
    d_filename = name;
}

inline void MDScannerBase::setMatched(std::string const &text)
{
    d_matched = text;
}

inline std::string const &MDScannerBase::matched() const
{
    return d_matched;
}

inline MDScannerBase::StartCondition__ MDScannerBase::startCondition() const
{
    return d_startCondition;
}

inline std::string const &MDScannerBase::filename() const
{
    return d_filename;
}

inline void MDScannerBase::echo() const
{
    *d_out << d_matched;
}

inline size_t MDScannerBase::length() const
{
    return d_matched.size();
}

inline void MDScannerBase::leave(int retValue) const
{
    throw static_cast<Leave__>(retValue);
}

inline size_t MDScannerBase::lineNr() const
{
    return d_input.lineNr();
}

inline void MDScannerBase::more()
{
    d_more = true;
}

inline void MDScannerBase::begin(StartCondition__ startCondition)
{
    d_dfaBase__ = 
        s_dfaBase__[static_cast<int>(d_startCondition = startCondition)];
}

inline size_t MDScannerBase::state__() const
{
    return d_state;
}

inline size_t MDScannerBase::get__()
{
    return d_input.get();
}

inline bool MDScannerBase::return__()
{
    return d_return;
}

inline void MDScannerBase::noReturn__()
{
    d_return = false;
}

// $insert namespace-close
}

#endif //  MDScannerBASE_H_INCLUDED




