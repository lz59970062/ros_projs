#ifndef JY901_h
#define JY901_h
#include <Arduino.h>
#define SAVE 0x00
#define CALSW 0x01
#define RSW 0x02
#define RRATE 0x03
#define BAUD 0x04
#define AXOFFSET 0x05
#define AYOFFSET 0x06
#define AZOFFSET 0x07
#define GXOFFSET 0x08
#define GYOFFSET 0x09
#define GZOFFSET 0x0a
#define HXOFFSET 0x0b
#define HYOFFSET 0x0c
#define HZOFFSET 0x0d
#define D0MODE 0x0e
#define D1MODE 0x0f
#define D2MODE 0x10
#define D3MODE 0x11
#define D0PWMH 0x12
#define D1PWMH 0x13
#define D2PWMH 0x14
#define D3PWMH 0x15
#define D0PWMT 0x16
#define D1PWMT 0x17
#define D2PWMT 0x18
#define D3PWMT 0x19
#define IICADDR 0x1a
#define LEDOFF 0x1b
#define GPSBAUD 0x1c

#define YYMM 0x30
#define DDHH 0x31
#define MMSS 0x32
#define MS 0x33
#define AX 0x34
#define AY 0x35
#define AZ 0x36
#define GX 0x37
#define GY 0x38
#define GZ 0x39
#define HX 0x3a
#define HY 0x3b
#define HZ 0x3c
#define Roll 0x3d
#define Pitch 0x3e
#define Yaw 0x3f
#define TEMP 0x40
#define D0Status 0x41
#define D1Status 0x42
#define D2Status 0x43
#define D3Status 0x44
#define PressureL 0x45
#define PressureH 0x46
#define HeightL 0x47
#define HeightH 0x48
#define LonL 0x49
#define LonH 0x4a
#define LatL 0x4b
#define LatH 0x4c
#define GPSHeight 0x4d
#define GPSYAW 0x4e
#define GPSVL 0x4f
#define GPSVH 0x50
#define Q0 0x51
#define Q1 0x52
#define Q2 0x53
#define Q3 0x54
#define DIO_MODE_AIN 0
#define DIO_MODE_DIN 1
#define DIO_MODE_DOH 2
#define DIO_MODE_DOL 3
#define DIO_MODE_DOPWM 4
#define DIO_MODE_GPS 5

struct STime
{
	unsigned char ucYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucHour;
	unsigned char ucMinute;
	unsigned char ucSecond;
	unsigned short usMiliSecond;
};
struct SAcc
{
	short a[3];
	short T;
};
struct SGyro
{
	short w[3];
	short T;
};
struct SAngle
{
	short Angle[3];
	short T;
};
struct SMag
{
	short h[3];
	short T;
};

struct SDStatus
{
	short sDStatus[4];
};

struct SPress
{
	long lPressure;
	long lAltitude;
};

struct SLonLat
{
	long lLon;
	long lLat;
};

struct SGPSV
{
	short sGPSHeight;
	short sGPSYaw;
	long lGPSVelocity;
};
struct SQ
{
	short q0, q1, q2, q3;
	short T;
};
class CJY901
{
public:
	struct STime stcTime;
	struct SAcc stcAcc;
	struct SGyro stcGyro;
	struct SAngle stcAngle;
	struct SMag stcMag;
	struct SDStatus stcDStatus;
	struct SPress stcPress;
	struct SLonLat stcLonLat;
	struct SGPSV stcGPSV;
	struct SQ stcSQ;
	CJY901();
	void StartIIC();
	void StartIIC(unsigned char ucAddr);
	void CopeSerialData(unsigned char ucData);
	short ReadWord(unsigned char ucAddr);
	void WriteWord(unsigned char ucAddr, short sData);
	void ReadData(unsigned char ucAddr, unsigned char ucLength, char chrData[]);
	void GetTime();
	void GetAcc();
	void GetGyro();
	void GetAngle();
	void GetMag();
	void GetPress();
	void GetDStatus();
	void GetLonLat();
	void GetGPSV();
	void GetQ();
	void save_config();
	void set_buad(long  buad);
	void set_rset();
	void set_calibrate();
	void zero_yaw();
	void writeRegister_ser(uint8_t add,unsigned short data);



private:
	unsigned char ucDevAddr;
	void readRegisters(unsigned char deviceAddr, unsigned char addressToRead, unsigned char bytesToRead, char *dest);
	void writeRegister(unsigned char deviceAddr, unsigned char addressToWrite, unsigned char bytesToRead, char *dataToWrite);
};

class Imu : public CJY901
{
public:
	Imu(uint8_t mode);
	void init();
	void update();
	void getEuler(float *roll, float *pitch, float *yaw);
	void getAcc(float *x, float *y, float *z);
	void getGyro(float *x, float *y, float *z);
	void getMag(float *x, float *y, float *z);

	void getEuler();
	void getAcc();
	void getGyro();
	void getMag();

	void getPress(float *press, float *alt);
	void getLonLat(float *lon, float *lat);
	void getGPSV(float *height, float *yaw, float *vel);
	void getDStatus(int *d0, int *d1, int *d2, int *d3);
	void getTime(int *year, int *month, int *day, int *hour, int *minute, int *second, int *mili);
	void getQ(float *w, float *x, float *y, float *z);
	uint8_t useSerial;
	uint8_t useIIC;
	float accx, accy, accz;
	float gyrox, gyroy, gyroz;
	float magx, magy, magz;
	float roll, pitch, yaw;
	float lgyrox, lgyroy, lgyroz;
};
void taskImu(void *pvParameters);
extern Imu imu;
// extern xSemaphoreHandle xSemaphore_imu;
#include <Wire.h>
#endif