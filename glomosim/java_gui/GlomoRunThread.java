import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

import javax.swing.*;

public class GlomoRunThread extends Thread implements ActionListener {
    private String executableName, traceFileName;
    private GlomoMobileNode mobileNodes[];
    private GlomoCanvas gCanvas;
    private GlomoMenuBar menuBar;
    private GlomoStatusPanel statusPanel;
    private GlomoToolBarPanel toolBarPanel;
    private Process proc=null;
    private JFrame topFrame;
    private int demoOption, magnification;
    private JDialog runDialog;
    private boolean nodeArraySet = false;
    private int nodesSetSoFar = 0;

    private boolean showDemoColorsOption;
    private Hashtable demoColorHtbl;
    private long currentSimTime = 0; 

    private boolean showTxRangeOption;
    private boolean showNodeConnectionsOption;

    public static final int STOP_STATE  = 0;    // suspended the simulation
    public static final int RUN_STATE   = 1;    // run the simulation
    public static final int STEP_STATE  = 2;    // step the simulation
    public static final int ABORT_STATE = 3;    // abort the simulation

    private volatile boolean initialWaiting = false;
    private volatile int simState = RUN_STATE;

    // used by setSimlationSpeed function
    public static final int SLOWER = -2;
    public static final int FASTER = -3;
    private volatile int numIterations = 100;
    private int speedGap = 1;
    private int lastIsSpeedUp = 0;

    // options for displaying simulation
    public static final int REAL_TIME = -4;
    public static final int WRITE_TRACE = -5;
    public static final int PLAYBACK_TRACE = -6;

    // options for specifying which layer of GloMoSim to display
    // for now, only LAYER_RADIO and LAYER_MOBILITY_ONLY are implemented
    public static final int LAYER_TCP = -7;
    public static final int LAYER_MAC = -8;
    public static final int LAYER_RADIO = -9;
    public static final int LAYER_MOBILITY_ONLY = -10;

    // different commands for drawing things on the canvas
    private static final byte INITIALIZE = 0;
    private static final byte MOVE_NODE = 1;
    private static final byte DRAW_BROADCAST = 2;
    private static final byte DRAW_LINE = 3;
    private static final byte DRAW_THICKLINE = 4;
    private static final byte DRAW_LINK = 5;
    private static final byte ERASE_LINK = 6;


    private static final Color colors[] = {
        Color.black, Color.blue, Color.cyan, Color.darkGray,
        Color.gray, Color.green, Color.lightGray, Color.magenta,
        Color.orange, Color.pink, Color.red, Color.white, Color.yellow
    };

    public synchronized void setSimulationSpeed(int choice) {
        if (choice == SLOWER) {
            if(lastIsSpeedUp == -1){
                if(speedGap < 64){
                    speedGap += speedGap;
                }
            }else if(lastIsSpeedUp == 1){
                speedGap = 1;
            }
            lastIsSpeedUp = -1;
            if ((numIterations+speedGap) >= 2000) {
                numIterations = 2000;
                return;
            }
            else {
                numIterations += speedGap;
            }
        }
        else if (choice == FASTER) {
            if(lastIsSpeedUp == 1){
                if(speedGap < 64){
                    speedGap += speedGap;
                }
            }else if(lastIsSpeedUp == -1){
                speedGap = 1;
            }
            lastIsSpeedUp = 1;

            if ((numIterations-speedGap) <= 1) {
                numIterations = 1;
                return;
            }
            else {
                numIterations -= speedGap;
            }
        }
    }

    public synchronized void stopInitialWaiting () {
        if (initialWaiting == true) {
            initialWaiting = false;
            notify();
        }
    }

    public synchronized void abortSim() { 
        simState = ABORT_STATE;
        notify();
    }

    public synchronized void pauseSim() {
        simState = STOP_STATE;
    }

    public synchronized void resumeSim() {
        simState = RUN_STATE;
        notify();
    }

