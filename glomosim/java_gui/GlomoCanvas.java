import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

/*
 * The displaying canvas
 */
public class GlomoCanvas extends JPanel
                    implements MouseListener, MouseMotionListener {
    private Color bgColor;
    private GlomoMobileNode mobileNodes[];
    private GlomoMobileNode selectedNode;
    private boolean nodesSet = false;
    private GlomoStatusPanel statusPanel;
    private int width, height, selectedX, selectedY, scaledX, scaledY;
    private int magnification = 4;
    private GlomoRunThread runThread;
    private GlomoRule columnRule, rowRule;

    public GlomoCanvas(int w, int h, GlomoStatusPanel gsp, Color bc, 
                       GlomoRule columnRule, GlomoRule rowRule) {
        super();
        setPreferredSize(new Dimension(w, h));
        width = w;
        height = h;
        bgColor = bc;
        setOpaque(true);
        setBackgroundColor(bgColor);
        statusPanel = gsp;
        this.columnRule = columnRule;
        this.rowRule = rowRule;
        addMouseListener(this);
        addMouseMotionListener(this);
    }

    public void setMagnification(int m) {
        magnification = m;

        columnRule.setMagnification(m);
        columnRule.repaint();

        rowRule.setMagnification(m);
        rowRule.repaint(); 
    }

    public void setBackgroundColor(Color c) {
        bgColor = c;
        setBackground(bgColor);
    }

    public Color getBackgroundColor(){
        return(bgColor);
    }

    public void setNodes(GlomoMobileNode mn[], GlomoRunThread rt) {
        mobileNodes = mn;
        nodesSet = true;
        runThread = rt;
    }

    public void paintComponent(Graphics g) {
        // do the super class painting
        super.paintComponent(g);

        g.setXORMode(bgColor);
        if (nodesSet == true) {
            for (int i = 0; i < mobileNodes.length ; i++) {
                mobileNodes[i].drawNode(g);
                mobileNodes[i].drawHigherIdConnections(g);
            }
            // notify run thread now that canvas has finished repainting 
            runThread.stopInitialWaiting();
        }
    }

    public void mousePressed(MouseEvent m) {
        if (nodesSet == false) {
            return;
        }

        selectedX = m.getX();
        selectedY = m.getY();
        
        int offset = 10;
        for (int i=0; i < mobileNodes.length; i++) {
            if (mobileNodes[i].inRegion(selectedX, selectedY, offset)) {
                Graphics g = getGraphics();
                g.setXORMode(bgColor);
                selectedNode = mobileNodes[i];
                scaledX = selectedX / magnification;
                scaledY = selectedY / magnification;
                selectedNode.drawPosition(g, selectedX, selectedY,
                                           scaledX, scaledY);
                g.dispose();
                break;
            }
            else {
                selectedNode = null;
            }
        }
    }

    public void mouseClicked(MouseEvent m) {}
    public void mouseReleased(MouseEvent m) {
        if ((nodesSet == false) || (selectedNode == null)) {
            return;
        }
        else {
            Graphics g = getGraphics();
            g.setXORMode(bgColor);
            scaledX = selectedX / magnification;
            scaledY = selectedY / magnification;
            selectedNode.erasePosition(g, selectedX, selectedY,
                                        scaledX, scaledY); 
            g.dispose();
        }
    }

    public void mouseMoved(MouseEvent m) {
        scaledX = m.getX() / magnification;
        scaledY = m.getY() / magnification;
        statusPanel.setCoordinates("X: " + scaledX + " Y: " + scaledY); 

        // Display a node's coordination while mouse move above it.
        if (nodesSet == false) {
            return;
        }

        statusPanel.setHelpMessage("Move above the Node to get its coordinates");

        selectedX = m.getX();
        selectedY = m.getY();

        int offset = 8;
        boolean isAboveNode = false;
        for (int i=0; i < mobileNodes.length; i++) {
            if (mobileNodes[i].inRegion(selectedX, selectedY, offset)) {
                String message = "Node" + i + " Position(" + mobileNodes[i].getNodeXCoord() + 
                                        "," + mobileNodes[i].getNodeYCoord() + ")";
                statusPanel.setHelpMessage(message);
                break;
            }
        }
    }

    public void mouseEntered(MouseEvent m) {}
    public void mouseExited(MouseEvent m) {
        statusPanel.setCoordinates("");
        statusPanel.setHelpMessage("");
    }

    public void mouseDragged(MouseEvent m) {}

    public int getMagnification() {
        return magnification;
    }
}
