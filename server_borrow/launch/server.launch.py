# 导入库
from launch import LaunchDescription    #描述文件内容
from launch_ros.actions import Node     #声明节点所在位置
from ament_index_python.packages import get_package_share_directory
import os.path

# 定义函数名称：generate_launch_description
def generate_launch_description():
    ld = LaunchDescription()
    server_dir = get_package_share_directory('server_borrow')
    params_path = os.path.join(
    server_dir,
    'config',
    'param.yaml'
    )
    #创建Action.Node对象，标明Node位置
    server_node = Node(
        package="server_borrow",
        executable="borrow_server",
        output='screen',
        parameters=[params_path]
        #parameters=[{"book_price":2}]
    )
    stock_node = Node(
        package="server_borrow",
        executable="stock_books",
    )
    # 创建LaunchDescription对象launch_description,用于描述launch文件
    # launch_description = LaunchDescription([server_node,stock_node])
    ld.add_action(server_node)
    ld.add_action(stock_node)

    # 返回让ROS2根据launch描述执行节点
    return ld