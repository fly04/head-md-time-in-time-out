# Code

The idea :
1. Arduino (accelerometer + gyroscope) send data to Processing via Serial
2. Processing send data to Wekinator (machine learning) via OSC
3. Wekinator recognize movement and send data to Processing via OSC
4. Processing send data to Arduino via Serial
5. Arduino do stuff (vibration + light)

Latest stuff :
- [Arduino: input + internal logic + output](../code/arduino/04_MPU6050_gestureRecognition/)
- [Processing: input + output](../code/processing/03_unified/)
- [Wekinator: gesture recognition](../code/wekinator/03_gestures_v3/)