This is the second version of my quadcopter project, which is further developed from the  [first version](https://bitbucket.org/DoanTrungNghia/quadcopterv1). There are many new aspects that are much better than that of the first version as described bellow:

- Use a more powerful micro controller ARM Cortex M4
- Use a better quadcopter frame with strong motors and high quality propellers  
- Well calibrated IMU 
-  [New IMU board design](https://bitbucket.org/DoanTrungNghia/imu-pcb-design)

**The pictures below illustrate the PCB design.**

![1.PNG](https://bitbucket.org/repo/z4zRAo/images/2519362671-1.PNG)

![2.PNG](https://bitbucket.org/repo/z4zRAo/images/3665513965-2.PNG)

![3.PNG](https://bitbucket.org/repo/z4zRAo/images/3108172442-3.PNG)

![Capture.PNG](https://bitbucket.org/repo/z4zRAo/images/138094156-Capture.PNG)
 
**The demo video is posted here:**

[demo video](https://www.youtube.com/watch?v=v4bNYTyeoJA)

**A scene cut from the demo video:**

![Capture.PNG](https://bitbucket.org/repo/az4KMR/images/3222669713-Capture.PNG)

**The user interface (using an RF module to transmit data)**

![Capture.PNG](https://bitbucket.org/repo/edEyqx/images/3524989322-Capture.PNG)

The IMU calibration process in terms of hard and soft iron noises for magnetic sensor is the implementation of [this paper](http://www.nxp.com/files/sensors/doc/app_note/AN4246.pdf). The IMU calibration process is integrated with the new user interface which is posted in the follow link: [IMU calibration demo.](https://www.youtube.com/watch?v=HDrIAQ7ofhY)

![10603387_801253693259982_7215176863128538925_n.jpg](https://bitbucket.org/repo/az4KMR/images/1338994944-10603387_801253693259982_7215176863128538925_n.jpg)
(During the IMU calibration process)