import java.awt.*;
import java.awt.event.*;
import java.io.*;

import javax.swing.*;
import javax.swing.text.*;
import javax.swing.event.*;

public class GlomoConfigDialog extends JDialog
                implements ActionListener, DocumentListener {
    private JFileChooser fDialog;
    private JDialog saveChangesDialog;
    private JTextArea notePad;
    private String titleBar = "GloMoSim Configuration File: ";
//  private String extension = ".IN";
    private String extension = "";
    private boolean textChanged = false;
    private GlomoMessageDialog messageDialog;
    private JFrame parentFrame;

    public GlomoConfigDialog(JFrame parent, GlomoMessageDialog gmd)
    {
        super(parent, "", true);

        Container contentPane = getContentPane();

        setBackground(Color.lightGray);
        setTitle(titleBar + "Untitled");
        setResizable(true);
        contentPane.setLayout(new BorderLayout());
        messageDialog = gmd;
        parentFrame = parent;

        fDialog = new JFileChooser();
        fDialog.setCurrentDirectory(new File("../bin"));
        //fDialog.setSelectedFile(new File('*' + extension));
        fDialog.setSelectedFile(new File("CONFIG.IN"));

        saveChangesDialog = new JDialog(parent, true);
        saveChangesDialog.getContentPane().setLayout(new BorderLayout()); 
        JButton yes = new JButton("Yes");
        yes.addActionListener(this);
        JButton no = new JButton("No");
        no.addActionListener(this);
        JButton cancel = new JButton("Cancel");
        cancel.addActionListener(this);
        JPanel pdp = new JPanel();
        pdp.add(yes);
        pdp.add(no);
        pdp.add(cancel);
        saveChangesDialog.getContentPane().add(pdp, BorderLayout.SOUTH);
        saveChangesDialog.getContentPane().add(new JLabel("Do you wish to save the changes " +
                    "you have made to this file?"), BorderLayout.CENTER); 
        saveChangesDialog.pack();

        JButton open = new JButton("Open...");
        JButton saveAs = new JButton("Save As...");
        JButton close = new JButton("Close");

        open.addActionListener(this);
        saveAs.addActionListener(this);
        close.addActionListener(this);

        JPanel p = new JPanel();
        p.add(open);
        p.add(saveAs);
        p.add(close);

        notePad = new JTextArea(40,80);
        notePad.setFont(new Font("Monospaced", Font.PLAIN, 12));
        notePad.getDocument().addDocumentListener(this);
        JScrollPane sp = new JScrollPane(notePad);
        sp.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        contentPane.add(p, BorderLayout.NORTH);
        contentPane.add(sp, BorderLayout.CENTER);
        pack();
    }

    public boolean openFile () throws IOException
    {
        int returnVal = fDialog.showOpenDialog(parentFrame);

        if (returnVal == JFileChooser.APPROVE_OPTION) {
            setTitle(titleBar + fDialog.getSelectedFile().getName());
            FileReader fr = new FileReader(fDialog.getSelectedFile());
            char[] buf = new char[(int) (fDialog.getSelectedFile()).length()];
            fr.read(buf);
            fr.close();
            notePad.setText(String.valueOf(buf));
            notePad.revalidate();
            textChanged = false;
            return(true);
        }
        else{
            return(false);
        }
    }

    private void saveFile() throws IOException
    {
        int returnVal = fDialog.showSaveDialog(parentFrame);

        if (returnVal == JFileChooser.APPROVE_OPTION) {
            setTitle(titleBar + fDialog.getSelectedFile().getName());
            FileWriter fr = new FileWriter(
                                fDialog.getCurrentDirectory().getName() 
                                + fDialog.getSelectedFile().getName());
            fr.write(notePad.getText());
            fr.close();
            textChanged = false;
        }
    }

    public void actionPerformed(ActionEvent e)
    {
        String command = e.getActionCommand();

        if (command.equals("Open...")) {
            try {
                openFile();
            } catch (IOException ex) {
                messageDialog.setMessage("", "Open: Error! " +
                                             "Check that file exists.");
            }
        }
        else if (command.equals("Save As...")) {
            try {
                saveFile();
            } catch (IOException ex) {
                messageDialog.setMessage("", "Save As...: Error! Make sure to" +
                                          " chmod file so that it is writable");
            }
        }
        else if (command.equals("Close")) {
// commenting this out because it works properly for jdk 1.1.7 on NT
// but does not work properly on jdk 1.1.3 on Solaris
//            if (textChanged == true) {
//                saveChangesDialog.setVisible(true);
//            }
//            else {
                saveChangesDialog.setVisible(false);
                notePad.setText("");
                setVisible(false);
//            }
        }
        else if (command.equals("Yes")) {
            try {
                saveFile();
            } catch (IOException ex) {
                messageDialog.setMessage("", "Save As...: Error! Make sure to" +
                                          " chmod file so that it is writable");
            }
            saveChangesDialog.setVisible(false);
            if (textChanged == false) {
                notePad.setText("");
                setVisible(false);
            }
        }
        else if (command.equals("No")) {
            saveChangesDialog.setVisible(false);
            notePad.setText("");
            setVisible(false);
        }
        else if (command.equals("Cancel")) {
            saveChangesDialog.setVisible(false);
        }
    }

    public void insertUpdate(DocumentEvent e) {
        textChanged = true;
    }

    public void removeUpdate(DocumentEvent e) {
        textChanged = true;
    }

    public void changedUpdate(DocumentEvent e) {
        //Plain text components don't fire these events
        textChanged = true;
    }
}
