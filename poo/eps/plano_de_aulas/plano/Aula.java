package plano;

public abstract class Aula {
	private String descricao;
	private int cargaHoraria;

    public Aula(String descricao) {
        this(descricao, 2);
    }

	public Aula(String descricao, int cargaHoraria) {
		this.setDescricao(descricao);
		this.setCargaHoraria(cargaHoraria);
	}

	public String getDescricao() {
		return this.descricao;
	}
	
	protected void setDescricao(String descricao) {
		this.descricao = descricao;
	}
	
	public int getCargaHoraria() {
	    return cargaHoraria;
	}
	
	public void setCargaHoraria(int cargaHoraria) {
	    this.cargaHoraria = cargaHoraria;
	}

	public abstract String getTipo();
}