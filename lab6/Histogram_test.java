import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.ArrayList;
import java.util.List;

class Histogram_test {
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Set image size: n (#rows), m(#kolumns)");
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        Obraz obraz_1 = new Obraz(n, m);

        // Obliczanie sekwencyjne
        System.out.println("\nSEKWENCYJNIE");
        //obraz_1.calculate_histogram();
        //obraz_1.print_histogram();

        
        obraz_1.calculate_histogram_block_chars(0, 94);
        obraz_1.print_histogram_block_chars(0, 0, 94);
        

        System.out.println("\nZADANIE");
        System.out.println("1: Wątki Thread - każdy wątek dla jednego znaku");
        System.out.println("2: Wątki Runnable - dekompozycja blokowa po znakach");
        System.out.println("3: Dekompozycja 1D wierszowa");
        System.out.println("4: Dekompozycja 2D blokowa");
        System.out.println("5: Połączenie dekompozycji");
       
        
        int variant = scanner.nextInt();
        System.out.println("Set number of threads");
        int num_threads = scanner.nextInt();

        switch(variant) {
            case 1:
                runVariant1(obraz_1, num_threads);
                break;
            case 2:
                runVariant2(obraz_1, num_threads);
                break;
            case 3:
                runVariant3(obraz_1, num_threads);
                break;
            case 4:
                runVariant4(obraz_1, num_threads);
                break;
            case 5:
                runVariant5(obraz_1, num_threads);
                break;
            default:
                System.out.println("Nieprawidłowy wybór!");
        }

        
        scanner.close();
    
    }

   
     //1Thread - każdy wątek dla jednego znaku
    
    private static void runVariant1(Obraz obraz, int num_threads) 
    {
        System.out.println("\nWARIANT 1: Thread - każdy wątek dla jednego znaku");
        Watek[] threads = new Watek[num_threads];
        
       
        int charsPerThread = 94 / num_threads;
        int remainingChars = 94 % num_threads;
        
        for(int i = 0; i < num_threads; i++) 
        {
            int startChar = i * charsPerThread;
            int endChar = startChar + charsPerThread;
            if(i == num_threads - 1) endChar += remainingChars;
            
            
            for(int k = startChar; k < endChar; k++) 
            {
                threads[k] = new Watek(k, obraz);
                threads[k].start();
            }
        }
        
        for(int i = 0; i < 94; i++) 
        {
            if(threads[i] != null) {
                try {
                    threads[i].join();
                } catch (InterruptedException e) {
                    System.out.println("Przerwano wątek: " + e.getMessage());
                }
            }
        }
    }

    
   //2 Runnable + dekompozycja blokowa po znakach

   
    private static void runVariant2(Obraz obraz, int num_threads) {
        System.out.println("\nRunnable + dekompozycja blokowa po znakach");
        Thread[] threads = new Thread[num_threads];
        int charsPerThread = 94 / num_threads;
        int remainingChars = 94 % num_threads;
        
        for(int i = 0; i < num_threads; i++) {
            int startChar = i * charsPerThread;
            int endChar = startChar + charsPerThread;
            if(i == num_threads - 1) endChar += remainingChars;
            
            WatekRunnableZnaki runnable = new WatekRunnableZnaki(i + 1, obraz, startChar, endChar);
            threads[i] = new Thread(runnable);
            threads[i].start();
        }
        
        for(int i = 0; i < num_threads; i++) 
        {
            try {
                threads[i].join();
            } 
            catch (InterruptedException e) 
            {
                System.out.println("Przerwano wątek: " + e.getMessage());
            }
        }
    }


  //3 Dekompozycja 1D wierszowa
    
