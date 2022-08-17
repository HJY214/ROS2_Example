/* 采取异步接受数据的方式 */
#include <rclcpp/rclcpp.hpp>
#include "example_interfaces/srv/add_two_ints.hpp"

class Client_Sum:public rclcpp::Node
{
public:
	Client_Sum(std::string name):Node(name)
	{
		RCLCPP_INFO(this -> get_logger(),"已初始化客户端：%s节点!",name.c_str());
		/* 创建客户端 */
		client_ = this ->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints_server_srv");
	}
	void send_request(int a,int b)
	{
		RCLCPP_INFO(this->get_logger(),"计算数据：%d + %d\n",a,b);

		/* 1.等待服务端上线 */
		while(!client_->wait_for_service(std::chrono::seconds(1)))
		{
			if (!rclcpp::ok())
			{
				RCLCPP_INFO(this -> get_logger(),"等待服务的过程被打断！");
			}
			RCLCPP_INFO(this -> get_logger(),"等待服务端上线....");
		}

		/* 2.构造请求 */
		auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
		request->a = a;
		request->b = b;

		/* 3.发送异步请求，然后等待返回，返回时调用回调函数 */
		client_-> async_send_request(request,std::bind(&Client_Sum::result_callback,this,std::placeholders::_1)); 
	}
private:
	/* 声明客户端 */
	rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;
	/* 接受请求回调函数 */
	void result_callback(rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture result_future)
	{
		auto response = result_future.get();
		RCLCPP_INFO(this -> get_logger(),"计算结果为:%ld\n",response->sum);
	}
	
};

int main(int argc,char ** argv)
{
	rclcpp::init(argc,argv);

	if (argc != 3) 
	{
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_two_ints_client X Y");
      return 1;
  	}

	auto node = std::make_shared<Client_Sum>("Client");
 
	node -> send_request(atoll(argv[1]),atoll(argv[2]));

	rclcpp::spin(node);

	rclcpp::shutdown();

	return 0;
}