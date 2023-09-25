package cartoes;

public class CartaoLimitado extends CartaoCredito {
    private double limite = 200;

    @Override
    public boolean pagarComCredito(double valor) {
        if (super.divida + valor <= limite) {
            divida += valor;
            return true;
        }
        return false;
    }
} 