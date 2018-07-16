
#include "zmq.h"
#include "zmq_utils.h"            //Zeromq 函数的导入在这里帮我们实现了
#include <iostream>
#pragma comment(lib,"libzmq-v120-mt-gd-4_0_4.lib")

int main()
{
	std::cout << "-------------------Zeromq REP style-----------------------" << std::endl;

	void* context = zmq_init(1);    //指定zmq 处理I/0事件的thread pool 为1
	void* z_socket = zmq_socket(context, ZMQ_REP);
	
	zmq_bind(z_socket, "tcp://*:8888");    //注意 此处localhost不适用

	int recvn = 1;
	while (1)    //循环工作
	{
		//接受部分
		zmq_msg_t recv_msg;
		zmq_msg_init(&recv_msg);
		zmq_msg_recv(&recv_msg, z_socket, 0); //0表示非阻塞
		std::cout << "第\t" << recvn++ << "\t次收到client信息：\t";
		std::cout << (char*)zmq_msg_data(&recv_msg) << std::endl;
		zmq_msg_close(&recv_msg);

		//发送部分
		zmq_msg_t send_msg;
		zmq_msg_init_size(&send_msg, 6);
		memcpy(zmq_msg_data(&send_msg), "world", 6);
		zmq_sendmsg(z_socket, &send_msg, 0);
		zmq_msg_close(&send_msg);
	}
	zmq_close(z_socket);
	zmq_term(context);
	
	return 0;
}