package view;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Toolkit;

public class Dashboard extends JFrame {

    private static final String FRAME_NAME = "Console Dashboard";
    private static final String BUTTON_NAME = "Maintenance done";
    private static final double WIDTH_PERC = 0.3;
    private static final double HEIGHT_PERC = 0.3;

    private final JPanel panel;
    private final JPanel maintenancePanel;
    private final JButton button;
    private final JTextArea errorArea;
    private final JTextArea counterArea;

    public Dashboard() {
        super(FRAME_NAME);
        this.panel = new JPanel(new BorderLayout());
        this.maintenancePanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        this.button = new JButton(BUTTON_NAME);
        this.errorArea = new JTextArea("Maintenance required");
        this.counterArea = new JTextArea("Counter");

        this.errorArea.setEditable(false);
        this.errorArea.setRows(5);
        this.errorArea.setColumns(30);
        this.counterArea.setEditable(false);

        final Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();

        this.maintenancePanel.add(this.errorArea);
        this.maintenancePanel.add(this.button);

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

        this.button.addActionListener(e -> {
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
            }
        });
    }

    public static void main(String[] args) {
        new Dashboard();
    }
}