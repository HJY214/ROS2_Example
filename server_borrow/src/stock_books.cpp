#include "rclcpp/rclcpp.hpp"
#include <string>
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/u_int32.hpp"

using namespace std;

class Stock_Books:public rclcpp::Node
{
    public:
    // 构造函数：创建节点并创建话题
    Stock_Books(std::string name):Node(name)
    {
        RCLCPP_INFO(this -> get_logger()," 新华书店 :%s 已开售!\n",name.c_str());
        using std::placeholders::_1;
        /* 创建订阅者 */
        money_subscribe = this->create_subscription<std_msgs::msg::UInt32>("Money",10,std::bind(&Stock_Books::money_callback,this,_1));
         /* 创建发布者 */
        books_publish = this -> create_publisher<std_msgs::msg::String>("Stock_Books",10);

    }
    private:
    /* 书本数量 */
    int books_num = 0;
    /* 声明钱款订阅者 */
    rclcpp::Subscription<std_msgs::msg::UInt32>::SharedPtr money_subscribe;
    /* 声明书本发布者 */
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr books_publish;
    /* 声明定时器 */
    rclcpp::TimerBase::SharedPtr timer_;

    void money_callback(std_msgs::msg::UInt32::SharedPtr msg)
    {
        rclcpp::Rate loop_rate(1);

        for (unsigned int i = 0; i < msg->data; i++)
        {
            if (books_num < 1024)
            {
                std_msgs::msg::String message;
                message.data ="第" + to_string(books_num+1) + "本书";
                RCLCPP_INFO(this -> get_logger()," 已发送第：%d 本书!\n",books_num+1);
                books_publish->publish(message);
            }
            else RCLCPP_INFO(this -> get_logger()," 没有存货了！！！！！!\n");
            books_num++;
            loop_rate.sleep();
        } 
    }
};

int main(int argc,char ** argv)
{
    rclcpp::init(argc,argv);

    auto node = std::make_shared<Stock_Books>("Stock_Shop"); 

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}