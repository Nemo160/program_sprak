import java.util.HashMap;
import java.util.Map;

public class OperatorTable {
    private record OpKey(TokenType op, Type left, Type right) {}

    private static final Map<OpKey, Type> TABLE = new HashMap<>();
    //run once.
    static {
        TABLE.put(new OpKey(TokenType.PLUS, Type.INTEGER, Type.INTEGER), Type.INTEGER);
        TABLE.put(new OpKey(TokenType.PLUS, Type.REAL, Type.REAL), Type.REAL);
        TABLE.put(new OpKey(TokenType.PLUS, Type.INTEGER, Type.REAL), Type.REAL);
        TABLE.put(new OpKey(TokenType.PLUS, Type.REAL, Type.INTEGER), Type.REAL);

        TABLE.put(new OpKey(TokenType.TIMES, Type.INTEGER, Type.INTEGER), Type.INTEGER);
        TABLE.put(new OpKey(TokenType.TIMES, Type.REAL, Type.REAL), Type.REAL);
        TABLE.put(new OpKey(TokenType.TIMES, Type.INTEGER, Type.REAL), Type.REAL);
        TABLE.put(new OpKey(TokenType.TIMES, Type.REAL, Type.INTEGER), Type.REAL);
    }

    public Type resultType(TokenType op, Type left, Type right) {
        return TABLE.getOrDefault(new OpKey(op, left, right), Type.UNDEFINED);
    }
}
