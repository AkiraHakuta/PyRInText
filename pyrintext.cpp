#include <cstring>
#include "cmdline.h" // from https://github.com/tanakh/cmdline

#include "antlr4-runtime.h"
#include "PyRInTextLexer.h"
#include "PyRInTextParser.h"
#include "PyRInTextListener.h"

#include "antlr4json.h"
using namespace antlr4;
using namespace tree;
using namespace std;

#include <Windows.h>

string sep = "###PyRInText2019###";
string version = "1.1";

map<string, string> pl_cmd;


class GetPyRCode : public PyRInTextListener{
    public:
        int PYCODE_left_len = strlen("\\begin{pycode}");
        int PYCODE_right_len =  strlen("\\end{pycode}");
        int PYC_left_len =  strlen("\\pyc{");
        int PYC_right_len =  strlen("\\pyc}");
        int PYP_left_len =  strlen("\\pyp{");
        int PYP_right_len =  strlen("\\pyp}");

        int RCODE_left_len = strlen("\\begin{Rcode}");
        int RCODE_right_len =  strlen("\\end{Rcode}");
        int RC_left_len =  strlen("\\Rc{");
        int RC_right_len =  strlen("\\Rc}");
        int RCAT_left_len =  strlen("\\Rcat{");
        int RCAT_right_len =  strlen("\\Rcat}");

        ParseTreeProperty<string>* pycd;
        ParseTreeProperty<string>* Rcd;

        GetPyRCode(ParseTreeProperty<string>* pycd1, ParseTreeProperty<string>* Rcd1){
            pycd = pycd1;
            Rcd  = Rcd1;
        }

        string getPYC(ParseTree *ctx) { return pycd->get(ctx); }
        void setPYC(ParseTree *ctx, string s) { pycd->put(ctx, s); }

        string getRC(ParseTree *ctx) { return Rcd->get(ctx); }
        void setRC(ParseTree *ctx, string s) { Rcd->put(ctx, s); }

        void enterStat(PyRInTextParser::StatContext * /*ctx*/) override { }
        void exitStat(PyRInTextParser::StatContext *ctx) override { 
            string pybuf = "";
            for (int i = 0; i < ctx->body().size(); i++){                
                PyRInTextParser::BodyContext* bodyi =  ctx->body(i);
                pybuf += getPYC(bodyi);                
            }
            setPYC(ctx, pybuf);

            string Rbuf = "";
            for (int i = 0; i < ctx->body().size(); i++){                
                PyRInTextParser::BodyContext* bodyi =  ctx->body(i);
                Rbuf += getRC(bodyi);                
            }
            setRC(ctx, Rbuf);
        }

        void enterBody(PyRInTextParser::BodyContext * /*ctx*/) override { }
        void exitBody(PyRInTextParser::BodyContext *ctx) override { 
            setPYC(ctx, getPYC(ctx->pyr()));
            setRC(ctx, getRC(ctx->pyr()));
        }

        void enterPycode(PyRInTextParser::PycodeContext * /*ctx*/) override { }
        void exitPycode(PyRInTextParser::PycodeContext *ctx) override { 
            size_t index = (ctx->start)->getTokenIndex();
            string index_str = "print(\'"+sep+"\')\n" + "print(" + to_string(index) + ")\n"+ "print(\'"+sep+"')\n"; 
            string buf = ctx->getText();
            size_t strLen = buf.length();
            buf = buf.substr(PYCODE_left_len, strLen - PYCODE_left_len - PYCODE_right_len) + "\n";
            setPYC(ctx, index_str + buf);
        }

        void enterPyc(PyRInTextParser::PycContext * /*ctx*/) override { }
        void exitPyc(PyRInTextParser::PycContext *ctx) override {
            size_t index = (ctx->start)->getTokenIndex();
            string index_str = "print(\'"+sep+"\')\n" + "print(" + to_string(index) + ")\n"+ "print(\'"+sep+"')\n"; 
            string buf = ctx->getText();
            size_t strLen = buf.length();
            buf = buf.substr(PYC_left_len, strLen - PYC_left_len - PYC_right_len) + "\n";
            setPYC(ctx, index_str + buf);
        }

