import java.awt.*;
import javax.swing.*;


/*
 * The definations of the Rule and Corner of the diaplay canvas
 */

public class GlomoRule extends JComponent {
    public static final int INCH = Toolkit.getDefaultToolkit().
            getScreenResolution();
    public static final int HORIZONTAL = 0;
    public static final int VERTICAL = 1;

    private Color bgColor = new Color(230,163,4);
    private Color fgColor = Color.black;
    private int orientation;
    private int increment = 50;
    private int magnification = 4;
    private int width, height;

    public GlomoRule(int o, int width, int height) {
        orientation = o;
        this.width = width;
        this.height = height;

        setPreferredSize(new Dimension(width, height));
    }

    public void setPreferredHeight(int ph) {
        height = ph;
        setPreferredSize(new Dimension(width, ph));
    }

    public void setPreferredWidth(int pw) {
        width = pw;
        setPreferredSize(new Dimension(pw, height));
    }

    public void setMagnification(int m)
    {
        magnification = m;
    }

    public void paintComponent(Graphics g) {

        g.setColor(bgColor);
        g.fillRect(0,0,width,height);

        // Do the ruler labels in a small font that's black.
        g.setFont(new Font("SansSerif", Font.PLAIN, 10));
        g.setColor(fgColor);

        int tickLength = 5;
        // ticks and labels
        if(orientation == HORIZONTAL){
            for ( int i = 0; i< (width / magnification); i += increment){
                g.drawLine(i*magnification, height-1, 
                           i*magnification, height-tickLength-1);
                g.drawString(String.valueOf(i), i*magnification+2,height-3);
            }
        }
        else{
            for ( int i = 0; i< (height / magnification); i += increment){
                g.drawLine(width-1, i*magnification, 
                           width-tickLength-1, i*magnification);
                g.drawString(String.valueOf(i), 2, i*magnification+10);
            }
        }
    }
}
