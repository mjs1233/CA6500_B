#pragma once
#include <vector>
#include <memory>
#include "ExternalDevice.h"

class ExternalDeviceControl
{
private:
	std::vector<std::unique_ptr<ExternalDevice_Base>> externalDevices;
public:
	void addExternalDevice(std::unique_ptr<ExternalDevice_Base>& device)
	{
		externalDevices.push_back(std::move(device));
	}


	void execute(PIN& pin)
	{
		for (auto& device : externalDevices)
		{
			device->execute(pin);
		}
	}
};