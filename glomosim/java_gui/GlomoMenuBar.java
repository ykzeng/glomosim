import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

import javax.swing.*;

public class GlomoMenuBar extends JMenuBar
                            implements ActionListener, ItemListener {
    private JMenuItem openMenuItem, resetMenuItem, exitMenuItem;
    private JMenuItem realTimeMenuItem, writeTraceMenuItem, abortMenuItem, playBackMenuItem;
    private JMenuItem breakPointMenuItem, statsMenuItem, guiOptionMenuItem;
    private JCheckBoxMenuItem toolBarMenuItem, statusBarMenuItem;
    private JMenuItem aboutMenuItem, contentsMenuItem;

    private JRadioButtonMenuItem //zoom sub-menu
                             oneMenuItem, twoMenuItem, threeMenuItem, fourMenuItem;
    private JMenuItem bgColorMenuItem;   //bgColor menu item
    private JButton okInputButton, cancelInputButton;
    private JCheckBox guiRadioOption, guiRoutingOption;
    private GlomoContentsDialog contentsDialog;
    private GlomoAboutDialog aboutDialog;
    private GlomoConfigDialog configDialog;
    private GlomoGuiOptionsDialog guiOptionsDialog;
    private GlomoMessageDialog messageDialog;
    private JFrame parent;
    private GlomoCanvas gCanvas;
    private GlomoStatusPanel statusPanel;
    private GlomoToolBarPanel toolBarPanel;
    private Color bgColor;
    private JDialog inputDialog;
    private int magnification = 4;
    private GlomoRunThread runThread;
    private JLabel executable, traceFile;
    private JTextField execTF, traceTF;
    private String executableName = "..\\bin\\glomosim ..\\bin\\config.in";
    private boolean guiRadio, guiRouting;
    private String traceFileName = "untitled.trace";
    private int traceOption;
    private JColorChooser colorChooser;

    private final String GUI_OPTION = "GUI-OPTION";
    private final String GUI_RADIO  = "GUI-RADIO";
    private final String GUI_ROUTING = "GUI-ROUTING";

    public GlomoMenuBar(JFrame parent, GlomoCanvas gc, GlomoStatusPanel sp,
                        GlomoToolBarPanel tbp, Color bgColor) {
        // Create the Menu Bar
        super();
        this.parent = parent;
        gCanvas = gc;
        statusPanel = sp;
        toolBarPanel = tbp;
        this.bgColor = bgColor;

        guiRadio = true;
        guiRouting = true;
  
        // set the executable file name according to the operationg system
        if(System.getProperty("file.separator","/").trim().equals("/")){ // Unix file system
            executableName = "../bin/glomosim ../bin/config.in";
        }
             
        // Create File Menu
        JMenu fileMenu = new JMenu("File");
        fileMenu.setMnemonic(KeyEvent.VK_F);

        openMenuItem = new JMenuItem("Open...", KeyEvent.VK_O);
        openMenuItem.setAccelerator(
                     KeyStroke.getKeyStroke(KeyEvent.VK_O,
                     ActionEvent.CTRL_MASK));
        openMenuItem.addActionListener(this);
        fileMenu.add(openMenuItem);

        resetMenuItem = new JMenuItem("Reset", KeyEvent.VK_R);
        resetMenuItem.setAccelerator(
                      KeyStroke.getKeyStroke(KeyEvent.VK_N, 
                      ActionEvent.CTRL_MASK));
        resetMenuItem.addActionListener(this);
        //fileMenu.add(resetMenuItem);

        fileMenu.addSeparator();
        exitMenuItem = new JMenuItem("Exit", KeyEvent.VK_X);
        exitMenuItem.setAccelerator(
                     KeyStroke.getKeyStroke(KeyEvent.VK_X, 
                     ActionEvent.CTRL_MASK));
        exitMenuItem.addActionListener(this);
        fileMenu.add(exitMenuItem);

        add(fileMenu);

        // Create view Menu
        JMenu viewMenu = new JMenu("View");
        viewMenu.setMnemonic(KeyEvent.VK_V);

        toolBarMenuItem = new JCheckBoxMenuItem("Tool Bar");
        toolBarMenuItem.setState(true);
        toolBarMenuItem.addItemListener(this);
        viewMenu.add(toolBarMenuItem);

        statusBarMenuItem = new JCheckBoxMenuItem("Status Bar");
        statusBarMenuItem.setState(true);
        statusBarMenuItem.addItemListener(this);
        viewMenu.add(statusBarMenuItem);

        add(viewMenu);

        // Create Simulate Menu
        JMenu simulateMenu = new JMenu("Simulate");
        simulateMenu.setMnemonic(KeyEvent.VK_S);

        realTimeMenuItem = new JMenuItem("Real Time",
                                  KeyEvent.VK_R);
        realTimeMenuItem.setAccelerator(
                         KeyStroke.getKeyStroke(KeyEvent.VK_R,
                         ActionEvent.CTRL_MASK));
        realTimeMenuItem.addActionListener(this);
        simulateMenu.add(realTimeMenuItem);

        writeTraceMenuItem = new JMenuItem("Write Trace",KeyEvent.VK_W);
        writeTraceMenuItem.setAccelerator(
                           KeyStroke.getKeyStroke(KeyEvent.VK_W,
                           ActionEvent.CTRL_MASK));
        writeTraceMenuItem.addActionListener(this);
        simulateMenu.add(writeTraceMenuItem);

        playBackMenuItem = new JMenuItem("Play Back",KeyEvent.VK_P);
        playBackMenuItem.setAccelerator(
                         KeyStroke.getKeyStroke(KeyEvent.VK_P,
                         ActionEvent.CTRL_MASK));
        playBackMenuItem.addActionListener(this);
        simulateMenu.add(playBackMenuItem);

        simulateMenu.addSeparator();
        abortMenuItem = new JMenuItem("Abort", KeyEvent.VK_A);
        abortMenuItem.setAccelerator(
                      KeyStroke.getKeyStroke(KeyEvent.VK_A,
                      ActionEvent.CTRL_MASK));
        abortMenuItem.addActionListener(this);
        abortMenuItem.setEnabled(false);
        simulateMenu.add(abortMenuItem);

        add(simulateMenu);

        // Create Options Menu
        JMenu optionsMenu = new JMenu("Options");
        optionsMenu.setMnemonic(KeyEvent.VK_O);
        
        // Create Zoom Sub Menu
        JMenu zoomMenu = new JMenu("Zoom");
        ButtonGroup group = new ButtonGroup();

        oneMenuItem = new JRadioButtonMenuItem("Normal");
        oneMenuItem.addActionListener(this);
        group.add(oneMenuItem);
        zoomMenu.add(oneMenuItem);

        twoMenuItem = new JRadioButtonMenuItem("times 2");
        twoMenuItem.addActionListener(this);
        group.add(twoMenuItem);
        zoomMenu.add(twoMenuItem);

        threeMenuItem = new JRadioButtonMenuItem("times 3");
        threeMenuItem.addActionListener(this);
        group.add(threeMenuItem);
        zoomMenu.add(threeMenuItem);

        fourMenuItem = new JRadioButtonMenuItem("times 4");
        fourMenuItem.addActionListener(this);
        group.add(fourMenuItem);
        zoomMenu.add(fourMenuItem);

        setZoomItems(fourMenuItem);

        optionsMenu.add(zoomMenu);

        // Create Color Menu Item
        bgColorMenuItem = new JMenuItem("Background Colors");
        bgColorMenuItem.addActionListener(this);
        optionsMenu.add(bgColorMenuItem);        

        // Create Gui Sub Menu
        guiOptionMenuItem = new JMenuItem("GUI Options...");
        guiOptionMenuItem.addActionListener(this);
        optionsMenu.add(guiOptionMenuItem);

        add(optionsMenu);

        // Create Debug Menu
        JMenu debugMenu = new JMenu("Debug");
        debugMenu.setMnemonic(KeyEvent.VK_D);

        breakPointMenuItem = new JMenuItem("Break Point", KeyEvent.VK_B);
        breakPointMenuItem.setAccelerator(
                           KeyStroke.getKeyStroke(KeyEvent.VK_B,
                           ActionEvent.CTRL_MASK));
        breakPointMenuItem.setEnabled (false);
        breakPointMenuItem.addActionListener(this);
        debugMenu.add(breakPointMenuItem);

        statsMenuItem = new JMenuItem("View stats...");
        statsMenuItem.addActionListener(this);
        debugMenu.add(statsMenuItem);

        add(debugMenu);

        // Create Help Menu
        // In order to make help menu at the right edage, create
        // a blank glue
        add(Box.createHorizontalGlue());

        JMenu helpMenu = new JMenu("Help");
        helpMenu.setMnemonic(KeyEvent.VK_H);

        contentsMenuItem = new JMenuItem("Contents",KeyEvent.VK_C);
        contentsMenuItem.addActionListener(this);
        helpMenu.add(contentsMenuItem);

        aboutMenuItem = new JMenuItem("About");
        aboutMenuItem.addActionListener(this);
        helpMenu.add(aboutMenuItem);

        add(helpMenu);

        // Set a raised bevel border of menu bar
        setBorder(BorderFactory.createRaisedBevelBorder());

        // Create Dialogs
        messageDialog = new GlomoMessageDialog(parent);
        configDialog = new GlomoConfigDialog(parent, messageDialog);
        contentsDialog = new GlomoContentsDialog(parent, messageDialog);
        aboutDialog = new GlomoAboutDialog(parent);
        guiOptionsDialog=new GlomoGuiOptionsDialog(parent, messageDialog);

        // Create the Color Chooser 
        colorChooser = new JColorChooser();
    }

    public void actionPerformed(ActionEvent e) {
        Object action = e.getSource();

        if (action == openMenuItem) {
            try {
                if(configDialog.openFile()){
                    configDialog.setVisible(true);
                }
            } catch(IOException ioe) {
                messageDialog.setMessage("Config Open...",
                                                "Error processing file!");
            }
        }
        else if (action == exitMenuItem) {
            System.exit(0);
        }
        else if (action == contentsMenuItem) {
            contentsDialog.setVisible(true);
        }
        else if (action == aboutMenuItem) {
            aboutDialog.setVisible(true);
        }
        else if (action == realTimeMenuItem) {
            traceOption = GlomoRunThread.REAL_TIME;
            inputDialog = new JDialog(parent, "", true);
            initInputDialog(inputDialog);
            inputDialog.setVisible(true);
        }
        else if (action == writeTraceMenuItem) {
            traceOption = GlomoRunThread.WRITE_TRACE;
            inputDialog = new JDialog(parent, "", true);
            initInputDialog(inputDialog);
            inputDialog.setVisible(true);
        }
        else if (action == playBackMenuItem) {
            traceOption = GlomoRunThread.PLAYBACK_TRACE;
            inputDialog = new JDialog(parent, "", true);
            initInputDialog(inputDialog);
            inputDialog.setVisible(true);
        }
        else if (action == cancelInputButton) {
            resetMenuAndToolBars();
            inputDialog.setVisible(false);
        }
        else if (action == okInputButton) {
            inputDialog.setVisible(false);

            //set menu items and tool buttons
            if ((traceOption == GlomoRunThread.WRITE_TRACE)){
                setRunSettings();
            }
            else{
                setPlayBackSettings();
            }

            if ((traceOption == GlomoRunThread.WRITE_TRACE)
                 || (traceOption == GlomoRunThread.REAL_TIME)) {
                executableName = execTF.getText();
                guiRadio = guiRadioOption.isSelected();
                guiRouting = guiRoutingOption.isSelected();
                if( !setGuiOptions(executableName, guiRadio, guiRouting)){
                    messageDialog.setMessage("Input Error","Wrong input command");
                    return;
                }
            }

            if (traceOption != GlomoRunThread.REAL_TIME) {
                traceFileName = traceTF.getText();
            }
            runThread.setParams(executableName, traceFileName);
            runThread.start();
        }
        else if (action == abortMenuItem) {
            runThread.abortSim();
            // if the runThread is currently paused, you need to resume it
            // before it can abort; otherwise, it will continue to wait()
            if (runThread.isSimPaused() == true) {
                runThread.resumeSim();
                toolBarPanel.setPauseLabel();
            }
        }
        else if (action == statsMenuItem) {
            try {
                GlomoStatsDialog statsDialog =
                                new GlomoStatsDialog(parent, messageDialog);
                statsDialog.openFile();
            } catch (NumberFormatException nfe) {
                messageDialog.setMessage("Stats Open...",
                                                "Error processing file!");
            } catch (IOException ioe) {
                messageDialog.setMessage("Stats Open...",
                                                "Error processing file!");
            }
        }
        else if (action == guiOptionMenuItem) {
            guiOptionsDialog.setVisible(true);
        }
        else if (action == oneMenuItem) {
            setMagnification(1);
            toolBarPanel.setMagnification(1);
        }
        else if (action == twoMenuItem) {
            setMagnification(2);
            toolBarPanel.setMagnification(2);
        }
        else if (action == threeMenuItem) {
            setMagnification(3);
            toolBarPanel.setMagnification(3);
        }
        else if (action == fourMenuItem) {
            setMagnification(4);
            toolBarPanel.setMagnification(4);
        }
        else if (action == bgColorMenuItem)
        {
            selectBackgroundColor();
        }
        else {
            messageDialog.setMessage("", "Unkown action!");
        }
    }

    public void itemStateChanged(ItemEvent ie) {
        Object item = ie.getSource();

        if(item == toolBarMenuItem)
        {
            if(ie.getStateChange() == ItemEvent.SELECTED)
            {
                toolBarPanel.setVisible(true);
            }
            else
            {
                toolBarPanel.setVisible(false);
            }
        }
        else if(item == statusBarMenuItem)
        {
            if(ie.getStateChange() == ItemEvent.SELECTED)
            {
                 statusPanel.setVisible(true);
            }
            else
            {
                 statusPanel.setVisible(false);
            }
        }
    }

    public boolean setGuiOptions(String executeString, 
                                 boolean guiRadio, boolean guiRouting){
        boolean setGuiOption = false;
        boolean setRadioOption = false;
        boolean setRoutingOption = false;

        if(executeString == null){
            return(false);
        }
       
        // get the file name of config file. 
        String tmpString = executeString.trim();
        if(tmpString == ""){
            return(false);
        }

        int pos = tmpString.indexOf(' ');
        if(pos == -1){
            return(false);
        }

        String configFileName = tmpString.substring(pos);
        configFileName = configFileName.trim();

        // open config file
        try{
            RandomAccessFile configFile = new RandomAccessFile(configFileName, "rw");

            //read all line from config file 
            Vector configFileLines = new Vector();
            String aLine;
            while((aLine = configFile.readLine()) != null){
                configFileLines.addElement(aLine);
            }

            // write lines into config file and modify gui options
            configFile.seek(0);
            configFile.setLength(0);
            for( int i=0; i< configFileLines.size(); i++){
                aLine = ((String)configFileLines.elementAt(i)).trim();
 
                if(aLine.indexOf(GUI_OPTION) == 0){  // gui option
                    configFile.writeBytes(GUI_OPTION + "   YES\n");
                    setGuiOption = true;
                }
                else if(aLine.indexOf(GUI_RADIO) == 0){  // gui radio option
                    if(guiRadio){
                        configFile.writeBytes(GUI_RADIO + "    YES\n");
                    }
                    else
                    {
                        configFile.writeBytes(GUI_RADIO + "    NO\n");
                    }
                    setRadioOption = true;
                }
                else if(aLine.indexOf(GUI_ROUTING) == 0){  // gui routing
                    if(guiRouting){
                        configFile.writeBytes(GUI_ROUTING + "  YES\n");
                    }
                    else
                    {
                        configFile.writeBytes(GUI_ROUTING + "  NO\n");
                    }
                    setRoutingOption = true;
                }
                else
                {
                    configFile.writeBytes(configFileLines.elementAt(i) + "\n");
                }
            }
   
            if(!setGuiOption){
                configFile.writeBytes(GUI_OPTION + "   YES\n");
            }

            if(!setRadioOption){
                if(guiRadio){
                    configFile.writeBytes(GUI_RADIO + "    YES\n");
                }
                else
                {
                    configFile.writeBytes(GUI_RADIO + "    NO\n");
                }
            }

            if(!setRoutingOption){
                if(guiRouting){
                    configFile.writeBytes(GUI_ROUTING + "  YES\n");
                }
                else
                {
                    configFile.writeBytes(GUI_ROUTING + "  NO\n");
                }
            }

            configFile.close();
        } catch (FileNotFoundException e){
            messageDialog.setMessage("File Error", "Can not open config file");
            return(false);
        } catch (IOException e){
            messageDialog.setMessage("File Error", "Write config file error");
        } finally{}

        return(true);
    }

    public void setMagnification(int m){
        if((m >= 1) && (m<=4)){
            magnification = m;
            switch(m){
                case 1 : setZoomItems(oneMenuItem);
                         break;

                case 2 : setZoomItems(twoMenuItem);
                         break;

                case 3 : setZoomItems(threeMenuItem);
                         break;

                case 4 : setZoomItems(fourMenuItem);
                         break;

            }
            gCanvas.setMagnification(m);
            gCanvas.repaint();
         }
    }

    public void setZoomItems(JRadioButtonMenuItem rbmi) {
        oneMenuItem.setSelected(false);
        twoMenuItem.setSelected(false);
        threeMenuItem.setSelected(false);
        fourMenuItem.setSelected(false);
        rbmi.setSelected(true);
    }

    public void selectBackgroundColor() {
        Color newColor = colorChooser.showDialog(parent,
                             "Choose Background Color",
                             bgColor);
        if((newColor != null) && (newColor != bgColor))
        {
            bgColor = newColor;
            gCanvas.setBackgroundColor(bgColor);
        }
    }

    public void setRunSettings() {
        writeTraceMenuItem.setEnabled(false);
        playBackMenuItem.setEnabled(false);
    }

    public void setPlayBackSettings() {
        writeTraceMenuItem.setEnabled(false);
        playBackMenuItem.setEnabled(false);
        toolBarPanel.setEnabledButtons(true);
        abortMenuItem.setEnabled(true);
    }

    public void resetMenuAndToolBars() {
        toolBarPanel.setEnabledButtons(false);
        writeTraceMenuItem.setEnabled(true);
        playBackMenuItem.setEnabled(true);
        abortMenuItem.setEnabled(false);
    }

    private void initInputDialog(JDialog inputDialog) {
        inputDialog.setResizable(true);
        inputDialog.getContentPane().setLayout(new GridLayout(0, 2));

        gCanvas.setBackgroundColor(bgColor);
        boolean showTxRangeOption = guiOptionsDialog.getShowTxRangeOption();
        boolean showNodeConnectionsOption =
                        guiOptionsDialog.getShowNodeConnectionsOption();
        boolean showDemoColorsOption =
                        guiOptionsDialog.getShowDemoColorsOption();
        Hashtable cHtbl = guiOptionsDialog.getColorHtbl();

        if(runThread != null){ // To kill old simulation
            if(runThread.isAlive()){
                runThread.abortSim();
                runThread = null;
            }
        }
        runThread = new GlomoRunThread(executableName, parent, gCanvas, this,
                       statusPanel, toolBarPanel, traceOption, 
                       showTxRangeOption,
                       showNodeConnectionsOption, showDemoColorsOption, cHtbl);
        runThread.setMagnification(magnification);
        toolBarPanel.setRunThread(runThread);

        if (traceOption == GlomoRunThread.REAL_TIME) {
            inputDialog.setTitle("Run Simulation in Real Time");
            executable = new JLabel("Executable:");
            execTF = new JTextField(executableName);
            inputDialog.getContentPane().add(executable);
            inputDialog.getContentPane().add(execTF);
        }
        else if (traceOption == GlomoRunThread.WRITE_TRACE) {
            inputDialog.setTitle("Create Trace File of Simulation");
            executable = new JLabel("Executable:");
            execTF = new JTextField(executableName);
            inputDialog.getContentPane().add(executable);
            inputDialog.getContentPane().add(execTF);
        }
        else {
            inputDialog.setTitle("Play Back Trace File");
        }

        traceFile = new JLabel("Trace File:");
        traceTF = new JTextField(traceFileName);
        okInputButton = new JButton("OK");
        okInputButton.addActionListener(this);
        cancelInputButton = new JButton("Cancel");
        cancelInputButton.addActionListener(this);

        if (traceOption != GlomoRunThread.REAL_TIME) {
            inputDialog.getContentPane().add(traceFile);
            inputDialog.getContentPane().add(traceTF);
        }

        if ((traceOption == GlomoRunThread.REAL_TIME) ||
            (traceOption == GlomoRunThread.WRITE_TRACE)){
            guiRadioOption = new JCheckBox("Show Radio Layer");
            guiRadioOption.setSelected(guiRadio);
            inputDialog.getContentPane().add(guiRadioOption);

            guiRoutingOption = new JCheckBox("Show Network Layer");
            guiRoutingOption.setSelected(guiRouting);
            inputDialog.getContentPane().add(guiRoutingOption);
        }
       
        inputDialog.getContentPane().add(okInputButton);
        inputDialog.getContentPane().add(cancelInputButton);

        inputDialog.pack();

        inputDialog.addWindowListener(
                        new GlomoWindowHandler(GlomoWindowHandler.CLOSE));
    }
}

