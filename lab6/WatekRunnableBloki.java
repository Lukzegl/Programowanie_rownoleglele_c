
 //Dekompozycja 2D (blokowa)

class WatekRunnableBloki implements Runnable {
    private int threadId;
    private Obraz obraz;
    private int startRow;
    private int endRow;
    private int startCol;
    private int endCol;

    public WatekRunnableBloki(int threadId, Obraz obraz, int startRow, int endRow, int startCol, int endCol) 
    {
        this.threadId = threadId;
        this.obraz = obraz;
        this.startRow = startRow;
        this.endRow = endRow;
        this.startCol = startCol;
        this.endCol = endCol;
    }

    @Override
    public void run() 
    {
        int[] localHist = new int[94];
        obraz.calculate_histogram_2d_block(startRow, endRow, startCol, endCol, localHist);
        obraz.add_to_global_histogram(localHist);
        System.out.println("Wątek " + threadId + " przetworzył blok: wiersze " + startRow + "-" + (endRow-1) + ", kolumny " + startCol + "-" + (endCol-1));
    }
}