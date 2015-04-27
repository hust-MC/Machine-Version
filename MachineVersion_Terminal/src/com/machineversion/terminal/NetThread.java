package com.machineversion.terminal;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class NetThread extends Thread implements CommunicationInterface
{
	final int timeout = 5000;
	final String ip = "192.168.137.251";
	final int port = 6666;			
	final int CameraMode = 1;			//CameraMode为1表示后摄像头，0表示前摄像头

	Socket socket;
	Handler handler;

	final int width = 1500;
	final int height = 100;
	final int quality = 50;

	public NetThread(Handler netHandler)
	{
		if (ip.isEmpty() || (port <= 0 || port >= 65536))
		{
			Log.d("MC", "PORT error");
		}
		handler = netHandler;
	}

	private void receivePic()
	{
		Runnable r = new Runnable()
		{
			@Override
			public void run()
			{
				try
				{
					InputStream is = socket.getInputStream();
					while (true)								// 循环接收相机发来的数据
					{
						Object[] rets = DataPack.recvDataPack(is);

						if (rets != null) 						// 如果数据正常，表示网络通畅
						{
							Integer OperationCode = (Integer) rets[1];

							switch (OperationCode)
							// 判断指令码
							{
							case 0:								// 请求保存数据
								// String mDirPath = "/savePic";
								// String Path = Environment
								// .getExternalStorageDirectory()
								// + mDirPath;
								// String savePath = savetoPic(data, Path);
								//
								// message.obj = savePath;
								// handler.sendMessage(message);
								break;
							case 1:								// 显示图片
								Message message = Message.obtain();
								message.obj = rets;
								handler.sendMessage(message);
								break;
							default:
								break;
							}
						}
						else
						// 接收的数据不正常，表示网络故障
						// Close
						{
							try
							{
								if (socket != null)
								{
									socket.close();
									socket = null;
								}
							} catch (Exception e)
							{
								Log.d("MC", "break");
							}
							break;
						}
					}
				} catch (Exception e)
				{
				} finally
				{
					Message message = Message.obtain();
					message.obj = null;
					handler.sendMessage(message);
				}
			}
		};

		if (MainActivity.netFlag)							// netFlag为true表示连接成功，启动进程接收图片
		{
			Thread t = new Thread(r);
			t.start();
		}
		else
		// netFlag为false表示连接失败，通知主线程显示失败信息提示
		{
			Message message = Message.obtain();
			message.what = 0x55;	    		// what 为0x55表示连接失败
			handler.sendMessage(message);
		}
	}

	@Override
	public void run()
	{
		try
		{
			socket = new Socket();
			SocketAddress sa = new InetSocketAddress(ip, port);
			socket.connect(sa, timeout);
			MainActivity.netFlag = true;										// 切换网络标志
			OutputStream os = socket.getOutputStream();
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			DataOutputStream dos = new DataOutputStream(baos);
			dos.writeInt(CameraMode);
			dos.writeInt(width);
			dos.writeInt(height);
			dos.writeInt(quality);
			DataPack.sendDataPack(baos.toByteArray(), os, -1);

		} catch (Exception e)
		{
			MainActivity.netFlag = false;
		} finally
		{
			MainActivity.dialog.dismiss();
			receivePic();
		}
	}

	@Override
	public void open()
	{
		this.start();
	}

	@Override
	public void send(byte[] data, int cmd)
	{
		OutputStream os;
		try
		{
			os = socket.getOutputStream();
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			DataOutputStream dos = new DataOutputStream(baos);
			dos.write(data);
			DataPack.sendDataPack(baos.toByteArray(), os, -1);
		} catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	@Override
	public void close()
	{
		
	}
}
