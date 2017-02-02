import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

//--------------------------------------------------------------------------
// class MessageDialog
//--------------------------------------------------------------------------
public class GlomoMessageDialog extends JDialog implements ActionListener {
    private JLabel message;
    private JButton okButton;
//  private JPanel panel;

  //----------------------------------------------------------------------
  // Constructor
  //----------------------------------------------------------------------
    GlomoMessageDialog(JFrame parent) {
        super(parent, "", true);
   
        Container contentPane = getContentPane();
 
        contentPane.setSize(new Dimension(300, 300));
        setResizable(true);
        contentPane.setLayout(new GridLayout(0,1));

        message = new JLabel("", JLabel.CENTER);
        contentPane.add(message);
    
        JPanel panel = new JPanel();
        okButton = new JButton("OK");
        okButton.addActionListener(this);
        panel.add(okButton);
        contentPane.add(panel);
        //pack();
    }

  //----------------------------------------------------------------------
  // setMessage
  //----------------------------------------------------------------------
    public void setMessage(String title, String msg) {
        setTitle(title);
        message.setText(msg);
        pack();
        setVisible(true);
    }  

  //----------------------------------------------------------------------
  // actionPerformed
  //----------------------------------------------------------------------
    public void actionPerformed(ActionEvent e) {
        setVisible(false);
    }  
}
