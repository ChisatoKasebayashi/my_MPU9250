project(my_MPU9250)

add_subdirectory(RTIMULib)
SET(MYSRC
	main.cpp
	)
include_directories(
	RTIMULib
	)
link_directories(
	RTIMULib
	)

add_executable(MPU9250
	${MYSRC}
	)

target_link_libraries(MPU9250
	RTIMULib
	)
