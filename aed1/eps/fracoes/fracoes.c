#include <assert.h>

typedef struct Fracao Fracao;
struct Fracao {
    int numerador, denominador;
};

Fracao somar(Fracao f1, Fracao f2);
Fracao somar_vetor(Fracao f[], int n_fracoes);
Fracao multiplicar(Fracao f1, Fracao f2);
Fracao multiplicar_vetor(Fracao f[], int n_fracoes);
Fracao simplificar_fracao(Fracao f);

int gcd(int a, int b) {
    int gcd, remainder;

    while (a != 0)
    {
        remainder = b % a;
        b = a;
        a = remainder;
    }

    gcd = b;

    return gcd;
}

Fracao simplificar_fracao(Fracao f) {
    Fracao resultado;
    int divisor_comum = gcd(f.numerador, f.denominador);
    resultado.numerador = f.numerador / divisor_comum;  
    resultado.denominador = f.denominador / divisor_comum;
    return resultado;
}

Fracao somar(Fracao f1, Fracao f2) {
    Fracao resultado;
    int divisor_comum;

    resultado.denominador = f1.denominador * f2.denominador;
    resultado.numerador = (
        (f1.numerador * (resultado.denominador / f1.denominador)) +
        (f2.numerador * (resultado.denominador / f2.denominador))
    );    

    return simplificar_fracao(resultado);
}

Fracao somar_vetor(Fracao f[], int n_fracoes) {
    Fracao resultado;

    resultado.numerador = 0;
    resultado.denominador = 1;
    for (int i = 0; i < n_fracoes; i++) {
        resultado = somar(resultado, f[i]);
    }

    return simplificar_fracao(resultado);
}

Fracao multiplicar(Fracao f1, Fracao f2) {
    Fracao resultado;

    resultado.numerador = f1.numerador * f2.numerador;
    resultado.denominador = f1.denominador * f2.denominador;

    return simplificar_fracao(resultado);
}

Fracao multiplicar_vetor(Fracao f[], int n_fracoes) {
    Fracao resultado;

    resultado.numerador = 1;
    resultado.denominador = 1;
    for (int i = 0; i < n_fracoes; i++) {
        resultado = multiplicar(resultado, f[i]);
    }

    return simplificar_fracao(resultado);
}

int main() {
    Fracao f1 = { 1, 2 }, f2 = { 3, 6 };
    Fracao soma, multiplicacao;

    soma = somar(f1, f2);
    multiplicacao = multiplicar(f1, f2);
    assert(soma.numerador == 1 && soma.denominador == 1);
    assert(multiplicacao.numerador == 1 && multiplicacao.denominador == 4);

    return 0;
}