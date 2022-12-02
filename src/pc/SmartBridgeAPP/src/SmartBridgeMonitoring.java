
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.time.Millisecond;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;

/**
 * Gui for the Second assignment for "IoT" course.
 * 
 * @author Nicola Montanari
 *
 */
public class SmartBridgeMonitoring extends JFrame{

    static TimeSeries ts = new TimeSeries("data");
	JLabel status;
	JLabel waterLevel;
	JLabel lights;
	double waterLevelValue = 0;
	final JPanel northDOWN;

	SmartBridgeMonitoring(){
		this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		this.setPreferredSize(new Dimension(800,800));
        this.setResizable(false);
        this.setTitle("SMART BRIDGE");
		
		final JPanel north = new JPanel();
        final JPanel center = new JPanel();
		final JPanel south = new JPanel();

		north.setPreferredSize(new Dimension(800, 100));
		south.setPreferredSize(new Dimension(800, 100));

		final JPanel northUP = new JPanel();
		this.northDOWN = new JPanel();

		northUP.setPreferredSize(new Dimension(800, 0));
		northDOWN.setPreferredSize(new Dimension(500, 50));
		northDOWN.setBackground(Color.BLACK);

		north.add(northUP, BorderLayout.NORTH);
		north.add(northDOWN, BorderLayout.SOUTH);

		this.status = new JLabel("STATUS: NORMAL");
		status.setFont(status.getFont().deriveFont(40.0f));
		status.setForeground(Color.BLACK);

		waterLevel = new JLabel("WATER LEVEL: 0");
		waterLevel.setFont(waterLevel.getFont().deriveFont(40.0f));
		waterLevel.setForeground(Color.BLACK);

		lights = new JLabel("SMART LIGHTS: OFF");
		lights.setFont(lights.getFont().deriveFont(20.0f));
		lights.setForeground(Color.WHITE);

		northDOWN.add(lights);

		north.add(status, SwingConstants.CENTER);
		south.add(waterLevel, SwingConstants.CENTER);

        center.setBorder(new TitledBorder(new EtchedBorder(), "PLOT"));

        // Setting Frame
		this.add(north, BorderLayout.NORTH);
        this.add(center, BorderLayout.CENTER);
		this.add(south, BorderLayout.SOUTH);
        this.pack();
        this.setLocationRelativeTo(null);
        this.setVisible(true);
	}

	void changeStatus(String status){
		this.status.setText("STATUS: "+status);
	}

	void changeWaterlevel(String value){
		this.waterLevel.setText("WATER LEVEL: "+value);
	}

	void changelights(boolean value){
		if(value){
			lights.setText("SMART LIGHTS: ON");
			lights.setForeground(Color.BLACK);
			northDOWN.setBackground(Color.GREEN);
		}else{
			lights.setText("SMART LIGHTS: OFF");
			lights.setForeground(Color.WHITE);
			northDOWN.setBackground(Color.BLACK);
		}
	}

	public static void main(String[] args) throws Exception {
		SerialCommChannel channel = new SerialCommChannel(args[0],9600);		
		/* attesa necessaria per fare in modo che Arduino completi il reboot */
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");		

		SmartBridgeMonitoring mainGUI = new SmartBridgeMonitoring();
		mainGUI.setVisible(true);

        TimeSeriesCollection dataset = new TimeSeriesCollection(ts);
        JFreeChart chart = ChartFactory.createTimeSeriesChart(
            "Water Monitoring",
            "Time",
            "Water Level",
            dataset,
            false,
            true,
            false
        );
        final XYPlot plot = chart.getXYPlot();
        ValueAxis axis = plot.getDomainAxis();
        axis.setAutoRange(true);
        axis.setFixedAutoRange(60000.0);
        ChartPanel label = new ChartPanel(chart);
        mainGUI.add(label, BorderLayout.CENTER);

		while (true){
			String msg = channel.receiveMsg();
			System.out.println(msg);

			switch (msg){
				case "State:Normal":
					mainGUI.changeStatus("NORMAL");
					break;
				case "State:PreAlarm":
					mainGUI.changeStatus("PREALARM");
					break;
				case "State:Alarm":
					mainGUI.changeStatus("ALARM");
					break;
				case "Smart Light:1":
					mainGUI.changelights(true);
					break;
				case "Smart Light:0":
					mainGUI.changelights(false);
					break;
				default:					
					break;
			}

			if(msg.split(":")[0].equals("WaterLevel")){
				mainGUI.waterLevelValue =  Integer.valueOf((msg.split(":")[1]).replaceAll("[^\\d]",""));
				mainGUI.changeWaterlevel(msg.split(":")[1]);
				ts.addOrUpdate(new Millisecond(), mainGUI.waterLevelValue/100);
			}
		}
	}
}
