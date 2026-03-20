package src;

public class zad2 {
    //calkowanie sin x od 0 do pi
    public static void main(String[] args) {
        double xp = 0;
        double xk = Math.PI;
        double dx = 0.0001;

        Calka_callable calkaTask = new Calka_callable(xp, xk, dx);
        double result = calkaTask.compute_integral();

        System.out.println("Wynik calkowania: " + result);
    }
    
}
