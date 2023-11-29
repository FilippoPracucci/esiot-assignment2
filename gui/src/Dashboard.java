import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextArea;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Toolkit;

import jssc.*;

public class Dashboard extends JFrame {

    private static final String FRAME_NAME = "Console Dashboard";
    private static final String BUTTON_NAME = "Maintenance done";
    private static final double WIDTH_PERC = 0.5;
    private static final double HEIGHT_PERC = 0.5;
    private static final String PORT = "COM9";
    private static final int BAUD_RATE = 9600;

    private final JPanel panel;
    private final JPanel maintenancePanel;
    private static JButton button;
    private static JTextArea errorArea;
    private static JTextArea counterArea;
    private static SerialPort serialPort;
    private static String textCounter;

    public Dashboard() {
        super(FRAME_NAME);
        this.panel = new JPanel(new BorderLayout());
        this.maintenancePanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        button = new JButton(BUTTON_NAME);
        button.setEnabled(false);
        errorArea = new JTextArea("");
        textCounter = new String("Number of washes completed = ");
        counterArea = new JTextArea(textCounter + 0);

        errorArea.setEditable(false);
        errorArea.setRows(5);
        errorArea.setColumns(30);
        counterArea.setEditable(false);

        final Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();

        this.maintenancePanel.add(errorArea);
        this.maintenancePanel.add(button);

        this.panel.add(this.maintenancePanel, BorderLayout.NORTH);
        this.panel.add(counterArea, BorderLayout.CENTER);

        this.panel.setPreferredSize(new Dimension(Double.valueOf(screenSize.getWidth() * WIDTH_PERC).intValue(),
                Double.valueOf(screenSize.getHeight() * HEIGHT_PERC).intValue()));

        this.add(this.panel);
        this.pack();
        this.setLocationRelativeTo(null);
        this.setVisible(true);
        this.setResizable(false);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        button.addActionListener(e -> {
            final String[] options = { "Yes", "No" };
            final int result = JOptionPane.showOptionDialog(this,
                    "Do you confirm that you have done the maintenance?",
                    "Confirmation",
                    JOptionPane.YES_NO_OPTION,
                    JOptionPane.QUESTION_MESSAGE,
                    null,
                    options,
                    options[1]);
            /* Action if he/she confirms */
            if (result == 0) {
                try {
                    serialPort.writeBytes("fix".getBytes());
                    errorArea.setText("");
                    button.setEnabled(false);
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            }
        });
    }

    public static void main(String[] args) throws Exception {
        new Dashboard();
        StringBuilder receivedData = new StringBuilder();
        serialPort = new SerialPort(PORT);
        try {
            serialPort.openPort();
            serialPort.setParams(
                BAUD_RATE, 
                SerialPort.DATABITS_8,
                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE
            );
        } catch (Exception e) {
            e.printStackTrace();
        }
        serialPort.addEventListener(new SerialPortEventListener() {

            @Override
            public void serialEvent(SerialPortEvent event) {
                if (event.isRXCHAR() && event.getEventValue() > 0) {
                    try {
                        byte[] buffer = serialPort.readBytes(event.getEventValue());
                        String data = new String(buffer, "UTF-8");
                        receivedData.append(data);
                        int newLineIndex;
                        while ((newLineIndex = receivedData.indexOf("\n")) != -1 ) {
                            String completeString = receivedData.substring(0, newLineIndex);
                            receivedData.delete(0, newLineIndex + 1);
                            completeString = completeString.substring(0, completeString.length() - 1);
                            /* System.out.println(completeString);
                            System.out.println("Lunghezza ultimo messaggio ricevuto: " + completeString.length()); */
                            /*if the string contains a number it indicates the number of washing completed*/
                            if (completeString.matches("[+-]?\\d*(\\.\\d+)?")) { 
                                counterArea.setText(textCounter + Integer.parseInt(completeString));
                            } else {
                                if (completeString.equals("warning")) {
                                    button.setEnabled(true);
                                    errorArea.setText("Maintenance required");
                                }

                            }
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
            
        });
    }
}