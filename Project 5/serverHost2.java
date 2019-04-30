
// package com.journaldev.socket;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.ClassNotFoundException;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * This class implements java Socket server
 * 
 * @author pankaj
 *
 */

public class serverHost2 {

    // static ServerSocket variable
    private static ServerSocket server;
    // socket server port on which it will listen
    private static int port = 9876;

    public static void main(String args[]) throws IOException, ClassNotFoundException {
        // create the socket server object
        server = new ServerSocket(port);
        int i = 1;
        // keep listens indefinitely until receives 'exit' call or program terminates
        while (true) {
            System.out.println("Waiting for the client request");
            // creating socket and waiting for client connection
            Socket socket = server.accept();
            serverThread rogueThread = new serverThread(socket, i);
            rogueThread.start();
            i++;
            if (i == 100) {
                break;
            }
        }
        server.close();
    }

}

class serverThread extends Thread {
    private Thread t;
    private Socket mySocket = null;
    private Integer threadName;

    serverThread(Socket passedSocket, Integer i) {
        mySocket = passedSocket;
        threadName = i;
        System.out.println("Creating " + threadName);
    }

    public void run() {
        try {
            Integer rotationNum = null;
            Boolean crashed = false;
            // keep listens indefinitely until receives 'exit' call or program terminates
            while (true) {
                System.out.println("Starting socket thread: " + threadName);
                // creating socket and waiting for client connection
                ObjectInputStream ois = new ObjectInputStream(mySocket.getInputStream());
                ObjectOutputStream oos = new ObjectOutputStream(mySocket.getOutputStream());
                String rotationMessage = (String) ois.readObject();
                System.out.println("Message Received: " + rotationMessage);
                rotationNum = Integer.parseInt(rotationMessage);
                // create ObjectOutputStream object
                // write object to Socket
                if (rotationNum <= 25 && rotationNum >= 1) {
                    oos.writeObject("Set the rotation to " + rotationNum);
                } else {
                    oos.writeObject("Invalid rotation given, shutting down socket");
                    crashed = true;
                }

                while (true && !crashed) {
                    String message = (String) ois.readObject();
                    System.out.println("Message Received: " + message);
                    if (message.equalsIgnoreCase("exit")) {
                        break;
                    }
                    message = encrypt(message, rotationNum).toString();
                    System.out.println("Message Written Back: " + message);
                    oos.writeObject(message);
                }
                ois.close();
                oos.close();
                mySocket.close();
                System.out.println("Shutting down Socket server!!");
            }
        } catch (IOException e) {
            System.out.println(e);
        } catch (ClassNotFoundException e) {
            System.out.println(e);
        }
    }

    public void start() {
        System.out.println("Starting " + threadName);
        if (t == null) {
            t = new Thread(this, Integer.toString(threadName));
            t.start();
        }
    }

    public static StringBuffer encrypt(String text, int s) {
        StringBuffer result = new StringBuffer();

        for (int i = 0; i < text.length(); i++) {
            if (Character.isLetter(text.charAt(i)) && text.charAt(i) != ' ') {
                if (Character.isUpperCase(text.charAt(i))) {
                    char ch = (char) (((int) text.charAt(i) + s - 65) % 26 + 65);
                    result.append(ch);
                } else {
                    char ch = (char) (((int) text.charAt(i) + s - 97) % 26 + 97);
                    result.append(ch);
                }
            } else {
                result.append(text.charAt(i));
            }
        }
        return result;
    }
}
