import java.awt.*;
import java.awt.event.*;
import java.io.*;

import javax.swing.*;

public class GlomoMain extends JFrame {
    private Color bgColor = Color.lightGray;
    private Color canvasBgColor = Color.gray;

    public static void main(String[] args) {
        new GlomoMain().addWindowListener(
                new GlomoWindowHandler(GlomoWindowHandler.EXIT));
    }

    public GlomoMain() {

        super("GloMoSim Visualization Tool");
 
        Container contentPane = getContentPane();
        contentPane.setLayout(new BorderLayout());

        contentPane.setBackground(bgColor);
        setSize(new Dimension(700, 800));
        setResizable(true);

        GlomoStatusPanel statusPanel = new GlomoStatusPanel();
        contentPane.add(statusPanel, BorderLayout.SOUTH);

        GlomoScrollCanvas sp = new GlomoScrollCanvas(1000, 1000,
                                         statusPanel, canvasBgColor);
        GlomoCanvas gc = sp.GetGlomoCanvas();
        contentPane.add(sp, BorderLayout.CENTER);

        GlomoToolBarPanel toolBarPanel = new GlomoToolBarPanel(gc);
        contentPane.add(toolBarPanel, BorderLayout.NORTH);

        GlomoMenuBar menuBar = new GlomoMenuBar( this, gc, 
                               statusPanel, toolBarPanel, canvasBgColor);
        setJMenuBar(menuBar);
        toolBarPanel.setMenuBar(menuBar);

	setVisible(true);
        toFront();
    }
}
