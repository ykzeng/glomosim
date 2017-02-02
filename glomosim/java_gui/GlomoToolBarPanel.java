import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.border.*;

public class GlomoToolBarPanel extends JToolBar implements ActionListener {
    private JButton speedUpButton, slowDownButton;// For control the speed of displaying.
    private JButton zoomInButton, zoomOutButton;     // To change the scale 
    private JButton rewindButton, stopButton, stepButton, runButton; // Control of display
    private Border stopRaisedBorder, stopLoweredBorder, runRaisedBorder, runLoweredBorder;
    private GlomoCanvas gCanvas;
    private GlomoMenuBar menuBar;
    private GlomoRunThread runThread;
    private JLabel simTimeLabel;
    private final String simTimeStringHead = "Timer(sec:msec:microsec)";

    public GlomoToolBarPanel(GlomoCanvas gc)
    {
        super();

        gCanvas = gc;

	setFloatable(false);
        setBorder(BorderFactory.createRaisedBevelBorder());
        setLayout(new BoxLayout(this, BoxLayout.X_AXIS));

        // Create speed control buttons
        JPanel speedPanel = new JPanel();

        speedUpButton = new JButton(new ImageIcon("SpeedUp.gif"));
        speedUpButton.setBorder(BorderFactory.createRaisedBevelBorder());
        speedUpButton.addActionListener(this);
        speedUpButton.setToolTipText("Speed Up");
        speedPanel.add(speedUpButton);

        slowDownButton = new JButton(new ImageIcon("SlowDown.gif"));
        slowDownButton.setBorder(BorderFactory.createRaisedBevelBorder());
        slowDownButton.addActionListener(this);
        slowDownButton.setToolTipText("Slow Down");
        speedPanel.add(slowDownButton);

        add(speedPanel);

        // Add a separator
        addSeparator();

        // Create zoom scale buttons
        JPanel zoomPanel = new JPanel();
        
        zoomInButton = new JButton(new ImageIcon("ZoomIn.gif"));
        zoomInButton.setBorder(BorderFactory.createRaisedBevelBorder());
        zoomInButton.addActionListener(this);
        zoomInButton.setToolTipText("Zoom In");
        zoomPanel.add(zoomInButton);

        zoomOutButton = new JButton(new ImageIcon("ZoomOut.gif"));
        zoomOutButton.setBorder(BorderFactory.createRaisedBevelBorder());
        zoomOutButton.addActionListener(this);
        zoomOutButton.setToolTipText("Zoom Out");
        zoomOutButton.setEnabled(false);
        zoomPanel.add(zoomOutButton);

	add(zoomPanel);

        // Add a separator
        addSeparator();

        // Create display control buttons
        JPanel controlPanel = new JPanel();

        stopRaisedBorder = BorderFactory.createRaisedBevelBorder();
        stopLoweredBorder = BorderFactory.createLoweredBevelBorder();
        runRaisedBorder = BorderFactory.createRaisedBevelBorder();
        runLoweredBorder = BorderFactory.createLoweredBevelBorder();

        rewindButton = new JButton(new ImageIcon("Rewind.gif"));
        rewindButton.setBorder(BorderFactory.createRaisedBevelBorder());
        rewindButton.addActionListener(this);
        rewindButton.setToolTipText("Rewind");
        //controlPanel.add(rewindButton);

        stopButton = new JButton(new ImageIcon("Stop.gif"));
        stopButton.setBorder(stopRaisedBorder);
        stopButton.addActionListener(this);
        stopButton.setToolTipText("Stop");
        controlPanel.add(stopButton);

        stepButton = new JButton(new ImageIcon("Step.gif"));
        stepButton.setBorder(BorderFactory.createRaisedBevelBorder());
        stepButton.addActionListener(this);
        stepButton.setToolTipText("Step");
        controlPanel.add(stepButton);

        runButton = new JButton(new ImageIcon("Run.gif"));
        runButton.setBorder(runRaisedBorder);
        runButton.addActionListener(this);
        runButton.setToolTipText("run");
        controlPanel.add(runButton);

        add(controlPanel);

        //add a box glue to make the simulation clock panel right alighment.
        add(Box.createHorizontalGlue());

        JPanel simTimePanel = new JPanel();
        simTimePanel.setPreferredSize(new Dimension(200,30));
        simTimePanel.setMaximumSize(new Dimension(200,30));
        simTimePanel.setMinimumSize(new Dimension(200,30));
        simTimePanel.setLayout(new GridLayout(0,1));

        simTimePanel.add(new JLabel(simTimeStringHead));
        simTimeLabel = new JLabel();
        simTimePanel.add(simTimeLabel);

        add(simTimePanel);

        setEnabledButtons(false);
    }

