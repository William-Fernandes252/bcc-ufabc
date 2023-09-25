public class ListaTarefasInvertida extends ListaTarefas {
    @Override
    public boolean adicionarTarefa(Tarefa novaTarefa) {
        if (this.tarefas.length - qtdTarefas - 1 < 0) {
            return false;
        }
        
        this.tarefas[this.tarefas.length - qtdTarefas - 1] = novaTarefa;
        qtdTarefas++;
        return true;
    }

    public void listarTarefasPorTipo(int tipo) {
        for (Tarefa tarefa : this.tarefas) {
            if (tarefa != null && tarefa.getTipo() == tipo) {
                this.imprimirItem(tarefa);
            }
        }
    }
}
