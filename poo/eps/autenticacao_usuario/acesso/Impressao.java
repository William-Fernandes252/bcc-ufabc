package acesso;

public class Impressao {
    public static void imprimirUsuarioAutenticado(String login) {
        System.out.println("Autenticado com sucesso");
    }

    public static void imprimirSenhaInvalida(String login) {
        System.out.println("Senha inválida");
    }

    public static void imprimirUsuarioBloqueado(String login) {
        System.out.println("Usuário bloqueado");
    }
}
