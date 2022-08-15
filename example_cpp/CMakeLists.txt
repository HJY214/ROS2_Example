cmake_minimum_required(VERSION 3.8)
project(example_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo 
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

add_executable(node_1 src/node_1.cpp)
ament_target_dependencies(node_1 rclcpp)
install(TARGETS
  node_1
  DESTINATION lib/${PROJECT_NAME}
  )

add_executable(node_oop src/node_oop.cpp)
ament_target_dependencies(node_oop rclcpp)
install(TARGETS
  node_oop
  DESTINATION lib/${PROJECT_NAME}
  )

add_executable(publisher src/node_publish.cpp)
ament_target_dependencies(publisher rclcpp std_msgs)
install(TARGETS
  publisher
  DESTINATION lib/${PROJECT_NAME}
  )

