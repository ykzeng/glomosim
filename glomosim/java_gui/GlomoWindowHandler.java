import java.awt.event.*;

import javax.swing.*;

public class GlomoWindowHandler extends WindowAdapter {
    public final static int CLOSE = 1;
    public final static int EXIT = 2;
    private int type;

    public GlomoWindowHandler(int t) {
        type = t;
    }

    public void windowClosing(WindowEvent e) {
        if (type == GlomoWindowHandler.CLOSE) {
            e.getWindow().setVisible(false);
            e.getWindow().dispose();
        }
        else if (type == GlomoWindowHandler.EXIT) {
            System.exit(0);
        }
    }
}
