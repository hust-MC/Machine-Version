#pragma once

#define Uint8	UINT8
#define Uint16	UINT16
#define NET_FRAME_MAGIC		0x695a695a

/*---------------------------------------------------------------------
	image type define
-----------------------------------------------------------------------
*/
typedef enum _PIC_TYPE
{
	PIC_TYPE_YUV422 = 1,	
	PIC_TYPE_RAW8,
	PIC_TYPE_RGB24
}
PIC_TYPE;

/*---------------------------------------------------------------------
	message source ID
-----------------------------------------------------------------------
*/
typedef enum _Net_Type_Msg
{
	MSG_NET_GET_VIDEO = 1,  // VIDEO
	MSG_NET_GENERAL,		// GENERAL
	MSG_NET_OV7620,			// OV7620
	MSG_NET_MT9V032,		// MT9V032
	MSG_NET_FPGA,			// FPGA
	MSG_NET_ISL12026,		// ISL12026
	MSG_NET_AD9849,			// AD9849
	MSG_NET_AT25040,		// AT25040
	MSG_NET_TEXTINFO,		// get text info
	MSG_NET_LINKINFO,		// get link info
	MSG_NET_NORMAL,			// delete all alg
	MSG_NET_FLASH,			// nand flash
	MSG_NET_TEST,			// just for test
	MSG_NET_STATE,			// get temperature etc. data
	MSG_NET_SEND_IMAGE,		// send image to DSP for algorithm
	MSG_NET_GET_RAW,		// get raw image data
	MSG_NET_UARTHECC,		// set uart and can
	MSG_NET_CONFSAVE,		// save config param
	MSG_NET_SETNET,			// set net param
	MSG_NET_FACTRESET,
	MSG_NET_GET_PARAM,		// get new param
	MSG_NET_SAVE_VIDEO,		// save image from dsp
	MSG_NET_TRIGGER,		// set trigger param
	MSG_NET_DSPTRIG,		// trigger for getting image
	MSG_NET_HELP_ALG_CMD,	// to get all available alg cmd
	MSG_NET_ALGRESULT = 200,	// to make a different message getting result from alg
}
NET_TYPE_Msg;

typedef enum _Net_User_Msg
{
	MSG_NET_HAAR = 100,			// haar detect
	MSG_NET_FACEDET,		// face detect
	MSG_NET_MOIRE,			// moire detect
}
NET_USER_Msg;

/*---------------------------------------------------------------------
	uart message
----------------------------------------------------------------------*/
#define MSG_UART_GET_PARAM			0x29E1

#define MSG_UART_SET_NET			0x50F9
#define MSG_UART_SET_UARTHECC		0x63F1
#define MSG_UART_SET_WORKMODE		0x4CF8
#define MSG_UART_SET_AD9849			0x72FA
#define MSG_UART_SET_ALG			0x37F5
#define MSG_UART_RESTORE			0x7ACA

#define MSG_UART_SET_TIME			0x4DF4
/*---------------------------------------------------------------------
	camera type define
-----------------------------------------------------------------------
*/
typedef enum _Camera_Type
{
	// ����CCD
	CAMERA_TYPE_ICX414AL = 1,
	CAMERA_TYPE_ICX424AL,
	CAMERA_TYPE_ICX424AQ,
	CAMERA_TYPE_ICX415AL,
	CAMERA_TYPE_ICX285AL,
	// ����CCD
	CAMERA_TYPE_RL1024 = 50,
	// ����CMOS
	CAMERA_TYPE_MT9V032M = 60,
	CAMERA_TYPE_MT9V032C,
	CAMERA_TYPE_OV7620,
	// ����
	CAMERA_TYPE_SA7111 = 100,

	// ��׼��ʽ
	CAMERA_TYPE_PAL = 200,
	CAMERA_TYPE_NTSC
}
CAMERA_Type;

/*---------------------------------------------------------------------
	link type define
-----------------------------------------------------------------------
*/
enum _Source_Msg
{
	MSG_KEY_ID = 1,			// ����
	MSG_UART_ID,			// ����			
	MSG_NET_ID,				// ����
	MSG_SPI_ID,				// SPI
	MSG_TOUCH_ID			// ������
};

