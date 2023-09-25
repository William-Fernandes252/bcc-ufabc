public class Tarefa {
	private int tipo;
	private String descricao;
	
	public Tarefa(int tipo, String descricao) {
		this.tipo = tipo;
		this.descricao = descricao;
	}
	
	public int getTipo() {
		return this.tipo;
	}
	
	public String getDescricao() {
		return this.descricao;
	}
}