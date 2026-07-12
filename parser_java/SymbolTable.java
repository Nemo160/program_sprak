import java.util.*;

public class SymbolTable {
    private final int NAME_LENGTH = 20;
    private final Map<String, Symbol> table = new LinkedHashMap<>();
    //variables not yet recieved type
    private final List<Symbol> waitingVars = new ArrayList<>();
    private int nextAddr = 0;
    private int progSize = 0;



    public void declareProgram(String name){
        table.put(name, new Symbol(name, Role.PROGRAM));
    }

    public void declareVariable(String name){
        Symbol symbol = new Symbol(name, Role.VARIABLE);
        table.put(name, symbol);
        waitingVars.add(symbol);
    }

    public boolean isDeclared(String name){
        return table.containsKey(name);
    }
    public Type typeOf(String name){
        Symbol s = table.get(name);
        if(s == null){
            return Type.UNDEFINED;
        }
        else{
            return s.getType();
        }
    }

    public void setWaitingType(Type type){
        for(Symbol s : waitingVars){
            s.setType(type);
            s.setSize(type.size);
            s.setAddr(nextAddr);
            nextAddr += type.size;
            progSize += type.size;
        }
        waitingVars.clear();
    }

    public void print(){
        System.out.println("______________________________________________________________");
        System.out.printf("%10s %10s %15s %10s %10s" , "NAME", "ROLE", "TYPE", "SIZE", "ADDR\n");
        System.out.println("______________________________________________________________");

        for(Symbol s : table.values()){
            printSymbol(s);
            //System.out.println("hey");
        }

        System.out.println("______________________________________________________________");
        System.out.printf("\nSTATIC STORAGE REQUIRED IS %d BYTES", progSize);

    }

    private void printSymbol(Symbol symbol){
        System.out.printf("%10s  %10s %15s %10d %10d%n",
                symbol.getName(),
                symbol.getRole(),
                symbol.getType(),
                symbol.getSize(),
                symbol.getAddr());

    }

}