/*---------------------------------------------------------------------
	algorithm id
-----------------------------------------------------------------------
*/
enum _ALGORITHM_TYPE
{
    ALG_NORMAL  = 0,       	// no use any alg
    ALG_FACEDET,      		// run face detect
    ALG_MOIRE,				// run moire center detect
	ALG_HAAR,				// run haar detect
	//add here
	ALG_FACE_NET,
	//DO NOT change ALG_OTHER, keep it ending
    ALG_OTHER         		// other undefined
};

/*---------------------------------------------------------------------
    _FaceRect <> FaceRect

    for record result face rects
-----------------------------------------------------------------------
*/
typedef struct _FaceRect
{
    int x;
    int y;
    int width;
    int height;
}
FaceRect;

/*---------------------------------------------------------------------
    CCD ��Ϣ�ṹ��

    color:  add by wei 2012.4.15
        0:  not color
        1:  color

	�޸����ɼ���С��ʵ�ʲɼ���С by wei 2012.11.13
-----------------------------------------------------------------------
*/
typedef struct _CAMERA_TYPE_INFO
{
	char*		ccdName;
	int			ccdId;			// CCD ���� ID
	int			maxWidth;		// �����ʾ���
	int			maxHeight;		// �����ʾ�߶�
	int			horzStartPix;	// ������ʼ����
	int			vertStartPix;	// ������ʼ����
	int			inWidth;		// ʵ�ʲɼ����
	int			inHeight;		// ʵ�ʲɼ��߶�
	int			pitch;			// �����������
	int			bitPerPix;		// ������Чλ��
	int			isColor;		// �Ƿ�Ϊ��ɫ
}
CAMERA_TypeInfo;

/*---------------------------------------------------------------------
    _NET_FRAME_INFO <> NET_FrameInfo <> pNET_FrameInfo

    network frame information struct
-----------------------------------------------------------------------
*/
typedef struct _NET_FRAME_INFO
{
	CAMERA_Type	ccdtype;	// ����ͷ����
	int			width;		// ����ͼ����
	int			height;		// ����ͼ��߶�
	int			size;		// ��������
	char		bitPerPix;	// ÿ����ռ�õ�λ��
	PIC_TYPE	pictype;	// ͼ���ʽ
}
NET_FrameInfo,* pNET_FrameInfo;

/*---------------------------------------------------------------------
    _IMG_INFO <> IMG_Info <> pIMG_Info

    global image information struct
-----------------------------------------------------------------------
*/
typedef struct _IMG_INFO 
{
	PIC_TYPE	pictype;	// ����ͼ���ʽ
	CAMERA_Type ccdtype;	// CCD�ͺ�
	int			picWidth;	// ͼ���ȣ�Pixel��
	int			picHeight;	// ͼ��߶ȣ�Pixel��
	int			picSize;	// ͼ���С
	int			disWidth;	// ��ʾ���
	int			disHeight;	// ��ʾ�߶�
	int			disX;		// ͼ����ʾY����
	int			disY;		// ͼ����ʾX����
	int			bitPerPix;	// ����λ��
	int			bytePerPix;	// ÿ����ռ�õ��ֽ���
	int			disType;	// ͼ����ʾ���� 0��8λ�Ҷȣ�1:24λ���
	int			adjustPix;	// Raw��ɫͼ��У��
	int			adjr;		// ��ɫ R ��������ֵ
	int			adjg;		// ��ɫ G ��������ֵ
	int			adjb;		// ��ɫ B ��������ֵ
}
IMG_Info,*pIMG_Info;

/*---------------------------------------------------------------------
    ���緢�Ϳ���ָ���
-----------------------------------------------------------------------
*/
#define  MT9V032_CTRL_CID_AUTOGAIN          0x00000001
#define  MT9V032_CTRL_CID_GAIN              0x00000002
#define  MT9V032_CTRL_CID_EXPOSURE_AUTO     0x00000004
#define  MT9V032_CTRL_CID_EXPOSURE          0x00000008
#define  MT9v032_CTRL_SET_WINDOW            0x00000010

/*---------------------------------------------------------------------
    _FRAME_NET

    net frame struct define
-----------------------------------------------------------------------
*/
typedef struct _FRAME_NET
{
    /* frame start flag should be 0x695a695a    */
	UINT32	startFlag;
	/* message frame type FRAME_TYPE_XXXX       */
	UINT32  frameType;
	/* frame number for video transport         */    
    UINT32	frameNum;
    /* frame data total length, (-128)          */
	UINT32	dataLen;
    /* frame data width in pixel                */
    UINT32  dataWidth;
    /* frame data height in pixel               */    
    UINT32  dataHeight;
	/* bit per pixel 8 / 16		                */  
	UINT32	bytePerPix;
    /* other any                                */
     
}
FRAME_Net, * pFRAME_Net;

