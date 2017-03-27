#include <iostream>
#include <RTIMULib.h>
#include <RTIMUSettings.h>

int main(void)
{
	RTIMUSettings *settings = new RTIMUSettings("RTIMULib");
	RTIMU *imu = RTIMU::createIMU(settings);

	if((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)){
		printf("No IMU found\n");
		exit(1);
	}
	imu->IMUInit();

	return 0;
}

