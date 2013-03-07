// Generated by Flexc++ V1.02.00 on Thu, 07 Mar 2013 15:18:07 -0300

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

// $insert class_ih
#include "mdscanner.ih"

// $insert namespace-open
namespace opwig
{

    // s_ranges__: use (unsigned) characters as index to obtain
    //           that character's range-number.
    //           The range for EOF is defined in a constant in the
    //           class header file
size_t const MDScannerBase::s_ranges__[] =
{
     0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
     4, 4, 4, 4, 4, 4, 4, 5, 6, 7, 8, 8, 8, 8, 9,10,10,10,10,10,10,10,10,11,11,
    11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,13,13,13,13,13,13,14,14,14,14,
    14,15,16,16,16,16,16,16,16,16,17,18,18,18,18,18,19,20,21,21,22,23,24,24,24,
    24,24,24,25,25,25,25,25,26,27,27,27,27,27,27,27,27,28,29,29,29,29,29,30,30,
    30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,
    30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,
    30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,
    30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,
    30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,
    30,30,30,30,30,31,
};

    // s_dfa__ contains the rows of *all* DFAs ordered by start state.
    // The enum class StartCondition__ is defined in the baseclass header
    // INITIAL is always 0.
    // Each entry defines the row to transit to if the column's
    // character range was sensed. Row numbers are relative to the
    // used DFA and d_dfaBase__ is set to the first row of the subset to use.
    // The row's final two values are begin and end indices in
    // s_rfc__[] (rule, flags and count), defining the state's rule details
int const MDScannerBase::s_dfa__[][35] =
{
    // INITIAL
    {-1, 1, 1, 1,-1, 1,-1, 2,-1, 3,-1, 4,-1, 5, 5, 6, 5, 5, 5,-1,
          7,-1, 5,-1, 5, 5, 5, 5, 5, 5,-1,-1,-1,   0, 0},  // 0
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,   0, 1},  // 1
    {-1, 2,-1, 2, 2, 2, 2, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
          9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,-1,-1,   1, 1},  // 2
    {-1,10,-1,10,10,10,10,10,10,-1,10,10,10,10,10,10,10,10,10,10,
         11,10,10,10,10,10,10,10,10,10,10,-1,-1,   1, 1},  // 3
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 4,-1,-1,-1,12,-1,12,-1,-1,
         -1,-1,-1,-1,-1,-1,12,-1,12,-1,-1,-1,-1,   1, 2},  // 4
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 5,-1, 5, 5, 5, 5, 5, 5,-1,
         13,-1, 5,-1, 5, 5, 5, 5, 5, 5,-1,-1,-1,   2, 3},  // 5
    {-1,-1,-1,-1,-1,-1,-1, 2,-1, 3,-1, 5,-1, 5, 5, 5, 5, 5, 5,-1,
         13,-1, 5,-1, 5, 5, 5, 5, 5, 5,-1,-1,-1,   3, 4},  // 6
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,14,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,15,-1,-1,-1,-1,   4, 4},  // 7
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,   4, 5},  // 8
    {-1, 2,-1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
          2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,-1,   5, 5},  // 9
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,   5, 5},  // 10
    {-1,10,-1,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
         10,10,10,10,10,10,10,10,10,10,10,10,-1,   5, 5},  // 11
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,   5, 6},  // 12
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,18,-1,-1,-1,-1,   6, 6},  // 13
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,19,-1,19,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,19,-1,-1,-1,-1,-1,-1,-1,-1,   6, 6},  // 14
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,-1,20,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,20,-1,-1,-1,-1,-1,-1,-1,-1,   6, 6},  // 15
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,   6, 7},  // 16
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,21,-1,21,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,21,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 17
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,22,-1,22,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,22,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 18
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,-1,23,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,23,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 19
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,24,-1,24,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,24,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 20
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,25,-1,25,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,25,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 21
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,26,-1,26,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,26,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 22
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,-1,27,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,27,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 23
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,-1,28,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,28,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 24
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,29,-1,29,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,29,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 25
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,30,-1,30,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,30,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 26
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,31,-1,31,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,31,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 27
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,14,-1,14,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,14,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 28
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,32,-1,32,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,32,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 29
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,-1,17,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,17,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 30
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,33,-1,33,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,33,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 31
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,34,-1,34,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,34,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 32
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,35,-1,35,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,35,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 33
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,36,-1,36,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,36,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 34
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,37,-1,37,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,37,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 35
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,38,-1,38,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,38,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 36
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 5,-1, 5,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1, 5,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 37
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 5,-1, 5,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1, 5,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 38
    // string
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
         -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,   7, 7},  // 0
};

    // The first value is the rule index
    // The second value is the FLAG: see the scannerbase.h file
    // 1: Final     4: Count        11: Final/BOL,Inc     
    // 2: Inc.      5: Final,Count  13: Final/BOL,Count
    // 3: Final,Inc 9: Final/BOL    
    // The third value is the LOP count value (valid for Count flags)
