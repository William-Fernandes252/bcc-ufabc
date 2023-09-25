package cartoes;

public class CartaoCredito extends CartaoDebito {
    protected double divida = 0;

    public boolean pagarComCredito(double valor) {
        divida += valor;
        return true;
    }

    public void quitarCredito(double valor) {
        divida -= valor;
    }

    public double verificarExtrato() {
        return divida;
    }
}
