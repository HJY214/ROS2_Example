# 导入库
from launch import LaunchDescription    #描述文件内容
from launch_ros.actions import Node     #声明节点所在位置
from ament_index_python.packages import get_package_share_directory
import os.path

# 定义函数名称：generate_launch_description
def generate_launch_description():
    ld = LaunchDescription()
    stock_dir = get_package_share_directory('server_borrow')
    params_path = os.path.join(
    stock_dir,
    'config',
    'param_stock.yaml'
    )
    #创建Action.Node对象，标明Node位置
    shop_node = Node(
        package="server_borrow",
        executable="borrow_client",
        output='screen',
        parameters=[params_path]
    )
    # 创建LaunchDescription对象launch_description,用于描述launch文件
    # launch_description = LaunchDescription([server_node,stock_node])
    ld.add_action(shop_node)

    # 返回让ROS2根据launch描述执行节点
    return ld