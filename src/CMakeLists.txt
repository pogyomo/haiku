find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(OpenCV 4.4 REQUIRED)

add_library(${PROJECT_NAME} SHARED
    integrate.cc
    tracking.cc
    runtime.cc
)
target_link_libraries(${PROJECT_NAME}
    Eigen3::Eigen
    ${OpenCV_LIBRARIES}
)
target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/include
    PUBLIC ${OpenCV_INCLUDE_DIRS}
)
