/* Code generated by cmd/cgo; DO NOT EDIT. */

/* package device-sdk/lib */


#line 1 "cgo-builtin-export-prolog"

#include <stddef.h>

#ifndef GO_CGO_EXPORT_PROLOGUE_H
#define GO_CGO_EXPORT_PROLOGUE_H

#ifndef GO_CGO_GOSTRING_TYPEDEF
typedef struct { const char *p; ptrdiff_t n; } _GoString_;
#endif

#endif

/* Start of preamble from import "C" comments.  */


#line 3 "c-inf.go"



#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef long long MQTTContext;
typedef struct {
	char* subTopic;
	int QoS;
}Filter;

typedef enum _MQTT_EVENT_ {
	MQTT_EVENT_FEATURE = 1,
	MQTT_EVENT_OTA  = 2,
	MQTT_EVENT_DEVICE_CFG  = 3,
	MQTT_EVENT_PRODUCT_CFG  = 4
}MQTT_EVENT;

typedef enum _MEASUREMENT_VALUE_TYPE_ {
	MEASUREMENT_VALUE_TYPE_NONE   = 0,
	MEASUREMENT_VALUE_TYPE_STRING  = 1,
	MEASUREMENT_VALUE_TYPE_NUMBER = 2
}MEASUREMENT_VALUE_TYPE;

typedef int (*MQTTOnRecevMsg)(MQTTContext ctx, char* topic, char* payload, int len);
typedef int (*MQTTOnClose)(MQTTContext ctx);
typedef void (*MQTTLogCallback)(char* level, char* msg);
typedef int (*MQTTOnEvent)(MQTTContext ctx, int eventId, char* args[], int n);
typedef char* (*MQTTOnRPC)(MQTTContext ctx, char* req);

static void doLogCallback(void* cb, char* level, char* msg) {((MQTTLogCallback)cb)(level, msg);}
static void doOnCloseCallback(void* cb, MQTTContext ctx) {((MQTTOnClose)cb)(ctx);}
static void doOnRecevMsgCallback(void* cb, MQTTContext ctx, char* topic, char* msg, int len) {((MQTTOnRecevMsg)cb)(ctx, topic, msg, len);}
static void doOnEventCallback(void* cb, MQTTContext ctx, int eventId, char* args, int n) {((MQTTOnEvent)cb)(ctx, eventId, (char**)args, n);}
static char* doOnRPCCallback(void* cb, MQTTContext ctx, char* req) {return ((MQTTOnRPC)cb)(ctx, req);}


// 日志函数，可自行调整
#define LOG_BUF_LEN 2048

