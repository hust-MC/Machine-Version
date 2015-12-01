package com.machineversion.sub_option;

public class SystemSetting_devicePacket
{
	public static class General extends DevicePacketBuilt
	{
		General general;

		private General()
		{
		}

		public General getInstance()
		{
			if (general == null)
			{
				general = new General();
			}
			return general;
		}

		public static final int LENGTH = 160;

		/* input camera type CAMERA_Type */
		public int input;
		/* output display way 0:lcd; 1:net; 2:crt */
		public int output;
		/* fpga 获取图像数据位数 0：8bit; 1:16bits */
		public int bitType;
		/* 所使用的算法 */
		public int algorithm;
		/* fpga 控制曝光时间 0-65535 */
		public int expTime;

		public int inited;
		/* 触发模式选择 0->auto, 1->dsp, 2->outside */
		public int trigger;
		/* ccdc 获取图像数据横向起始位置 */
		public int horzStartPix;
		/* ccdc 获取图像数据纵向起始位置 */
		public int vertStartPix;
		/* ccdc 获取图像数据实际宽度 */
		public int inWidth;
		/* ccdc 获取图像数据实际高度 */
		public int inHeight;

		public int outWidth;
		public int outHeight;
	}

	public static class Sensor
	{
		private static Sensor sensor;

		private Sensor()
		{
		}

		public static Sensor getInstatce()
		{
			if (sensor == null)
			{
				sensor = new Sensor();
			}
			return sensor;
		}

		public int width_max;
		public int height_max;
		public int width_input;
		public int height_input;
		public int startPixel_height;
		public int startPixel_width;
		public int sensor_number;
		public int isColour;
		public int bitPixel;
	}

	public static class Mode
	{

		private static Mode mode;

		private Mode()
		{

		}
		public static Mode getInstance()
		{
			if (mode == null)
			{
				mode = new Mode();
			}
			return mode;
		}

		public int expoTime;
		public int trigger;
		public int algorithm;
		public int width_crt;
		public int height_crt;
		public int work_mode;
		public int bitType;
	}

	public static class Trigger extends DevicePacketBuilt
	{
		static Trigger trigger;

		private Trigger()
		{
		}

		public static Trigger getInstance()
		{
			if (trigger == null)
			{
				trigger = new Trigger();
			}
			return trigger;
		}

		public int trigDelay; // 0.1mm
		public int partDelay; // 0.1mm
		public int velocity;  // mm/s
		public int departWide;	// ms
		public int expLead;	// us
		public int checksum;
	}

	public static class AD9849 extends DevicePacketBuilt
	{
		static AD9849 ad9849;

		private AD9849()
		{
		}

		public static AD9849 getInstance()
		{
			if (ad9849 == null)
			{
				ad9849 = new AD9849();
			}
			return ad9849;
		}

		public int[] vga = new int[2];
		public int[] pxga = new int[4];
		public int[] hxdrv = new int[4];
		public int rgdrv;
		public int shp, shd;
		public int hpl, hnl;
		public int rgpl, rgnl;
	}

	public static class MT9V032 extends DevicePacketBuilt
	{
		static MT9V032 mt9v032;

		private MT9V032()
		{
		}
		public static MT9V032 getInstance()
		{
			if (mt9v032 == null)
			{
				mt9v032 = new MT9V032();
			}
			return mt9v032;
		}

		public int isAgc;
		public int isAec;
		public int agVal;
		public int aeVal;
	}

	public static class ISL12026 extends DevicePacketBuilt
	{
		static ISL12026 isl12026;

		private ISL12026()
		{

		}
		public static ISL12026 getInstatce()
		{
			if (isl12026 == null)
			{
				isl12026 = new ISL12026();
			}
			return isl12026;
		}

		public int[] time = new int[8];
		public int[] alarm0 = new int[8];
		public int[] alarm1 = new int[8];
	}

	public static class Net extends DevicePacketBuilt
	{
		static Net net;

		private Net()
		{
		}
		public static Net getInstance()
		{
			if (net == null)
			{
				net = new Net();
			}
			return net;
		}

		public short port;
		public int work_mode;	// 1,2 tcpip server and client; 3,4 udp
		public int[] ip_address = new int[4];
		public int[] remote_ip = new int[4];
		public int[] mac_address = new int[6];
		public int[] gateway = new int[4];
		public int[] ip_mask = new int[4];
		public int[] dns = new int[4];

		public int checksum;
	}

	public static class UART extends DevicePacketBuilt
	{
		static UART uart;

		private UART()
		{
		}
		public static UART getInstace()
		{
			if (uart == null)
			{
				uart = new UART();
			}
			return uart;
		}

		public int baudRate;
		public int work_mode;
		public int checksum;
	}

	public static class HECC extends DevicePacketBuilt
	{
		static HECC hecc;

		private HECC()
		{
		}
		public static HECC getInstance()
		{
			if (hecc == null)
			{
				hecc = new HECC();
			}
			return hecc;
		}

		public int baudRate;
		public int id;
		public int checksum;
	}

	public static class AT25040 extends DevicePacketBuilt
	{

		static AT25040 at25040;

		private AT25040()
		{
		}
		public static AT25040 getInstance()
		{
			if (at25040 == null)
			{
				at25040 = new AT25040();
			}
			return at25040;
		}

		public int version;
		public int[] macAddr = new int[6];
		public int[] ipAddr = new int[4];
		public int port;
	}

	public static class Parameters
	{
		private static Parameters parameters;

		private Parameters()
		{
		}
		public static Parameters getInstace()
		{
			if (parameters == null)
			{
				parameters = new Parameters();
				parameters.hecc = HECC.getInstance();
				parameters.mode = Mode.getInstance();
				parameters.net = Net.getInstance();
				parameters.sensor = Sensor.getInstatce();
				parameters.trigger = Trigger.getInstance();
				parameters.uart = UART.getInstace();
			}

			return parameters;
		}

		public Net net;
		public HECC hecc;
		public UART uart;
		public Sensor sensor;
		public Mode mode;
		public Trigger trigger;
	}
}

class DevicePacketBuilt
{
	public int[] buildData()
	{
		return null;
	}
}