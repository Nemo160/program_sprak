//Edinson Uribe

/**********************************************************************/
/* lab 1 DVG C01 - Parser OBJECT                                      */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
#include "keytoktab.h" 
#include "lexer.h"
#include "symtab.h"
#include "optab.h"

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 0
static int  lookahead=0;
static int  is_parse_ok=1;
static toktyp curr_type=0;

static void prog();
static void program_header();
static void var_part();
static void var_dec_list();
static void var_dec();
static void id_list();
static void type();

static void stat_part();
static void stat_list();
static void stat();
static void assign_stat();


static toktyp expr();
static toktyp term();
static toktyp factor();
static toktyp operand();



/*
program xyz(input, output);
var A,B,c: integer;
begin
A := B + C * 2
end.
*/


/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
static void in(char* s)
{
    if(DEBUG) printf("\n *** In  %s", s);
}
static void out(char* s)
{
    if(DEBUG) printf("\n *** Out %s", s);
}
/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/
static void match(int t)
{
    if(DEBUG){ in("match"); printf("\t\t\texpected %s found %s",
                    tok2lex(t), tok2lex(lookahead));
    }
    if (lookahead == t) lookahead = get_token();
    else {
        is_parse_ok=0;
        printf("\nSYNTAX: Symbol expected %s found %s",
        tok2lex(t), get_lexeme());
    }
}

/**********************************************************************/
/* The grammar functions                                              */
/**********************************************************************/

static void program_header()
{
    in("program_header");
    match(program);
    addp_name(get_lexeme());
    match(id);
    match('(');
    match(input);
    match(',');
    match(output);
    match(')');
    match(';');
    out("program_header");
}

//VAR PART ########################################
static void type(){
    in("type");
    if(lookahead == integer){
        curr_type = integer;
        match(integer);
    }
    else if(lookahead == real){
        curr_type = real;
        match(real);
    }
    else if(lookahead == boolean){
        curr_type = boolean;
        match(boolean);
    }
    else{
        is_parse_ok = 0;
        printf("\nSYNTAX: Type name expected found %s", get_lexeme());
        curr_type = error;
    }
    out("type");
}

static void id_list(){
    in("id_list");
        if(find_name(get_lexeme())){
        is_parse_ok = 0;
        printf("\nSEMANTIC: ID already declared: %s", get_lexeme());
    }

    //get var name from lexer
    addv_name(get_lexeme());
    match(id);
    while(lookahead == ','){
        match(',');
        if(find_name(get_lexeme())){
            is_parse_ok = 0;
            printf("\nSEMANTIC: ID already declared: %s", get_lexeme());
        }

        addv_name(get_lexeme()); 
        match(id);
    }
    out("id_list");
}

static void var_dec(){
    in("var_dec");
    id_list();
    match(':');
    type();

    setv_type(curr_type);   
    
    match(';');
    out("var_dec");
}

static void var_dec_list(){
    in("var_dec_list");
    var_dec();
    while(lookahead == id){
        var_dec();
    }
    out("var_dec_list");
}

static void var_part(){
    in("var_part");
    if(lookahead == var){
        match(var);
        var_dec_list();
    }
    out("var_part");
}

// STAT PART ########################################

//returns type of operand

static toktyp operand(){
    toktyp t = undef;
    in("opreand");

    if(lookahead == id){
        char *id_name = get_lexeme();
        if (!find_name(id_name)) {
            is_parse_ok = 0;
            printf("\nSEMANTIC: ID NOT declared: %s", id_name);
        }
        //get declared type from symtab
        else{
            t = get_ntype(id_name);
        }
        match(id);
    }
    //integer
    else if(lookahead == number){
        t = integer;
        match(number);
    }

    out("opreand");
    return t;
}

static toktyp factor(){

    toktyp t = undef;
    //(expr | opreand)
    in("factor");

    if(lookahead == '('){
        match('(');
        t = expr();
        match(')');
    }
    else{
        t = operand();
    }
    out("factor");
    return t;
}


static toktyp term(){
    toktyp t = undef;
    in("expr");
    
    t = factor();
    while(lookahead == '*'){
        //use get_otype to check each * operation
        match('*');
        toktyp t2 = factor();
        toktyp result = get_otype('*', t, t2);
        if(result == undef && t != error && t != undef && t2 != error && t2 != undef){
            is_parse_ok = 0;
            printf("\nSEMANTIC: Assign Types: %s := %s",
                tok2lex(t), tok2lex(t2));
        }
        t = result;
    }
    out("expr");
    return t;
}

static toktyp expr(){
    toktyp t = undef;
    in("expr");
    t = term();
    while(lookahead == '+'){
        match('+');
        toktyp t2 = term();
        toktyp result = get_otype('+', t, t2);
        if(result == undef && t != error && t != undef && t2 != error && t2 != undef){
            is_parse_ok = 0;
            printf("\nSEMANTIC: Assign types: %s := %s", tok2lex(t), tok2lex(t2));
        }
        t = result;
    }
    out("expr");
    return t;
}

static void assign_stat(){
    in("assign_stat");
    char *var_name = get_lexeme();
    toktyp type_l = undef;

    if (!find_name(var_name)) {
        is_parse_ok = 0;
        printf("\nSEMANTIC: ID NOT declared: %s", var_name);
    }
    else{
        type_l = get_ntype(var_name);
    }

    match(id);
    match(assign);
    toktyp type_r = expr();

    if (type_l != type_r) {
        is_parse_ok = 0;
        printf("\nSEMANTIC: Assign types: %s := %s",
            tok2lex(type_l), tok2lex(type_r));
    }

    
    out("assign_stat");
}

static void stat(){
    in("stat");
    assign_stat();
    out("stat");
}

static void stat_list(){
    in("stat_list");
    stat();
    while(lookahead == ';'){
        match(';');
        stat();
    }
    out("stat_list");
}

static void stat_part(){
    in("stat_part");
    match(begin);
    stat_list();
    match(end);
    match('.');
    out("stat_part");
}


static void prog(){
    in("prog");
    program_header();
    var_part();
    stat_part();
    out("prog");
}
/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/

int parser()
{
    //p_toktab();                    //token and keyword tables                     //symbol table before parse
    lookahead = get_token();        //get the first token
    prog(); //main program
    out("parser");

    p_symtab();                     //symbol table after parse
    printf("\n");                  
    return is_parse_ok;             // status indicator
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
