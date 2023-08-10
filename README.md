# Bar Mitzvah Shield
## What is a Bar Mitzvah?
A Bar Mitzvah is a Jewish rite of passage where a boy becomes a man in the eyes of Jewish talmudic law. A Bar Mitzvah student leads part of the Saturday morning service, consisting of reading from the holy book (Torah), reciting/singing from scriptures (Haftarah), and delivering several speeches and a sermon.

I completed my Bar Mitzvah in my [conservative](https://www.myjewishlearning.com/article/conservative-judaism-how-the-middle-became-a-movement/) synagogue at the age of 13 (conservative being a semi-strict Jewish branch, not an economic ideology). As the eldest child, I set the standard for my siblings to go above and beyond with extra prayers during the Bar Mitzvah service. Per custom, the congregation threw candy at me after I finished a 10 minute chanting of a Hebrew scripture. As a personal form of amusement, I wore a riot helmet as I was pelted with Bit-O-Honey.

<p align="center">
<img width=200 src=images/bit-o-honey.png alt=Bit-O-Honey>
</p>
<center><em>If God made a candy even</em> he <em>couldn't break.</em></center>

## Shield of Daniel
When my brother Daniel's Bar Mitzvah rolled around several years later, he wanted something above and beyond as well. To block the candy, he crafted a wooden shield with a Jewish Star in the center. The humor is not lost on Hebrew-speaking people when the Jewish Star (known as the "Shield of David") is superglued on a shield for a child's Bar Mitzvah.

<p align="center">
<img width=50% src=images/shield-of-daniel.jpeg alt="Shield of Daniel">
</p>

*Shield of Daniel*

In a moment of "divine inspiration", I wondered how easy it could be to count how many candies were deflected by the shield.

### Engineering Parts
- 1 Arduino Nano
- 5 100KΩ resistors
- 1 3.7V LiPo Battery
- 1 DC voltage boost converter
- 1 TM1637 LED digit counter
- 5 Piezo ceramic wafer plates
- 1 Push-button

I took a deep dive into piezoelectricity several months prior to this project, and I was excited to finally have an applied project for this fascinating phenomenon. I will be using manufactured piezoelectric ceramic wafers instead of quartz crystals, but the piezoelectric process is essentially the same.
#### Piezoelectricity - Quartz
Piezoelectricity occurs when physical pressure is converted to an electric charge. Quartz is a beautiful example of piezoelecricity: when a precisely angled cut of quartz is struck, it releases voltage. One interesting quality of quartz is that every time it is struck with the same force, it releases the same voltage every time. This is why quartz is used in elecronic oscillators, clocks, and watches. 

<p align="center">
<img src=images/silicon-dioxide.gif alt="Silicon Dioxide">
</p>

*This is how silicon dioxide materials (e.g quartz) create DC voltage with pressure*

### Physical Routing

<p align="center">
<img width=50% src=images/shield-bb.jpg alt="Fritzing Model">
</p>

The Piezo wafer sensors are connected to the analog ports to provide different feedback for various pressures. I also attached a 100KΩ resistor to each wafer to prevent damage to the Nano. I used whatever large-load resistors were lying around, but I recommend 1MΩ for future projects.

I used [this](https://www.amazon.com/MakerFocus-Discharge-Integrated-Charging-Protection/dp/B07PZT3ZW2/) boost converter in my project because of its battery charging capabilities bundled with a pretty cool battery indicator. I desoldered the "key" button and bridged the connection with the push-button to allow turning on and prevent powering off.

### Code

This is the first completed project where I used a C++ class in a practical scenario. Although OOP wasn't necessary, it was interesting to complete. The code is in `shield.ino` with ample comments to set you on your way. :)

### Images
## Images
<p align="center">
<img width=50% src=/assets/files/bar-mitzvah/unconnected.jpg alt="Exposed">
</p>
<center><em>Sensor Placement</em></center>

<p align="center">
<img width=50% src=/assets/files/bar-mitzvah/cardboard.jpg alt="Covered">
</p>
<center><em>Final Product</em></center>

<em>Shield Sensors Demo (2 candies thrown simultaneously)</em>

### Final Thoughts
The shield detected a total of 44 candies during his service. My brother got recognition of having the coolest and most well thought out Bar Mitzvah candy blocker in the synagogue. Sure, other children had tennis raquets or fly swatters, but they all cower at the might of Daniel's mighty Shield!

Could I have used a better wiring system? Were the wire solder connections exposed? Could I have aesthetically made it much prettier and safer? Yes to all these questions. I had the idea to create an impact-sensor shield with a built in counter a week before the Bar Mitzvah began, and I managed to finish it the night before. I am amazed I could even finish on time, let alone it working as well as it did.
