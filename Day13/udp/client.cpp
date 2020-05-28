#include <Unixfunc.h>
#include <iostream>
using namespace std;

int main()
{
    int ret;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");
    struct sockaddr_in sockinfo;
    socklen_t len = sizeof(sockinfo);
    bzero(&sockinfo, sizeof(sockinfo));
    sockinfo.sin_addr.s_addr = inet_addr("172.21.0.7");
    sockinfo.sin_port = htons(2012);
    sockinfo.sin_family = AF_INET;

    sendto(sockfd, "hello", 5, 0, (sockaddr*)&sockinfo, len);
    char buf[100] = {0};
    recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
    cout << "receving from server:" << buf << endl;

    close(sockfd);
    return 0;
}