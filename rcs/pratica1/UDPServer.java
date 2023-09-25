// created on 29/09/2010 at 22:33
import java.net.*;
import java.util.List;
import java.util.ArrayList;

class UDPServer {
	public static void main(String args[]) throws Exception {
		// Create server socket
		DatagramSocket serverSocket = new DatagramSocket(9876);

		// Client black list
		List<String> blackList = new ArrayList<String>();
		blackList.add("localhost");

		// Receive messages
		boolean shutDown = false;
		while(!shutDown) {
			byte[] receiveData = new byte[1024];

			//block until packet is sent by client
			DatagramPacket receivedPacket = new DatagramPacket(receiveData, receiveData.length);
			serverSocket.receive(receivedPacket);

			//Get the information about the datagram of the client
			InetAddress IPAddress = receivedPacket.getAddress();
			int port = receivedPacket.getPort();

			//Get the data of the packet
			String sentence = new String(receivedPacket.getData(), 0, 1024);
			System.out.println("RECEIVED FROM CLIENT "+IPAddress.getHostAddress()+": " + sentence);
			
			//Generate response		
			String response;
			if (blackList.indexOf(IPAddress.getHostAddress()) != -1) {
				response = "ACCESS DENIED";
			} else if (sentence.indexOf("shutdown") != -1) {
				shutDown = true;
				continue;
			} else {
				response = sentence.toUpperCase();
			}
			byte[] sendData = response.getBytes();

			//Send back the response to the client
			DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);
			serverSocket.send(sendPacket);
		}

		serverSocket.close();	
	}
}
