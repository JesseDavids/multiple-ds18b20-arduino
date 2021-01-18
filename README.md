# MULTIPLE DS18B20 SENSORS ON A ONE-WIRE BUS
created by Jesse Davids.

**This project features multiple ds18b20 temperature sensors, all on a one wire bus. All sensors are identified by their unique serial number, accompanied by their sensor value. This data is sent to a web server, posted as JSON on a webpage. You can retrieve the data sent to the webpage into your network management software, graph it out and boom. Done.**

<h2>What you need to consider</h2>
  
* This repo supports only the DS18B20, other sensors have not yet been tested. You can feel free to do so.
* You will need a pull-up resistor, i used a 5K ohm resistor.
* Alter code to use up to 18 sensors.

<h2>Please check the pictures folder for a better understanding of the whole set-up</h2>


<h1>Sensor modification</h1>
1. We took old telephone cable and soldered it onto the sensor. On the other end of the cable we added a RJ45 connector. </br>
    ![Sensor RJ45 cable](DS18B20 project images/IMG_3486.jpg)
3. Took a piece of patch panel apart and connected it in-line with the RJ45 connector of the sensor. </br>
    ![Patch panel on the right](DS18B20 project images/IMG_3478.jpg)
    ![Board in the upper-middle](DS18B20 project images/IMG_3479.jpg)
    ![Pull-up resistor](DS18B20 project images/IMG_3486.jpg)
4. Added everything into a housing after testing. </br>
    ![Final product](DS18B20 project images/View recent photos.png)



<h3>What the output should look like</h3>

![alt text](fridgeproject.png)
