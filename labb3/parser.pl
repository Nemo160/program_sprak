/******************************************************************************/
/* From Programming in Prolog (4th Ed.) Clocksin & Mellish, Springer (1994)   */
/* Chapter 5, pp 101-103 (DFR (140421) modified for input from a file)        */
/******************************************************************************/
/*PART ONE READER*/
read_in(File,[W|Ws]) :- see(File), get0(C), 
                        readword(C, W, C1), restsent(W, C1, Ws), nl, seen.

/******************************************************************************/
/* Given a word and the character after it, read in the rest of the sentence  */
/******************************************************************************/

restsent(W, _, [])         :- W = -1.                /* added EOF handling */
restsent(W, _, [])         :- lastword(W).
restsent(_, C, [W1 | Ws ]) :- readword(C, W1, C1), restsent(W1, C1, Ws).

/******************************************************************************/
/* Read in a single word, given an initial character,                         */
/* and remembering what character came after the word (NB!)                   */
/******************************************************************************/

readword(C, W, _)  :- C = -1, W = C.                    /* added EOF handling */
readword(C, W, C2) :- C = 58, get0(C1), readwordaux(C, W, C1, C2).
readwordaux(_, W, C1, C2) :- C1= 61, name(W, [58, 61]), get0(C2).
readwordaux(_, W, C1, C1) :- C1\=61, name(W,[58]).
readword(C, W, C1) :- single_character( C ), name(W, [C]), get0(C1).

readword(C, W, C2) :-
    in_word(C, NewC),
    NewC > 96, NewC < 123,
    get0(C1),
    restword(C1, Cs, C2),
    name(W, [NewC|Cs]).

readword(C, W, C2) :-
    C > 47, C < 58,
    get0(C1),
    restword_digit(C1, Cs, C2),
    name(W, [C|Cs]).

/*skip space*/
readword(_, W, C2) :-
    get0(C1),
    readword(C1,W,C2).

restword(C, [NewC|Cs], C2) :-
    in_word(C, NewC),
    get0(C1),
    restword(C1, Cs, C2).
restword(C, [], C).

restword_digit(C, [C|Cs], C2) :-
    C > 47, C < 58,
    get0(C1),
    restword_digit(C1, Cs, C2).
restword_digit(C, [], C).

/******************************************************************************/
/* These characters form words on their own                                   */
/******************************************************************************/

single_character(40).                  /* ( */
single_character(41).                  /* ) */
single_character(42).                  /* + */
single_character(43).                  /* * */
single_character(44).                  /* , */
single_character(45).                  /* , */
single_character(59).                  /* ; */
single_character(61).                  /* = */
single_character(46).                  /* . */

/******************************************************************************/
/* These characters can appear within a word.                                 */
/* The second in_word clause converts character to lower case                 */
/******************************************************************************/

in_word(C, C) :- C>96, C<123.             /* a b ... z */
in_word(C, L) :- C>64, C<91, L is C+32.   /* A B ... Z */
in_word(C, C) :- C>47, C<58.              /* 1 2 ... 9 */

/******************************************************************************/
/* These words terminate a sentence                                           */
/******************************************************************************/

lastword('.').

/******************************************************************************/
/* PART 2: LEXER                                           */
/******************************************************************************/
/*head and tail with first and rest of output*/
lexer([],[]).
lexer([First | Rest], [Token | MoreTokens]) :- match(First, Token), lexer(Rest, MoreTokens).

/* exact numbers*/
match(program, 256).
match(input, 257).
match(output, 258).
match(var, 259).
match(integer, 260).
match(begin, 261).
match(end, 262).
match(real, 264).
match('(', 40).
match(')', 41).
match('*', 42).
match('+', 43).
match(',', 44).
match('.', 46).
match(':', 58).
match(';', 59).
match(':=', 271).

/*integer literal so that every element is a digit*/

match(L, 272) :-
    integer(L), L >= 0.

char_type_num(C) :- char_type(C, digit).

match(L, 270) :-
    atom(L),
    atom_chars(L, [First|_]),
    char_type(First, alpha).
    
match(-1, 275).
match(_, 273).


