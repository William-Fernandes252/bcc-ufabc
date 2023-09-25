public class CrachaFuncionario extends Cracha {
    private String cargo;
    private int mesAdmissao;
    private int anoAdmissao;

    public String getCargo() {
        return cargo;
    }

    public void setCargo(String cargo) {
        this.cargo = cargo;
    }

    public int getAnoAdmissao() {
        return anoAdmissao;
    }

    public void setAnoAdmissao(int anoAdmissao) {
        this.anoAdmissao = anoAdmissao;
    }

    public int getMesAdmissao() {
        return mesAdmissao;
    }

    public void setMesAdmissao(int mesAdmissao) {
        this.mesAdmissao = mesAdmissao;
    }

    public void imprimir() {
        System.out.println("FUNCIONARIO");
        System.out.println("Nome: " + this.getNome());
        System.out.println("Cargo: " + this.getCargo());
        System.out.println("Admissao: " + this.getMesAdmissao() + "/" + this.getAnoAdmissao());
    }
}
