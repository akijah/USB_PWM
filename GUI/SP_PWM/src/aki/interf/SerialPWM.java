/**
 * 
 */
package aki.interf;

/**
 * @author A_Kozlov
 *
 */

import jssc.*;
//import jssc.SerialPortException;
//------------------------------------------------------------------------------------------
public class SerialPWM 
{
	private String[] portNames;
	static SerialPort serialPort;
	 byte[] buffer;
	private boolean isOpen; 
	
	public SerialPWM()
	{	portNames = SerialPortList.getPortNames();
    	//for(int i = 0; i < portNames.length; i++)
    	//System.out.println((i+1)+" "+portNames[i]);
		isOpen=false;
    	
    	
	}
//----------------------------------------------------------------------------------------
	public boolean OpenPort(String Name)
	{	if(isOpen) return false;
		serialPort=new SerialPort(Name);
		try {
				serialPort.openPort();//Open serial port
				serialPort.setParams(SerialPort.BAUDRATE_9600, 
                             SerialPort.DATABITS_8,
                             SerialPort.STOPBITS_1,
                             SerialPort.PARITY_NONE);//Set params. Also you can set params by this string: serialPort.setParams(9600, 8, 1, 0);
				int mask = SerialPort.MASK_RXCHAR + SerialPort.MASK_CTS + SerialPort.MASK_DSR;//Prepare mask
				serialPort.setEventsMask(mask);//Set mask
				serialPort.addEventListener(new SerialPortReader());//Add SerialPortEventListener
				isOpen=true;
        
            }
		catch (SerialPortException ex) 
		{
			System.out.println(ex);
			isOpen=false;
		}
		return isOpen;
	}	
//---------------------------------------------------------------------------------------	
	public boolean IsOpen(){return isOpen;}
//---------------------------------------------------------------------------------------	
	public String[] getPorts()	{ return portNames;	}	
//----------------------------------------------------------------------------------------	
	public boolean WriteB(byte K)
	{	if(!isOpen) return false;
		try {
			  serialPort.writeByte(K);
			  return true;
			}
			catch (SerialPortException ex) 
			{        System.out.println(ex);
					 return false;
			}
		
	}
//--------------------------------------------------------------------------------------	
	public int ReadB()
	{	if(!isOpen) return 0;
		try {
				buffer=serialPort.readBytes(10);
				return buffer.length; 
			}
			catch (SerialPortException ex) 
			{        System.out.println(ex);
					 return 0;
			}
		
	}
//--------------------------------------------------------------------------------------	
	public boolean ClosePort()
	{   if(!isOpen) return false;
		try 
		{
		 serialPort.closePort();//Close serial port
		
		}
		catch (SerialPortException ex) 
		{        System.out.println(ex);
				 return false;
		}
		serialPort=null;
		isOpen=false;
		return true;
		
	}
	
//--------------------------------------------------------------------------------------	
	
	
	
	
	 static class SerialPortReader implements SerialPortEventListener {

	        public void serialEvent(SerialPortEvent event) {
	            if(event.isRXCHAR()){//If data is available
	                if(event.getEventValue() == 10){//Check bytes count in the input buffer
	                    //Read data, if 10 bytes available 
	                    try {
	                        byte buffer[] = serialPort.readBytes(10);
	                        for(int s=0; s<buffer.length; s++) System.out.println(buffer[s]);
	                    }
	                    catch (SerialPortException ex) {
	                        System.out.println(ex);
	                    }
	                }
	            }
	            else if(event.isCTS()){//If CTS line has changed state
	                if(event.getEventValue() == 1){//If line is ON
	                    System.out.println("CTS - ON");
	                }
	                else {
	                    System.out.println("CTS - OFF");
	                }
	            }
	            else if(event.isDSR()){///If DSR line has changed state
	                if(event.getEventValue() == 1){//If line is ON
	                    System.out.println("DSR - ON");
	                }
	                else {
	                    System.out.println("DSR - OFF");
	                }
	            }
	        }
	    }
	
	
	
	/**
	 * @param args
	 */
	
	
	
	
	
	public static void main(String[] args)
	{
		// TODO Auto-generated method stub
		SerialPWM ser=new SerialPWM();
		
		for(int i=0;i<25;i++)System.out.println("Write Byte: " +ser.WriteB((byte)i));
		//System.out.println("Read Byte: " +ser.ReadB());
		
		System.out.println("Port closed: " +ser.ClosePort());
		 
       // try {
       //     System.out.println("Port opened: " + serialPort.openPort());
       //     System.out.println("Params setted: " + serialPort.setParams(9600, 8, 1, 0));
       //     System.out.println("\"Hello World!!!\" successfully writen to port: " + serialPort.writeBytes("Hello World!!!".getBytes()));
       //     System.out.println("Port closed: " + serialPort.closePort());
       // }
       // catch (SerialPortException ex){
       //     System.out.println(ex);	
       // }

	}
}