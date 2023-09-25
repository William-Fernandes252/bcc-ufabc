package matematica;

public class Fracao {
    private int numerador;
    private int denominador;

    private static int getMaximoDivisorComum(int numerador, int denominador) {
        while (numerador % denominador != 0) {
            int resto = numerador % denominador;
            numerador = denominador;
            denominador = resto;
        }
        return denominador;
    }


    public Fracao(int numerador, int denominador) {
        int maximoDivisorComum = getMaximoDivisorComum(numerador, denominador);
        this.numerador = numerador / maximoDivisorComum;
        this.denominador = denominador / maximoDivisorComum;
    }

    public Fracao(int numerador) {
        this(numerador, 1);
    }

    public Fracao() {
        this(1, 1);
    }

    public String getRepresentacao() {
        return numerador + "/" + denominador;
    }

    public Fracao somar(Fracao f2) {
        return new Fracao(numerador * f2.denominador + f2.numerador * denominador, denominador * f2.denominador);
    }

    public static Fracao somar(Fracao f1, Fracao f2) {
        return new Fracao(f1.numerador * f2.denominador + f2.numerador * f1.denominador, f1.denominador * f2.denominador);
    }

    public static Fracao somar(Fracao[] fracoes) {
        Fracao soma = new Fracao(0, 1);
        for (Fracao f : fracoes) {
            soma = soma.somar(f);
        }
        return soma;
    }

    public static Fracao multiplicar(Fracao f1, Fracao f2) {
        return new Fracao(f1.numerador * f2.numerador, f1.denominador * f2.denominador);
    }
}
