import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextArea;

import communication.CommunicationChannel;
import communication.SerialCommunicationChannel;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Toolkit;

import jssc.*;

public class Dashboard extends JFrame {

    private static final String FRAME_NAME = "Console Dashboard";
    private static final String BUTTON_NAME = "Maintenance done";
    private static final double WIDTH_PERC = 0.3;
    private static final double HEIGHT_PERC = 0.3;
    private static final String PORT = "COM14";
    private static final int BAUD_RATE = 9600;

    private final JPanel panel;
    private final JPanel maintenancePanel;
    static JButton button;
    static JTextArea errorArea;
    private final JTextArea counterArea;

    public Dashboard(CommunicationChannel channel) {
        super(FRAME_NAME);
        this.panel = new JPanel(new BorderLayout());
        this.maintenancePanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        button = new JButton(BUTTON_NAME);
        //button.setEnabled(false);
        errorArea = new JTextArea("");
        this.counterArea = new JTextArea("Counter");

        errorArea.setEditable(false);
        errorArea.setRows(5);
        errorArea.setColumns(30);
        this.counterArea.setEditable(false);

        final Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();

        this.maintenancePanel.add(errorArea);
        this.maintenancePanel.add(button);

        this.panel.add(this.maintenancePanel, BorderLayout.NORTH);
        this.panel.add(this.counterArea, BorderLayout.CENTER);

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
                channel.sendMsg("fix");
            }
        });
    }

    public static void main(String[] args) throws Exception {
        final CommunicationChannel channel = new SerialCommunicationChannel(PORT, BAUD_RATE);
        String msg;
        new Dashboard(channel);
        while (true) {
            msg = channel.receiveMsg();
            if (msg.compareToIgnoreCase("Maintenance required") == 0) {
                errorArea.setText(msg);
                button.setEnabled(true);
            } else {
                errorArea.setText("");
                //button.setEnabled(false);
            }
        }
    }
}