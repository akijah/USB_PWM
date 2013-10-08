package aki.interf;

import java.awt.*;
import java.awt.event.*;
import java.util.Random;

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;



public class WindPWM
{
	public static final int WIDTH=260;	
	public static final int HEIGHT=300;
	GrPan panel;
	

	public WindPWM()
	{
		// TODO Auto-generated constructor stub
		JFrame frame=new JFrame();
		frame.setSize(WIDTH,HEIGHT);
		//frame.setExtendedState(Frame.MAXIMIZED_BOTH);
		frame.setTitle("Serial PWM v.1.01");
		frame.setResizable(false);
		//frame.setUndecorated(true); //Для отображения окна без рамки и заголовка
		//frame.setLocationRelativeTo(null);//по центру
		frame.setLocationByPlatform(true); //самостоятельно выбираетя место
		//frame.setIconImage(img);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);	
		
		panel=new GrPan();
		frame.setJMenuBar(panel.menuBar);
		frame.getContentPane().add(panel.toolBar, BorderLayout.NORTH);
		
		frame.add(panel);
		
		frame.setVisible(true);
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		WindPWM wp=new WindPWM();
		
		
		
	}

}

//------------------------------------------------------------------------------------------
class GrPan extends JPanel implements ChangeListener, ActionListener 
{	public JMenuBar menuBar;
	public JToolBar toolBar;
	JSlider SlPWM1,SlPWM2;
	JLabel	PWMVal1,PWMVal2;
	SerialPWM ser;
	 JComboBox<String> PortSelect;
	 JButton ConnectBut;
	 JButton BM100,BM10,BDef,BP100,BP10;
	public GrPan()
	{	super(true);
		
		ser=new SerialPWM();
	
		setLayout(null);
		
		menuBar = new JMenuBar();
		menuBar.setBorder(new BevelBorder(BevelBorder.RAISED));
		JMenu menu = new JMenu("File");
	    menuBar.add(menu);

	    toolBar = new JToolBar();
	    toolBar.setBorder(new EtchedBorder());
	
	    SampleAction exampleAction = new SampleAction("Connect",null,this);//new ImageIcon("action.gif")

// Finally, add the sample action to the menu and the toolbar.
// These methods are no longer preferred:
// menu.add(exampleAction);
// toolBar.add(exampleAction);
	    
	    JMenuItem exampleItem = new JMenuItem(exampleAction);
	    menu.add(exampleItem);
	    
	    ConnectBut = new JButton(exampleAction);
	    
	    PortSelect=new JComboBox<String> (ser.getPorts());
	   // PortSelect.setSize(100, 60);
	    toolBar.add(PortSelect);
	    toolBar.add(ConnectBut);
	    
		setBackground(Color.LIGHT_GRAY);
		setBorder(BorderFactory.createEmptyBorder(12, 12, 12,12));
	//----------------------------------------------------------------	
		JLabel PWMCap1=new JLabel("PWM Canal 1");
        PWMCap1.setBounds(5, 2, 140, 30);
        PWMCap1.setFont(new Font("Arial",Font.BOLD,15));
        add(PWMCap1);
        
		SlPWM1=new JSlider(JSlider.HORIZONTAL,0,100,0);
		SlPWM1.setMinorTickSpacing(2);
		SlPWM1.setMajorTickSpacing(10);
		SlPWM1.setPaintTicks(true);
		//SlPWM1.setPaintLabels(false);
		//SlPWM1.setLabelTable(SlPWM1.createStandardLabels(10));
		SlPWM1.setBounds(2, 34, 250, 30);
		SlPWM1.setBorder(BorderFactory.createCompoundBorder());
		SlPWM1.addChangeListener(this);
        add(SlPWM1);//, BorderLayout.CENTER
        
        PWMVal1=new JLabel();
        PWMVal1.setBounds(150, 2, 100, 30);
        
        PWMVal1.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        PWMVal1.setHorizontalAlignment(SwingConstants.CENTER);
        add(PWMVal1);
	
        BM100=new JButton("<<");
        BM100.setBounds(2,66, 48, 30);
        BM100.addActionListener(this);
        add(BM100);
       
        BM10=new JButton("<");
        BM10.setBounds(52,66, 48, 30);
        BM10.addActionListener(this);
        add(BM10);
        BDef=new JButton("D");
        BDef.setBounds(102,66, 48, 30);
        BDef.addActionListener(this);
        add(BDef);
        BP10=new JButton(">");
        BP10.setBounds(152,66, 48, 30);
        BP10.addActionListener(this);
        add(BP10);
        BP100=new JButton(">>");
        BP100.setBounds(202,66, 48, 30);
        BP100.addActionListener(this);
        add(BP100);
        
        
     //----------------------------------------------------------------   
       /* SlPWM2=new JSlider(JSlider.HORIZONTAL,0,100,0);
		SlPWM2.setMinorTickSpacing(2);
		SlPWM2.setMajorTickSpacing(10);
		SlPWM2.setPaintTicks(true);
		//SlPWM2.setPaintLabels(false);
		//SlPWM2.setLabelTable(SlPWM1.createStandardLabels(10));
		SlPWM2.setBounds(2, 62, 250, 30);
		SlPWM2.addChangeListener(this);
        add(SlPWM2);
        
        
        
        PWMVal2=new JLabel();
        PWMVal2.setBounds(220, 80, 100, 60);
        
        PWMVal2.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        PWMVal2.setHorizontalAlignment(SwingConstants.CENTER);
        add(PWMVal2);*/
        
        
        SlPWM1.setValue(50);
       // SlPWM2.setValue(50);
        //ll.setCursor(Cursor.HAND_CURSOR);
		//ll.setBounds(10, 10, 100, 40);
		//add(sl);
	
	}
	 public void stateChanged(ChangeEvent ce)
	 {	 int Val; 	
		 if(ce.getSource()==SlPWM1)	
		 {Val=SlPWM1.getValue()*10+1000;
		  System.out.println("Sl1:"+Val);
		  PWMVal1.setText(Val+" ms");
		  ser.WriteB((byte)SlPWM1.getValue());
		 }
		 if(ce.getSource()==SlPWM2)	
		 {	Val=SlPWM2.getValue()*10+1000;
		    System.out.println("Sl2:"+Val);
		    PWMVal2.setText(Val+" ms");
		 }
		
		 //getColorSelectionModel().setSelectedColor(grays[scale.getValue()]);
		    //label.setText("" + (100-(int)Math.round(scale.getValue() / 2.55)));
	 }	
	 
