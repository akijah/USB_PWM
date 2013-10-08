package aki.interf;

import java.awt.*;
import java.awt.event.*;
import java.util.Random;

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;



public class WindPWM
{
	public static final int WIDTH=400;	
	public static final int HEIGHT=300;
	GrPan panel;
	SerialPWM ser;

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
		ser=new SerialPWM();
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
	
	public GrPan()
	{	super(true);
		setLayout(null);
		menuBar = new JMenuBar();
		menuBar.setBorder(new BevelBorder(BevelBorder.RAISED));
		JMenu menu = new JMenu("Menu");
	    menuBar.add(menu);

	    toolBar = new JToolBar();
	    toolBar.setBorder(new EtchedBorder());
	
	    SampleAction exampleAction = new SampleAction("Download",new ImageIcon("action.gif"));

// Finally, add the sample action to the menu and the toolbar.
// These methods are no longer preferred:
// menu.add(exampleAction);
// toolBar.add(exampleAction);
	    
	    JMenuItem exampleItem = new JMenuItem(exampleAction);
	    JButton exampleButton = new JButton(exampleAction);
	    menu.add(exampleItem);
	    toolBar.add(exampleButton);
	    
		setBackground(Color.LIGHT_GRAY);
		setBorder(BorderFactory.createEmptyBorder(12, 8, 12, 8));
		/*JButton yB=new JButton("Pusk");
		//yB.setBounds(10, 10, 100, 30);
		//yB.setLocation(10,10);
		add(yB);
		
		JCheckBox cb=new JCheckBox("Asd"); 
		add(cb);
		
		JFormattedTextField ftf=new JFormattedTextField("asddd");
		add(ftf);
		
		
		JLabel ll=new JLabel("куку");
		//ll.setCursor(Cursor.HAND_CURSOR);
		ll.setBounds(10, 10, 100, 40);
		add(ll);*/
	
		
		
		SlPWM1=new JSlider(JSlider.HORIZONTAL,0,100,0);
		SlPWM1.setMinorTickSpacing(10);
		SlPWM1.setMajorTickSpacing(5);
		SlPWM1.setPaintTicks(true);
		SlPWM1.setPaintLabels(true);
		SlPWM1.setLabelTable(SlPWM1.createStandardLabels(10));
		SlPWM1.setBounds(10, 10, 200, 60);
		SlPWM1.setBorder(BorderFactory.createCompoundBorder());
		SlPWM1.addChangeListener(this);
        add(SlPWM1);//, BorderLayout.CENTER
        
        SlPWM2=new JSlider(JSlider.HORIZONTAL,0,100,0);
		SlPWM2.setMinorTickSpacing(10);
		SlPWM2.setMajorTickSpacing(5);
		SlPWM2.setPaintTicks(true);
		SlPWM2.setPaintLabels(true);
		SlPWM2.setLabelTable(SlPWM1.createStandardLabels(10));
		SlPWM2.setBounds(10, 80, 200, 60);
		SlPWM2.addChangeListener(this);
        add(SlPWM2);
        
        
        PWMVal1=new JLabel();
        PWMVal1.setBounds(220, 10, 100, 60);
        
        PWMVal1.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        PWMVal1.setHorizontalAlignment(SwingConstants.CENTER);
        add(PWMVal1);
	
        PWMVal2=new JLabel();
        PWMVal2.setBounds(220, 80, 100, 60);
        
        PWMVal2.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        PWMVal2.setHorizontalAlignment(SwingConstants.CENTER);
        add(PWMVal2);
        
        
        SlPWM1.setValue(50);
        SlPWM2.setValue(50);
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
	 {
		    int val = 100 - Integer.parseInt(ae.getActionCommand());
		    System.out.println(val);
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
{
    // This is our sample action. It must have an actionPerformed() method,
    // which is called when the action should be invoked.
    public SampleAction(String text, Icon icon) {
      super(text,icon);
    }

    public void actionPerformed(ActionEvent e) {
      System.out.println("Action [" + e.getActionCommand() + "] performed!");
    }
}