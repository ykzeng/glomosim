import java.awt.*;
import java.util.*;

import javax.swing.*;

public class GlomoMobileNode {
    private int nodeId;
    private Color nodeColor;
    private Color linkColor;
    private Color connectionColor;
    private Point coord;
    private int range;
    private boolean showTxRangeOption, showNodeConnectionsOption;
    private Vector connectionVec;
    private GlomoCanvas gCanvas;
    private int m;
    //private String nodeName;
    //private double batteryPower=0;

    public GlomoMobileNode(int id, int x, int y, int tr, GlomoCanvas canvas,
                           Color nc, Color cc, boolean stro, boolean snco) {
        nodeId = id;
        coord = new Point(x, y);
        range = tr;
        nodeColor = nc;
        connectionColor = cc;
        showTxRangeOption = stro;
        showNodeConnectionsOption = snco;
        connectionVec = new Vector();
        gCanvas = canvas;
    }

    public boolean inRegion(int x, int y, int offset) { 
        m = gCanvas.getMagnification();
        if ((m*coord.x >= (x - offset)) && (m*coord.x <= (x + offset)) &&
             (m*coord.y >= (y - offset)) && (m*coord.y <= (y + offset))) {
            return true;
        }
        else {
            return false;
        }
    }

    public void drawAllConnections(Graphics g) {
        GlomoMobileNode otherNode;

        if (showNodeConnectionsOption == false) {
            return;
        }

        for (int i=0; i < connectionVec.size(); i++) {
            otherNode = (GlomoMobileNode) connectionVec.elementAt(i);
            if (nodeId == otherNode.getId()) {
                System.err.println("Error! Node cannot be linked to itself!");
                System.exit(1);
            }
            drawLink(otherNode, connectionColor, g);
        }
    }

    public void drawHigherIdConnections(Graphics g) {
        GlomoMobileNode otherNode;

        if (showNodeConnectionsOption == false) {
            return;
        }

        for (int i=0; i < connectionVec.size(); i++) {
            otherNode = (GlomoMobileNode) connectionVec.elementAt(i);
            if (nodeId == otherNode.getId()) {
                System.err.println("Error! Node cannot be linked to itself!");
                System.exit(1);
            }
            if (nodeId < otherNode.getId()) {
                drawLink(otherNode, connectionColor, g);
            }
        }
    }

    // For xor mode, erase the connections by redrawing them over themselves
    public void eraseAllConnections(Graphics g) {
        if (showNodeConnectionsOption == false) {
            return;
        }

        drawAllConnections(g);
    }

    public void createInitialConnections(GlomoMobileNode mobileNodes[]) {
        m = gCanvas.getMagnification();
        connectionVec.removeAllElements();
        for (int i=0; i< mobileNodes.length; i++) {
            if (this == mobileNodes[i]) {
                continue;
            }
            if (inRegion(mobileNodes[i].getXCoord(), mobileNodes[i].getYCoord(),
                         m*range) == true) {
                connectionVec.addElement(mobileNodes[i]);
            }
        }
    }

    public void updateConnections(GlomoMobileNode mobileNodes[]) {
        boolean b;
        connectionVec.removeAllElements();
        for (int i=0; i < mobileNodes.length; i++) {
            if (this == mobileNodes[i]) {
                continue;
            }
            b = inRegion(mobileNodes[i].getXCoord(), mobileNodes[i].getYCoord(),
                         m*range);
            if (b == true) {
                connectionVec.addElement(mobileNodes[i]);
            }
            mobileNodes[i].updateTheirConnection(this, b);
        }
    }

    private void updateTheirConnection(GlomoMobileNode node, boolean b) {
        if (b == false) {
            connectionVec.removeElement(node);
        }
        else if (b == true) {
            if (connectionVec.contains(node) == false) {
                connectionVec.addElement(node);
            }
        }
    }

    public void drawPosition(Graphics g, int x, int y,
                              int scaledX, int scaledY) {
        g.setXORMode(gCanvas.getBackgroundColor());
        g.setColor(nodeColor);
        g.drawString("(" + String.valueOf(scaledX) + ","
                      + String.valueOf(scaledY) + ")", x, y);
    }

    // For xor mode, erase the pos by drawing over it again (using same color)
    public void erasePosition(Graphics g, int x, int y,
                               int scaledX, int scaledY) {
        drawPosition(g, x, y, scaledX, scaledY);
    }

