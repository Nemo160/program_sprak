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
/* #include "optab.h"       */       /* when the optab     is added   */

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
static void expr();
static void term();
static void factor();
static void operand();



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
    }
}

/**********************************************************************/
/* The grammar functions                                              */
/**********************************************************************/

static void program_header()
{
    match(program);
    addp_name(get_lexeme()); 
    match(id);
    match('('); 
    match(input);
    match(','); 
    match(output); 
    match(')'); 
    match(';');
}

//VAR PART ########################################
static void type(){
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
}

static void id_list(){
    //get var name from lexer
    addv_name(get_lexeme());
    match(id);
    while(lookahead == ','){
        match(',');
        addv_name(get_lexeme()); 
        match(id);
    }
}

static void var_dec(){
    id_list();
    match(':');
    type();

    setv_type(curr_type);   
    
    match(';');
}

static void var_dec_list(){
    var_dec();
    while(lookahead == id){
        var_dec();
    }
}

static void var_part(){
    if(lookahead == var){
        match(var);
        var_dec_list();
    }
}

// STAT PART ########################################

static void operand(){
    if(lookahead == id){
        char *id_name = get_lexeme();
        if (!find_name(id_name)) {
            printf("\n*** Error: Undefined variable: %s", id_name);
            is_parse_ok = 0;
        }
        match(id);
    }
    else if(lookahead == number){
        match(number);
    }
}

static void factor(){
    //(expr | opreand)
    if(lookahead == '('){
        match('(');
        expr();
        match(')');
    }

    else{
        operand();
    }
}

static void term(){
    factor();
    while(lookahead == '*'){
        match('*');
        factor();
    }
}

static void expr(){
    term();
    while(lookahead == '+'){
        match('+');
        term();
    }
}

static void assign_stat(){
    char *var_name = get_lexeme();
    if (!find_name(var_name)) {
        is_parse_ok = 0;
    }
    match(id);
    match(assign);
    expr();
}

static void stat(){
    assign_stat();
}

static void stat_list(){
    stat();
    while(lookahead == ';'){
        match(';');
        stat();
    }
}

static void stat_part(){
    match(begin);
    stat_list();
    match(end);
    match('.');

}


static void prog(){

    program_header();
    var_part();
    stat_part();

}
/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/

int parser()
{
    //p_toktab();                    //token and keyword tables
    p_symtab();                      //symbol table before parse
    in("parser");
    lookahead = get_token();        //get the first token
    prog(); //main program
    
    out("parser");

    printf("\n\n");
    p_symtab();                     //symbol table after parse
    printf("\n");                  
    return is_parse_ok;             // status indicator
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