size_t const MDScannerBase::s_rfc__[][3] =
{
//     R  F  C
     { 0, 1, 0},  // 0
     { 3, 1, 0},  // 1
     { 4, 1, 0},  // 2
     { 4, 1, 0},  // 3
     { 1, 1, 0},  // 4
     { 3, 1, 0},  // 5
     { 2, 1, 0},  // 6
};

int const (*MDScannerBase::s_dfaBase__[])[35] =
{
    s_dfa__ + 0,
    s_dfa__ + 39,
};

size_t MDScannerBase::s_istreamNr = 0;

// $insert inputImplementation
MDScannerBase::Input::Input()
:
    d_in(0),
    d_lineNr(1)
{}

MDScannerBase::Input::Input(std::istream *iStream, size_t lineNr)
:
    d_in(iStream),
    d_lineNr(lineNr)
{}

size_t MDScannerBase::Input::get()
{
    switch (size_t ch = next())         // get the next input char
    {
        case '\n':
            ++d_lineNr;
        // FALLING THROUGH

        default:
        return ch;
    }
}

size_t MDScannerBase::Input::next()
{
    size_t ch;

    if (d_deque.empty())                    // deque empty: next char fm d_in
    {
        if (d_in == 0)
            return AT_EOF;
        ch = d_in->get();
        return *d_in ? ch : AT_EOF;
    }

    ch = d_deque.front();
    d_deque.pop_front();

    return ch;
}

void MDScannerBase::Input::reRead(size_t ch)
{
    if (ch < 0x100)
    {
        if (ch == '\n')
            --d_lineNr;
        d_deque.push_front(ch);
    }
}

void MDScannerBase::Input::reRead(std::string const &str, size_t fm)
{
    for (size_t idx = str.size(); idx-- > fm; )
        reRead(str[idx]);
}

MDScannerBase::MDScannerBase(std::istream &in, std::ostream &out)
:
    d_filename("-"),
    d_startCondition(StartCondition__::INITIAL),
    d_state(0),
    d_out(new std::ostream(out.rdbuf())),
    d_sawEOF(false),
    d_atBOL(true),
    d_tailCount(5, std::numeric_limits<size_t>::max()),
// $insert interactiveInit
    d_in(0),
    d_input(new std::istream(in.rdbuf())),
    d_dfaBase__(s_dfa__)
{}

void MDScannerBase::switchStream__(std::istream &in, size_t lineNr)
{
    d_input.close();
    d_state = 0;
    d_input = Input(new std::istream(in.rdbuf()), lineNr);
    d_sawEOF = false;
    d_atBOL = true;
}


MDScannerBase::MDScannerBase(std::string const &infilename, std::string const &outfilename)
:
    d_filename(infilename),
    d_startCondition(StartCondition__::INITIAL),
    d_state(0),
    d_out(outfilename == "-"    ? new std::ostream(std::cout.rdbuf()) :
          outfilename == ""     ? new std::ostream(std::cerr.rdbuf()) :
                                  new std::ofstream(outfilename)),
    d_sawEOF(false),
    d_atBOL(true),
    d_tailCount(5, std::numeric_limits<size_t>::max()),
    d_input(new std::ifstream(infilename)),
    d_dfaBase__(s_dfa__)
{}

void MDScannerBase::switchStreams(std::istream &in, std::ostream &out)
{
    switchStream__(in, 1);
    switchOstream(out);
}


void MDScannerBase::switchOstream(std::ostream &out)
{
    *d_out << std::flush;
    d_out.reset(new std::ostream(out.rdbuf()));
}

// $insert debugFunctions
void MDScannerBase::setDebug(bool onOff)
{}

bool MDScannerBase::debug() const
{
    return false;
}

