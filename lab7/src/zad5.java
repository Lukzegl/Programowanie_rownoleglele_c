package src;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class zad5 {
    public static void main(String[] args) {
        double xp = 0;
        double xk = Math.PI;
        double dx = 0.0001;

        int nThreads = 4;
        int nTasks = 10;
        ExecutorService executor = Executors.newFixedThreadPool(nThreads); 

        Calka_runnable calkaTasks[] = new Calka_runnable[nTasks];

        double interval = (xk - xp) / nTasks;
        for (int i = 0; i < nTasks; i++) {
            double start = xp + i * interval;
            double end = (i == nTasks - 1) ? xk : start + interval;

            calkaTasks[i] = new Calka_runnable(start, end, dx);
            executor.submit(calkaTasks[i]);
        }
        executor.shutdown();

        while(!executor.isTerminated()) {
        }

        double wynik = 0;
        for (int i = 0; i < nTasks; i++) {
            wynik += calkaTasks[i].getResult();
        }

        System.out.println("Wynik calkowania: " + wynik);

        
    }
}
