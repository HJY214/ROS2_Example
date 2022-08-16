#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicPublisher:public rclcpp::Node
{
    public:
    // 构造函数：创建节点并创建话题
    TopicPublisher(std::string name):Node(name)
    {
        RCLCPP_INFO(this -> get_logger()," 发布者节点 :%s 已启动!\n",name.c_str());

        common_publish = this -> create_publisher<std_msgs::msg::String>("common",10);
        //创建定时器，定时发布
        timer_ = this -> create_wall_timer(std::chrono::milliseconds(500),std::bind(&TopicPublisher::time_callback,this));

    }
    private:
    // 声明话题发布者
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr common_publish;
    //声明定时器
    rclcpp::TimerBase::SharedPtr timer_;

    void time_callback()
    {
        std_msgs::msg::String message;
        message.data = "forword";

        RCLCPP_INFO(this -> get_logger(),"Publish:%s\n",message.data.c_str());

        common_publish -> publish(message);
    }
};

int main(int argc,char ** argv)
{
    rclcpp::init(argc,argv);

    auto node = std::make_shared<TopicPublisher>("publisher_1"); 

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}
