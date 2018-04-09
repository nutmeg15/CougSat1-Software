package space.cougs.ground.gui;

import java.awt.Dimension;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import space.cougs.ground.CougSat1Telemetry;
import space.cougs.ground.utils.CustomColors;
import space.cougs.ground.utils.Fonts;

@SuppressWarnings("serial")
public class GUI extends JFrame {

	private CougSat1Panel cougSat1Panel = new CougSat1Panel();
	private JScrollPane cougSat1ScrollPane = new JScrollPane(cougSat1Panel, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
			JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
	private JTabbedPane jtp = new JTabbedPane();
	private JPanel homePanel = new JPanel();
	private JScrollPane homeScrollPane = new JScrollPane(homePanel, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
			JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

	public GUI() {
		super();

		try {
			UIManager.setLookAndFeel("javax.swing.plaf.metal.MetalLookAndFeel");
		} catch (ClassNotFoundException | InstantiationException | IllegalAccessException
				| UnsupportedLookAndFeelException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		jtp.setFont(Fonts.getInstance().monofonto[Fonts.getInstance().MEDIUM]);
		jtp.setBackground(CustomColors.WSU_GRAY);
		jtp.setPreferredSize(new Dimension(900, 700));
		jtp.setMinimumSize(new Dimension(200, 200));
		jtp.addTab("     Home      ", homeScrollPane);
		jtp.addTab("   CougSat-1   ", cougSat1ScrollPane);

		this.setIconImage(new ImageIcon("resources/images/rocket.png").getImage());
		this.setTitle("CiS Ground Control");
		this.add(jtp);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);// makes exit button work
		this.pack();//
		this.setMinimumSize(new Dimension(200, 200));
		this.setLocationRelativeTo(null);// centers the screen
		this.setVisible(true); // makes GUI visible to user / makes visible
		this.setResizable(true); // Disables the full screen mode
		this.setExtendedState(JFrame.MAXIMIZED_BOTH);

		jtp.setSelectedComponent(cougSat1ScrollPane);

	}

	public void updateData(CougSat1Telemetry data)
	{
		
		cougSat1Panel.upgdateData(data);
		this.repaint();
	}

}
