public class SymbolTable {
    private final int TABSIZE = 1024;
    private final int NAMELEN = 20;
    private int size;
    private int addr;

    private int prog_size = 0;
    private int startp = 0;
    private int numrows = 0;
    public SymbolTable() {

    }
    public void addProgramName(String lexeme){

    }

    public void print(){
        System.out.println("______________________________________________________________");
        System.out.printf("%10s %10s %15s %10s %10s" , "NAME", "ROLE", "TYPE", "SIZE", "ADDR\n");
        System.out.println("______________________________________________________________");
        for(int i = 0; i< numrows; i++){
            p_symrow(i);
        }
        System.out.println("______________________________________________________________");
        System.out.printf("\nSTATIC STORAGE REQUIRED IS %d BYTES", prog_size);

    }

    private void p_symrow(int i){

    }

    private void addpName(char fpname){
        startp = numrows;
    }
}
