package src;

public class Calka_runnable implements Runnable {
    private double dx;
    private double xp;
    private double xk;
    private int N;
    private double calka;

    public Calka_runnable(double xp, double xk, double dx) {
	this.xp = xp;
	this.xk = xk;
	this.N = (int) Math.ceil((xk-xp)/dx);
	this.dx = (xk-xp)/N;
	System.out.println("Creating an instance of Calka_runnable");
	System.out.println("xp = " + xp + ", xk = " + xk + ", N = " + N);
	System.out.println("dx requested = " + dx + ", dx final = " + this.dx);
    }

    private double getFunction(double x) {  
	return Math.sin(x);
    }

    @Override
    public void run() {
        int i;
        for(i=0; i<N; i++){
            double x1 = xp+i*dx;
            double x2 = x1+dx;
            this.calka += ((getFunction(x1) + getFunction(x2))/2.)*dx;
        }
        System.out.println("Calka czastkowa: " + this.calka);
    }

    public double getResult() {
        return this.calka;
    }
}