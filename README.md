# MS5611 Sensor Driver

This repository contains a platform-independent C API for the TE Connectivity MS5611 sensor. The driver facilitates communication via SPI or I2C, calibration, and raw data transformation.

## Features

- **Raw Data Transformation**: Handle transformation of raw sensor data.
- **Adaptive Settings**: Adjusts to changed settings dynamically.
- **SPI/I2C Communication**: Supports both communication protocols.

## Updates and Bug Reports

For updates and to report bugs, visit: [GitHub Repository](https://github.com/Berkin99/MS5611)

## Usage

### Initialization

To create and initialize a new MS5611 device instance:

```c
MS5611_Device_t ms5611_device = MS5611_NewDevice(interface, MS5611_INTF_I2C, read_function, write_function, delay_function);

```

### Functions Overview

- **MS5611_Init**: Initializes the MS5611 device.
- **MS5611_Test**: Performs a self-test on the device.
- **MS5611_Reset**: Resets the MS5611 device.
- **MS5611_GetData**: Retrieves processed temperature and pressure data.
- **MS5611_RawDataProcess**: Processes raw ADC data to calculate temperature and pressure.

## References

- [Datasheet](ENG_DS_MS5611-01BA03_B3.pdf)
