public class CrachaEstudante extends Cracha {
    private String curso;

    public String getCurso() {
        return curso;
    }

    public void setCurso(String curso) {
        this.curso = curso;
    }

    public void imprimir() {
        System.out.println("ESTUDANTE");
        System.out.println("Nome: " + this.getNome());
        System.out.println("Curso: " + this.getCurso());
    }
}
