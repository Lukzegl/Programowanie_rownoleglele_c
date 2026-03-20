
// Połączenie dekompozycji 

class WatekRunnableCombined implements Runnable {
    private int threadId;
    private Obraz obraz;
    private int startRow;
    private int endRow;
    private int startCol;
    private int endCol;
    private int startChar;
    private int endChar;

    public WatekRunnableCombined(int threadId, Obraz obraz, int startRow, int endRow, 
                               int startCol, int endCol, int startChar, int endChar) {
        this.threadId = threadId;
        this.obraz = obraz;
        this.startRow = startRow;
        this.endRow = endRow;
        this.startCol = startCol;
        this.endCol = endCol;
        this.startChar = startChar;
        this.endChar = endChar;
    }

    @Override
    public void run() 
    {
        int[] localHist = new int[94];
        obraz.calculate_histogram_combined(startRow, endRow, startCol, endCol, startChar, endChar, localHist);
        obraz.add_to_global_histogram(localHist);
        System.out.println("Wątek " + threadId + ": obszar[" + startRow + "-" + (endRow-1) + "][" + startCol + "-" + (endCol-1) + "], znaki '" + obraz.getTabSymb()[startChar] + "'-'" + obraz.getTabSymb()[endChar-1] + "'");
    }
}