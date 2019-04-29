
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
        InetAddress brooksServeAddress = InetAddress.getByName("brooks.cs.calvin.edu");
        System.out.println("IP ADDRESS: " + brooksServeAddress);
        // establish socket connection to server
        Scanner keyboard = new Scanner(System.in);
        System.out.print("Enter the rotation amount to be used or quit to quit: ");
        String userIn = keyboard.next();
        while (userIn != "quit") {
            socket = new Socket("153.106.116.87", 9876);
            // write to socket using ObjectOutputStream
            oos = new ObjectOutputStream(socket.getOutputStream());
            System.out.println("Sending request to Socket Server");
            oos.writeObject(12);
            // read the server response message
            System.out.println("Getting request to Socket Server");
            ois = new ObjectInputStream(socket.getInputStream());
            Integer message = (Integer) ois.readObject();
            System.out.println("Message: " + message);
            // close resources
            ois.close();
            oos.close();
            Thread.sleep(100);
            System.out.print("Enter the rotation amount to be used or quit to quit: ");
            userIn = keyboard.next();
        }
        keyboard.close();
        socket.close();
    }
}
