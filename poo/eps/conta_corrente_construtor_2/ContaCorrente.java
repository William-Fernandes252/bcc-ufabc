public class ContaCorrente {
    private double saldo;
    private String titular;
    private static int quantidadeContas;

    public ContaCorrente(String nome, double saldo) {
        this.saldo = saldo;
        this.titular = nome;
        ContaCorrente.quantidadeContas++;
    }

    public ContaCorrente (String nome) {
        this(nome, 0);
    }

    public double getSaldo() {
        return saldo;
    }

    public String getTitular() {
        return titular;
    }

    public static int getQuantidadeContas() {
        return quantidadeContas;
    }

    public boolean sacar(double valor) {
        if (valor <= 0 || valor > saldo) {
            return false;
        }
        saldo -= valor; 
        return true;
    }

    public boolean depositar(double valor) {
        if (valor <= 0) {
            return false;
        }
        saldo += valor;
        return true;
    }

    public static boolean transferir(ContaCorrente de, ContaCorrente para, double valor) {
        if (!de.sacar(valor)) {
            return false;
        }
        
        return para.depositar(valor);
    }
}
