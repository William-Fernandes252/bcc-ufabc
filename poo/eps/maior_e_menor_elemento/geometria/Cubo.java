package geometria;

public class Cubo implements Comparable<Cubo> {
    private double lado;

    public Cubo(double lado) {
        this.lado = lado;
    }

    public double getLado() {
        return lado;
    }

    public double area() {
        return 6 * lado * lado;
    }

    public int compareTo(Cubo o) {
        return Double.compare(area(), o.area());
    }

    @Override
    public String toString() {
        return String.format("cubo de area %.1f", this.area());
    }
}
