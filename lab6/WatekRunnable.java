
// Runnable + dekompozycja blokowa po znakach

class WatekRunnableZnaki implements Runnable {
    private int threadId;
    private Obraz obraz;
    private int startChar;
    private int endChar;

    public WatekRunnableZnaki(int threadId, Obraz obraz, int startChar, int endChar) {
        this.threadId = threadId;
        this.obraz = obraz;
        this.startChar = startChar;
        this.endChar = endChar;
    }

    @Override
    public void run() {
        obraz.calculate_histogram_block_chars(startChar, endChar);
        obraz.print_histogram_block_chars(threadId, startChar, endChar);
    }
}