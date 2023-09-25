package plano;

public class Teorica extends Aula {

    public Teorica(String descricao) {
        super(descricao, 2);
    }

    public Teorica(String descricao, int cargaHoraria) {
        super(descricao, cargaHoraria);
    }

	@Override
	public String getTipo() {
		return "Teorica";
	}
}