#include "rclcpp/rclcpp.hpp"


/*	1.导入库文件
	2.初始化客户端库
	3.创造ROS2节点
	4.spin循环节点
	5.关闭客户端库
*/

int main(int argc,char ** argv)
{
	
	rclcpp::init(argc,argv);//初始化rclcpp

	auto node = std::make_shared<rclcpp::Node>("node_1");//创造节点

	RCLCPP_INFO(node -> get_logger(),"node_1 节点已经启动！");

	rclcpp::spin(node);//运行节点，检测到Ctrl+C后退出

	rclcpp::shutdown();//停止运行

	return 0;
}

