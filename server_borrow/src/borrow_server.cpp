#include <queue>
#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/u_int32.hpp"
#include "cust_interfaces/srv/sell_books.hpp"

class Server_borrow:public rclcpp::Node
{
public:
	Server_borrow(std::string name):Node(name)
	{ 
		RCLCPP_INFO(this -> get_logger(),"卖书%s服务已经开启!",name.c_str());
        using std::placeholders::_1;
        using std::placeholders::_2;
        /* 创建订阅者 */
        stock_subscribe = this->create_subscription<std_msgs::msg::String>("Stock_Books",10,std::bind(&Server_borrow::books_callback,this,_1));
        /* 创建发布者 */
        money_publish = this -> create_publisher<std_msgs::msg::UInt32>("Money",10);
		/* 创建服务 */
		server_ = this ->create_service<cust_interfaces::srv::SellBooks>("sell_server_srv",std::bind(&Server_borrow::borrow_callback_,this,_1,_2),rmw_qos_profile_services_default,callback_group_ser_);
	}
private:
    /* 声明书本订阅者 */
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr stock_subscribe;
    /* 声明货款发布者 */
    rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr money_publish;
	/* 声明服务 */
	rclcpp::Service<cust_interfaces::srv::SellBooks>::SharedPtr server_;
    /* 声明回调函数组，多线程处理防止死锁 */
    rclcpp::CallbackGroup::SharedPtr callback_group_ser_;
    /* 创建小说队列书库 */
    std::queue<std::string> books_queue;

    /* 书本进货回调函数 */
    void books_callback(const std_msgs::msg::String::SharedPtr msg)
    {
         /* ￥人民币 */
        std_msgs::msg::UInt32 money;
        money.data = 10;

        /* 货物款发出 */
        money_publish->publish(money);
        RCLCPP_INFO(this ->get_logger(),"收到了'%s书本',给了%d块钱\n",msg->data.c_str(), money.data);

        /* 把书放入书库 */
        books_queue.push(msg->data);
    }


	/* 处理请求数据 */
	void borrow_callback_(const cust_interfaces::srv::SellBooks::Request::SharedPtr request,
		const cust_interfaces::srv::SellBooks::Response::SharedPtr response)
	{
		RCLCPP_INFO(this ->get_logger(),"收到买书请求，给了￥%d块钱\n",request->money);
		unsigned int books_sum = request->money/1; //一块钱一本

        /* 查看书库是否有足够的书*/
        if (books_queue.size() < books_sum)
        {
            RCLCPP_INFO(this ->get_logger(),"目前书库有 %ld 本书，不够需求量，等待...\n",books_queue.size());

            /* 设置检查周期，1s一次*/
            rclcpp::Rate loop_rate(1);

            /* 书库数量一直小于请求数则循环*/
            while (books_queue.size()<books_sum)
            {
               if (!rclcpp::ok())
               {
                    RCLCPP_INFO(this ->get_logger(),"程序中止\n");
               }
               /* 当前书库数量和需要的数量*/
                RCLCPP_INFO(this ->get_logger(),"书库有 %ld 本书，缺少 %ld 本书\n",books_queue.size(),books_sum-books_queue.size());
                loop_rate.sleep();
            }
            RCLCPP_INFO(this ->get_logger(),"当前书库里书数量 %ld 满足\n",books_queue.size());

             /* 把书一本本取出来放入response中*/
            for (int i = 0; i < (int)books_sum; i++)
            {
                response->books.push_back(books_queue.front());
                books_queue.pop();
            }          
        }   
	}
};

int main(int argc,char ** argv)
{
	rclcpp::init(argc,argv);

	auto node = std::make_shared<Server_borrow>("Server");

	rclcpp::executors::MultiThreadedExecutor exector;
    exector.add_node(node);
    exector.spin();
    rclcpp::shutdown();
    
    //rclcpp::spin(node);

	//rclcpp::shutdown();

	return 0;
}