    public synchronized void stepSim() {
        simState = STEP_STATE;
        notify();
    }

    public boolean isSimPaused() {
        return (simState == STOP_STATE);
    }

    public void setParams(String e, String t) {
        executableName = e;
        traceFileName = t;
    }

    public void setMagnification(int m) {
        magnification = m;
    }

   public GlomoRunThread(String c, JFrame f, GlomoCanvas gc, GlomoMenuBar gmb,
                          GlomoStatusPanel sp, GlomoToolBarPanel tb, int op,
                          boolean stro, boolean snco,
                          boolean sdco, Hashtable htbl) {
        executableName = c;
        topFrame = f;
        gCanvas = gc;
        menuBar = gmb;
        statusPanel = sp;
        toolBarPanel = tb;
        demoOption = op;
        showTxRangeOption = stro;
        showNodeConnectionsOption = snco;
        showDemoColorsOption = sdco;
        demoColorHtbl = htbl;
        runDialog = new JDialog(topFrame, "Running...", false);
    }

    public void run() {
        GlomoMessageDialog messageDialog = new GlomoMessageDialog(topFrame);
        JLabel runLabel = new JLabel("Executing " + executableName); 
        runDialog.setResizable(true);
        runDialog.getContentPane().setLayout(new GridLayout(0, 1));
        runDialog.getContentPane().add(runLabel); 
        JButton cancel = new JButton("Cancel");
        cancel.addActionListener(this);
        runDialog.getContentPane().add(cancel);
        runDialog.pack();

        try {
            switch (demoOption) {
            case WRITE_TRACE:
                runDialog.setVisible(true);
                proc = Runtime.getRuntime().exec(executableName);
                BufferedReader brFromGlomo = new BufferedReader(
                                new InputStreamReader(proc.getInputStream()));
                BufferedWriter traceFile = new BufferedWriter(
                                            new FileWriter(traceFileName));
                String line;
                while ((line = brFromGlomo.readLine()) != null) {
                    traceFile.write(line);
                    traceFile.newLine();
                }
                traceFile.close();
                break;

            case REAL_TIME:
            case PLAYBACK_TRACE:
                // clear the canvas first 
                gCanvas.repaint();
                BufferedReader br;
                if (demoOption == REAL_TIME) {
                    proc = Runtime.getRuntime().exec(executableName);
                    br= new BufferedReader(
                          new InputStreamReader(proc.getInputStream()));
                }
                else {
                    br = new BufferedReader(new FileReader(traceFileName));
                }
                showSimulation(br);
                break;

            default:    
                messageDialog.setMessage("", "RunThread: no such option!");
            } // end switch(demoOption)
        } catch (FileNotFoundException fnfe) {
            messageDialog.setMessage("", "Error! File not found.");
            if(proc != null){
                proc.destroy();
                proc = null;
            }
        } catch (IOException ex) {
            messageDialog.setMessage("", "Error! I/O Exception occured. " +
                                     "Check that GloMoSim is working properly");
            if(proc != null){
                proc.destroy();
                proc = null;
            }
        } catch (InterruptedException e) {
            messageDialog.setMessage("", "Error! "
                                          + "Interrupted Exception occured."); 
        } finally {
            // only displayed for the WRITE_TRACE case
            runDialog.setTitle("Done");
            runLabel.setText("Simulation successfully completed! " +
                              "Ready for Play Back.");
            cancel.setText("Ok");
            runDialog.pack();
            menuBar.resetMenuAndToolBars();
        }
    } // end run
    
