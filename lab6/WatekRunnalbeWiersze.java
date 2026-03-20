
 //1D(wierszowa

class WatekRunnableWiersze implements Runnable {
    private int threadId;
    private Obraz obraz;
    private int startRow;
    private int endRow;

    public WatekRunnableWiersze(int threadId, Obraz obraz, int startRow, int endRow) {
        this.threadId = threadId;
        this.obraz = obraz;
        this.startRow = startRow;
        this.endRow = endRow;
    }

    @Override
    public void run()
     {
        int[] localHist = new int[94];
        obraz.calculate_histogram_rows(startRow, endRow, localHist);
        obraz.add_to_global_histogram(localHist);
        System.out.println("Wątek " + threadId + " przetworzył wiersze " + startRow + "-" + (endRow-1));
    }
}