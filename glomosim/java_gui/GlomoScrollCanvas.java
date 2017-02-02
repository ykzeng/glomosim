import java.awt.*;
import javax.swing.*;

/*
 * The scroll canvas
 */
public class GlomoScrollCanvas extends JPanel{
    private GlomoRule columnView, rowView;
    private GlomoCanvas displayCanvas;

    public GlomoScrollCanvas(int w, int h, GlomoStatusPanel gsp, Color bc) {
        // Create the row and column rule of the display view
        columnView = new GlomoRule(GlomoRule.HORIZONTAL,w,20);
        rowView = new GlomoRule(GlomoRule.VERTICAL, 20, h);

        // Create the display canvas
        displayCanvas = new GlomoCanvas(w, h, gsp, bc, columnView, rowView);

        // Create the corners.
        JPanel corner = new JPanel();

        // Set up the scroll pane.
        JScrollPane scrollPanel = new JScrollPane(displayCanvas);
        scrollPanel.setPreferredSize(new Dimension(300, 250));
        scrollPanel.setViewportBorder(
                    BorderFactory.createLineBorder(Color.black));
        scrollPanel.setColumnHeaderView(columnView);
        scrollPanel.setRowHeaderView(rowView);

        scrollPanel.setCorner(JScrollPane.UPPER_LEFT_CORNER, corner);

        // put in in this panel.
        setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
        add(scrollPanel);
    }

    public GlomoCanvas GetGlomoCanvas()
    {
        return(displayCanvas);
    }
}
