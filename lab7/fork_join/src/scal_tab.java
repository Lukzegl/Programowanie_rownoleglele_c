package src;

import java.util.concurrent.RecursiveTask;
import java.util.Arrays;

class DivideTask extends RecursiveTask<int[]> {
 
  int[] arrayToDivide;
  private static int threshold = 4;
 
  public DivideTask(int[] arrayToDivide) {
    this.arrayToDivide = arrayToDivide;
  }
 
  protected int[] compute() {

      // .......
      if (arrayToDivide.length <= threshold) {
      int[] sortedArray = Arrays.copyOf(arrayToDivide, arrayToDivide.length);
      Arrays.sort(sortedArray);
      return sortedArray;
      }

      int mid = arrayToDivide.length / 2;

      int[] leftPart = Arrays.copyOfRange(arrayToDivide, 0, mid);
      int[] rightPart = Arrays.copyOfRange(arrayToDivide, mid, arrayToDivide.length);

      DivideTask task1 = new DivideTask(leftPart);
      DivideTask task2 = new DivideTask(rightPart);

      // System.out.println("Dividing: " + Arrays.toString(arrayToDivide) +
      //         " into " + Arrays.toString(leftPart) + " and " + Arrays.toString(rightPart));
      // .......


      task1.fork();
      task2.fork();

      //Wait for results from both tasks
      int[] tab1 = task1.join();
      int[] tab2 = task2.join();

        int[] scal_tab = new int[arrayToDivide.length];
 
      scal_tab(tab1, tab2, scal_tab);
      return scal_tab;

  }

  private void scal_tab(
          int[] tab1,
          int[] tab2,
          int[] scal_tab) {
     
    int i = 0, j = 0, k = 0;
     
    while ((i < tab1.length) && (j < tab2.length)) {
     
      if (tab1[i] < tab2[j]) {
        scal_tab[k] = tab1[i++];
      } else {
        scal_tab[k] = tab2[j++];
      }
       
      k++;
    }
     
    if (i == tab1.length) {
       
      for (int a = j; a < tab2.length; a++) {
        scal_tab[k++] = tab2[a];
      }
       
    } else {
       
      for (int a = i; a < tab1.length; a++) {
        scal_tab[k++] = tab1[a];
      }
       
    }
  }

}
