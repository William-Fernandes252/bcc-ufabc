public class ListaTarefas {
	private String titulo;
	Tarefa[] tarefas = new Tarefa[5];
	int qtdTarefas = 0;
	
	public void setTitulo(String titulo) {
		this.titulo = titulo;
	}
	
	public boolean adicionarTarefa(Tarefa novaTarefa) {
		if (qtdTarefas >= tarefas.length)
			return false;
		
		tarefas[qtdTarefas++] = novaTarefa;
		return true;
	}
	
	protected void imprimirItem(Tarefa tarefaImpressao) {
		System.out.println(String.format("tarefa: %s", tarefaImpressao.getDescricao()));
	}
	
	public void imprimirLista() {
		System.out.println("-------------------------------");
		System.out.println("Lista: " + this.titulo);
		for (int i = 0; i < tarefas.length; i++)
			if (tarefas[i] != null)
			    imprimirItem(tarefas[i]);
		System.out.println("-------------------------------");
	}
}