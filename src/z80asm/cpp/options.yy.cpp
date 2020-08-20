// cpp/options.yy.cpp generated by reflex 2.0.1 from cpp/options.l

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  OPTIONS USED                                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define REFLEX_OPTION_dotall              true
#define REFLEX_OPTION_fast                true
#define REFLEX_OPTION_freespace           true
#define REFLEX_OPTION_header_file         "cpp/options.yy.h"
#define REFLEX_OPTION_lex                 lex
#define REFLEX_OPTION_lexer               OptionsLexer
#define REFLEX_OPTION_noline              true
#define REFLEX_OPTION_outfile             "cpp/options.yy.cpp"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %top user code                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


// silence warnings from RE-flex
#ifdef _MSC_VER
#pragma warning(disable:4102)
#pragma warning(disable:4800)
#else
#ifdef __GNUC__
//#pragma GCC   diagnostic ignored "-Wignored-qualifiers"
#else
#ifdef __clang__
//#pragma clang diagnostic ignored "-Wignored-qualifiers"
#endif
#endif
#endif


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  REGEX MATCHER                                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/matcher.h>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  ABSTRACT LEXER CLASS                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/abslexer.h>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  LEXER CLASS                                                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

class OptionsLexer : public reflex::AbstractLexer<reflex::Matcher> {
public:
    typedef reflex::AbstractLexer<reflex::Matcher> AbstractBaseLexer;
    OptionsLexer(
        const reflex::Input& input = reflex::Input(),
        std::ostream&        os    = std::cout)
        :
        AbstractBaseLexer(input, os) {
    }
    static const int INITIAL = 0;
    virtual int lex();
    int lex(
        const reflex::Input& input,
        std::ostream*        os = NULL) {
        in(input);
        if (os)
            out(*os);
        return lex();
    }
};

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %{ user code %}                                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// z80asm restart
// Copyright (C) Paulo Custodio, 2011-2020
// License: The Artistic License 2.0, http://www.perlfoundation.org/artistic_license_2_0
//-----------------------------------------------------------------------------


#include "App.h"

#include <string>
#include <utility>
#include <vector>

#include <cassert>
#include <climits>
#include <cstring>
#include <cstdlib>

static int parseNum(const std::string& text);
static void optionDefine(const std::string& text);


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 2: rules                                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

extern void reflex_code_INITIAL(reflex::Matcher&);