// 在管理平台记录调试日志
#define DeviceDLog(ctx, format, ...)  \
{\
 char msg[LOG_BUF_LEN]; \
 char* dt = MQTTNowDataTime(); \
 int n = snprintf(msg, sizeof(msg)-2, "{\"time\":\"%s\",\"level\":\"debug\",\"line\":\"%s:%d\",\"msg\":\"" format "\"}", dt,__FILE__,__LINE__,##__VA_ARGS__); \
 msg[n] = '\n'; \
 msg[n+1] = 0; \
 MQTTPulbishLog(ctx, "debug", msg); \
 free(dt);\
}

// 在本机输出调试日志
#define DLog(format, ...)  \
{\
 char msg[LOG_BUF_LEN]; \
 char* dt = MQTTNowDataTime(); \
 int n = snprintf(msg, sizeof(msg)-2, "{\"time\":\"%s\",\"level\":\"debug\",\"line\":\"%s:%d\",\"msg\":\"" format "\"}", dt,__FILE__,__LINE__,##__VA_ARGS__); \
 msg[n] = '\n'; \
 msg[n+1] = 0; \
 MQTTWriteLog("debug", msg); \
 free(dt);\
}

// 在管理平台记录提示日志
#define DeviceILog(ctx, format, ...)  \
{\
 char msg[LOG_BUF_LEN]; \
 char* dt = MQTTNowDataTime(); \
 int n = snprintf(msg, sizeof(msg)-2, "{\"time\":\"%s\",\"level\":\"info\",\"line\":\"%s:%d\",\"msg\":\"" format "\"}", dt,__FILE__,__LINE__,##__VA_ARGS__); \
 msg[n] = '\n'; \
 msg[n+1] = 0; \
 MQTTPulbishLog(ctx, "info", msg); \
 free(dt);\
}

// 在本机输出提示日志
#define ILog(format, ...)  \
{\
 char msg[LOG_BUF_LEN]; \
 char* dt = MQTTNowDataTime(); \
 int n = snprintf(msg, sizeof(msg)-2, "{\"time\":\"%s\",\"level\":\"info\",\"line\":\"%s:%d\",\"msg\":\"" format "\"}", dt,__FILE__,__LINE__,##__VA_ARGS__); \
 msg[n] = '\n'; \
 msg[n+1] = 0; \
 MQTTWriteLog("info", msg); \
 free(dt);\
}

// 在管理平台记录告警日志
#define DeviceWLog(ctx, format, ...)  \
{\
 char msg[LOG_BUF_LEN]; \
 char* dt = MQTTNowDataTime(); \
 int n = snprintf(msg, sizeof(msg)-2, "{\"time\":\"%s\",\"level\":\"warn\",\"line\":\"%s:%d\",\"msg\":\"" format "\"}", dt,__FILE__,__LINE__,##__VA_ARGS__); \
 msg[n] = '\n'; \
 msg[n+1] = 0; \
 MQTTPulbishLog(ctx, "warn", msg); \
free(dt);\
}

// 在本机输出告警日志
#define WLog(format, ...)  \
{\
 char msg[LOG_BUF_LEN]; \
 char* dt = MQTTNowDataTime(); \
 int n = snprintf(msg, sizeof(msg)-2, "{\"time\":\"%s\",\"level\":\"warn\",\"line\":\"%s:%d\",\"msg\":\"" format "\"}", dt,__FILE__,__LINE__,##__VA_ARGS__); \
 msg[n] = '\n'; \
 msg[n+1] = 0; \
 MQTTWriteLog("warn", msg); \
free(dt);\
}

// 在管理平台记录错误日志
#define DeviceELog(ctx, format, ...)  \
{\
 char msg[LOG_BUF_LEN]; \
 char* dt = MQTTNowDataTime(); \
 int n = snprintf(msg, sizeof(msg)-2, "{\"time\":\"%s\",\"level\":\"error\",\"line\":\"%s:%d\",\"msg\":\"" format "\"}", dt,__FILE__,__LINE__,##__VA_ARGS__); \
 msg[n] = '\n'; \
 msg[n+1] = 0; \
 MQTTPulbishLog(ctx, "error", msg); \
 free(dt);\
}

// 在本机输出错误日志
#define ELog(format, ...)  \
{\
 char msg[LOG_BUF_LEN]; \
 char* dt = MQTTNowDataTime(); \
 int n = snprintf(msg, sizeof(msg)-2, "{\"time\":\"%s\",\"level\":\"error\",\"line\":\"%s:%d\",\"msg\":\"" format "\"}", dt,__FILE__,__LINE__,##__VA_ARGS__); \
 msg[n] = '\n'; \
 msg[n+1] = 0; \
 MQTTWriteLog("error", msg); \
 free(dt);\
}


#line 1 "cgo-generated-wrapper"


/* End of preamble from import "C" comments.  */


/* Start of boilerplate cgo prologue.  */
#line 1 "cgo-gcc-export-header-prolog"

#ifndef GO_CGO_PROLOGUE_H
#define GO_CGO_PROLOGUE_H

typedef signed char GoInt8;
typedef unsigned char GoUint8;
typedef short GoInt16;
typedef unsigned short GoUint16;
typedef int GoInt32;
typedef unsigned int GoUint32;
typedef long long GoInt64;
typedef unsigned long long GoUint64;
typedef GoInt64 GoInt;
typedef GoUint64 GoUint;
typedef size_t GoUintptr;
typedef float GoFloat32;
typedef double GoFloat64;
#ifdef _MSC_VER
#include <complex.h>
typedef _Fcomplex GoComplex64;
typedef _Dcomplex GoComplex128;
#else
typedef float _Complex GoComplex64;
typedef double _Complex GoComplex128;
#endif

/*
  static assertion to make sure the file is being used on architecture
  at least with matching size of GoInt.
*/
typedef char _check_for_64_bit_pointer_matching_GoInt[sizeof(void*)==64/8 ? 1:-1];

#ifndef GO_CGO_GOSTRING_TYPEDEF
typedef _GoString_ GoString;
#endif
typedef void *GoMap;
typedef void *GoChan;
typedef struct { void *t; void *v; } GoInterface;
typedef struct { void *data; GoInt len; GoInt cap; } GoSlice;

#endif

/* End of boilerplate cgo prologue.  */

#ifdef __cplusplus
extern "C" {
#endif


/*
功能描述：创建设备上下文，代表一个设备
输入参数：无
返回结果：设备上下文
*/
extern MQTTContext MQTTNewContext();

/*
功能描述：删除设备对象，释放资源
输入参数：ctx - 设备上下文
返回结果：无
*/
extern void MQTTDeleteContext(MQTTContext ctx);

/*
功能描述：设置broker地址
输入参数：
    ctx - 设备上下文
    host - ip或域名
    port - 非加密通信1883，加密端口是8883
返回结果：无
*/
extern void MQTTSetBroker(MQTTContext ctx, char* host, int port);

/*
功能描述：设置产品ID
输入参数：
    ctx - 设备上下文
    productID - 从控制台获取到的产品id
返回结果：无
*/
extern void MQTTSetProductID(MQTTContext ctx, char* productID);

/*
功能描述：获取产品ID
输入参数：
    ctx - 设备上下文
返回结果：产品ID，需释放
*/
extern char* MQTTGetProductID(MQTTContext ctx);

/*
功能描述：设置设备ID
输入参数：
    ctx - 设备上下文
    deviceID - 从控制台获取到的设备id
返回结果：无
*/
extern void MQTTSetDeviceID(MQTTContext ctx, char* deviceID);

/*
功能描述：获取设备ID
输入参数：
    ctx - 设备上下文
返回结果：设备id，需释放
*/
extern char* MQTTGetDeviceID(MQTTContext ctx);

/*
功能描述：获取物模型ID
输入参数：
    ctx - 设备上下文
返回结果：物模型id，需释放
*/
extern char* MQTTGetMeasurementID(MQTTContext ctx);

/*
功能描述：设置清除会话选项
输入参数：
	ctx - 设备上下文
	clear - 0表示保留会话，1表示不保留会话
返回结果：无
*/
extern void MQTTSetClearSession(MQTTContext ctx, int clear);

/*
功能描述：设置mqtt鉴权信息
输入参数：
    ctx - 设备上下文
    clientID - mqtt客户端id
    userName - mqtt用户名
    password - mqtt密码
返回结果：无
*/
extern void MQTTSetAuth(MQTTContext ctx, char* clientID, char* userName, char* password);

/*
功能描述：设置连接超时，包括读写超时，心跳超时,如不设置超时，默认是5秒
输入参数：
    ctx: 设备上下文
    timeout: 超时时间，单位是秒
返回结果：无
*/
extern void MQTTSetTimeout(MQTTContext ctx, int timeout);

/*
功能描述：设置鉴权密钥
输入参数：
    ctx: 设备上下文
    psk: 鉴权密钥，base64格式
返回结果：无
*/
extern void MQTTSetPSK(MQTTContext ctx, char* psk);

/*
功能描述：设置鉴权证书(双向认证)
输入参数：
    ctx: 设备上下文
    cert: 公钥证书文件路径，pem格式
    key：私要证书文件路径，pem格式
    ca: ca授权证书文件路径，pem格式
返回结果：无
*/
extern void MQTTSetCert(MQTTContext ctx, char* cert, char* key, char* ca);

/*
功能描述：发起mqtt连接(psk鉴权明文传输)
输入参数：ctx - 设备上下文
返回结果：返回值为0表示成功，非0表示失败
*/
extern int MQTTConnectPskNoTLS(MQTTContext ctx);

/*
功能描述：发起mqtt连接(psk鉴权tls加密传输)
输入参数：ctx - 设备上下文
返回结果：返回值为0表示成功，非0表示失败
*/
extern int MQTTConnectPskTLS(MQTTContext ctx);

/*
功能描述：发起mqtt连接(证书认证tls加密传输)
输入参数：ctx - 设备上下文
返回结果：返回值为0表示成功，非0表示失败
*/
extern int MQTTConnectCertTLS(MQTTContext ctx);

/*
功能描述：发布mqtt消息
输入参数：
    ctx - 设备上下文
    subTopic - 主题后缀
    QoS - 有效值是0、1、2, 依次表示QoS0、QoS1、QoS2
	msg - 消息内容
	n - 消息长度(字节数)
返回结果：返回值为0表示成功，非0表示失败
*/
extern int MQTTPublish(MQTTContext ctx, char* subTopic, int QoS, char* msg, int n);

/*
功能描述：订阅主题
输入参数：
    ctx - 设备上下文
    filters - 订阅主题，此参数是数组，支持批量订阅
    n - 表示filters有多少个成员
返回结果：返回值为0表示成功，非0表示失败
*/
extern int MQTTSubscribe(MQTTContext ctx, Filter** filters, int n);

/*
功能描述：取消订阅
输入参数：
    ctx - 设备上下文
    filters - 订阅主题，此参数是数组，支持批量订阅
返回结果：返回值为0表示成功，非0表示失败
*/
extern int MQTTUnSubscribe(MQTTContext ctx, char** filters, int n);

/*
功能描述：毫秒延时
输入参数：
    delay - 延时时间值，单位是毫秒
返回结果：返回值为0表示成功，非0表示失败
*/
extern void MQTTSleep(long long int delay);

/*
功能描述：获取时间
输入参数：无
返回结果：纳秒
*/
extern long long int MQTTNowUnixNano();

/*
功能描述：获取日期时间
输入参数：无
返回结果：日期时间
*/
extern char* MQTTNowDataTime();

/*
功能描述：设置日志回调接口，可以重定向sdk日志
输入参数：无
    ctx - 设备上下文
    cb - 回调函数，用来接收日志
*/
extern void MQTTSetLogOutput(MQTTLogCallback cb);

/*
功能描述：设置连接关闭通知函数，用户可在回调函数里实现重连等其它操作
输入参数：
    ctx - 设备上下文
    cb - 回调函数，用来接收连接关闭消息
返回结果：无
*/
extern void MQTTSetOnClose(MQTTContext ctx, MQTTOnClose cb);

/*
功能描述：设置消息回调函数
输入参数：
    ctx - 设备上下文
    cb - 回调函数，用来接收消息
返回结果：无
*/
extern void MQTTSetOnRecevMsg(MQTTContext ctx, MQTTOnRecevMsg cb);

/*
功能描述：设置消息回调函数
输入参数：
    ctx -设备上下文
    cb - 回调函数，用来接收消息
返回结果：无
*/
extern void MQTTSetOnEvent(MQTTContext ctx, MQTTOnEvent cb);

/*
功能描述：设置RPC回调
输入参数：
    ctx - 设备上下文
    cb - 回调函数，用来响应远程请求
返回结果：无
*/
extern void MQTTSetOnRPC(MQTTContext ctx, MQTTOnRPC cb);

/*
功能描述：产生随机数
输入参数：n - 产品的随机数小于n
返回结果：[0,n)随机数
*/
extern int MQTTRandNum(int n);

/*
功能描述：判断属性类型
输入参数：
	ctx - 设备上下文
	propertyId - 属性id
返回结果：属性类型(见请枚举类型MEASUREMENT_VALUE_TYPE)
*/
extern MEASUREMENT_VALUE_TYPE MQTTMeasurementTypeOf(MQTTContext ctx, char* propertyId);

/*
功能描述：判断属性是否存在
输入参数：
	ctx - 设备上下文
	propertyId - 属性id
返回结果：
	0 - 不存在
	1 - 存在
*/
extern int MQTTMeasurementPropertyIdExist(MQTTContext ctx, char* propertyId);

/*
功能描述：获取物模型属性值(字符串类型)
输入参数：
	ctx - 设备上下文
	propertyId - 属性id
返回结果：属性值，需释放
*/
extern char* MQTTMeasurementGetStringValue(MQTTContext ctx, char* propertyId);

/*
功能描述：获取物模型属性值(数值类型)
输入参数：
	ctx - 设备上下文
	propertyId - 属性id
返回结果：无
*/
extern double MQTTMeasurementGetNumberValue(MQTTContext ctx, char* propertyId);

/*
功能描述：设置属性值(字符串)
输入参数：
	ctx - 设备上下文
	propertyId - 属性id
	value - 属性值
返回结果：无
*/
extern void MQTTMeasurementSetStringValue(MQTTContext ctx, char* propertyId, char* value);

/*
功能描述：设置属性值(数值)
输入参数：
	ctx - 设备上下文
	propertyId - 属性id
	value - 属性值
返回结果：无
*/
extern void MQTTMeasurementSetNumberValue(MQTTContext ctx, char* propertyId, double value);

/*
功能描述：把所有属性值上报到平台
输入参数：
	ctx - 设备上下文
返回结果：无
*/
extern void MQTTMeasurementUpdate(MQTTContext ctx);

/*
功能描述：上报日志
输入参数：
	ctx - 设备上下文
	level- 日志级别，有效值是：debug、info、warn、error
	log - 日志内容
返回结果：无
*/
extern void MQTTPulbishLog(MQTTContext ctx, char* level, char* log);

/*
功能描述：本机输出日志
输入参数：
	ctx - 设备上下文
	level- 日志级别，有效值是：debug、info、warn、error
返回结果：无
*/
extern void MQTTWriteLog(char* level, char* log);

/*
功能描述：获取设备配置
输入参数：ctx - 设备上下文
返回结果：设备配置，需释放
*/
extern char* MQTTGetDeviceConfig(MQTTContext ctx);

/*
功能描述：获取产品配置
输入参数：ctx - 设备上下文
返回结果：产品配置，需释放
*/
extern char* MQTTGetProductConfig(MQTTContext ctx);

/*
功能描述：获取固件文件名
输入参数：ctx - 设备上下文
返回结果：文件名，需释放
*/
extern char* MQTTOTAGetFileName(MQTTContext ctx);

/*
功能描述：获取固件文件key
输入参数：ctx - 设备上下文
返回结果：固件文件key，需释放
*/
extern char* MQTTOTAGetFileKey(MQTTContext ctx);

/*
功能描述：获取固件版本
输入参数：ctx - 设备上下文
返回结果：版本号，需释放
*/
extern char* MQTTOTAGetVersion(MQTTContext ctx);

/*
功能描述：下载固件
输入参数：
	ctx - 设备上下文
	dir - 保存固件的目录
返回结果：固件文件名，需释放
*/
extern char* MQTTOTADownload(MQTTContext ctx, char* dir);

#ifdef __cplusplus
}
#endif
