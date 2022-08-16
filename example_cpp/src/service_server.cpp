#include <rclcpp/rclcpp.hpp>
#include "example_interfaces/srv/add_two_ints.hpp"

class Server_Sum:public rclcpp::Node
{
public:
	Server_Sum(std::string name):Node(name)
	{ 
		RCLCPP_INFO(this -> get_logger(),"已初始化服务端：%s节点!",name.c_str());
		//创建服务
		add_ints_server = this ->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints_server_srv",std::bind(&Server_Sum::handle_add_two_ints,this,std::placeholders::_1,std::placeholders::_2));
	}
private:
	//声明服务
	rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr add_ints_server;

	//处理请求数据
	void handle_add_two_ints(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request>request,
		std::shared_ptr<example_interfaces::srv::AddTwoInts::Response>response)
	{
		RCLCPP_INFO(this ->get_logger(),"收到数据:a=%ld ,b=%ld\n",request->a,request->b);
		response -> sum = request->a + request->b;

	}
	

};

int main(int argc,char ** argv)
{
	rclcpp::init(argc,argv);

	auto node = std::make_shared<Server_Sum>("Server");

	rclcpp::spin(node);

	rclcpp::shutdown();

	return 0;
}