        void enterPyp(PyRInTextParser::PypContext * /*ctx*/) override { }
        void exitPyp(PyRInTextParser::PypContext *ctx) override {
            size_t index = (ctx->start)->getTokenIndex();
            string index_str = "print(\'"+sep+"\')\n" + "print(" + to_string(index) + ")\n"+ "print(\'"+sep+"')\n"; 
            string buf = ctx->getText();
            size_t strLen = buf.length();
            buf = buf.substr(PYP_left_len, strLen - PYP_left_len - PYP_right_len);
            buf = "print(" + buf + ")\n";
            setPYC(ctx, index_str + buf);
        }

        void enterRcode(PyRInTextParser::RcodeContext * /*ctx*/) override { }
        void exitRcode(PyRInTextParser::RcodeContext *ctx) override { 
            size_t index = (ctx->start)->getTokenIndex();
            string index_str = "cat(\'"+sep+"\')\n" + "cat(" + to_string(index) + ")\n"+ "cat(\'"+sep+"')\n"; 
            string buf = ctx->getText();
            size_t strLen = buf.length();
            buf = buf.substr(RCODE_left_len, strLen - RCODE_left_len - RCODE_right_len) + "\n";
            setRC(ctx, index_str + buf);
        }

        void enterRc(PyRInTextParser::RcContext * /*ctx*/) override { }
        void exitRc(PyRInTextParser::RcContext *ctx) override { 
            size_t index = (ctx->start)->getTokenIndex();
            string index_str = "cat(\'"+sep+"\')\n" + "cat(" + to_string(index) + ")\n"+ "cat(\'"+sep+"')\n"; 
            string buf = ctx->getText();
            size_t strLen = buf.length();
            buf = buf.substr(RC_left_len, strLen - RC_left_len - RC_right_len) + "\n";
            setRC(ctx, index_str + buf);
        }

        void enterRcat(PyRInTextParser::RcatContext * /*ctx*/) override { }
        void exitRcat(PyRInTextParser::RcatContext *ctx) override { 
            size_t index = (ctx->start)->getTokenIndex();
            string index_str = "cat(\'"+sep+"\')\n" + "cat(" + to_string(index) + ")\n"+ "cat(\'"+sep+"')\n"; 
            string buf = ctx->getText();
            size_t strLen = buf.length();
            buf = buf.substr(RCAT_left_len, strLen - RCAT_left_len - RCAT_right_len);
            buf = "cat(" + buf + ")\n";
            setRC(ctx, index_str + buf);
        }

        void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
        void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
        void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
        void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }        
};



class SetTextCode : public PyRInTextListener{
    public:
        ParseTreeProperty<string>* textcd;
        map<int, string> *result_map;

        SetTextCode(ParseTreeProperty<string>* textcd1, map<int, string>* result_map1){
            textcd = textcd1;
            result_map = result_map1;
        }

        string getText(ParseTree *ctx) { return textcd->get(ctx); }
        void setText(ParseTree *ctx, string s) { textcd->put(ctx, s); }

        void enterStat(PyRInTextParser::StatContext * /*ctx*/) override { }
        void exitStat(PyRInTextParser::StatContext *ctx) override { 
            string buf = "";
            for (int i = 0; i < ctx->body().size(); i++){                
                PyRInTextParser::BodyContext* bodyi =  ctx->body(i);
                buf += getText(bodyi);                
            }
            setText(ctx, buf);
        }

        void enterBody(PyRInTextParser::BodyContext * /*ctx*/) override { }
        void exitBody(PyRInTextParser::BodyContext *ctx) override { 
            string buf;
            size_t ctx_type = ctx->getStart()->getType();
            if (ctx_type == PyRInTextParser::BKSL or ctx_type == PyRInTextParser::OTHER)
                buf = ctx->getText();
            else
                buf = getText(ctx->pyr());              
            setText(ctx, buf);
        }