    public void setEnabledButtons(boolean b) {
        speedUpButton.setEnabled(b);
        slowDownButton.setEnabled(b);
 
        stepButton.setEnabled(b);
        stopButton.setBorder(stopRaisedBorder);
        stopButton.setEnabled(b);
        runButton.setEnabled(false);
        if(b){
            runButton.setBorder(runLoweredBorder);
        }
        else{
            runButton.setBorder(runRaisedBorder);
        }
    }

    public void setPauseLabel() {
        stopButton.setBorder(BorderFactory.createLoweredBevelBorder());
    }

    public void setRunThread(GlomoRunThread gr) {
        runThread = gr;
    }
    
    public void setMenuBar(GlomoMenuBar mb) {
        menuBar = mb;
    }

    public void setMagnification(int m){
        if( m == 4){
            zoomOutButton.setEnabled(false);
            zoomInButton.setEnabled(true);
        }
        else if ( m == 1){
            zoomInButton.setEnabled(false);
            zoomOutButton.setEnabled(true);
        }
        else{
            zoomOutButton.setEnabled(true);
            zoomInButton.setEnabled(true);
        }
    }

    public void actionPerformed(ActionEvent e) {
        Object command = e.getSource();

        if (command == stopButton) {
            runThread.pauseSim();
            stopButton.setBorder(stopLoweredBorder);
            stopButton.setEnabled(false);
            runButton.setBorder(runRaisedBorder);
            runButton.setEnabled(true);
        }
        else if (command == runButton) {
            runThread.resumeSim();
            stopButton.setBorder(stopRaisedBorder);
            stopButton.setEnabled(true);
            runButton.setBorder(runLoweredBorder);
            runButton.setEnabled(false);
        }
        else if (command == stepButton) {
            runThread.stepSim();
            stopButton.setBorder(stopLoweredBorder);
            stopButton.setEnabled(false);
            runButton.setBorder(runRaisedBorder);
            runButton.setEnabled(true);
        }
        else if (command == rewindButton) {
        }
        else if (command == speedUpButton) {
            runThread.setSimulationSpeed(GlomoRunThread.FASTER);
        }
        else if (command == slowDownButton) {
            runThread.setSimulationSpeed(GlomoRunThread.SLOWER);
        }
        else if (command == zoomOutButton){ //enlarge the scale of rule
            int m = gCanvas.getMagnification();
            if(m < 4){
                menuBar.setMagnification(m+1);
                setMagnification(m+1);
            }
        }
        else if (command == zoomInButton){ //smallen the scale of rule
            int m = gCanvas.getMagnification();
            if(m > 1){
                menuBar.setMagnification(m-1);
                setMagnification(m-1);
            }
        }
        else {
            System.err.println("GlomoToolBarPanel: Error!");
            System.exit(-1);
        }
    }

    // Display the simulation clock 
    public void setSimTime(long nanoSeconds){
        long seconds = nanoSeconds / 1000000000L;
        long milliSeconds = (nanoSeconds / 1000000L) % 1000;
        long microSeconds = (nanoSeconds / 1000L) % 1000;
        simTimeLabel.setText(seconds + ":" + milliSeconds + ":" + microSeconds);
    }
}
