#include <chrono>
#include <rclcpp/rclcpp.hpp>

/*
    # declare_parameter            声明和初始化一个参数
    # describe_parameter(name)  通过参数名字获取参数的描述
    # get_parameter                通过参数名字获取一个参数
    # set_parameter                设置参数的值
*/

class Paramter:public rclcpp::Node
{
public:
	explicit Paramter(std::string name):Node(name)
	{
		RCLCPP_INFO(this -> get_logger(),"已初始化%s节点!",name.c_str());
        this->declare_parameter("rcl_log_level",0);        //声明参数
        this->get_parameter("rcl_log_level",log_level);    //获取参数
        /* 设置日志级别*/
        this->get_logger().set_level((rclcpp::Logger::Level)log_level);

        using namespace std::literals::chrono_literals;
        timer_ = this->create_wall_timer(500ms,std::bind(&Paramter::timer_callback,this));
	}
private:
    int log_level;
    rclcpp::TimerBase::SharedPtr timer_;
    
    void timer_callback()
    {
        this->get_parameter("rcl_log_level",log_level);
        /* 设置日志级别*/
        this->get_logger().set_level((rclcpp::Logger::Level)log_level);
        std::cout<<"======================================================"<<std::endl;
        RCLCPP_DEBUG(this->get_logger(), "我是DEBUG级别的日志,我被打印出来了!");
        RCLCPP_INFO(this->get_logger(), "我是INFO级别的日志,我被打印出来了!");
        RCLCPP_WARN(this->get_logger(), "我是WARN级别的日志,我被打印出来了!");
        RCLCPP_ERROR(this->get_logger(), "我是ERROR级别的日志,我被打印出来了!");
        RCLCPP_FATAL(this->get_logger(), "我是FATAL级别的日志,我被打印出来了!");
    }
};

int main(int argc,char ** argv)
{
	rclcpp::init(argc,argv);

	auto node = std::make_shared<Paramter>("param_node");

	rclcpp::spin(node);

	rclcpp::shutdown();

	return 0;
}