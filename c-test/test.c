#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../lib/libmqttcli_aarch64.h"

/* 首先定义一些回调函数 */

// 用来接口sdk日志
void logOutput(char *level, char *msg) {
    printf("---%s,%s\n", level, msg);
}

// 收到消息
int OnRecevMsg(MQTTContext ctx, char *topic, char *payload, int len) {
    printf("topic:%s\n", topic);
    printf("payload:%s\n\n", payload);

    // 在这里处理消息

    return 0;
}

// 连接中断通知
int OnClose(MQTTContext ctx) {

    // 重新连接
    while (MQTTConnectPskTLS(ctx) < 0) {
        MQTTSleep(3000);
    }
}

// 消息事件，注意：不要释放args成员
int OnEvent(MQTTContext ctx, int eventId, char *args[], int n) {

    switch (eventId) {
    case MQTT_EVENT_FEATURE: {
        // 获取当前属性值
        for (int i = 0;i < n;i++) {
            char* propertyId = args[i];

            if (MQTTMeasurementTypeOf(ctx, propertyId) == MEASUREMENT_VALUE_TYPE_STRING) {
                char* value = MQTTMeasurementGetStringValue(ctx, propertyId);
                printf("属性id: %s, 属性值: %s\n", propertyId, value);
                free(value);
            } else if (MQTTMeasurementTypeOf(ctx, propertyId) == MEASUREMENT_VALUE_TYPE_NUMBER) {
                double value = MQTTMeasurementGetNumberValue(ctx, propertyId);
                printf("属性id: %s, 属性值: %f\n", propertyId, value);
            }
        }

        break;
    }

    case MQTT_EVENT_DEVICE_CFG: {
        char* cfg = MQTTGetDeviceConfig(ctx);
        printf("设备配置: %s\n", cfg);
        free(cfg);
        break;
    }

    case MQTT_EVENT_PRODUCT_CFG: {
        char *cfg = MQTTGetProductConfig(ctx);
        printf("产品配置: %s\n", cfg);
        free(cfg);
        break;
    }

    case MQTT_EVENT_OTA: {
        // 下载OTA
        char *fileKey = MQTTOTAGetFileKey(ctx);
        printf("当前OTA文件id: %s\n", fileKey);
        free(fileKey);

        // 下载到指定目录
        MQTTOTADownload(ctx, "./ota");

        break;
    }

    default:
        break;
    }
}

char *OnRPC(MQTTContext ctx, char *req) {
    printf("OnRPC: %s\n", req);
    return "response-xxx";
}

void TestDevice01() {

    // 分配client对象
    MQTTContext ctx = MQTTNewContext();

    // 服务端地址
    // MQTTSetBroker(ctx, "server.iotbase.link", 8883);
    MQTTSetBroker(ctx, "10.211.55.4", 8883);

    // 从管理平台得到产品id和和设备名称
    MQTTSetDeviceID(ctx, "100009");
    MQTTSetProductID(ctx, "100012");

    // 修改默认超时，改为3秒
    MQTTSetTimeout(ctx, 3);

    // 从管理平台得到的psk，非证书认证时才需要设置psk
    MQTTSetPSK(ctx, "eWs1c2o4NTI=");

    // 设置一个回调函数，用来处理网络中断的善后工作，例如重新连接
    MQTTSetOnClose(ctx, OnClose);

    // 设置一个回调函数，用来接收订阅的消息
    MQTTSetOnRecevMsg(ctx, OnRecevMsg);

    // 设置一个回调函数，用来接收平台事件
    MQTTSetOnEvent(ctx, OnEvent);

    // 设置一个回调函数，用来处理远程调用
    MQTTSetOnRPC(ctx, OnRPC);

    // 每次连接清除会话(清除历史消息和订阅状态)
    MQTTSetClearSession(ctx, true);

    // 发起连接，使用psk tls方式
    if (MQTTConnectPskTLS(ctx) < 0) {
        printf("连接失败\n");
        // 记得关闭
        MQTTDeleteContext(ctx);
        return;
    }

    // 发起连接，使用tls证书认证(从管理平台得到设备证书)
    // MQTTSetCert(ctx, "../cert/dev2.crt", "../cert/dev2.key", "../cert/ca.crt");
    // if (MQTTConnectCertTLS(ctx) < 0)
    // {
    //     printf("连接失败\n");
    //     // 记得关闭
    //     MQTTDeleteContext(ctx);
    //     return;
    // }

    char* id = MQTTGetDeviceID(ctx);

   	// 本地日志
	DLog("设备上线: deviceId=%s", id);

	// 云日志，在控制台可查看
	DeviceDLog(ctx, "设备上线: deviceId=%s", id);
    free(id);

    // 需要订阅的自定义主题
    Filter *filters[2];
    filters[0] = (Filter *)malloc(sizeof(Filter));
    filters[0]->subTopic = "set";
    filters[0]->QoS = 1;
    filters[1] = (Filter *)malloc(sizeof(Filter));
    filters[1]->subTopic = "control/#";
    filters[1]->QoS = 1;

    MQTTSubscribe(ctx, filters, 2);

    free(filters[0]);
    free(filters[1]);

    int running = 1;
    while (running) {

       	// 在管理平台上定义的物模型属性，改变这些属性值会自动上报给平台
		MQTTMeasurementSetNumberValue(ctx, "power", (double)MQTTRandNum(100));

		// 开关量
		MQTTMeasurementSetNumberValue(ctx, "radio", 1);

		// 多选，发送json数组字符串
		MQTTMeasurementSetStringValue(ctx, "select", "[\"2\"]");

		// 单选
		MQTTMeasurementSetStringValue(ctx, "select1", "[2]");

		// 文本
		MQTTMeasurementSetStringValue(ctx, "text123", "ddfxxx");

		// 将所有属性值上报给平台
		MQTTMeasurementUpdate(ctx);

		// 也可以发送自定义消息
        char msg[] = "working...";
		MQTTPublish(ctx, "status", 1, msg, strlen(msg));

        MQTTSleep(1000);
    }

    // 记得关闭
    MQTTDeleteContext(ctx);
}

int main() {
    // 可以注册日志接口，重定向sdk日志，如果不注册就直接输出
    // MQTTSetLogOutput(logOutput);
    TestDevice01();
    return 0;
}
