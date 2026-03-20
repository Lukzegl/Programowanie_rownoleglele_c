
 //1 Dziedziczenie po Thread - każdy wątek dla jednego znaku

class Watek extends Thread {
    private int znakIndex;
    private Obraz obraz;

    public Watek(int znakIndex, Obraz obraz) {
        this.znakIndex = znakIndex;
        this.obraz = obraz;
    }

    @Override
    public void run() 
    {
        obraz.calculate_histogram_for_char(znakIndex);
        obraz.print_histogram_for_char(znakIndex);
    }
}