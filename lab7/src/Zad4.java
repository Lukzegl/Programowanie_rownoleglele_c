package src;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.ArrayList;
import java.util.List;

public class Zad4 {
    public static void main(String[] args) {
        double xp = 0;
        double xk = Math.PI;
        double dx = 0.0001;

        int nThreads = 4;
        int nTasks = 10;
        ExecutorService executor = Executors.newFixedThreadPool(nThreads); 

        double interval = (xk - xp) / nTasks;
        List<Future<Double>> results = new ArrayList<>();
        for (int i = 0; i < nTasks; i++) {
            double start = xp + i * interval;
            double end = (i == nTasks - 1) ? xk : start + interval;

            Calka_callable calkaTask = new Calka_callable(start, end, dx);
            Future<Double> futureResult = executor.submit(calkaTask);
            results.add(futureResult);
        }

        executor.shutdown();
        double result = 0.0;
        for(Future<Double> future : results) {
            try {
                result += future.get();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        System.out.println("Wynik calkowania: " + result);
    }
}