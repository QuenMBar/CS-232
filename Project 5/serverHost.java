
/**serverHost.java is a java program that connects to other (can be multiple) clients on 
 * the calvin network, and, using a tcp connection, is able to recive messages from the 
 * client and encrypt and decrypt messages based on the Cesar Cipher. Then it sends the 
 * encrypted message back to the client. This is done by reciving a string from the user, 
 * and then sending a string back to user.
 * 
 * Also holds the serverThread class used for making the program multi-threaded
 * 
 * Recives arguemnts for the port of the server
 * 
 * Author: Quentin Barnes
 * Date: Apr 30, 2019
 */

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.ClassNotFoundException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Vector;

/**
 * This class implements a java socket server that can encrypt and decrypt
 * messages Recives arguemnts for the port of the server
 */

public class serverHost {

    // Creates the server socket
    private static ServerSocket server;

    public static void main(String args[]) throws IOException, ClassNotFoundException {
        // Parses the port given and uses it to start the server
        Integer port = Integer.parseInt(args[0]);
        server = new ServerSocket(port);
        int i = 1;
        System.out.println("Waiting for the client connection");
        // Until the server is closed or processes 100 requests, the server keeps
        // running
        while (true) {
            // creating socket and waiting for client connection
            Socket socket = server.accept();
            // Start the a new socket on a new thread
            serverThread newThread = new serverThread(socket, i);
            newThread.start();
            i++;
            if (i == 100) {
                break;
            }
        }
        // close server
        server.close();
    }

}

/**
 * The server thread class is used to create sockets on different threads so
 * that multiple users can connect to the server at once. It is created by
 * passing it a socket and a integer to be used as the thread name.
 */
class serverThread extends Thread {
    // Creates private variables to be used in the rest of the program.
    private Thread t;
    private Socket mySocket = null;
    private Integer threadName;

    /**
     * Constructor class for serverThread class. Recives a socket and an int and
     * sets mySocket and threadName with them.
     * 
     * @param passedSocket
     * @param i
     */
    serverThread(Socket passedSocket, Integer i) {
        mySocket = passedSocket;
        threadName = i;
        System.out.print("Creating " + threadName + " ");
    }

    /**
     * This is the function that the newly created thread runs. It recives the
     * rotation number and then encrypts any message recived after with the cesar
     * cipher.
     */
    public void run() {
        // Catches IOException and ClassNotFoundException for the socket and its streams
        try {
            // Creates variables for the rotationNum and if the program crashed
            Integer rotationNum = null;
            Boolean crashed = false;
            Boolean secondRun = true;
            // Creates the streams given the socket
            ObjectInputStream serverInStream = new ObjectInputStream(mySocket.getInputStream());
            ObjectOutputStream serverOutStream = new ObjectOutputStream(mySocket.getOutputStream());
            // Gets and sets rotation amount from client
            String rotationMessage = (String) serverInStream.readObject();
            System.out.println(threadName + ": Rotation Received: " + rotationMessage);
            rotationNum = Integer.parseInt(rotationMessage);
            // Checks to see if rotation number is between 1 and 25
            if (rotationNum <= 25 && rotationNum >= 1) {
                serverOutStream.writeObject(Integer.toString(rotationNum));
            } else {
                serverOutStream.writeObject("Invalid rotation given, shutting down socket");
                crashed = true;
            }

            // While program hasnt crashed and exit message hasnt been recived, keep running
            while (true && !crashed) {
                // Read message from client
                String message = (String) serverInStream.readObject();
                if (!secondRun) {
                    System.out.println(threadName + ": Message Received: " + message);
                }
                // If exit message, break
                if (message.equalsIgnoreCase("quit")) {
                    break;
                }
                // Encrypt message
                message = encryptText(message, rotationNum);
                if (!secondRun) {
                    System.out.println(threadName + ": Message Written Back: " + message);
                }
                if (secondRun) {
                    secondRun = false;
                }
                // Write message back
                serverOutStream.writeObject(message);
            }
            // Close resources
            serverInStream.close();
            serverOutStream.close();
            mySocket.close();
            System.out.println("Shutting down Socket server!!");

        } catch (IOException e) {
            System.out.println(e);
        } catch (ClassNotFoundException e) {
            System.out.println(e);
        }
    }

    /**
     * Starts the thread by passing it this and the thread name. Then starts itself
     * which calls run().
     */
    public void start() {
        System.out.print("Starting " + threadName + "\n");
        if (t == null) {
            t = new Thread(this, Integer.toString(threadName));
            t.start();
        }
    }

    /**
     * Function used to encrypt text with the cesar cipher.
     * 
     * @param clientIn
     * @param rotationAmount
     * @return serverOut
     */
    public static String encryptText(String clientIn, int rotationAmount) {
        // Create string buffer to return
        StringBuffer serverOut = new StringBuffer();
        // For ever character in clientIn
        for (int i = 0; i < clientIn.length(); i++) {
            // If character isnt a num or a space convert them, else dont
            if (Character.isLetter(clientIn.charAt(i)) && clientIn.charAt(i) != ' ') {
                // if the character is upercase, keep it upper
                if (Character.isUpperCase(clientIn.charAt(i))) {
                    // Convert the character using the ascii values of the characters
                    char newChar = (char) (((int) clientIn.charAt(i) + rotationAmount - 65) % 26 + 65);
                    serverOut.append(newChar);
                    // Else keep it lower
                } else {
                    // Convert the character using the ascii values of the characters
                    char newChar = (char) (((int) clientIn.charAt(i) + rotationAmount - 97) % 26 + 97);
                    serverOut.append(newChar);
                }
            } else {
                serverOut.append(clientIn.charAt(i));
            }
        }
        // Return the encrypted string
        return serverOut.toString();
    }
}
