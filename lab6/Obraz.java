import java.util.Random;
import java.util.concurrent.locks.ReentrantLock;

class Obraz {
    
    private int size_n;
    private int size_m;
    private char[][] tab;
    private char[] tab_symb;
    private int[] histogram;
    private int[] hist_parallel;
    private ReentrantLock lock;
    
    public Obraz(int n, int m) {
        this.size_n = n;
        this.size_m = m;
        tab = new char[n][m];
        tab_symb = new char[94];
        histogram = new int[94];
        hist_parallel = new int[94];
        lock = new ReentrantLock();
        
        final Random random = new Random();
        
        // Inicjalizacja tablicy symboli (ASCII 33-126)
        for(int k = 0; k < 94; k++) {
            tab_symb[k] = (char)(k + 33);
        }

        // Generowanie losowej tablicy znaków
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {    
                tab[i][j] = tab_symb[random.nextInt(94)];
                System.out.print(tab[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println();
        
        clear_histogram();
    }
    
    // Gettery dla rozmiarów
    public int getSizeN() { return size_n; }
    public int getSizeM() { return size_m; }
    public char[] getTabSymb() { return tab_symb; }
    
    public void clear_histogram() {
        for(int i = 0; i < 94; i++) {
            histogram[i] = 0;
            hist_parallel[i] = 0;
        }
    }

    // Obliczanie sekwencyjne 
    public void calculate_histogram() 
    {
        for(int i = 0; i < size_n; i++) 
        {
            for(int j = 0; j < size_m; j++) 
            {
                for(int k = 0; k < 94; k++) 
                {
                    if(tab[i][j] == tab_symb[k]) histogram[k]++;
                }
            }
        }
    }

    // WT 1: Każdy wątek dla jednego znaku (Thread)

    public void calculate_histogram_for_char(int k) 
    {
        int count = 0;
        for(int i = 0; i < size_n; i++) 
        {
            for(int j = 0; j < size_m; j++) 
            {
                if(tab[i][j] == tab_symb[k]) count++;
            }
        }
        hist_parallel[k] = count;
    }

    public synchronized void print_histogram_for_char(int k) 
    {
        System.out.print("Wątek " + (k + 1) + ": " + tab_symb[k] + " ");
        for(int i = 0; i < hist_parallel[k]; i++) 
        {
            System.out.print("=");
        }
        System.out.println();
    }

  
    // Runnable + dekompozycja blokowa po znakach
  
    public void calculate_histogram_block_chars(int startChar, int endChar) 
    {
        for(int k = startChar; k < endChar; k++) 
        {
            int count = 0;
            for(int i = 0; i < size_n; i++) 
            {
                for(int j = 0; j < size_m; j++) 
                {
                    if(tab[i][j] == tab_symb[k]) count++;
                }
            }
            hist_parallel[k] = count;
        }
    }

    public synchronized void print_histogram_block_chars(int threadId, int startChar, int endChar) {
        for(int k = startChar; k < endChar; k++) 
        {
            if(hist_parallel[k] > 0) 
            {
                System.out.print("Wątek " + threadId + " (" + tab_symb[k] + "): ");
                for(int i = 0; i < hist_parallel[k]; i++) 
                {
                    System.out.print("=");
                }
                System.out.println();
            }
        }
    }

    // 3 Dekompozycja 1D wierszowa

    public void calculate_histogram_rows(int startRow, int endRow, int[] localHist) {
        for(int i = startRow; i < endRow; i++) 
        {
            for(int j = 0; j < size_m; j++) 
            {
                int index = (int)tab[i][j] - 33;
                if(index >= 0 && index < 94) 
                {
                    localHist[index]++;
                }
            }
        }
    }

    // Synchronizowane dodawanie histogramu lokalnego do globalnego
    public void add_to_global_histogram(int[] localHist) 
    {
        lock.lock();
        try {
            for(int i = 0; i < 94; i++) 
            {
                hist_parallel[i] += localHist[i];
            }
        } finally 
        {
            lock.unlock();
        }
    }


    // WARIANT 4: Dekompozycja 2D blokowa

    public void calculate_histogram_2d_block(int startRow, int endRow, int startCol, int endCol, int[] localHist) {
        for(int i = startRow; i < endRow; i++) {
            for(int j = startCol; j < endCol; j++) {
                int index = (int)tab[i][j] - 33;
                if(index >= 0 && index < 94) {
                    localHist[index]++;
                }
            }
        }
    }


    //  5 Połączenie dekompozycji fragment tablicy + znaki

    public void calculate_histogram_combined(int startRow, int endRow, int startCol, int endCol, 
                                           int startChar, int endChar, int[] localHist) {
        for(int i = startRow; i < endRow; i++) 
        {
            for(int j = startCol; j < endCol; j++) 
            {
                for(int k = startChar; k < endChar; k++) 
                {
                    if(tab[i][j] == tab_symb[k])
                    {
                        localHist[k]++;
                    }
                }
            }
        }
    }


    // Metody pomocnicze

    public void print_histogram() 
    {
        System.out.println("Histogram sekwencyjny:");
        for(int i = 0; i < 94; i++) 
        {
            if(histogram[i] > 0) 
            {
                System.out.println(tab_symb[i] + " " + histogram[i]);
            }
        }
    }

    public void print_parallel_histogram() 
    {
        System.out.println("Histogram równoległy:");
        for(int i = 0; i < 94; i++) 
        {
            if(hist_parallel[i] > 0) 
            {
                System.out.println(tab_symb[i] + " " + hist_parallel[i]);
            }
        }
    }

    public void compare_histograms() 
    {
        boolean identical = true;
        for(int i = 0; i < 94; i++) 
        {
            if(histogram[i] != hist_parallel[i]) 
            {
                System.out.println("RÓŻNICA: '" + tab_symb[i] + "' - sekwencyjny: " + histogram[i] + ", równoległy: " + hist_parallel[i]);
                identical = false;
            }
        }
        if(identical) 
        {
            System.out.println("✓ Histogramy są IDENTYCZNE!");
        } else 
        {
            System.out.println("✗ Histogramy są RÓŻNE!");
        }
    }
}