# ProjektSmartHome
 skole projekt Af Casper Wind

I dette projekt skal jeg lave IOT til mit hus.
<ul>
<li>Tempratur måler til soveværlset ✔</li>
<li>RGB lys til børneværlset✔</li>
<li>Kodelås til vinkælderen❌</li>
</ul>

# Indhold


- [ProjektSmartHome](#projektsmarthome)
- [Indhold](#indhold)
- [HIPO](#hipo)
- [switchMux](#switchmux)
- [Interrupt ISR(ADC_vect)](#interrupt-isradc_vect)
- [Tempratur måler til soveværlset](#tempratur-måler-til-soveværlset)
    - [Opsætning ef tempratur måler og motor.](#opsætning-ef-tempratur-måler-og-motor)
    - [Opsætning af termometer.](#opsætning-af-termometer)
- [RGB lys til børneværlset](#rgb-lys-til-børneværlset)
    - [opsærning af joystik.](#opsærning-af-joystik)
    - [opsætning af RGB pære](#opsætning-af-rgb-pære)


# HIPO
![HIPO](Hipo.png)


# switchMux

# Interrupt ISR(ADC_vect)

# Tempratur måler til soveværlset


Den måler tempratueren og starter en motor når tempratueren kommer over 25 grader.
Og stopper igen når den kommer under 23 grader.

Hvis du ønsker at lave om på hvornår den begynder og stopper så skal det laves om i koden, Fil temp.c

```
if (TempC > 25) // tjekker om tempraturen er over 25 grader. og starter motoren hvis det er over.
	{
		OCR3A = 255;
	}
	if (TempC < 23) // tjekker om tempraturen er under 23 grader og slukker for motoren hvis det er under.
	{
		OCR3A = 0;
	}
```
Den skal lave nogen beregninger for at finde ud af hvad tempraturen er. Den modtaer en ```ADC``` fra ``` ISR(ADC_VECT) ``` som den omregner med føglene regne stykke:
```
    ADC_voltage = 5.0 * ADC_data / 1024.0;
	temp = log(10000.0 * (1024.0 / ADC_data -1));
	tempK = 1/(0.001129148+(0.000234125+(0.0000000876741*temp*temp))*temp);
	tempC = tempK - 273.15; 
```
til sidst bliver ```tempC``` sendt til ```StartOrStopMotor(float TempC)``` som ser på ```tempC``` og hvis ```tempC``` er over 25 grader så starter motoren. Og hvis der er under 23 grader så stopper motoren.

### Opsætning ef tempratur måler og motor.

motoren skal sættes op sådan her.

Nu skal L293D Chip på. Og det er meget VIGTIGT at den vender som den skal. Der er et lille hak øverst på chippen og så er ben nummer 1 til venstre for det hak så kan vi tælle. Der skulle meget gerne være 16 ben. 

![Motor setup](motorsetup.png)

Ben 16 til 5v.

Ben 15 til selve ardrorino bordet i dette projekt skal den hen til pin 5.

14 til +siden af motoren og fra motoren til jord. Og imellem motoren og jord skal der en diode som pejer ind mod ben 14.

13 og 12 skal til jord.

11 og 10 skal vi ikke gøre noget med.

Ben 9 til 5v.

### Opsætning af termometer.

termometeret skal sættes op sådan her.

![termometersetup](termometersetup.png)

den ledning som skal til adrorino bordet sider i mit projekt i pin A0. det er vigtigt at den sider i en analo port da den sender et analogt signal som skal om regnes til digitalt med en ADC.

det der sker i programmet er at den termimst som sider på bordet. laver en modstand som ADC'en fanger og om regner til tempraturen.


# RGB lys til børneværlset

Det består af et joystik og en RGB pære. Hvor pæren skifter farve alt efter hvordan man stiller på joystikket.

Joystikket har en x og en y akse, som ændre verdien den sender til ADC'en. Derfor skal der være 2 porte som er analog porte. Så i dette projekt har jeg valgt at køre med de 2 porte PF1(PINA1) og PF2(PINA2). vi tager udgangs punkt i yaksen. den modtager en ```ADC``` verdi fra ```ISR(ADC_VECT) ```  som læses i ```ReadY(int YADC)``` hvor verdien ```YADC``` bliver divideret med 4 da vi skal ned på 255 som OCRX køre på og ADC køre mellem 0 og 1023. så for at får det til at stemme over ens skal det dividers med 4. og der ved kan vi styre lyset mellem 0 og 255 med joystikket.

### opsærning af joystik.

her vises opsætningen af joystikket.

![joystik](joystik.png)

GND --> Jord. (Sort Ledning)\
+5V --> 5V. (Hvid ledning)\
VRx --> PINA2 (gul ledning)\
VRy --> PINA1 (Orange ledning)\
SW --> PIN2 (Blå ledning)

### opsætning af RGB pære

Her vises opsætning af RGB pæren

![RGB](RGB.png)

Det er <B>meget</B> vigtigt at der er modstande med 220 Ω ellers ødelægger du RGB pæren.

Den har 4 ben som ses på billedet. den længeste ben er jord. 
de andre skal sættes op som på billedet.\
Her er et billede af min opsætning

![RGBLive](RGBLive.png)

