// antlr_target(PyRLaTeXGrammar PyRInText.g4 LISTENER)
grammar PyRInText;

stat : body*;

body : ( pyr | SP | OTHER );

pyr : PYCODE # pycode
    | PYC   # pyc
    | PYP   # pyp
    | RCODE # rcode
    | RC    # rc
    | RCAT  # rcat
    ;

PYCODE : '\\begin{pycode}' .*? '\\end{pycode}' ;
PYC    : '\\pyc{' .*? '\\pyc}'  ;
PYP    : '\\pyp{' .*? '\\pyp}'  ;
RCODE  : '\\begin{Rcode}' .*? '\\end{Rcode}' ;
RC     : '\\Rc{' .*? '\\Rc}'  ;
RCAT   : '\\Rcat{' .*? '\\Rcat}'  ;

LINE_COMMENT : '%' ~[\r\n]*  -> skip ;
COMMENT :   '/*' .*? '*/'    -> skip ;
SP : [ ] ;
OTHER :  . ;