class GlomoAboutDialog extends JDialog implements ActionListener {
    private JLabel message;
    private JButton okButton;

    public GlomoAboutDialog(JFrame parent) {
        super(parent, "About GloMoSim Visualization Tool", true);
        setResizable(true);

        getContentPane().setLayout(new GridLayout(0, 1));

        message = new JLabel("GloMoSim Visualization Tool", JLabel.CENTER);
        getContentPane().add(message);
        message = new JLabel("Version 1.1, 1999", JLabel.CENTER);
        getContentPane().add(message);
        message = new JLabel("by Addison Lee", JLabel.CENTER);
        getContentPane().add(message);
        message = new JLabel("Upgraded by Kaixin Xu", JLabel.CENTER);
        getContentPane().add(message);
        message = new JLabel("Go UCLA Bruins!", JLabel.CENTER);
        getContentPane().add(message);

        okButton = new JButton("OK");
        okButton.addActionListener(this);
        JPanel okPanel = new JPanel();
        okPanel.add(okButton); 
        getContentPane().add(okPanel);

        pack();
        addWindowListener(new GlomoWindowHandler(GlomoWindowHandler.CLOSE));
    }

    public void actionPerformed(ActionEvent e) {
        setVisible(false);
    }
}

class GlomoContentsDialog extends JDialog implements ActionListener {
    GlomoMessageDialog messageDialog;