/*---------------------------------------------------------------------
    _NET_MSG_PACK

    ����ͨ��Э��ṹ�嶨��
-----------------------------------------------------------------------
*/
typedef struct _NET_FRAME_HEAD
{
    /* frame start flag should be 0x695a695a    */
	UINT32		magic;
	UINT32		version;
	/* 0: no return value; 1: have return value */
	UINT32		type;
	UINT32		block;
	/* frame total length include frame head    */
	UINT32		length;
    /* size of NetFrameHead						*/
	UINT32		offset;
	/* net message minor id 					*/
	UINT32		minid;
	UINT8		data[1];
}
NetFrameHead, * pNetFrameHead;

/*---------------------------------------------------------------------
	RTC ʱ�� ISL12026 ��Ϣ�ṹ��
-----------------------------------------------------------------------
*/
typedef struct _ISL12026_INFO
{
	/* current time value		               */ 
	UINT8	time[8];
	/* alarm0 time value		               */ 
	UINT8	alarm0[8];
	/* alarm1 time value		               */ 
	UINT8	alarm1[8];
}
ISL12026_Info;

/*---------------------------------------------------------------------
	��Ƶ����������� ��Ϣ�ṹ��
-----------------------------------------------------------------------
*/
typedef struct _GENERAL_INFO
{
	/* input camera type	CAMERA_Type			*/ 
	UINT8		input;
	/* output display way 0:lcd; 1:net; 2:crt	*/ 
	UINT8		output;
	/* fpga ��ȡͼ������λ�� 0��8bit; 1:16bits	*/ 
	UINT8		bitType;
	/* ��ʹ�õ��㷨								*/
	UINT8		algorithm;
	/* fpga �����ع�ʱ�� 0-1720					*/ 
	UINT16		expTime;

	UINT8		inited;
	/* ����ģʽѡ�� 0->auto, 1->dsp, 2->outside	*/
	UINT8		trigger;
	/* ccdc ��ȡͼ�����ݺ�����ʼλ��			*/
	UINT16		horzStartPix;
	/* ccdc ��ȡͼ������������ʼλ��			*/
	UINT16		vertStartPix;
	/* ccdc ��ȡͼ������ʵ�ʿ��				*/
	UINT16		inWidth;
	/* ccdc ��ȡͼ������ʵ�ʸ߶�				*/
	UINT16		inHeight;

	UINT16		outWidth;
	UINT16		outHeight;
}
GENERAL_Info;

/*---------------------------------------------------------------------
    AD9849	���ò����ṹ��
-----------------------------------------------------------------------
*/
typedef struct _AD9849_INFO
{
	UINT8		vga[2];
	UINT8		pxga[4];
	UINT8		hxdrv[4];
	UINT8		rgdrv;
	UINT8		shp, shd;
	UINT8		hpl, hnl;
	UINT8		rgpl, rgnl;
}
AD9849_Info;

/*---------------------------------------------------------------------
	uart hecc����
-----------------------------------------------------------------------
*/
typedef struct _UARTHECC_INFO
{
	int	uartBaudrate;
	int heccBaudrate;
	int uartStop;
	int uartDataLen;
	int uartParity;
}
UARTHECC_Info;
/*---------------------------------------------------------------------
    AT25040 ������Ϣ�ṹ��
-----------------------------------------------------------------------
*/
typedef struct _AT25040_INFO
{
	/* ������ �汾��			               */ 
	UINT8		version;
	/* ������ mac ��ַ			               */ 
	UINT8		macAddr[6];
	/* ������ ip ��ַ						   */ 
	UINT8		ipAddr[4];
	/* ������ �˿�							   */ 
	UINT8		port;
}
AT25040_Info;

/*---------------------------------------------------------------------
    MT9v032 ������Ϣ�ṹ��
-----------------------------------------------------------------------
*/
typedef struct _MT9V032_INFO
{
	/* �Զ��������				               */ 
	UINT8		isAgc;
	/* �Զ��ع����				               */ 
	UINT8		isAec;
	/* ���������С							   */ 
	UINT16		agVal;
	/* �����ع��С							   */ 
	UINT16		aeVal;
}
MT9V032_Info;