void MDScannerBase::redo(size_t nChars)
{
    size_t from = nChars >= length() ? 0 : length() - nChars;
    d_input.reRead(d_matched, from);
    d_matched.resize(from);
}

void MDScannerBase::switchOstream(std::string const &outfilename)
{
    *d_out << std::flush;
    d_out.reset(
            outfilename == "-"    ? new std::ostream(std::cout.rdbuf()) :
            outfilename == ""     ? new std::ostream(std::cerr.rdbuf()) :
                                    new std::ofstream(outfilename));
}


void MDScannerBase::switchIstream(std::string const &infilename)
{
    d_input.close();
    d_filename = infilename;
    d_input = Input(new std::ifstream(infilename));
    d_sawEOF = false;
    d_atBOL = true;
}

void MDScannerBase::switchStreams(std::string const &infilename,
                           std::string const &outfilename)
{
    switchOstream(outfilename);
    switchIstream(infilename);
}

void MDScannerBase::pushStream(std::istream  &istr)
{
    std::istream *streamPtr = new std::istream(istr.rdbuf());
    p_pushStream("(istream)", streamPtr);
}

void MDScannerBase::pushStream(std::string const &name)
{
    std::istream *streamPtr = new std::ifstream(name);
    if (!*streamPtr)
    {
        delete streamPtr;
        throw std::runtime_error("Cannot read " + name);
    }
    p_pushStream(name, streamPtr);
}


void MDScannerBase::p_pushStream(std::string const &name, std::istream *streamPtr)
{
    if (d_streamStack.size() == s_maxSizeofStreamStack__)
    {
        delete streamPtr;
        throw std::length_error("Max stream stack size exceeded");
    }

    d_streamStack.push_back(StreamStruct{d_filename, d_input});
    d_filename = name;
    d_input = Input(streamPtr);
    d_sawEOF = false;
    d_atBOL = true;
}


bool MDScannerBase::popStream()
{
    d_input.close();

    if (d_streamStack.empty())
        return false;

    StreamStruct &top = d_streamStack.back();

    d_input =   top.pushedInput;
    d_filename = top.pushedName;
    d_streamStack.pop_back();
    d_sawEOF = false;

    return true;
}

MDScannerBase::ActionType__ MDScannerBase::actionType__(size_t range)
{
    d_nextState = d_dfaBase__[d_state][range];

    if (d_nextState != -1)                  // transition is possible
        return ActionType__::CONTINUE;

    if (atFinalState())                     // FINAL state reached
        return ActionType__::MATCH;

    if (d_matched.size())
        return ActionType__::ECHO_FIRST;    // no match, echo the 1st char

    return range != s_rangeOfEOF__ ? 
                ActionType__::ECHO_CH 
            : 
                ActionType__::RETURN;
}

void MDScannerBase::accept(size_t nChars)          // old name: less
{
    if (nChars < d_matched.size())
    {
        d_input.reRead(d_matched, nChars);
        d_matched.resize(nChars);
    }
}

  // The size of d_matched is determined:
  //    The current state is a known final state (as determined by 
  // inspectRFCs__(), just prior to calling matched__). 
  //    The contents of d_matched are reduced to d_final's size or (if set)
  // to the LOP-rule's tail size.
void MDScannerBase::determineMatchedSize(FinData const &final)
{
    size_t length = final.matchLen;
    if (final.tailCount != std::numeric_limits<size_t>::max())
        length -= final.tailCount;

    d_input.reRead(d_matched, length);      // reread the tail section
    d_matched.resize(length);               // return what's left
}

  // At this point a rule has been matched.  The next character is not part of
  // the matched rule and is sent back to the input.  The final match length
  // is determined, the index of the matched rule is determined, and then
  // d_atBOL is updated. Finally the rule index is returned.
size_t MDScannerBase::matched__(size_t ch)
{
    d_input.reRead(ch);

    if (!d_atBOL)
        d_final.atBOL.rule = std::numeric_limits<size_t>::max();

    FinData &final = d_final.atBOL.rule == std::numeric_limits<size_t>::max() ? 
                            d_final.notAtBOL
                        :
                            d_final.atBOL;

    determineMatchedSize(final);

    d_atBOL = *d_matched.rbegin() == '\n';


    return final.rule;
}

size_t MDScannerBase::getRange__(int ch)       // using int to prevent casts
{
    if (ch != AT_EOF)
        d_sawEOF = false;

    return ch == AT_EOF ? static_cast<size_t>(s_rangeOfEOF__) : s_ranges__[ch];
}

  // At this point d_nextState contains the next state and continuation is
  // possible. The just read char. is appended to d_match, and LOP counts
  // are updated.
