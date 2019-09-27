// antlr_target(PyRLaTeXGrammar PyRInText.g4 LISTENER)
grammar PyRInText;

stat : body*;

body : ( pyr | others );

pyr : PYCODE # pycode
    | PYC   # pyc
    | PYP   # pyp
    | RCODE # rcode
    | RC    # rc
    | RCAT  # rcat
    ;

others : OTHER+ ;

PYCODE : '\\begin{pycode}' .*? '\\end{pycode}' ;
PYC    : '\\pyc{' .*? '\\pyc}'  ;
PYP    : '\\pyp{' .*? '\\pyp}'  ;
RCODE  : '\\begin{Rcode}' .*? '\\end{Rcode}' ;
RC     : '\\Rc{' .*? '\\Rc}'  ;
RCAT   : '\\Rcat{' .*? '\\Rcat}'  ;

OTHER : .(~[\\]*);

