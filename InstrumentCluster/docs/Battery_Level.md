# Battery Level Calculation
The Piracer runs on three Sanyo 18650 lithium-ion batteries. Usually, the battery level of a lithium-ion battery is a complex function of the battery's state of charge (SOC) and the battery's voltage. 
Unfortunately, the Piracer's battery controller does not provide a SOC value. The only information we have is the current voltage in V and the current in mA. 
To get a rough estimate of the battery level, we can use the voltage measurement and reference discharging curve of the battery from [LiIon batteries](https://lygte-info.dk/info/BatteryChargePercent%20UK.html). 

#Todo: details on algorithm