    public GlomoContentsDialog(JFrame parent, GlomoMessageDialog gmDialog) {
        super(parent, "Help Contents", false);
        messageDialog = gmDialog;
        setResizable(true);

        getContentPane().setLayout(new BorderLayout()); 

        JTextArea helpPad = new JTextArea("", 40, 80);
        helpPad.setFont(new Font("Monospaced", Font.PLAIN, 12));
        String fileName = "vis_help.txt";
        try {
            FileReader fr = new FileReader(fileName);
            char[] buf = new char[(int) (new File(fileName)).length()];
            fr.read(buf);
            fr.close();
            helpPad.setText(String.valueOf(buf));
        } catch(FileNotFoundException fnfe) {
            messageDialog.setMessage("", "Help: " + fileName + " not found!");
        } catch(IOException ioe) {
            messageDialog.setMessage("", "Help: IOException occurred!"); 
        }

        JScrollPane sp = new JScrollPane(helpPad);
        getContentPane().add(sp, BorderLayout.CENTER);

        JPanel p = new JPanel();
        JButton cancelButton = new JButton("Cancel");
        cancelButton.addActionListener(this);
        p.add(cancelButton);
        getContentPane().add(p, BorderLayout.SOUTH);

        pack();
        addWindowListener(new GlomoWindowHandler(GlomoWindowHandler.CLOSE));
    }

