#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicPublisher:public rclcpp::Node
{
    public:
    // 构造函数：创建节点并发布话题
    TopicPublisher(std::string name):Node(name)
    {
        RCLCPP_INFO(this -> get_logger()," 发布者节点 :%s 已启动!\n",name.c_str());

        common_publish = this -> create_publisher<std_msgs::msg::String>("common",10);
    }
    private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr common_publish;
};

int main(int argc,char ** argv)
{
    rclcpp::init(argc,argv);

    auto node = std::make_shared<TopicPublisher>("publisher_1");

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}
