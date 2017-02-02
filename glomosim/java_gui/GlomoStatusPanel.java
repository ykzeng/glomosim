import java.awt.*;
import javax.swing.*;

public class GlomoStatusPanel extends JPanel {
    private JLabel  helpMessageLabel;
    private JLabel  coordinatesLabel;
    private final String coordinatesString = "Coordinates of Mouse: ";
    private final String helpString = "  Info: ";

    public GlomoStatusPanel()
    {   
        super();
        setPreferredSize(new Dimension(700,30));
        setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
        setBorder(BorderFactory.createEmptyBorder());

        helpMessageLabel = new JLabel("");
        helpMessageLabel.setFont(new Font("Serif", Font.BOLD, 12));
        helpMessageLabel.setMinimumSize(new Dimension(200,25));
        add(helpMessageLabel);

        add(Box.createHorizontalGlue());

        coordinatesLabel = new JLabel(coordinatesString);
        coordinatesLabel.setMaximumSize(new Dimension(280,25));
        coordinatesLabel.setPreferredSize(new Dimension(280,25));
        coordinatesLabel.setMinimumSize(new Dimension(280,25));
        coordinatesLabel.setAlignmentX(LEFT_ALIGNMENT);
        add(coordinatesLabel);
    }

    // displays coordinates of mouse
    public void setCoordinates(String s) {
        coordinatesLabel.setText(coordinatesString + s);
    }

    // displays help message at the left side of the status button
    public void setHelpMessage(String s){
        if(s == null)
            helpMessageLabel.setText(helpString);
        else
            helpMessageLabel.setText(helpString + s);
    }
}