void MDScannerBase::continue__(int ch)
{
    d_state = d_nextState;

    if (ch != AT_EOF)
        d_matched += ch;
}

void MDScannerBase::echoCh__(size_t ch)
{
    *d_out << static_cast<char>(ch);
    d_atBOL = ch == '\n';
}


   // At this point there is no continuation. The last character is
   // pushed back into the input stream as well as all but the first char. in
   // the buffer. The first char. in the buffer is echoed to stderr. 
   // If there isn't any 1st char yet then the current char doesn't fit any
   // rules and that char is then echoed
void MDScannerBase::echoFirst__(size_t ch)
{
    d_input.reRead(ch);
    d_input.reRead(d_matched, 1);
    echoCh__(d_matched[0]);
}

    // Inspect all s_rfc__ elements associated with the current state
    //  If the s_rfc__ element has its COUNT flag set then set the 
    // d_tailCount[rule] value to the element's tailCount value, if it has its 
    // INCREMENT flag set then increment d_tailCount[rule]
    //  If neither was set set the d_tailCount[rule] to numeric_limits<size_t>::max()
    // 
    // If the s_rfc__ element has its FINAL flag set then store the rule number
    // in d_final.second. If it has its FINAL + BOL flags set then store the
    // rule number in d_final.first
void MDScannerBase::inspectRFCs__()
{
    for 
    (
        size_t begin = d_dfaBase__[d_state][s_finacIdx__], 
                 end = d_dfaBase__[d_state][s_finacIdx__ + 1];
            begin != end;
                ++begin
    )
    {
        size_t const *rfc = s_rfc__[begin];
        size_t flag = rfc[FLAGS];
        size_t rule = rfc[RULE];

        if (flag & INCREMENT)
            ++d_tailCount[rule];
        else 
            d_tailCount[rule] = (flag & COUNT) ? rfc[ACCCOUNT] : std::numeric_limits<size_t>::max();

        if (flag & FINAL)
        {
            FinData &final = (flag & BOL) ? d_final.atBOL : d_final.notAtBOL;
            final = FinData { rule, d_matched.size(), d_tailCount[rule] };
        }
    }
}

void MDScannerBase::reset__()
{
    d_final = Final { {std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max() }, 
                      {std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max() } };
    d_state = 0;
    d_return = true;

    if (!d_more)
        d_matched.clear();

    d_more = false;
}

int MDScanner::executeAction__(size_t ruleIdx)
try
{
    switch (ruleIdx)
    {
        // $insert actions
        case 0:
        {
#line 33 "mdscanner.lex"
            ;

        }
        break;
        case 1:
        {
#line 35 "mdscanner.lex"
            return MDParserBase::STRING_LITERAL;

        }
        break;
        case 2:
        {
#line 37 "mdscanner.lex"
            return MDParserBase::CHARACTER_LITERAL;

        }
        break;
        case 3:
        {
#line 39 "mdscanner.lex"
            return MDParserBase::INTEGER_LITERAL;

        }
        break;
        case 4:
        {
#line 41 "mdscanner.lex"
            return MDParserBase::IDENTIFIER;

        }
        break;
    }
    noReturn__();
    return 0;
}
catch (Leave__ value)
{
    return static_cast<int>(value);
}

int MDScanner::lex__()
{
    reset__();
    preCode();

    while (true)
    {
        size_t ch = get__();                // fetch next char
        size_t range = getRange__(ch);      // determine the range

        inspectRFCs__();                    // update d_tailCount values

        switch (actionType__(range))        // determine the action
        {
            case ActionType__::CONTINUE:
                continue__(ch);
            continue;

            case ActionType__::MATCH:
            {
                d_token__ = executeAction__(matched__(ch));
                if (return__())
                {
                    print();
                    return d_token__;
                }
                break;
            }

            case ActionType__::ECHO_FIRST:
                echoFirst__(ch);
            break;

            case ActionType__::ECHO_CH:
                echoCh__(ch);
            break;

            case ActionType__::RETURN:
                if (!popStream())
                    return 0;
            continue;
        } // switch

        reset__();
        preCode();
    } // while
}

void MDScannerBase::print__() const
{
}


// $insert namespace-close
}
