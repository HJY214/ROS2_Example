cmake_minimum_required(VERSION 3.8)
project(server_borrow)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(cust_interfaces REQUIRED)

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

add_executable(borrow_server src/borrow_server.cpp)
ament_target_dependencies(borrow_server rclcpp cust_interfaces std_msgs)
install(TARGETS
  borrow_server
  DESTINATION lib/${PROJECT_NAME}
  )

add_executable(stock_books src/stock_books.cpp)
ament_target_dependencies(stock_books rclcpp std_msgs)
install(TARGETS
  stock_books
  DESTINATION lib/${PROJECT_NAME}
  )

add_executable(borrow_client src/borrow_client.cpp)
ament_target_dependencies(borrow_client rclcpp std_msgs cust_interfaces)
install(TARGETS
  borrow_client
  DESTINATION lib/${PROJECT_NAME}
  )

ament_package()
