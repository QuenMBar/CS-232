
/**clientHost.java is a java program that connects to another server on the calvin network, and,
 * using a tcp connection, is able to ask the server to encrypt and decrypt messages based on
 * the Cesar Cipher. This is done by sending the server a string, and then reciving a string 
 * from the server.
 * 
 * Recives arguemnts for the address and port of the server
 * 
 * Author: Quentin Barnes
 * Date: Apr 30, 2019
 */
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

/**
 * This class implements a java socket client that can encrypt and decrypt
 * messages Recives arguemnts for the address and port of the server
 */
public class clientHost {

    public static void main(String[] args)
            throws UnknownHostException, IOException, ClassNotFoundException, InterruptedException {
        // Creates empty versions of the socket and its streams
        Socket mySocket = null;
        ObjectOutputStream socketOutStream = null;
        ObjectInputStream socketInStream = null;
        // Grabs the ip address for the given machine
        InetAddress myServeAddress = InetAddress.getByName(args[0] + ".cs.calvin.edu");
        System.out.println("Connecting to: " + myServeAddress);
        // establish socket connection to server
        Scanner keyboard = new Scanner(System.in);
        String userIn = "";
        // Grabs the rotation abount from user
        System.out.print("Welcome to the CesarCipher Client.\nEnter the rotation amount to be used to begin: ");
        Integer rotationAmount = keyboard.nextInt();
        Boolean firstRun = true;
        Boolean secondRun = false;
        // Creates sockets and streams
        mySocket = new Socket(myServeAddress, Integer.parseInt(args[1]));
        socketOutStream = new ObjectOutputStream(mySocket.getOutputStream());
        socketInStream = new ObjectInputStream(mySocket.getInputStream());
        // While the user doesnt input quit, keep running
        while (!(userIn.equalsIgnoreCase("quit")) || firstRun) {
            // First time throuhg, write the rotation abount, after that, write
            // the users input to the server
            if (firstRun) {
                socketOutStream.writeObject(Integer.toString(rotationAmount));
            } else {
                socketOutStream.writeObject(userIn);
            }
            // Read what the server sends back and output the message
            String message = (String) socketInStream.readObject();
            if (!secondRun) {
                System.out.println("Message: " + message);
            }
            // If the server responds with the wrong rotation the first time through,
            // then print an error and shut down.
            if (firstRun && Integer.parseInt(message) != rotationAmount) {
                System.out.println("Error: Different Rotation Recived from server");
                break;
            }
            if (message.equals("Invalid rotation given, shutting down socket")) {
                break;
            }
            if (firstRun) {
                firstRun = false;
                secondRun = true;
            } else if (secondRun) {
                secondRun = false;
            }
            // Get the next input from user
            if (!secondRun) {
                System.out.print("Enter the message or quit to quit: ");
            }
            userIn = keyboard.nextLine();
        }
        // Send the server socket and exit message and close resources
        socketOutStream.writeObject("quit");
        socketInStream.close();
        socketOutStream.close();
        keyboard.close();
        mySocket.close();
    }
}
