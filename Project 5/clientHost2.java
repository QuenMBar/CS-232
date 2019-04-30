
// package com.journaldev.socket;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

/**
 * This class implements java socket client
 * 
 * @author pankaj
 *
 */
public class clientHost2 {

    public static void main(String[] args)
            throws UnknownHostException, IOException, ClassNotFoundException, InterruptedException {
        // get the localhost IP address, if server is running on some other IP, you need
        // to use that
        Socket socket = null;
        ObjectOutputStream oos = null;
        ObjectInputStream ois = null;
        InetAddress brooksServeAddress = InetAddress.getByName(args[0] + ".cs.calvin.edu");
        System.out.println("IP ADDRESS: " + brooksServeAddress);
        // establish socket connection to server
        Scanner keyboard = new Scanner(System.in);
        String userIn = "";
        System.out.print("Enter the rotation amount to be used: ");
        Integer rotationAmount = keyboard.nextInt();
        Boolean firstRun = true;
        socket = new Socket(brooksServeAddress, Integer.parseInt(args[1]));
        oos = new ObjectOutputStream(socket.getOutputStream());
        ois = new ObjectInputStream(socket.getInputStream());
        while (!(userIn.equalsIgnoreCase("quit")) || firstRun) {
            // write to socket using ObjectOutputStream
            System.out.println("Sending request to Socket Server");
            if (firstRun) {
                oos.writeObject(Integer.toString(rotationAmount));
            } else {
                oos.writeObject(userIn);
            }
            // read the server response message
            System.out.println("Getting request to Socket Server");
            String message = (String) ois.readObject();
            System.out.println("Message: " + message);
            if (message.equals("Invalid rotation given, shutting down socket")) {
                break;
            }
            // close resources
            firstRun = false;
            System.out.print("Enter the message or quit to quit: ");
            userIn = keyboard.nextLine();
        }
        oos.writeObject("exit");
        ois.close();
        oos.close();
        keyboard.close();
        socket.close();
    }
}