        void enterPycode(PyRInTextParser::PycodeContext * /*ctx*/) override { }
        void exitPycode(PyRInTextParser::PycodeContext *ctx) override { 
            size_t index = (ctx->start)->getTokenIndex();
            auto itr = result_map->find(index);
            if(itr != result_map->end())
                setText(ctx, result_map->at(index));
        }

        void enterPyc(PyRInTextParser::PycContext * /*ctx*/) override { }
        void exitPyc(PyRInTextParser::PycContext *ctx) override {
            size_t index = (ctx->start)->getTokenIndex();
            auto itr = result_map->find(index);
            if(itr != result_map->end())
                setText(ctx, result_map->at(index));    
        }

        void enterPyp(PyRInTextParser::PypContext * /*ctx*/) override { }
        void exitPyp(PyRInTextParser::PypContext *ctx) override {
            size_t index = (ctx->start)->getTokenIndex();
            auto itr = result_map->find(index);
            if(itr != result_map->end())
                setText(ctx, result_map->at(index));          
        }

        void enterRcode(PyRInTextParser::RcodeContext * /*ctx*/) override { }
        void exitRcode(PyRInTextParser::RcodeContext *ctx) override { 
            size_t index = (ctx->start)->getTokenIndex();
            auto itr = result_map->find(index);
            if(itr != result_map->end())
                setText(ctx, result_map->at(index));
        }

        void enterRc(PyRInTextParser::RcContext * /*ctx*/) override { }
        void exitRc(PyRInTextParser::RcContext *ctx) override { 
            size_t index = (ctx->start)->getTokenIndex();
            auto itr = result_map->find(index);
            if(itr != result_map->end())
                setText(ctx, result_map->at(index));
        }

        void enterRcat(PyRInTextParser::RcatContext * /*ctx*/) override { }
        void exitRcat(PyRInTextParser::RcatContext *ctx) override { 
            size_t index = (ctx->start)->getTokenIndex();
            auto itr = result_map->find(index);
            if(itr != result_map->end())
                setText(ctx, result_map->at(index));
        }

        void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
        void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
        void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
        void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }        
};



string getFileName(const string &fn)
{
    string::size_type pos;
    if((pos = fn.find_last_of(".")) == string::npos){
        return fn;
    } 
    return fn.substr(0, pos);
}


string getFileExtension(const string &fn)
{
    string::size_type pos;
    if((pos = fn.find_last_of(".")) == string::npos){
        return "";
    }
    return fn.substr(pos + 1);
}


bool ExecCmd(const char* cmd, string& stdOut, int& exitCode) {
    stdOut = "";
    FILE* fp = popen(cmd, "r");
    if (fp == NULL){
        cerr << "popen error" << "\n";
        return false;
    }
    shared_ptr<FILE> pipe(fp , [&](FILE* p) {exitCode = pclose(p); });
    //cerr << "exitCode=" << exitCode << "\n";
    if (!pipe) { 
        cerr << "!pipe" << "\n";       
        return false;
    }
    array<char, 256> buf;
    while (!feof(pipe.get())) {
        if (fgets(buf.data(), buf.size(), pipe.get()) != nullptr) {
            stdOut += buf.data();
        }
    }
    return true;
}


vector<string> split(string stringToBeSplitted, string delimeter)
{
     vector<string> splittedString;
     int startIndex = 0;
     int  endIndex = 0;
     while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() ) {
       string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
       splittedString.push_back(val);
       startIndex = endIndex + delimeter.size();
     }
     if(startIndex < stringToBeSplitted.size()) {
       string val = stringToBeSplitted.substr(startIndex);
       splittedString.push_back(val);
     }
     return splittedString;
}


string replaceString(string target, string from, string to) 
{
    string result = target;
    string::size_type pos = 0;
    while(pos = result.find(from, pos), pos != string::npos) {
        result.replace(pos, from.length(), to);
        pos += to.length();
    }
    return result;
}