int OptionsLexer::lex() {
    static const reflex::Pattern PATTERN_INITIAL(reflex_code_INITIAL);
    if (!has_matcher())
        matcher(new Matcher(PATTERN_INITIAL, stdinit(), this));
    while (true) {
        switch (matcher().scan()) {
        case 0:
            if (matcher().at_end())
                return int();
            else
                out().put(matcher().input());
            break;
        case 1: // rule at line 50: -\?\z|-h\z :
        { App::ExitManual(); }
        break;
        case 2: // rule at line 51: -v\z :
        { app.options.verbose = true; return true; }
        break;
        case 3: // rule at line 52: -m\z :
        { app.options.mapfile = true; return true; }
        break;
        case 4: // rule at line 53: -s\z :
        { app.options.symtable = true; return true; }
        break;
        case 5: // rule at line 54: -l\z :
        { app.options.listfile = true; return true; }
        break;
        case 6: // rule at line 55: -g\z :
        { app.options.globaldef = true; return true; }
        break;
        case 7: // rule at line 56: -b\z :
        { app.options.makeBinary = true; return true; }
        break;
        case 8: // rule at line 57: -d\z :
        { app.options.update = true; return true; }

        break;
        case 9: // rule at line 59: -mz80\z :
        { app.options.cpu.Init(Cpu::Type::Z80); return true; }
        break;
        case 10: // rule at line 60: -mz80n\z :
        { app.options.cpu.Init(Cpu::Type::Z80N); return true; }
        break;
        case 11: // rule at line 61: -mz180\z :
        { app.options.cpu.Init(Cpu::Type::Z180); return true; }
        break;
        case 12: // rule at line 62: -mr2k\z :
        { app.options.cpu.Init(Cpu::Type::R2K); return true; }
        break;
        case 13: // rule at line 63: -mr3k\z :
        { app.options.cpu.Init(Cpu::Type::R3K); return true; }
        break;
        case 14: // rule at line 64: -m8080\z :
        { app.options.cpu.Init(Cpu::Type::I8080); return true; }
        break;
        case 15: // rule at line 65: -m8085\z :
        { app.options.cpu.Init(Cpu::Type::I8085); return true; }
        break;
        case 16: // rule at line 66: -mgbz80\z :
        { app.options.cpu.Init(Cpu::Type::GBZ80); return true; }
        break;
        case 17: { // rule at line 67: -mti83\z :
            app.options.cpu.Init(Cpu::Type::Z80);
            app.options.arch.Init(Arch::Type::TI83);
            return true;
        }
        break;
        case 18: { // rule at line 70: -mti83plus\z :
            app.options.cpu.Init(Cpu::Type::Z80);
            app.options.arch.Init(Arch::Type::TI83PLUS);
            return true;
        }
        break;
        case 19: // rule at line 73: -IXIY\z :
        { app.options.swapIxIy = true; return true; }
        break;
        case 20: // rule at line 74: -opt-speed\z :
        { app.options.optimizeSpeed = true; return true; }
        break;
        case 21: { // rule at line 75: -debug\z :
            app.options.debugInfo = true;
            app.options.mapfile = true;
            return true;
        }
        break;
        case 22: // rule at line 78: -I[\x00-\xff]+\z :
        { app.options.includePath.push_back(text() + 2);  return true; }

        break;
        case 23: // rule at line 80: -L[\x00-\xff]+\z :
        { app.options.libraryPath.push_back(text() + 2);  return true; }
        break;
        case 24: // rule at line 81: -x[\x00-\xff]+\z :
        { app.options.outputLibrary = text() + 2; return true; }
        break;
        case 25: // rule at line 82: -l[\x00-\xff]+\z :
        { app.options.libraries.push_back(text() + 2); return true; }

        break;
        case 26: // rule at line 84: -O[\x00-\xff]+\z :
        { app.options.outputDirectory = text() + 2; return true; }
        break;
        case 27: // rule at line 85: -o[\x00-\xff]+\z :
        { app.options.outputFile = text() + 2; return true; }

        break;
        case 28: { // rule at line 87: -D(?:[A-Z_a-z][0-9A-Z_a-z]*)(?:=(?:(?:0[Xx][0-9A-Fa-f]+|\$[0-9A-Fa-f]+|[0-9][0-9A-Fa-f]*[Hh])|(?:[0-9]+)))?\z :
            optionDefine(text() + 2); return true;
        }
        break;
        case 29: // rule at line 89: -split-bin\z :
        { app.options.splitBinary = true; return true; }

        break;
        case 30: // rule at line 91: [\x00-\xff] :
        { return false; }

        break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 3: user code                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


// parse NUM
static int parseNum(const std::string& text) {
    char* end = nullptr;
    const char* p = text.c_str();
    long lval;
    int radix;
    char suffix = '\0';

    if (p[0] == '\0') 		// empty
        return -1;
    else if (p[0] == '$') {
        p++;
        radix = 16;
    }
    else if (p[0] == '0' && tolower(p[1]) == 'x') {
        p += 2;
        radix = 16;
    }
    else if (isdigit(p[0]) && tolower(p[strlen(p) - 1]) == 'h') {
        suffix = p[strlen(p) - 1];
        radix = 16;
    }
    else
        radix = 10;

    lval = strtol(p, &end, radix);
    if (end == nullptr || *end != suffix || errno == ERANGE || lval < 0 || lval > INT_MAX)
        return -1;
    else
        return static_cast<int>(lval);
}

static void optionDefine(const std::string& text) {
    using namespace std;

    auto p = text.find('=');
    if (p == string::npos) {		// -Dvar
        app.options.defines.push_back({ text, 1});
    }
    else {							// -Dvar=value
        string name = text.substr(0, p);
        int num = parseNum(text.c_str() + p + 1);
        assert(num >= 0);

        app.options.defines.push_back({ name, num});
    }
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  TABLES                                                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/matcher.h>

#if defined(OS_WIN)
#pragma warning(disable:4101 4102)
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-label"
#elif defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-label"
#endif

void reflex_code_INITIAL(reflex::Matcher& m) {
    int c0 = 0, c1 = 0;
    m.FSM_INIT(c1);

S0:
    m.FSM_FIND();
    c1 = m.FSM_CHAR();
    if (c1 == '-') goto S2;
    if (0 <= c1) goto S19;
    return m.FSM_HALT(c1);

S2:
    m.FSM_TAKE(30);
    c1 = m.FSM_CHAR();
    if (c1 == 'x') goto S51;
    if (c1 == 'v') goto S25;
    if (c1 == 's') goto S34;
    if (c1 == 'o') goto S48;
    if (c1 == 'm') goto S27;
    if (c1 == 'l') goto S37;
    if (c1 == 'h') goto S23;
    if (c1 == 'g') goto S39;
    if (c1 == 'd') goto S43;
    if (c1 == 'b') goto S41;
    if (c1 == 'O') goto S52;
    if (c1 == 'L') goto S50;
    if (c1 == 'I') goto S46;
    if (c1 == 'D') goto S53;
    if (c1 == '?') goto S21;
    return m.FSM_HALT(c1);

S19:
    m.FSM_TAKE(30);
    return m.FSM_HALT();

S21:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(1, c1);
    return m.FSM_HALT(c1);

S23:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(1, c1);
    return m.FSM_HALT(c1);

S25:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(2, c1);
    return m.FSM_HALT(c1);

S27:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(3, c1);
    if (c1 == 'z') goto S63;
    if (c1 == 't') goto S73;
    if (c1 == 'r') goto S66;
    if (c1 == 'g') goto S71;
    if (c1 == '8') goto S69;
    return m.FSM_HALT(c1);

S34:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(4, c1);
    if (c1 == 'p') goto S77;
    return m.FSM_HALT(c1);

S37:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(5, c1);
    if (0 <= c1) goto S81;
    return m.FSM_HALT(c1);

S39:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(6, c1);
    return m.FSM_HALT(c1);

S41:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(7, c1);
    return m.FSM_HALT(c1);

S43:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(8, c1);
    if (c1 == 'e') goto S89;
    return m.FSM_HALT(c1);

S46:
    c1 = m.FSM_CHAR();
    if (c1 == 'X') goto S91;
    if (0 <= c1) goto S94;
    return m.FSM_HALT(c1);

S48:
    c1 = m.FSM_CHAR();
    if (c1 == 'p') goto S96;
    if (0 <= c1) goto S99;
    return m.FSM_HALT(c1);

S50:
    c1 = m.FSM_CHAR();
    if (0 <= c1) goto S101;
    return m.FSM_HALT(c1);

S51:
    c1 = m.FSM_CHAR();
    if (0 <= c1) goto S103;
    return m.FSM_HALT(c1);

S52:
    c1 = m.FSM_CHAR();
    if (0 <= c1) goto S105;
    return m.FSM_HALT(c1);

S53:
    c1 = m.FSM_CHAR();
    if ('a' <= c1 && c1 <= 'z') goto S107;
    if (c1 == '_') goto S107;
    if ('A' <= c1 && c1 <= 'Z') goto S107;
    return m.FSM_HALT(c1);

S57:
    m.FSM_TAKE(1);
    return m.FSM_HALT();

S59:
    m.FSM_TAKE(2);
    return m.FSM_HALT();

S61:
    m.FSM_TAKE(3);
    return m.FSM_HALT();

S63:
    c1 = m.FSM_CHAR();
    if (c1 == '8') goto S114;
    if (c1 == '1') goto S116;
    return m.FSM_HALT(c1);

S66:
    c1 = m.FSM_CHAR();
    if (c1 == '3') goto S120;
    if (c1 == '2') goto S118;
    return m.FSM_HALT(c1);

S69:
    c1 = m.FSM_CHAR();
    if (c1 == '0') goto S122;
    return m.FSM_HALT(c1);

S71:
    c1 = m.FSM_CHAR();
    if (c1 == 'b') goto S124;
    return m.FSM_HALT(c1);

S73:
    c1 = m.FSM_CHAR();
    if (c1 == 'i') goto S126;
    return m.FSM_HALT(c1);

S75:
    m.FSM_TAKE(4);
    return m.FSM_HALT();

S77:
    c1 = m.FSM_CHAR();
    if (c1 == 'l') goto S128;
    return m.FSM_HALT(c1);

S79:
    m.FSM_TAKE(5);
    return m.FSM_HALT();

S81:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(25, c1);
    if (0 <= c1) goto S81;
    return m.FSM_HALT(c1);

S83:
    m.FSM_TAKE(6);
    return m.FSM_HALT();

S85:
    m.FSM_TAKE(7);
    return m.FSM_HALT();

S87:
    m.FSM_TAKE(8);
    return m.FSM_HALT();

S89:
    c1 = m.FSM_CHAR();
    if (c1 == 'b') goto S132;
    return m.FSM_HALT(c1);

S91:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(22, c1);
    if (c1 == 'I') goto S134;
    if (0 <= c1) goto S94;
    return m.FSM_HALT(c1);

S94:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(22, c1);
    if (0 <= c1) goto S94;
    return m.FSM_HALT(c1);

S96:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(27, c1);
    if (c1 == 't') goto S139;
    if (0 <= c1) goto S99;
    return m.FSM_HALT(c1);

S99:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(27, c1);
    if (0 <= c1) goto S99;
    return m.FSM_HALT(c1);

S101:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(23, c1);
    if (0 <= c1) goto S101;
    return m.FSM_HALT(c1);

S103:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(24, c1);
    if (0 <= c1) goto S103;
    return m.FSM_HALT(c1);

S105:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(26, c1);
    if (0 <= c1) goto S105;
    return m.FSM_HALT(c1);

S107:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(28, c1);
    if ('a' <= c1 && c1 <= 'z') goto S107;
    if (c1 == '_') goto S107;
    if ('A' <= c1 && c1 <= 'Z') goto S107;
    if (c1 == '=') goto S152;
    if ('0' <= c1 && c1 <= '9') goto S107;
    return m.FSM_HALT(c1);

S114:
    c1 = m.FSM_CHAR();
    if (c1 == '0') goto S156;
    return m.FSM_HALT(c1);

S116:
    c1 = m.FSM_CHAR();
    if (c1 == '8') goto S159;
    return m.FSM_HALT(c1);

S118:
    c1 = m.FSM_CHAR();
    if (c1 == 'k') goto S161;
    return m.FSM_HALT(c1);

S120:
    c1 = m.FSM_CHAR();
    if (c1 == 'k') goto S163;
    return m.FSM_HALT(c1);

S122:
    c1 = m.FSM_CHAR();
    if (c1 == '8') goto S165;
    return m.FSM_HALT(c1);

S124:
    c1 = m.FSM_CHAR();
    if (c1 == 'z') goto S168;
    return m.FSM_HALT(c1);

S126:
    c1 = m.FSM_CHAR();
    if (c1 == '8') goto S170;
    return m.FSM_HALT(c1);

S128:
    c1 = m.FSM_CHAR();
    if (c1 == 'i') goto S172;
    return m.FSM_HALT(c1);

S130:
    m.FSM_TAKE(25);
    return m.FSM_HALT();

S132:
    c1 = m.FSM_CHAR();
    if (c1 == 'u') goto S174;
    return m.FSM_HALT(c1);

S134:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(22, c1);
    if (c1 == 'Y') goto S176;
    if (0 <= c1) goto S94;
    return m.FSM_HALT(c1);

S137:
    m.FSM_TAKE(22);
    return m.FSM_HALT();

S139:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(27, c1);
    if (c1 == '-') goto S178;
    if (0 <= c1) goto S99;
    return m.FSM_HALT(c1);

S142:
    m.FSM_TAKE(27);
    return m.FSM_HALT();

S144:
    m.FSM_TAKE(23);
    return m.FSM_HALT();

S146:
    m.FSM_TAKE(24);
    return m.FSM_HALT();

S148:
    m.FSM_TAKE(26);
    return m.FSM_HALT();

S150:
    m.FSM_TAKE(28);
    return m.FSM_HALT();

S152:
    c1 = m.FSM_CHAR();
    if ('1' <= c1 && c1 <= '9') goto S194;
    if (c1 == '0') goto S181;
    if (c1 == '$') goto S190;
    return m.FSM_HALT(c1);

S156:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(9, c1);
    if (c1 == 'n') goto S203;
    return m.FSM_HALT(c1);

S159:
    c1 = m.FSM_CHAR();
    if (c1 == '0') goto S205;
    return m.FSM_HALT(c1);

S161:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(12, c1);
    return m.FSM_HALT(c1);

S163:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(13, c1);
    return m.FSM_HALT(c1);

S165:
    c1 = m.FSM_CHAR();
    if (c1 == '5') goto S213;
    if (c1 == '0') goto S211;
    return m.FSM_HALT(c1);

S168:
    c1 = m.FSM_CHAR();
    if (c1 == '8') goto S215;
    return m.FSM_HALT(c1);

S170:
    c1 = m.FSM_CHAR();
    if (c1 == '3') goto S217;
    return m.FSM_HALT(c1);

S172:
    c1 = m.FSM_CHAR();
    if (c1 == 't') goto S220;
    return m.FSM_HALT(c1);

S174:
    c1 = m.FSM_CHAR();
    if (c1 == 'g') goto S222;
    return m.FSM_HALT(c1);

S176:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(19, c1);
    if (0 <= c1) goto S94;
    return m.FSM_HALT(c1);

S178:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(27, c1);
    if (c1 == 's') goto S226;
    if (0 <= c1) goto S99;
    return m.FSM_HALT(c1);

S181:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(28, c1);
    if (c1 == 'x') goto S229;
    if (c1 == 'h') goto S239;
    if ('a' <= c1 && c1 <= 'f') goto S233;
    if (c1 == 'X') goto S229;
    if (c1 == 'H') goto S239;
    if ('A' <= c1 && c1 <= 'F') goto S233;
    if ('0' <= c1 && c1 <= '9') goto S194;
    return m.FSM_HALT(c1);

S190:
    c1 = m.FSM_CHAR();
    if ('a' <= c1 && c1 <= 'f') goto S242;
    if ('A' <= c1 && c1 <= 'F') goto S242;
    if ('0' <= c1 && c1 <= '9') goto S242;
    return m.FSM_HALT(c1);

S194:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(28, c1);
    if (c1 == 'h') goto S239;
    if ('a' <= c1 && c1 <= 'f') goto S233;
    if (c1 == 'H') goto S239;
    if ('A' <= c1 && c1 <= 'F') goto S233;
    if ('0' <= c1 && c1 <= '9') goto S194;
    return m.FSM_HALT(c1);

S201:
    m.FSM_TAKE(9);
    return m.FSM_HALT();

S203:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(10, c1);
    return m.FSM_HALT(c1);

S205:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(11, c1);
    return m.FSM_HALT(c1);

S207:
    m.FSM_TAKE(12);
    return m.FSM_HALT();

S209:
    m.FSM_TAKE(13);
    return m.FSM_HALT();

S211:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(14, c1);
    return m.FSM_HALT(c1);

S213:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(15, c1);
    return m.FSM_HALT(c1);

S215:
    c1 = m.FSM_CHAR();
    if (c1 == '0') goto S255;
    return m.FSM_HALT(c1);

S217:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(17, c1);
    if (c1 == 'p') goto S259;
    return m.FSM_HALT(c1);

S220:
    c1 = m.FSM_CHAR();
    if (c1 == '-') goto S261;
    return m.FSM_HALT(c1);

S222:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(21, c1);
    return m.FSM_HALT(c1);

S224:
    m.FSM_TAKE(19);
    return m.FSM_HALT();

S226:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(27, c1);
    if (c1 == 'p') goto S265;
    if (0 <= c1) goto S99;
    return m.FSM_HALT(c1);

S229:
    c1 = m.FSM_CHAR();
    if ('a' <= c1 && c1 <= 'f') goto S268;
    if ('A' <= c1 && c1 <= 'F') goto S268;
    if ('0' <= c1 && c1 <= '9') goto S268;
    return m.FSM_HALT(c1);

S233:
    c1 = m.FSM_CHAR();
    if (c1 == 'h') goto S273;
    if ('a' <= c1 && c1 <= 'f') goto S233;
    if (c1 == 'H') goto S273;
    if ('A' <= c1 && c1 <= 'F') goto S233;
    if ('0' <= c1 && c1 <= '9') goto S233;
    return m.FSM_HALT(c1);

S239:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(28, c1);
    if ('0' <= c1 && c1 <= '9') goto S239;
    return m.FSM_HALT(c1);

S242:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(28, c1);
    if ('a' <= c1 && c1 <= 'f') goto S242;
    if ('A' <= c1 && c1 <= 'F') goto S242;
    if ('0' <= c1 && c1 <= '9') goto S242;
    return m.FSM_HALT(c1);

S247:
    m.FSM_TAKE(10);
    return m.FSM_HALT();

S249:
    m.FSM_TAKE(11);
    return m.FSM_HALT();

S251:
    m.FSM_TAKE(14);
    return m.FSM_HALT();

S253:
    m.FSM_TAKE(15);
    return m.FSM_HALT();

S255:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(16, c1);
    return m.FSM_HALT(c1);

S257:
    m.FSM_TAKE(17);
    return m.FSM_HALT();

S259:
    c1 = m.FSM_CHAR();
    if (c1 == 'l') goto S277;
    return m.FSM_HALT(c1);

S261:
    c1 = m.FSM_CHAR();
    if (c1 == 'b') goto S279;
    return m.FSM_HALT(c1);

S263:
    m.FSM_TAKE(21);
    return m.FSM_HALT();

S265:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(27, c1);
    if (c1 == 'e') goto S281;
    if (0 <= c1) goto S99;
    return m.FSM_HALT(c1);

S268:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(28, c1);
    if ('a' <= c1 && c1 <= 'f') goto S268;
    if ('A' <= c1 && c1 <= 'F') goto S268;
    if ('0' <= c1 && c1 <= '9') goto S268;
    return m.FSM_HALT(c1);

S273:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(28, c1);
    return m.FSM_HALT(c1);

S275:
    m.FSM_TAKE(16);
    return m.FSM_HALT();

S277:
    c1 = m.FSM_CHAR();
    if (c1 == 'u') goto S284;
    return m.FSM_HALT(c1);

S279:
    c1 = m.FSM_CHAR();
    if (c1 == 'i') goto S286;
    return m.FSM_HALT(c1);

S281:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(27, c1);
    if (c1 == 'e') goto S288;
    if (0 <= c1) goto S99;
    return m.FSM_HALT(c1);

S284:
    c1 = m.FSM_CHAR();
    if (c1 == 's') goto S291;
    return m.FSM_HALT(c1);

S286:
    c1 = m.FSM_CHAR();
    if (c1 == 'n') goto S293;
    return m.FSM_HALT(c1);

S288:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(27, c1);
    if (c1 == 'd') goto S295;
    if (0 <= c1) goto S99;
    return m.FSM_HALT(c1);

S291:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(18, c1);
    return m.FSM_HALT(c1);

S293:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(29, c1);
    return m.FSM_HALT(c1);

S295:
    c1 = m.FSM_CHAR();
    if (m.FSM_META_EOB(c1))
        m.FSM_TAKE(20, c1);
    if (0 <= c1) goto S99;
    return m.FSM_HALT(c1);

S297:
    m.FSM_TAKE(18);
    return m.FSM_HALT();

S299:
    m.FSM_TAKE(29);
    return m.FSM_HALT();

S301:
    m.FSM_TAKE(20);
    return m.FSM_HALT();
}