	 public void actionPerformed(ActionEvent ae)
	 {	 int V=SlPWM1.getValue();
		 
	 	 if(ae.getSource()==BM100) 	V-=10;
		 	
		 if(ae.getSource()==BM10) 	V--;
		 	
		 if(ae.getSource()==BDef)	V=50;  
		 	
		 if(ae.getSource()==BP10)   V++;
		
		 if(ae.getSource()==BP100)	V+=10;
		 
		 SlPWM1.setValue(V);
		 
		 
		 
		 
		 
		 
		 
		 //int val = 100 - Integer.parseInt(ae.getActionCommand());
		    //System.out.println(val);
		    // getColorSelectionModel().setSelectedColor(grays[(int)(val * 2.55)]);
	 }
	/*public void paintComponent(Graphics g)
	{ super.paintComponent(g);
	   for(int i=0;i<GrMas.length;i++)
	   { GrMas[i].paintComponent(g);
	   
	   }
	}*/

}
//--------------------------------------------------------------------------------




//--------------------------------------------------------------------------------
class SampleAction extends AbstractAction 
{	GrPan P;
    // This is our sample action. It must have an actionPerformed() method,
    // which is called when the action should be invoked.
    public SampleAction(String text, Icon icon,GrPan k) {
      super(text,icon);
      P=k;
    }

    public void actionPerformed(ActionEvent e)
    {
    	 System.out.println(P.PortSelect.getSelectedItem());
		 	if(!P.ser.IsOpen())
	 		{	if(P.ser.OpenPort((String)P.PortSelect.getSelectedItem()))P.ConnectBut.setText("Disconnect");
	 			
	 		}
	 		else
	 		{	if(P.ser.ClosePort())P.ConnectBut.setText("Connect");
	 			
	 		}
    	
    	
    	System.out.println("Action [" + e.getActionCommand() + "] performed!");
    }
}