void set_result_map(string code, string file_name, map<int, string>& result_map_1, string pl_name)
{
    if (code == "")
        return;
    ofstream writeFile;
    writeFile.open(file_name);
    writeFile << code;
    writeFile.close();
    cout << "Output written on " <<  file_name << "\n";
    string com_str = pl_cmd[pl_name] + file_name; 
    string result;
    int exitCode;
    vector<string> result_vec; 
    const char* cmd = com_str.c_str();
    if (!ExecCmd(cmd, result, exitCode) or exitCode != 0){
        cerr << com_str + " error" << "\n";
        return;   
    }
    else{
        //cout << "result=" << result << "\n";
        cout << com_str << "\n";
        result_vec = split(result, sep);
        if (result_vec.size() < 3)
            return;
        for (int j = 1; j < result_vec.size(); j += 2){
            string value = result_vec[j+1];        
            size_t strLen = value.length();
            if (pl_name == "Python")
                value = value.substr(1, strLen - 2);
            else
                value = value.substr(0, strLen);     
            value = replaceString(value, "\r\n", "\n");
            result_map_1[stoi(result_vec[j])] = value;
        }                
    }
}  


string GetConfigString(const string& filePath, const char* pSectionName, const char* pKeyName)
{
    if (filePath.empty()) {
        return "";
    }
    array<char, MAX_PATH> buf = {};
    GetPrivateProfileStringA(pSectionName, pKeyName, "", &buf.front(), static_cast<DWORD>(buf.size()), filePath.c_str());
    return string(&buf.front());
}


string  getcurrpath()
{
    char szModulePath[MAX_PATH];
    GetModuleFileNameA(NULL, szModulePath, sizeof(szModulePath)/sizeof(szModulePath[0]));
    string result = szModulePath;
    string::size_type pos;
    if((pos = result.find_last_of("\\")) == string::npos){
        return result;
    } 
    return result.substr(0, pos);
}


void cmdline_msg(cmdline::parser* cp){    
    cout << cp->usage();
    cout  << "filename (add the suffix \"_pyr\"  e.g. test_pyr.tex)" << "\n";
    cout  << "e.g. $ C:/.../pyrintext.exe test_pyr.tex -p ans=0 -r \"value<-23\"" << "\n";
}


bool checkFileExistence(const string& str)
{
    ifstream ifs(str);
    return ifs.is_open();
}


string getLanguageCmd(map<unsigned int,JSON_NODE> &ajson, string lang)
{
    unsigned int lang_addr = getJasonNodeKeyAddr(ajson, lang);
    string lcmd = "";
    if (lang_addr == 0)        
        return "None";
    //cout << lang_addr << "\n";
    JSON_NODE* jn = jasonNodeWalk(ajson, ajson[lang_addr], "cccc");
    for ( ; ; jn = &ajson[jn->sibling_addr]){
            lcmd += jasonNodeWalk(ajson, ajson[jn->my_addr], "c")->atom + " ";
        if (jn->sibling_addr == 0) break;
    }
    if (lcmd == "")
        return "None";
    return lcmd;
}