    public void actionPerformed(ActionEvent e)
    {
        String clicked = e.getActionCommand();

        if (clicked.equals("Cancel")) {
            setVisible(false);
        }
        else {
            messageDialog.setMessage("", "Help: Invalid Action!");
        }
    }
}

class GlomoStatsDialog extends JDialog implements ActionListener {

    private JButton showStatsButton, cancelButton;
    private GlomoMessageDialog messageDialog;
    private JCheckBox statsCheckBoxes[];
    private JTextArea statsPad;
    //private String directoryName = "../bin";
    private String directoryName = "";
    private File statsFile = new File("GLOMO.STAT");
    private String titleBar = "GloMoSim Statistics File: ";
    private BufferedReader brStats; 
    private JFrame parent;

    public GlomoStatsDialog(JFrame f, GlomoMessageDialog gmDialog)
    {
        super(f, "View Stats...", true);
        parent = f;
        messageDialog = gmDialog;
        setResizable(true);

        getContentPane().setLayout(new BorderLayout());

        statsPad = new JTextArea("", 40, 100);
        statsPad.setFont(new Font("Monospaced", Font.PLAIN, 12));
        JScrollPane  sp = new JScrollPane(statsPad);

        JPanel buttonPanel = new JPanel(new GridLayout(1, 2));
        showStatsButton = new JButton("Show Stats");
        showStatsButton.addActionListener(this);
        cancelButton = new JButton("Cancel");
        cancelButton.addActionListener(this);
        buttonPanel.add(showStatsButton);
        buttonPanel.add(cancelButton);

        getContentPane().add(sp, BorderLayout.CENTER);
        getContentPane().add(buttonPanel, BorderLayout.SOUTH);

        pack();
        addWindowListener(new GlomoWindowHandler(GlomoWindowHandler.CLOSE));
    }