    public void drawName(Graphics g, int x, int y) {
        g.setXORMode(gCanvas.getBackgroundColor());
        g.setColor(nodeColor);
        g.drawString(String.valueOf(nodeId), x, y);
    }

    // For xor mode, erase the name by drawing over it again (using same color)
    public void eraseName(Graphics g, int x, int y) {
        drawName(g, x, y);
    }

    public void drawNode(Graphics g) {
        m = gCanvas.getMagnification();
        g.setXORMode(gCanvas.getBackgroundColor());
        g.setColor(nodeColor.brighter());
        g.fillOval(m*coord.x-1, m*coord.y-1,2,2);
        g.setColor(nodeColor);
        g.drawString(String.valueOf(nodeId), m*coord.x, m*coord.y);
        if (showTxRangeOption == true) {
            g.drawOval(m*coord.x - m*range, m*coord.y - m*range, m*2*range, m*2*range);
        }
    }

    // For xor mode, erase the node by drawing over it again (using same color)
    public void eraseNode(Graphics g, int numIterations) {
        drawNode(g);
        busyWait(numIterations);
    }

    public void drawLink(GlomoMobileNode dest, Color lc, Graphics g) {
        m = gCanvas.getMagnification();
        linkColor = lc;
        g.setXORMode(gCanvas.getBackgroundColor());
        g.setColor(linkColor);
        g.drawLine(m*coord.x, m*coord.y, dest.getXCoord(), dest.getYCoord());
    }

    // For xor mode, erase the line by drawing over it again (using same color)
    public void eraseLink(GlomoMobileNode dest, Graphics g) {
        drawLink(dest, this.linkColor, g);
    }

    public void drawLine(GlomoMobileNode dest, Color txColor, Graphics g,
                          int numIterations) {
        m = gCanvas.getMagnification();
        g.setXORMode(gCanvas.getBackgroundColor());
        g.setColor(txColor);
        g.drawLine(m*coord.x, m*coord.y, dest.getXCoord(), dest.getYCoord());
        busyWait(numIterations);
        g.drawLine(m*coord.x, m*coord.y, dest.getXCoord(), dest.getYCoord());
    }

    public void drawThickLine(GlomoMobileNode dest, int thickness,
                               Color txColor, Graphics g, int numIterations) {
        m = gCanvas.getMagnification();

        g.setXORMode(gCanvas.getBackgroundColor());
        g.setColor(txColor);

        for (int i=0; i < thickness; i++) {
            g.drawLine((m*coord.x), (m*coord.y)+i, dest.getXCoord(), dest.getYCoord()+i);
        }

        busyWait(numIterations);

        for (int i=0; i < thickness; i++) {
            g.drawLine((m*coord.x), (m*coord.y)+i, dest.getXCoord(), dest.getYCoord()+i);
        }
    }

    public void drawBroadcast(Graphics g, Color txColor, int numIterations) {
        m = gCanvas.getMagnification();
        g.setXORMode(gCanvas.getBackgroundColor());
        g.setColor(txColor);

        g.drawOval((m*coord.x)-(m*range)/3, (m*coord.y)-(m*range)/3, (m*2*range)/3,(m*2*range)/3);
        busyWait(numIterations);
        g.drawOval((m*coord.x)-(m*range)/3, (m*coord.y)-(m*range)/3, (m*2*range)/3,(m*2*range)/3);

        g.drawOval((m*coord.x)-(m*2*range)/3,(m*coord.y)-(m*2*range)/3, (m*4*range)/3,(m*4*range)/3);
        busyWait(numIterations);
        g.drawOval((m*coord.x)-(m*2*range)/3,(m*coord.y)-(m*2*range)/3, (m*4*range)/3,(m*4*range)/3);

        g.drawOval((m*coord.x) - (m*range), (m*coord.y) - (m*range), (m*2*range), (m*2*range));
        busyWait(numIterations);
        g.drawOval((m*coord.x) - (m*range), (m*coord.y) - (m*range), (m*2*range), (m*2*range));
    }

    public void setLocation(Point p) {
        coord.setLocation(p);
    }

    private void busyWait(int numIterations) {
        try{
            Thread.sleep(numIterations);
        }catch (InterruptedException e){}
    }

    public int getId() {
        return nodeId;
    }

    private int getXCoord() {
        m = gCanvas.getMagnification();
        return m*coord.x;
    }

    private int getYCoord() {
        m = gCanvas.getMagnification();
        return m*coord.y;
    }

    public int getNodeXCoord() {
        return coord.x;
    }

    public int getNodeYCoord() {
        return coord.y;
    }
}

