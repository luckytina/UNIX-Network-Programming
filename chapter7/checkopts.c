#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>

union
{
		int 	i_val;
		long	l_val;
		struct 	linger	linger_val;			//在头文件<sys/socket.h>中
		struct 	timeval	timeval_val;		//在头文件<sys/time.h>中
}val;

static char *sock_str_flag(union val *, int);
static char *sock_str_int(union val *, int);
static char *sock_str_linger(union val *, int);
static char *sock_str_timeval(union val *, int);

struct sock_opts
{
		const char		*opt_str;
		int				opt_level;
		int				opt_name;
		char			*(*opt_val_str)(union val *, int);
}sock_opts[] = {
		{"SO_BROADCAST", SOL_SOCKET, SO_BROADCAST, sock_str_falg},		//允许发送广播数据报
		{"SO_DEBUG", SOL_SOCKET, SO_DEBUG, sock_str_falg},				//开发调试跟踪
		{"SO_DONTROUTE", SOL_SOCKET, SO_DONTROUTE, sock_str_flag},		//绕过外出路由表查询
	   	{"SO_ERROR", SOL_SOCKET, SO_ERROR, sock_str_int},				//获取待处理数据并清除
		{"SO_KEEPLEALIVE", SOL_SOCKET, SO_KEEPLEALIVE, sock_str_flag},  //周期性测试连接是否存在
		{"SO_LINGER", SOL_SOCKET, SO_LINGER, sock_str_linger},			//若有数据待发送则延迟发送
		{"SO_OOBINLINE", SOL_SOCKET, SO_OOBINLINE, sock_srt_flag},		//让接受到的外带数据持续在线存留
		{"SO_RCVBUF",  SOL_SOCKET, SO_RCVBUF, sock_srt_int},			//接收缓冲区大小
		{"SO_SNDBUF",	SOL_SOCKET,	SO_SNDBUF, sock_str_int},			//发送缓冲区大小
		{"SO_RCVLOWAT", SOL_SOCKET,	SO_RCVLOWAT, sock_str_int},			//接收缓冲区低水位标记
		{"SO_SNDLOWAT", SOL_SOCKET, SO_RCVLOWAT, sock_str_int},			//发送缓冲区低水位标记
		{"SO_RCVTIMEO", SOL_SOCKET,	SO_RCVTMEO,  sock_str_timeval},     //接收缓冲区超时
		{"SO_SNDTIMEO", SOL_SOCKET, SO_SNDTIMEO, sock_srt_timeval},		//发送缓冲区超时
		{"SO_REUSEADDR", SOL_SOCKET, SO_REUSEADDR, sock_str_flag},		//允许从用本地地址

};

