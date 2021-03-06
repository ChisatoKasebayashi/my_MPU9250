#include <iostream>
#include <RTIMULib.h>
#include <RTIMUSettings.h>

int main(void)
{
	int sampleCount = 0;
	int sampleRate = 0;
	uint64_t rateTimer;
	uint64_t displayTimer;
	uint64_t now;
	RTIMUSettings *settings = new RTIMUSettings("RTIMULib");
	RTIMU *imu = RTIMU::createIMU(settings);

	if((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)){
		printf("No IMU found\n");
		exit(1);
	}
	imu->IMUInit();

	imu->setSlerpPower(0.02);
	imu->setGyroEnable(true);
	imu->setAccelEnable(true);
	imu->setCompassEnable(false);

	rateTimer = displayTimer = RTMath::currentUSecsSinceEpoch();

	while(1)
	{
		usleep(imu->IMUGetPollInterval() * 1000);
		while(imu->IMURead())
		{
			RTIMU_DATA imuData = imu->getIMUData();
			sampleCount++;
			now = RTMath::currentUSecsSinceEpoch();

			if((now - displayTimer) > 1000000)
			{
				printf("Sample rate %d: %s\r", sampleRate, RTMath::displayDegrees("", imuData.fusionPose));
				fflush(stdout);
				std::cout << "accel.x" << imu->getAccel().x() 
					<< "  " << imu->getIMUData().accel.x() << std::endl;
				std::cout << "accel.y" << imu->getAccel().y() 	
					<< "  " << imu->getIMUData().accel.y() << std::endl;
				std::cout << "accel.z" << imu->getAccel().z() 	
					<< "  " << imu->getIMUData().accel.z() << std::endl;


				std::cout << "gyro.x" << imu->getGyro().x() 
					<< "  " << imu->getIMUData().gyro.x() << std::endl;
				std::cout << "gyro.y" << imu->getGyro().y() 	
					<< "  " << imu->getIMUData().gyro.y() << std::endl;
				std::cout << "gyro.z" << imu->getGyro().z() 	
					<< "  " << imu->getIMUData().gyro.z() << std::endl;



				displayTimer = now;
			}

			if((now - rateTimer) > 1000000)
			{
				sampleRate = sampleCount;
				sampleCount = 0;
				rateTimer = now;
			}
		}
	}

	return 0;
}

