# Arduino-Rhythm-Metronome

This project is an Arduino-based rhythm with LED system. Besides common rhythm function, it allows users to record and playback rhythm patterns using two buttons. The system controls an array of 10 LEDs (1*10 LED bar) to respond the recorded rhythm pattern.

# Components and supplies
1 Arduino Uno<br>
10 LEDs (or 1 1*10 LED bar) <br>
1 Buzzer<br>
3 Buttons<br>
Wires and breadboards

# Circuit Diagram


# Actual Figure

<div align="center">
  <img src="https://github.com/okilitive/Arduino-Rhythm-Metronome/blob/main/figure/Actual%20figure1.jpg" alt="1" width="600" style="margin-right: 20px; vertical-align: middle;"/>
 
</div>
 <br>
<div align="center">
  <img src="https://github.com/okilitive/Arduino-Rhythm-Metronome/blob/main/figure/Actual%20figure2.jpg" alt="1" width="600" style="margin-right: 20px; vertical-align: middle;"/>
 
</div>

# Schematic Diagram

<div align="center">
  <img src="https://github.com/okilitive/Arduino-Rhythm-Metronome/blob/main/figure/Schematic%20diagram.jpg" alt="1" width="600" style="margin-right: 20px; vertical-align: middle;"/>
   <p>Schematic diagram of the arduino project, generated by www.tinkercad.com </p>
</div>

#Functions

This project enables two main functions for the Arduino platform.

1. Common Metronome: After connecting the device to power, pressing the metronome button (connected to the port A0) with a stable pace will trigger the buzzer to play a rhythm that matches the pace you input. This can be used as a common metronome aid to assist with music performance. Furthermore, the LED bar will display the time interval between two consecutive paces.

2. Rhythm Player: users can use two buttons (connected to ports ~2 and ~3) to record the rhythm and playback the recorded rhythm patterns on the LED bar, synchronized with the pace set by the function Common Metronome. As a beginner saxophonist, I found it difficult to read music quickly and match the rhythm of a metronome. This project addresses that challenge.
Once the rhythm is recorded, one bright point will move across the bar from this side to the other side, representing one same note on the staff. The time it takes for the bright point to travel through the LED bar reflects the duration of one same note. The steps for recording the rhythm is as follows:
   
   i> First, use the Common Metronome (Function 1) to set the base tempo. Then, press both buttons (connected to ports ~2 and ~3) simultaneously to start recording the rhythm;<br>
   ii> For clarity, pressing the button on port ~3 once is recorded as "0" (representing the separation between notes). Pressing the button on port ~2 once is recorded as "1" (representing a 1/4 beat length). These buttons are used to record the duration of each note, and pressing both buttons simultaneously again will complete the recording.<br>
   iii> Given a simple example here. The rhythm on the below staff could be recorded as "01(together) 0 1111 0 1111 0 11111111 0 11 0 1111 0 111111 01(together)" (the space is just for easily understanding). <br>
   iv> Once recording is complete, the LED bar will blink together three times, then display the recorded rhythm.<br>
<div align="center">
  <img src="https://github.com/okilitive/Arduino-Rhythm-Metronome/blob/main/figure/Demo%20staff.jpg" alt="1" width="600" style="margin-right: 20px; vertical-align: middle;"/>
   <p>Simple demo staff </p>
</div>
<br>
A demo video showcasing both functions is available, you could find it on:
https://github.com/okilitive/Arduino-Rhythm-Metronome/blob/main/figure/Demo%20video.mp4
<br>
<br>
Thanks.


