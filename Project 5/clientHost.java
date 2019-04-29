import java.util.Scanner;
import java.io.*;
import java.net.*;
import java.net.UnknownHostException;

class clientHost {
    public static void main(String[] args) throws UnknownHostException {
        Scanner keyboard = new Scanner(System.in);
        System.out.print("Enter the rotation amount to be used: ");
        int offset;
        offset = keyboard.nextInt();
        InetAddress brooksServeAddress = InetAddress.getByName("brooks.cs.calvin.edu");

        keyboard.close();
        System.out.print("1 ");
        Socket MyClient = null;
        DataOutputStream outStream = null;
        BufferedReader inStream = null;
        try {
            System.out.print("2 ");
            MyClient = new Socket(brooksServeAddress, 9876);
            outStream = new DataOutputStream(MyClient.getOutputStream());
            inStream = new BufferedReader(new InputStreamReader(MyClient.getInputStream()));
            System.out.print("3 ");
        } catch (UnknownHostException e) {
            System.out.print("3.1 ");
            System.err.println("Don't know about host: hostname");
        } catch (IOException e) {
            System.out.print("3.2 ");
            System.out.println(e);
        }
        System.out.print("4 ");
        if (MyClient != null && outStream != null && inStream != null) {
            try {
                System.out.print("5 ");
                outStream.writeBytes("14");
                System.out.print("6 ");
                String responseLine = inStream.readLine();
                System.out.println(responseLine);
                System.out.print("7 ");
                outStream.close();
                inStream.close();
                MyClient.close();
                System.out.print("8 ");
            } catch (UnknownHostException e) {
                System.out.print("8.1 ");
                System.err.println("Trying to connect to unknown host: " + e);
            } catch (IOException e) {
                System.out.print("8.2 ");
                System.err.println("IOException:  " + e);
            }
        }

    }
}