/*--------------------------------------------------------------------*
	AT25040 ����Ĭ����������
*--------------------------------------------------------------------*/
/*typedef struct _BOOT_CONFIG_PARAM
{
	char 	version[20];		// program image version
	char 	camera_sn[8];  		// camera serial number
	char 	write_time[12];		// program image write time
	UINT8 	mac_address[8];		// camera mac address
	UINT8 	ip_address[4];		// camera ip address
	int	 	port;				// camera port;
	int  	boot_delay;			// boot delay time(s)
	GENERAL_Info	gen;		// vpss general information
}
BOOT_ConfigParam;*/


typedef struct _BOOT_CONFIG_NET
{
	Uint16	port;
	Uint8 	work_mode;	//1,2 tcpip server and client; 3,4 udp
	Uint8 	ip_address[4];
	Uint8	remote_ip[4];
	Uint8	mac_address[6];	
	Uint8	gateway[4];
	Uint8	ip_mask[4];
	Uint8	dns[4];

	Uint8	checksum;
}
BOOT_ConfigNet;

typedef struct _BOOT_CONFIG_UART
{
	Uint8 	baudRate;	//1, 115200, 2, 19200, 3, 9600
	Uint8 	work_mode;	//D1~D0, 00 ��У�飬01 ��У�飬 10��żУ��
						//D3~D2, 00 1λֹͣλ�� 10�� 2λֹͣλ
						//D7~D4������λ����5~8
	Uint8	checksum;
}
BOOT_ConfigUart;

typedef struct _BOOT_CONFIG_HECC
{
	Uint8 	baudRate;
	Uint8	id;

	Uint8	checksum;
}
BOOT_ConfigHecc;

typedef struct _BOOT_CONFIG_SENSOR
{
	Uint16 	width_max;
	Uint16	height_max;
	Uint16 	width_input;
	Uint16	height_input;
	Uint16 	startPixel_width;
	Uint16	startPixel_height;
	Uint8 	sensor_number;
	Uint8	isColour;
	Uint8	bitPixel;

	Uint8	checksum;
}
BOOT_ConfigSensor;

typedef struct _BOOT_CONFIG_MODE
{
	int 	expoTime;
	Uint8 	trigger;
	Uint8 	algorithm;
	Uint16	width_crt;
	Uint16 	height_crt;
	Uint8	output_mode;	//1, crt, 2, net, 3, lcd	
	Uint8	bitType;

	Uint8	checksum;
}
BOOT_ConfigMode;

typedef struct _BOOT_RECORD_VERSION
{
	Uint8 	id[4];
	Uint16 	version;
	Uint8	write_time[6];

	Uint8	checksum;
}
BOOT_RecordVersion;

typedef struct _BOOT_CONFIG_TRIGGER
{
	int trigDelay; // 0.1mm
	int partDelay; // 0.1mm
	int velocity;  // mm/s
	int departWide;	// ms
	int expLead;	// us

	Uint8 checksum;
}
BOOT_ConfigTrigger;

#define NET_POS			16
#define HECC_UART_POS	48
#define SENSOR_POS		64
#define MODE_POS		80
#define VERSION_POS		96
#define AD9849_POS		112
#define TRIGGER_POS		144

typedef struct _BOOT_CONFIG_PARAM
{
	BOOT_ConfigNet 		netConf;
	BOOT_ConfigHecc		heccConf;
	BOOT_ConfigUart		uartConf;
	BOOT_ConfigSensor	sencorConf;
	BOOT_ConfigMode		modeConf;
	BOOT_RecordVersion	versionRec;
	AD9849_Info		ad9849Reg;
	BOOT_ConfigTrigger	triggerConf;
}
BOOT_ConfigParam;


/*---------------------------------------------------------------------
    �ײ��豸���� ��Ϣ�ṹ��
-----------------------------------------------------------------------
*/
typedef struct _DEVICE_INFO
{
	GENERAL_Info	general;
	ISL12026_Info	isl12026;
	AD9849_Info	ad9849;
	AT25040_Info	at25040;
	MT9V032_Info	mt9v032;
	UARTHECC_Info	uartHecc;
	BOOT_ConfigNet	net;
	BOOT_ConfigTrigger trigger;
}
DEVICE_Info;

#define AT25040_HEAD	"BOOT_PARAM3"
#define AT25040_HEAD_COUNT	11

/*--------------------------------------------------------------------*/
