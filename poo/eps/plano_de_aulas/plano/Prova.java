package plano;

public class Prova extends Aula implements Avaliacao {
	private double peso;

    public Prova(int peso, String descricao) {
        this(peso, descricao, 2);
        this.setPeso(peso);
    }

    public Prova(int peso, String descricao, int cargaHoraria) {
        super(descricao, cargaHoraria);
        this.setPeso(peso);
    }
	
	@Override
	public String getTipo() {
		return "Prova";
	}
	
	public double getPeso() {
		return this.peso;
	}

    public void setPeso(double peso) {
        this.peso = peso;
    }
}