package src;

import java.util.Scanner;
import java.util.concurrent.ForkJoinPool;
import java.util.Random;

public class ForkJoinTest {

    final static int size = 99;
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] arrayToSort = new int[size];
        Random random = new Random();

        for (int i = 0; i < arrayToSort.length; i++) {
            arrayToSort[i] = random.nextInt(100);
        }
        
        System.out.println("Unsorted array:");
        for (int num : arrayToSort) {
            System.out.print(num + " ");
        }
        System.out.println("\n");

        DivideTask mainTask = new DivideTask(arrayToSort);
        ForkJoinPool forkJoinPool = new ForkJoinPool();

        int[] result = forkJoinPool.invoke(mainTask);
        forkJoinPool.execute(mainTask);
        forkJoinPool.submit(mainTask);
        
        System.out.println("Sorted array:");
        for (int num : result) {
            System.out.print(num + " ");
        }
        
        forkJoinPool.close();
        scanner.close();
    }
}
