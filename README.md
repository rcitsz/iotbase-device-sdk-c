目前只支持linux arm64或linux amd64t系统。请参考参这个文件的例子：c-test/test.c

例如，在arm64环境编译：
gcc test.c -o test -L../lib -lmqttcli_aarch64 -lpthread