    public void formatStats() throws FileNotFoundException, IOException {
        String line, word;
        StringTokenizer strTokenizer;
        Hashtable statsHtbl = new Hashtable(statsCheckBoxes.length);

        for (int i=0; i < statsCheckBoxes.length; i++) { 
            if (statsCheckBoxes[i].isSelected() == true) {
                statsHtbl.put(statsCheckBoxes[i].getText() + ",", "0");
            }
        }

        statsPad.setText("");

        brStats = new BufferedReader(new FileReader(statsFile));
        while ((line = brStats.readLine()) != null) {
            strTokenizer = new StringTokenizer (line); 

            // incorrect line format or blank line
            if(strTokenizer.countTokens() < 5) {
                continue;
            }

            // skip over the first three fields in the stats file
            strTokenizer.nextToken();
            strTokenizer.nextToken();
            word = strTokenizer.nextToken();

            // check for proper file format
            if (word.equals("Layer:") != true) {
                messageDialog.setMessage("", "Wrong format for Stats file!");
                break;
            }

            word = strTokenizer.nextToken();

            // check if we want to show this type of statistic
            if (statsHtbl.containsKey(word) == true) {
                statsPad.append(line + "\n");
            }
        }
        statsPad.revalidate();
    }

    public void openFile() throws IOException, NumberFormatException
    {
        JFileChooser fc = new JFileChooser();
        fc.setCurrentDirectory(new File(directoryName));
        fc.setSelectedFile(statsFile);

        int returnVal = fc.showOpenDialog(parent);
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            statsFile = fc.getSelectedFile();
            setTitle(titleBar + statsFile.getName());
            directoryName = fc.getCurrentDirectory().getName();
            brStats = new BufferedReader(new FileReader(statsFile));
            String word, line;
            int oldNodeNum = -1, newNodeNum = -1;
            boolean firstLine = true;
            Vector statsCheckBoxVec = new Vector();

            while ((line = brStats.readLine()) != null) {
                StringTokenizer strTokenizer = new StringTokenizer (line); 
                
                if(strTokenizer.countTokens() < 5) {
                    continue;
                }

                strTokenizer.nextToken();

                word = strTokenizer.nextToken();
                if (word.endsWith(",")) {
                    word = word.substring(0, word.length() - 1);
                }
                newNodeNum = Integer.parseInt(word);
                if (firstLine == true) {
                    firstLine = false;
                    oldNodeNum = newNodeNum;
                }
                if (oldNodeNum != newNodeNum) {
                    break;
                }
                oldNodeNum = newNodeNum;

                word = strTokenizer.nextToken();

                if (word.equals("Layer:") != true) {
                    messageDialog.setMessage("","Wrong format for Stats file!");
                    break;
                }
                word = strTokenizer.nextToken();
                word = word.substring(0, word.length() - 1);
                if (statsCheckBoxVec.contains(word) == false) {
                    statsCheckBoxVec.addElement(word);
                }
            }

            JPanel optionPanel = new JPanel(new GridLayout(0, 1));
            statsCheckBoxes = new JCheckBox[statsCheckBoxVec.size()];
            for (int i=0; i < statsCheckBoxes.length ; i++) { 
                statsCheckBoxes[i] = new JCheckBox(
                                    (String) statsCheckBoxVec.elementAt(i));
                optionPanel.add(statsCheckBoxes[i]); 
            }
            getContentPane().add(optionPanel, BorderLayout.WEST);
            pack();
            setVisible(true);
        }
    }

    public void actionPerformed(ActionEvent e)
    {
        Object clicked = e.getSource();

        if (clicked == showStatsButton) {
            try {
                formatStats();
            } catch (FileNotFoundException fnfe) {
                messageDialog.setMessage(
                        "", "File not found!");
            } catch (IOException ioe) {
                messageDialog.setMessage(
                        "", "IO Error occured while processing stats file!");
            }
        }
        else if (clicked == cancelButton) {
            setVisible(false); 
        }
    }
}

