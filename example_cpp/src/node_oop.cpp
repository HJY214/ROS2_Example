#include <rclcpp/rclcpp.hpp>

class Node_1:public rclcpp::Node
{
public:
	Node_1(std::string name):Node(name)
	{
		RCLCPP_INFO(this -> get_logger(),"大家好，我是%s节点！",name.c_str());
	}
private:
};

int main(int argc,char ** argv)
{
	rclcpp::init(argc,argv);

	auto node = std::make_shared<Node_1>("node_oop");

	rclcpp::spin(node);

	rclcpp::shutdown();

	return 0;
}