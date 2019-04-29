
// package com.journaldev.socket;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * This class implements java socket client
 * @author pankaj
 *
 */
public class clientHost2 {

    public static void main(String[] args) throws UnknownHostException, IOException, ClassNotFoundException, InterruptedException{
        //get the localhost IP address, if server is running on some other IP, you need to use that
        Socket socket = null;
        ObjectOutputStream oos = null;
        ObjectInputStream ois = null;
        //establish socket connection to server
        socket = new Socket("brooks.cs.calvin.edu", 9876);
        //write to socket using ObjectOutputStream
        oos = new ObjectOutputStream(socket.getOutputStream());
        System.out.println("Sending request to Socket Server");
        oos.writeObject(12);
        //read the server response message
        System.out.println("Getting request to Socket Server");
        ois = new ObjectInputStream(socket.getInputStream());
        String message = (String) ois.readObject();
        System.out.println("Message: " + message);
        //close resources
        ois.close();
        oos.close();
        socket.close();
    }
}
