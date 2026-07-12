

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.Reader;

public class ParserMain {
    public static final boolean DEBUG = true;
    public static void main(String[] args) throws Exception {
        //read from stdin
        //pass reader to lexer
        Reader reader = new BufferedReader(new InputStreamReader(System.in));
        Lexer lexer = new Lexer(reader);
        SymbolTable symbolTable = new SymbolTable();
        OperatorTable operatorTable = new OperatorTable();
        if(DEBUG) {lexer.printIntput();}
        Parser parser = new Parser(lexer, symbolTable, operatorTable);
        parser.parse();
    }
}