int main(int argc, const char *args[])
{  
    cmdline::parser cp;
    cp.add<string>("pycd", 'p', "insert code in the top of Python (e.g. -p ans=1)", false, "");
    cp.add<string>("rcd", 'r', "insert code in the top of R (e.g. -r \"b<-0\")", false, "");
    cp.add("help", 'h', "print usage and exit");
    cp.add("version", 'v', "print version and exit");
    cp.footer("");
    cp.set_program_name("pyrintext.exe filename");

    bool ok = cp.parse(argc, args);
    if (argc == 1 || cp.exist("help")){
        cmdline_msg(&cp);
        return 0;
    }
    if (argc == 1 || cp.exist("version")){
        cout << "pyrintext " + version << "\n";
        return 0;
    }
      
    if (!ok){
        cerr << cp.error() << "\n" << cp.usage();
        return 0;
    }
    if (cp.rest().size() != 1){
        cout << "argument error\n";
        cmdline_msg(&cp);
        return 0;
    }
    string fname = cp.rest()[0];
    string pyct = cp.get<string>("pycd");
    string rct = cp.get<string>("rcd");
    if (pyct != "")
        pyct += "\n";    
    if (rct != "")
        rct += "\n";
    
    cout << "This is pyrintext " + version << "\n";    
    
    //string Rscript, Rscript_encoding, Python_option;
    string currpath = getcurrpath();
    string inifilePath =  currpath + "\\..\\pyrintext.ini";
    if (!checkFileExistence(inifilePath)){
        cerr << inifilePath << " does not exist" << "\n";
        return 0;
    }

    map<unsigned int,JSON_NODE> ajson = antlr4json(inifilePath);
    //dump_antlr4json(ajson);
    pl_cmd["Python"] = getLanguageCmd(ajson, "Python");
    pl_cmd["Rscript"] = getLanguageCmd(ajson, "Rscript");
    
    ParseTreeProperty<string>* pycd = new ParseTreeProperty<string>();   
    ParseTreeProperty<string>* Rcd = new ParseTreeProperty<string>(); 

    ifstream ifs;
    ifs.open(fname);
    if(ifs.fail()){
        cout << "Can't open " + fname << "\n";
        exit(0);
    }
    string basename = getFileName(fname);
    string extention = getFileExtension(fname);
    size_t strLen = basename.length();

    if (strLen < 4){
        cout << "file name \"" << fname << "\" is wrong\n";
        cmdline_msg(&cp);
        return 0;        
    }
    
    string st_pyr =  basename.substr(strLen - 4, 4);
    if (st_pyr != "_pyr"){
        cout << "file name \"" << fname << "\" is wrong\n";
        cmdline_msg(&cp);
        return 0;        
    }
    string pyfile  = basename.substr(0, strLen - 4) + ".py";
    string Rfile  = basename.substr(0, strLen - 4) + ".r";
    string create_file = basename.substr(0, strLen - 4) + "." + extention;

    ANTLRInputStream input(ifs);
    ifs.close();

    PyRInTextLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    /*
    cout << "Tokens:" << endl;
    tokens.fill();
    for (Token *token : tokens.getTokens())
        cout << token->toString() << endl;/**/

    PyRInTextParser parser(&tokens);
    tree::ParseTree *tree = parser.stat();
    /*
    cout << endl << "Parse tree (Lisp format):" << endl;
    string lisp_tree_str = tree->toStringTree(&parser);
    cout <<lisp_tree_str  << endl;
    cout <<beautify_lisp_string(lisp_tree_str) << endl;/**/    
    
    GetPyRCode *pyrcode = new GetPyRCode(pycd, Rcd);    
    tree::ParseTreeWalker* walker = new tree::ParseTreeWalker();
    walker->walk(pyrcode, tree);
    //cout << "\nPython code:\n" << pyrcode->getPYC(tree) << endl;
    //cout << "\nR code:\n" << pyrcode->getRC(tree) << endl;

    map<int, string> result_map;
    if (pl_cmd["Python"] != "None")
        set_result_map(pyct + pyrcode->getPYC(tree) , pyfile, result_map, "Python");
    if (pl_cmd["Rscript"] != "None")
        set_result_map(rct + pyrcode->getRC(tree), Rfile, result_map, "Rscript");

    ParseTreeProperty<string>* create_file_cd = new ParseTreeProperty<string>();
    SetTextCode *create_code = new SetTextCode(create_file_cd, &result_map);
    walker->walk(create_code, tree);
    //cout << "\ncreate_code:\n" << create_code->getText(tree) << endl;
    ofstream writeFile;
    writeFile.open(create_file);
    writeFile << create_code->getText(tree);
    writeFile.close();
    cout << "Output written on " +  create_file << "\n\n";

    return 0;
}


