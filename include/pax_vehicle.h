#ifndef PAX_VEHICLE_H
#define PAX_VEHICLE_H

enum class VehiclePowerType {
	PETROL,
	DIESEL,
	ELECTRIC,
};

class Vehicle {
private:
	/* Speed in kmh */
	unsigned int speed;
	
	unsigned int length;
	unsigned int width;
	unsigned int height;	// possibly unnecessary

	VehiclePowerType power_type;

	/* Power in kW */
	unsigned int power;

public:
	Vehicle();
	~Vehicle();

	// determine whether x,y should be controlled by external members
	void Initialise();
	unsigned int GetVehicleSpeed();
};

#endif