class GlomoGuiOptionsDialog extends JDialog
        implements ActionListener, ItemListener, AdjustmentListener {
    private GlomoMessageDialog messageDialog;
    private JCheckBox showTxRangeCb, showNodeConnectionsCb, showDemoColorsCb;
    private Hashtable rgbHtbl;
    private JComboBox displayType;
    private JPanel demoCanvas;
    private JScrollBar redSb, greenSb, blueSb;
    private JLabel redLabel, greenLabel, blueLabel;
    private JButton okButton;
    private GridBagLayout gbLayout;
    private GridBagConstraints gbConstraints;

    public GlomoGuiOptionsDialog(JFrame parent, GlomoMessageDialog gmDialog) {
        super(parent, "Options Dialog...", true);
        messageDialog = gmDialog;
        setResizable(true);

        gbLayout = new GridBagLayout();
        gbConstraints = new GridBagConstraints();
        //gbConstraints.weightx = 1;
        //gbConstraints.weighty = 1;
        gbConstraints.gridwidth = 1;
        gbConstraints.gridheight = 1;
        gbConstraints.fill = GridBagConstraints.BOTH;
        getContentPane().setLayout(gbLayout);

        // boolean options
        addComponent(new JLabel("Show Transmission Range:"), 4, 0);
        showTxRangeCb = new JCheckBox("", false);
        addComponent(showTxRangeCb, 4, 1);

        addComponent(new JLabel("Show Node Connections:"), 5, 0);
        showNodeConnectionsCb = new JCheckBox("", false);
        addComponent(showNodeConnectionsCb, 5, 1);

        addComponent(new JLabel("Use Demo Colors:"), 6, 0);
        showDemoColorsCb = new JCheckBox("", false);
        addComponent(showDemoColorsCb, 6, 1);

        // Hash table for storing rgb values of the different display types
        rgbHtbl = new Hashtable(5);
        rgbHtbl.put("Node Color", new int[] {255, 0, 0});
        rgbHtbl.put("Line Color", new int[] {0, 255, 0});
        rgbHtbl.put("Link Color", new int[] {0, 0, 255});
        rgbHtbl.put("Broadcast Color", new int[] {0, 255, 0});
        rgbHtbl.put("Connection Color", new int[] {0, 0, 255});

        // choice menu for the different display types
        displayType = new JComboBox();
        for (Enumeration e = rgbHtbl.keys(); e.hasMoreElements() == true;) {
            displayType.addItem((String) e.nextElement());
        }
        displayType.addItemListener(this);
        addComponent(displayType, 7, 0);

        // canvas to display rgb color of selected display type
        demoCanvas = new JPanel();
        demoCanvas.setPreferredSize(new Dimension(10, 10));
        String key = (String)displayType.getSelectedItem();
        int[] rgb = (int[]) rgbHtbl.get(key);
        demoCanvas.setBackground(new Color(rgb[0], rgb[1], rgb[2]));
//        demoCanvas.repaint();
        addComponent(demoCanvas, 7, 1);

        redSb = new JScrollBar(JScrollBar.HORIZONTAL, 0, 1, 0, 255);
        redSb.addAdjustmentListener(this);
        redLabel = new JLabel(String.valueOf(redSb.getValue()));
        greenSb = new JScrollBar(JScrollBar.HORIZONTAL, 0, 1, 0, 255);
        greenSb.addAdjustmentListener(this);
        greenLabel = new JLabel(String.valueOf(greenSb.getValue()));
        blueSb = new JScrollBar(JScrollBar.HORIZONTAL, 0, 1, 0, 255);
        blueSb.addAdjustmentListener(this);
        blueLabel = new JLabel(String.valueOf(blueSb.getValue()));
        addComponent(redSb, 8, 0);
        addComponent(new JLabel(" r"), 8, 1);
        addComponent(redLabel, 9, 0);
        addComponent(greenSb, 10, 0);
        addComponent(new JLabel(" g"), 10, 1);
        addComponent(greenLabel, 11, 0);
        addComponent(blueSb, 12, 0);
        addComponent(new JLabel(" b"), 12, 1);
        addComponent(blueLabel, 13, 0);

        okButton = new JButton("OK");
        okButton.addActionListener(this);
        addComponent(okButton, 14, 0);

        pack();
        addWindowListener(new GlomoWindowHandler(GlomoWindowHandler.CLOSE));
    }

    public void addComponent(JComponent c, int row, int column) {
        gbConstraints.gridx = column;
        gbConstraints.gridy = row;
        gbLayout.setConstraints(c, gbConstraints);
        getContentPane().add(c);
    }

    public boolean getShowTxRangeOption() {
        return showTxRangeCb.isSelected();
    }

    public boolean getShowNodeConnectionsOption() {
        return showNodeConnectionsCb.isSelected();
    }

    public boolean getShowDemoColorsOption() {
        return showDemoColorsCb.isSelected();
    }

    public Hashtable getColorHtbl() {
        return rgbHtbl;
    }

    // updates scrollbars and canvas to reflect the rgb of the selected item
    public void itemStateChanged(ItemEvent ie) {
        //String key = (String)((JComboBox) ie.getSource()).getSelectedItem();
        int[] rgb = (int[]) rgbHtbl.get((String)displayType.getSelectedItem());

        redSb.setValue(rgb[0]);
        greenSb.setValue(rgb[1]);
        blueSb.setValue(rgb[2]);

        redLabel.setText(String.valueOf(rgb[0]));
        greenLabel.setText(String.valueOf(rgb[1]));
        blueLabel.setText(String.valueOf(rgb[2]));

        demoCanvas.setBackground(new Color(rgb[0], rgb[1], rgb[2]));
//        validate();
    }
    
    // updates the rgb values of the currently selected item
    public void adjustmentValueChanged(AdjustmentEvent ae) {
        Adjustable colorSb = ae.getAdjustable();
        Vector colorVec;
        int r = redSb.getValue();
        int g = greenSb.getValue();
        int b = blueSb.getValue();
        int[] rgb = (int[]) rgbHtbl.get((String)displayType.getSelectedItem());

        if (colorSb == redSb) {
            redLabel.setText(String.valueOf(r));
            rgb[0] = r;
        }
        else if (colorSb == greenSb) {
            greenLabel.setText(String.valueOf(g));
            rgb[1] = g;
        }
        else if (colorSb == blueSb) {
            blueLabel.setText(String.valueOf(b));
            rgb[2] = b;
        }
        else {
            messageDialog.setMessage("", "Error! Invalid adjustable!");
        }

        demoCanvas.setBackground(new Color(r, g, b));
//        validate();
    }

    public void actionPerformed(ActionEvent e) {
        Object action = e.getSource();

        if (action == okButton) {
            setVisible(false);
        }
        else {
            messageDialog.setMessage("", "Error! Invalid ActionEvent!");
        }
    }

}