    private static void runVariant3(Obraz obraz, int num_threads) 
    {
        System.out.println("\nDekompozycja 1D wierszowa");
        Thread[] threads = new Thread[num_threads];
        int rowsPerThread = obraz.getSizeN() / num_threads;
        int remainingRows = obraz.getSizeN() % num_threads;
        
        for(int i = 0; i < num_threads; i++) 
        {
            int startRow = i * rowsPerThread;
            int endRow = startRow + rowsPerThread;
            if(i == num_threads - 1) endRow += remainingRows;
            
            WatekRunnableWiersze runnable = new WatekRunnableWiersze(i + 1, obraz, startRow, endRow);
            threads[i] = new Thread(runnable);
            threads[i].start();
        }
        
        for(int i = 0; i < num_threads; i++) 
        {
            try {
                threads[i].join();
            } 
            catch (InterruptedException e) 
            {
                System.out.println("Przerwano wątek: " + e.getMessage());
            }
        }
        
        obraz.print_parallel_histogram();
    }

  
   // 4 2D(blokowa

    private static void runVariant4(Obraz obraz, int num_threads) {
    System.out.println("\nDekompozycja 2D blokowa z pulą wątków");
    
    
    int sqrtThreads = (int)Math.sqrt(num_threads);
    int rowsPerBlock = obraz.getSizeN() / sqrtThreads;
    int colsPerBlock = obraz.getSizeM() / sqrtThreads;
    
    //pula ątków
    ExecutorService executor = Executors.newFixedThreadPool(num_threads);
    
    // Lista  zadań
    List<Future<?>> futures = new ArrayList<>(num_threads);
    int threadIndex = 0;
    
    for(int i = 0; i < sqrtThreads; i++) {
        for(int j = 0; j < sqrtThreads; j++) {
            if(threadIndex >= num_threads) break;
            
            int startRow = i * rowsPerBlock;
            int endRow = (i == sqrtThreads - 1) ? obraz.getSizeN() : startRow + rowsPerBlock;
            int startCol = j * colsPerBlock;
            int endCol = (j == sqrtThreads - 1) ? obraz.getSizeM() : startCol + colsPerBlock;
            
            // Tworzenie zadania
            Runnable task = new WatekRunnableBloki(threadIndex + 1, obraz, 
                startRow, endRow, startCol, endCol);
            
            //zapisanie Future
            futures.add(executor.submit(task));
            threadIndex++;
        }
    }
    
    //  zakończenie  zadań
    for(Future<?> future : futures) {
        try {
            future.get(); // get() 
        } catch (Exception e) {
            System.out.println("Błąd podczas wykonania wątku: " + e.getMessage());
        }
    }
    
    // Zamknięcie puli wątków
    executor.shutdown();
    
    obraz.print_parallel_histogram();
}

  
    // WARIANT 5: Połączenie dekompozycji
   
    private static void runVariant5(Obraz obraz, int num_threads) 
    {
        System.out.println("\nPołączenie dekompozycji ");
        
    
        int areaThreads = Math.min(2, num_threads);
        int charThreads = num_threads - areaThreads;
        
        if(charThreads == 0) 
        {
            System.out.println(">2");
            return;
        }
        
        Thread[] threads = new Thread[num_threads];
        int threadIndex = 0;
        
        // Wątki obszary
        int rowsPerThread = obraz.getSizeN() / areaThreads;
        for(int i = 0; i < areaThreads; i++) 
        {
            int startRow = i * rowsPerThread;
            int endRow = (i == areaThreads - 1) ? obraz.getSizeN() : startRow + rowsPerThread;
            
            // dekom obszarowe
            int charsPerAreaThread = 94 / charThreads;
            for(int j = 0; j < charThreads; j++) 
            {
                if(threadIndex >= num_threads) break;
                
                int startChar = j * charsPerAreaThread;
                int endChar = (j == charThreads - 1) ? 94 : startChar + charsPerAreaThread;
                
                WatekRunnableCombined runnable = new WatekRunnableCombined(threadIndex + 1, obraz,
                    startRow, endRow, 0, obraz.getSizeM(), startChar, endChar);
                threads[threadIndex] = new Thread(runnable);
                threads[threadIndex].start();
                threadIndex++;
            }
        }
        
        for(int i = 0; i < threadIndex; i++) 
        {
            try {
                threads[i].join();
            } 
            catch (InterruptedException e) 
            {
                System.out.println("Przerwano wątek: " + e.getMessage());
            }
        }
        
        obraz.print_parallel_histogram();
    }
}