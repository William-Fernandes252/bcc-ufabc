import java.net.*;
import java.io.*;

public class TCPMultithreadedServer {
    public static void main(String args[]) throws Exception {
        // Create a new server socket on port 9000
        ServerSocket serverSocket = new ServerSocket(9000);
        System.out.println("Waiting for connection at port 9000.");

        // Continuously listen for new client connections
        while (true) {
            Socket clientSocket = serverSocket.accept();
            System.out.println("Connection established from " + clientSocket.getInetAddress().getHostAddress());

            // Start a new thread to handle the client
            Thread t = new Thread(new ClientHandler(clientSocket));
            t.start();
        }
    }

    static class ClientHandler implements Runnable {
        private final Socket clientSocket;

        public ClientHandler(Socket socket) {
            this.clientSocket = socket;
        }

        public void run() {
            try {
                // Create input and output streams for the client socket
                BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

                String inputLine;
                while ((inputLine = in.readLine()) != null) {
                    // Process client input
                    System.out.println("Received from client: " + inputLine);
                    out.println("Server received: " + inputLine);
                }

                // Close input and output streams and the client socket
                in.close();
                out.close();
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}