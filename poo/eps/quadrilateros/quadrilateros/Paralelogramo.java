package quadrilateros;

public class Paralelogramo extends Quadrilatero{
    public void setLados(double lado1, double lado2){
        super.setLados(lado1, lado2, lado1, lado2);
    }

    @Override
    public String getPropriedades() {
        return super.getPropriedades() + " " + "Lados opostos paralelos.";
    }
}
