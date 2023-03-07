目前只支持linux arm64或linux amd64系统。 c-test/test.c

文件说明：
头文件和静态库：lib/ <br>
完整例子：c-test/test.c

例如，在arm64环境编译：
gcc test.c -o test -L../lib -lmqttcli_aarch64 -lpthread
