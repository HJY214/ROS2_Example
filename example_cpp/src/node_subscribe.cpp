#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicSubscribe:public rclcpp::Node
{
    public:
    // 构造函数：创建节点并创建话题
    TopicSubscribe(std::string name):Node(name)
    {
        RCLCPP_INFO(this -> get_logger()," 订阅者节点 :%s 已启动!\n",name.c_str());

        common_subscribe = this -> create_subscription<std_msgs::msg::String>("common",10,std::bind(&TopicSubscribe::sub_callback,this,std::placeholders::_1));
       
    }
    private:
    // 声明话题订阅者
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr common_subscribe;

    void sub_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        double speed = 0.0f;
        if(msg -> data == "forword")
        {
            speed = 0.2f;
        }
        RCLCPP_INFO(this -> get_logger(),"收到指令:%s,输出小车速度%f\n",msg->data.c_str(),speed);
    }

};

int main(int argc,char ** argv)
{
    rclcpp::init(argc,argv);

    auto node = std::make_shared<TopicSubscribe>("subscriber_1"); 

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}