/*PROGRAM KEYWORDS*/
program_kw  --> [256].
input_kw    --> [257].
output_kw   --> [258].
var_kw      --> [259].
integer_kw  --> [260].
begin_kw    --> [261].
end_kw      --> [262].
real_kw     --> [264].
lparenth    --> [40].
rparenth    --> [41].
times       --> [42].
plus        --> [43].
comma       --> [44].
dot         --> [46].
colon       --> [58].
semicolon   --> [59].
assign      --> [271].
integer_lit --> [272].
id          --> [270].
boolean_kw  --> [274].

program         --> prog_head, var_part, stat_part.

/******************************************************************************/
/* Program Header                                                             */
/******************************************************************************/
prog_head       --> program_kw, id, lparenth, input_kw,
                    comma, output_kw, rparenth, semicolon.

/******************************************************************************/
/* Var_part                                                                   */
/******************************************************************************/
var_part        --> var_kw, var_dec_list.

var_dec_list    --> var_dec, var_dec_list.
var_dec_list    --> var_dec.

var_dec         --> id_list, colon, type, semicolon.

id_list         --> id, comma, id_list.
id_list         --> id.

type            --> integer_kw.
type            --> real_kw.
type            --> boolean_kw.

/******************************************************************************/
/* Stat part                                                                  */
/******************************************************************************/
stat_part       --> begin_kw, stat_list, end_kw, dot.
stat_list       --> stat, semicolon, stat_list.
stat_list       --> stat.

stat            --> id, assign, expr.
expr            --> term, plus, expr.
expr            --> term.

term            --> factor, times, term.
term            --> factor.

factor          --> id.
factor          --> integer_lit.
factor          --> lparenth, expr, rparenth.

/******************************************************************************/
/* parser                                                                     */
/******************************************************************************/
parser(Tokens, Result) :-
    (program(Tokens, Result), Result =[]
    -> write('Parse OK!')  ; write('Parse Fail!')).

parseFile(File) :-
    write('Testing '), write(File), nl,                                            
    read_in(File, Lexemes),
    write(Lexemes), nl,
    lexer(Lexemes, Tokens),
    write(Tokens), nl,
    parser(Tokens, Result),
    nl,
    write(File), write(' end of parse'),
    nl, nl.


parseFiles([]).
parseFiles([Head|Tail]) :-
    parseFile(Head),
    parseFiles(Tail).


test :-
    tell('parser.out'),
    write('Testing OK programs '), nl, nl,
    parseFiles([
        'testfiles/testok1.pas',
        'testfiles/testok2.pas',
        'testfiles/testok3.pas',
        'testfiles/testok4.pas',
        'testfiles/testok5.pas',
        'testfiles/testok6.pas',
        'testfiles/testok7.pas'
    ]),

    write('Testing a-z programs '), nl, nl,
    parseFiles([
        'testfiles/testa.pas',
        'testfiles/testb.pas',
        'testfiles/testc.pas',
        'testfiles/testd.pas',
        'testfiles/teste.pas',
        'testfiles/testf.pas',
        'testfiles/testg.pas',
        'testfiles/testh.pas',
        'testfiles/testi.pas',
        'testfiles/testj.pas',
        'testfiles/testk.pas',
        'testfiles/testl.pas',
        'testfiles/testm.pas',
        'testfiles/testn.pas',
        'testfiles/testo.pas',
        'testfiles/testp.pas',
        'testfiles/testq.pas',
        'testfiles/testr.pas',
        'testfiles/tests.pas',
        'testfiles/testt.pas',
        'testfiles/testu.pas',
        'testfiles/testv.pas',
        'testfiles/testw.pas',
        'testfiles/testx.pas',
        'testfiles/testy.pas',
        'testfiles/testz.pas'
    ]),

    write('Testing fun programs '), nl, nl,
    parseFiles([
        'testfiles/fun1.pas',
        'testfiles/fun2.pas',
        'testfiles/fun3.pas',
        'testfiles/fun4.pas',
        'testfiles/fun5.pas'
    ]),

    write('Testing sem programs '), nl, nl,
    parseFiles([
        'testfiles/sem1.pas',
        'testfiles/sem2.pas',
        'testfiles/sem3.pas',
        'testfiles/sem4.pas',
        'testfiles/sem5.pas'
    ]),

    told.
/******************************************************************************/
/* End of program                                                             */
/******************************************************************************/
