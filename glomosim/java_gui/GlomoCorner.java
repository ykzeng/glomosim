import java.awt.*;
import javax.swing.*;

/*
 * The corner defination of the GlomoCanvas
 */ 
public class GlomoCorner extends JComponent {
    public void paintComponent(Graphics g) {
        // Fill me with dirty brown/orange.
        g.setColor(new Color(230, 163, 4));
        g.fillRect(0, 0, getWidth(), getHeight());
    }
}

