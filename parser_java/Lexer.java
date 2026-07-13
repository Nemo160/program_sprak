import java.io.IOException;
import java.io.Reader;
import java.util.HashMap;
import java.util.Map;

public class Lexer {
    private static final Map<Character, TokenType> SYMBOLS = new HashMap<>();
    private static final Map<String, TokenType> KEYWORDS = new HashMap<>();
    //map symbols and keywords once.
    static {
        for(TokenType i : TokenType.values()) {
            if(i.isKeyword){
                KEYWORDS.put(i.lexeme, i);
            }
        }

        for(TokenType i : TokenType.values()){
            if(i.lexeme.length() == 1){
                SYMBOLS.put(i.lexeme.charAt(0), i);
            }
        }
    }
    private final String BUFFER;
    private int pos = 0;

    public Lexer(Reader reader) throws IOException {
        StringBuilder bf = new StringBuilder();
        int c;
        while((c = reader.read()) != -1){
            bf.append((char)c);
        }
        this.BUFFER = bf.toString();
    }


    public Token nextToken(){

        //check for space, single character operators
        //alphabets
        //skip whitespace

        while(pos < BUFFER.length() && Character.isWhitespace(BUFFER.charAt(pos))){
            pos++;
        }

        if(pos >= BUFFER.length()){
            return new Token(TokenType.EOF, "$");
        }

        char a =  BUFFER.charAt(pos);

        //check for assign
        if(a == ':' && pos +1 < BUFFER.length() && BUFFER.charAt(pos+1) == '='){
            pos += 2;
            return new Token(TokenType.ASSIGN, ":=");
        }

        //check for single character using table
        if(SYMBOLS.containsKey(a)){
            pos++;
            return new Token(SYMBOLS.get(a),String.valueOf(a));
        }

        //check for digit
        if(Character.isDigit(a)){
            int start = pos;
            while(pos < BUFFER.length() && Character.isDigit(BUFFER.charAt(pos))){
                pos++;
            }
            String number = BUFFER.substring(start, pos);
            return new Token(TokenType.NUMBER, number);
        }

        //check for variable declaration and keyword
        if(Character.isLetter(a)){
            int start = pos;
            while(pos < BUFFER.length() && Character.isLetterOrDigit(BUFFER.charAt(pos))){
                pos++;
            }
            String varName = BUFFER.substring(start, pos);
            //returns keyword type if mapped, defaults as id.
            TokenType type = KEYWORDS.getOrDefault(varName, TokenType.ID);
            return new Token(type, varName);
        }

        //unrecognized character
        String unknown = String.valueOf(a);
        pos++;
        return new Token(TokenType.UNKNOWN, unknown);
    }

    public void printInput() {
        System.out.println("______________________________________________________________");
        System.out.println(" THE PROGRAM TEXT");
        System.out.println("______________________________________________________________");
        System.out.println(BUFFER);
        System.out.println("______________________________________________________________");
    }
}
