import java.io.*;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.time.Instant;
import java.time.temporal.ChronoUnit;
import java.security.SecureRandom;

public class Player {
    private int rank;
    private int division;
    private String username;
    private String password;
    private String token;
    private int points;

    private long tokenLimit;
    private long timestampQueue;

    //Socket Variables
    private BufferedReader inputStream;
    private PrintWriter outputStream;

    private Socket socket;

    private String status = "NONE";
    private String connectionStatus = "NONE";

    public Player(String username, String password){
        this.username = username;
        this.password = password;
        this.token = "0";
        this.points=0;
        this.timestampQueue = 0;
        this.rank = 0;
    }

    public synchronized int getRank() {
        return rank;
    }

    public synchronized void setRank(int rank) {
        this.rank = rank;
    }

    public synchronized void updateRank(int rank) {
        this.rank += rank;
        if(this.rank < 0)
            this.rank = 0;
        else if(this.rank > 100)
            this.rank = 100;
    }

    public synchronized void updateDivision() {
        if(rank <= 25)
            division = 3;
        else if(rank < 50)
            division = 2;
        else
            division = 1;
    }

    public synchronized int getDivision() {
        return division;
    }

    public synchronized String getUsername() {
        return username;
    }

    public synchronized void setUsername(String username) {
        this.username = username;
    }

    public synchronized String getPassword() {
        return password;
    }

    public synchronized void setPassword(String password) {
        this.password = password;
    }

    public synchronized String getToken() {
        return token;
    }

    public synchronized void setToken(String token) {
        this.token = token;
    }

    public synchronized void generateToken(int minutes) {
        SecureRandom random = new SecureRandom();
        String tokenGen = random.nextLong(1000000, 10000000) + this.username;

        try {
            // Create an instance of MessageDigest with SHA-256 algorithm
            MessageDigest digest = MessageDigest.getInstance("SHA-256");

            // Convert the password string to bytes
            byte[] passwordBytes = tokenGen.getBytes(StandardCharsets.UTF_8);

            // Update the digest with the password bytes
            byte[] hashedBytes = digest.digest(passwordBytes);

            // Convert the hashed bytes to hexadecimal format
            StringBuilder hexBuilder = new StringBuilder();
            for (byte b : hashedBytes) {
                hexBuilder.append(String.format("%02x", b));
            }

            this.token = hexBuilder.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }

        this.tokenLimit = Instant.now().plus(minutes, ChronoUnit.MINUTES).getEpochSecond();
    }

    public synchronized long getTimestampQueue() {
        return timestampQueue;
    }

    public synchronized void setTimestampQueue(long timestampQueue) {
        this.timestampQueue = timestampQueue;
    }

    public synchronized void generateTimestampQueue() {
        this.timestampQueue = Instant.now().getEpochSecond();
    }

    public synchronized long getTokenLimit() {
        return tokenLimit;
    }

    public synchronized void setTokenLimit(long tokenLimit) {
        this.tokenLimit = tokenLimit;
    }

    public synchronized void printPlayer() {
        System.out.println("Username: " + this.username);
        System.out.println("Password: " + this.password);
        System.out.println("Rank: " + this.rank);
        System.out.println("Token: " + this.token);
        System.out.println("TokenLimit: " + this.tokenLimit);
        System.out.println("TimestampQueue: " + this.timestampQueue);
    }

    public synchronized Socket getSocket() {
        return socket;
    }

    public synchronized void setSocket(Socket socket) {
        this.socket = socket;
    }
    public synchronized BufferedReader getInputStream() {
        return inputStream;
    }

    public synchronized void setInputStream(BufferedReader inputStream) {
        this.inputStream = inputStream;
    }

    public synchronized PrintWriter getOutputStream() {
        return outputStream;
    }

    public synchronized void setOutputStream(PrintWriter outputStream) {
        this.outputStream = outputStream;
    }

    public synchronized void updateUserFile(String path) {
        //username:password:rank:token:tokenLimit:timestampQueue
        try {
            String filename = path + this.username + ".txt";
            File file = new File(filename);

            // Check if the file doesn't exist
            if (!file.exists()) {
                file.createNewFile(); // Create a new file
            }

            FileWriter writer = new FileWriter(filename);
            String separator = ":";
            writer.write(
                    getPassword() + separator +
                            getRank() + separator +
                            getToken() + separator +
                            getTokenLimit() + separator +
                            getTimestampQueue());
            writer.close();
        } catch (IOException e) {
            System.out.println("An error occurred: " + e.getMessage());
        }
    }
    public synchronized int getPoints(){
        return points;
    }

    public synchronized void addPoints(){
        points ++;
    }
    public synchronized void removePoints(){
        points -- ;
    }

    public synchronized void resetPoints() {
        this.points = 0;
    }

    public synchronized void setStatusQueue() {
        this.status = "QUEUE";
    }
    public synchronized void setStatusGame() {
        this.status = "GAME";
    }
    public synchronized void setStatusLogin() {
        this.status = "LOGIN";
    }

    public synchronized void setStatusAddQueue() {
        this.status = "ADDQUEUE";
    }

    public synchronized void setStatusAlive() {
        this.status = "CHECKALIVE";
    }
    public synchronized void setConnnectionDEAD() {
        this.connectionStatus = "DEAD";
    }
    public synchronized void setConnnectionALIVE() {
        this.connectionStatus = "ALIVE";
    }

    public synchronized String getConnectionStatus() {
        return this.connectionStatus;
    }

    public synchronized String getStatus() {
        return this.status;
    }

    public synchronized long getTime() {
        return (Instant.now().getEpochSecond() - timestampQueue)/60;
    }

}
