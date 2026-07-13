import java.util.*;

public class SymbolTable {
    private final List<Symbol> rows = new ArrayList<>();
    //linked hashmap to preserve access order (declaration order)
    private final Map<String, Symbol> lookup = new LinkedHashMap<>();
    private final List<Symbol> waitingVars = new ArrayList<>();
    private Symbol programSymbol;
    private int nextAddr = 0;
    private int progSize = 0;



    public void declareProgram(String name){
        Symbol symbol = new Symbol(name, Role.PROGRAM);
        symbol.setType(Type.PROGRAM);
        rows.add(symbol);
        lookup.putIfAbsent(name, symbol);
        programSymbol = symbol;
    }

    public void declareVariable(String name){
        Symbol symbol = new Symbol(name, Role.VARIABLE);
        rows.add(symbol);
        lookup.putIfAbsent(name, symbol);
        waitingVars.add(symbol);
    }

    public boolean isDeclared(String name){
        return lookup.containsKey(name);
    }

    public Type typeOf(String name){
        Symbol s = lookup.get(name);
        if(s == null){
            return Type.UNDEFINED;
        }
        else{
            return s.getType();
        }
    }

    public void setWaitingType(Type type){
        for(Symbol i : waitingVars){
            i.setType(type);
            i.setSize(type.size);
            i.setAddr(nextAddr);
            nextAddr += type.size;
            progSize += type.size;
        }
        waitingVars.clear();
        if(programSymbol != null){
            programSymbol.setSize(progSize);
        }
    }

    public void print(){
        System.out.println("______________________________________________________________");
        System.out.println("THE SYMBOL TABLE");
        System.out.println("______________________________________________________________");
        System.out.printf("%10s %10s %15s %10s %10s" , "NAME", "ROLE", "TYPE", "SIZE", "ADDR\n");
        System.out.println("______________________________________________________________");

        for(Symbol i : rows){
            printSymbol(i);
        }

        System.out.println("______________________________________________________________");
        System.out.println("STATIC STORAGE REQUIRED IS " + progSize +  " BYTES");
        System.out.println("______________________________________________________________");

    }

    private void printSymbol(Symbol symbol){
        System.out.printf("%10s %10s %15s %10d %10d\n",
                symbol.getName(),
                symbol.getRole(),
                symbol.getType(),
                symbol.getSize(),
                symbol.getAddr());

    }

}
