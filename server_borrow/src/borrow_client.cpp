/* 采取异步接受数据的方式 */

#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/u_int32.hpp"
#include "cust_interfaces/srv/sell_books.hpp"

int money_;

class Borrow_Client:public rclcpp::Node
{
public:
	Borrow_Client(std::string name):Node(name)
	{
		RCLCPP_INFO(this -> get_logger(),"已初始化客户端：%s节点!",name.c_str());
        /* 声明参数 */
        this->declare_parameter("money",money_);
		/* 创建客户端 */
		client_ = this ->create_client<cust_interfaces::srv::SellBooks>("sell_server_srv");
	}
	void send_request(int a)
	{
		RCLCPP_INFO(this->get_logger(),"给了 %d 块钱买书\n",a);

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
		auto request = std::make_shared<cust_interfaces::srv::SellBooks::Request>();
		request->money = a;

		/* 3.发送异步请求，然后等待返回，返回时调用回调函数 */
		client_-> async_send_request(request,std::bind(&Borrow_Client::result_callback,this,std::placeholders::_1)); 
	}
private:
	/* 声明客户端 */
	rclcpp::Client<cust_interfaces::srv::SellBooks>::SharedPtr client_;
	/* 接受请求回调函数 */
	void result_callback(rclcpp::Client<cust_interfaces::srv::SellBooks>::SharedFuture response)
	{
		auto result = response.get();
		RCLCPP_INFO(this -> get_logger(),"收到了:%ld 本书\n",result->books.size());

        for (std::string books:result->books)
        {
            RCLCPP_INFO(this -> get_logger(),"%s",books.c_str());
        }
         RCLCPP_INFO(this->get_logger(), "书本拿完了，好开心，好期待更多的书呀！");
	}
	
};

int main(int argc,char ** argv)
{
	rclcpp::init(argc,argv);

	// if (argc != 2) 
	// {
    //   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "只能给一次钱哦!");
    //   return 1;
  	// }

	auto node = std::make_shared<Borrow_Client>("Borrow_Client");

    node->get_parameter("money",money_);
 
	node -> send_request(money_);

	rclcpp::spin(node);

	rclcpp::shutdown();

	return 0;
}