package cartoes;

public class CartaoDebito {
    private String titular;
    private double saldo = 0;

    public void setTitular(String titular) {
        this.titular = titular;
    }

    public String getTitular() {
        return titular;
    }

    public void adicionarSaldoDebito(double valor) {
        this.saldo += valor;
    }

    public double verificarSaldoDebito() {
        return saldo;
    }

    public boolean pagarComDebito(double valor) {
        if (this.saldo >= valor) {
            this.saldo -= valor;
            return true;
        }
        return false;
    }
}
