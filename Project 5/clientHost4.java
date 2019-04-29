import java.io.*;
import java.net.*;

class clientHost4 {
    public static void main(String argv[]) throws Exception {
        String sentence;
        String modifiedSentence;
        InetAddress brooksServeAddress = InetAddress.getByName("brooks.cs.calvin.edu");
        BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
        Socket clientSocket = new Socket(brooksServeAddress, 9876);
        DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
        BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        sentence = inFromUser.readLine();
        outToServer.writeBytes("12");
        modifiedSentence = inFromServer.readLine();
        System.out.println("FROM SERVER: " + modifiedSentence);
        clientSocket.close();
    }
}