    private void showSimulation(BufferedReader br)
                throws IOException, InterruptedException {
        String line;
        StringTokenizer strTokenizer;
        int type;

        while ((line = br.readLine()) != null) {
            if( simState == ABORT_STATE){ // abort the simulation
                 killSubProcess();
                 break;
            }
            else if(simState == STEP_STATE){ // step the simulation
                 simState = STOP_STATE;
            }
            else if(simState == STOP_STATE){ // stop the simulation
                 synchronized(this){
                     while (simState == STOP_STATE){
                         wait();
                     }
                 }
            }

            if( simState == ABORT_STATE){ // abort the simulation
                 killSubProcess();
                 break;
            }

            strTokenizer = new StringTokenizer(line);

            // blank line
            if(strTokenizer.hasMoreTokens() == false) {
                continue;
            }

            try {
                type = Integer.parseInt(strTokenizer.nextToken());
            } catch (NumberFormatException ne) {
                // if first word of line is not an enum, ignore the line
                continue;
            }
            
            playLine(type, strTokenizer);
        }
    }

    private void playLine(int type, StringTokenizer strTokenizer)
                throws IOException, InterruptedException {
        int x, y, id, idDest, numNodes, txRange, thickness;
        long time;
        Color nodeColor, connectionColor, txColor;
        Graphics gContext = gCanvas.getGraphics();

        // display simtime if different from old simtime
        if (type != INITIALIZE) {
            time = Long.parseLong(strTokenizer.nextToken());
            if (time != currentSimTime) {
                toolBarPanel.setSimTime(time);
                currentSimTime = time;
            }
        }

        switch (type) {
        case INITIALIZE:
            numNodes = Integer.parseInt(strTokenizer.nextToken());
            if (nodeArraySet == false) {
                mobileNodes = new GlomoMobileNode[numNodes];
                nodeArraySet = true;
            }

            id = Integer.parseInt(strTokenizer.nextToken());
            x = Integer.parseInt(strTokenizer.nextToken());
            y = Integer.parseInt(strTokenizer.nextToken());
            txRange = Integer.parseInt(strTokenizer.nextToken());
            nodeColor = colors[Byte.parseByte(strTokenizer.nextToken())];
            connectionColor = colors[Byte.parseByte(strTokenizer.nextToken())];
            if (showDemoColorsOption == true) {
                int[] nodeRGB = (int[]) demoColorHtbl.get("Node Color");
                int[] conRGB = (int[]) demoColorHtbl.get("Connection Color");
                Color node = new Color(nodeRGB[0], nodeRGB[1], nodeRGB[2]);
                Color connection = new Color(conRGB[0], conRGB[1], conRGB[2]);
                mobileNodes[id] = new GlomoMobileNode(id, x,
                                    y, txRange,
                                    gCanvas,
                                    node, connection, showTxRangeOption,
                                    showNodeConnectionsOption);
            }
            else {
                mobileNodes[id] = new GlomoMobileNode(id, x,
                                        y, txRange,
                                        gCanvas,
                                        nodeColor, connectionColor,
                                        showTxRangeOption,
                                        showNodeConnectionsOption);
            }

            nodesSetSoFar++;
            if (nodesSetSoFar == numNodes) {
                for (int i=0; i < mobileNodes.length; i++) {
                    mobileNodes[i].createInitialConnections(mobileNodes);
                }
                gCanvas.setNodes(mobileNodes, this);

                // important: the order of the following two statements must NOT
                // be changed; otherwise, deadlock may sometimes occur
                initialWaiting = true;
                gCanvas.repaint();

                // the reason for waiting is to make sure that the canvas is
                // repainted BEFORE the simulation continues; gCanvas sets
                // initialWaiting to false
                synchronized(this) {
                    while (initialWaiting == true) {
                        wait();
                    }
                }
            }
            break;

        case MOVE_NODE:
            id = Integer.parseInt(strTokenizer.nextToken());
            x = Integer.parseInt(strTokenizer.nextToken());
            y = Integer.parseInt(strTokenizer.nextToken());

            mobileNodes[id].eraseAllConnections(gContext);
            mobileNodes[id].eraseNode(gContext, numIterations);
            mobileNodes[id].setLocation(
                               new Point(x, y));
            mobileNodes[id].updateConnections(mobileNodes);
            mobileNodes[id].drawNode(gContext);
            mobileNodes[id].drawAllConnections(gContext);
            break;

        case DRAW_BROADCAST:
            id = Integer.parseInt(strTokenizer.nextToken());
            txColor = colors[Byte.parseByte(strTokenizer.nextToken())];
            if (showDemoColorsOption == true) {
                int[] rgb = (int[]) demoColorHtbl.get("Broadcast Color");
                Color c = new Color(rgb[0], rgb[1], rgb[2]);
                mobileNodes[id].drawBroadcast(gContext, c, numIterations);
            }
            else {
                mobileNodes[id].drawBroadcast(gContext, txColor, numIterations);
            }
            break;

        case DRAW_LINE:
            id = Integer.parseInt(strTokenizer.nextToken());
            idDest = Integer.parseInt(strTokenizer.nextToken());
            txColor = colors[Byte.parseByte(strTokenizer.nextToken())];

            if (showDemoColorsOption == true) {
                int[] rgb = (int[]) demoColorHtbl.get("Line Color");
                Color demoLineColor = new Color(rgb[0], rgb[1], rgb[2]);
                mobileNodes[id].drawLine(mobileNodes[idDest], demoLineColor,
                                         gContext, numIterations);
            }
            else {
                mobileNodes[id].drawLine(mobileNodes[idDest], txColor,
                                         gContext, numIterations);
            }
            break;

        case DRAW_THICKLINE:
            id = Integer.parseInt(strTokenizer.nextToken());
            idDest = Integer.parseInt(strTokenizer.nextToken());
            thickness = Integer.parseInt(strTokenizer.nextToken());
            txColor = colors[Byte.parseByte(strTokenizer.nextToken())];

            if (showDemoColorsOption == true) {
                int[] rgb = (int[]) demoColorHtbl.get("Line Color");
                Color demoLineColor = new Color(rgb[0], rgb[1], rgb[2]);
                mobileNodes[id].drawThickLine(mobileNodes[idDest], thickness,
                                        demoLineColor, gContext, numIterations);
            }
            else {
                mobileNodes[id].drawThickLine(mobileNodes[idDest], thickness,
                                              txColor, gContext, numIterations);
            }
            break;

        case DRAW_LINK:
            id = Integer.parseInt(strTokenizer.nextToken());
            idDest = Integer.parseInt(strTokenizer.nextToken());
            txColor = colors[Byte.parseByte(strTokenizer.nextToken())];

            if (showDemoColorsOption == true) {
                int[] rgb = (int[]) demoColorHtbl.get("Link Color");
                Color demoLinkColor = new Color(rgb[0], rgb[1], rgb[2]);
                mobileNodes[id].drawLink(mobileNodes[idDest], demoLinkColor,
                                         gContext);
            }
            else {
                mobileNodes[id].drawLink(mobileNodes[idDest], txColor,
                                         gContext);
            }
            break;

        case ERASE_LINK:
            id = Integer.parseInt(strTokenizer.nextToken());
            idDest = Integer.parseInt(strTokenizer.nextToken());
            mobileNodes[id].eraseLink(mobileNodes[idDest], gContext);
            break;

        default:
            killSubProcess();
            System.err.println("Error! Unrecognized gui command!");
            System.exit(-1);

        } // end switch(type)

        gContext.dispose();

    } // end playLine

    public void actionPerformed(ActionEvent e) {
        String command = e.getActionCommand();

        if (command.equals("Cancel")) {
            killSubProcess();   
            menuBar.resetMenuAndToolBars();
            runDialog.setVisible(false);
        }
        else if (command.equals("Ok")) {
            runDialog.setVisible(false);
        }
    }

    public void killSubProcess() {
        if(proc != null){
            proc.destroy(); 
            proc = null;
        }
    }
}

