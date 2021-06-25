# BOF (Bling_On_ofF)

Arduino library for playing with relay, LED, and other On/OFF.

## Description
BOF (Bling_On_ofF) is an small Arduino library for relay, LED, and other On/OFF thing. 

Void for the moment :
- on(); to turn on the relay (reprend le bling s'il y a);
- off(); to turn off (concerve le rythme bling);
- bling(float offduration,float onduration,float offduration) ; variables en sec si BMP activé sinon en ms) ; rythme toujours en fond de tache même si desactivé par blingOff() voir ci-dessous)
- blingOff(); stoppe le bling (permettant d'avoir une led allumée en permanence par exemple) ; relance un void bling() pour relancer bling  
- fade(float); for a fadein the float must be >1 ; for fadeout this float must be between 1 and 0 
- isEnable(); active les commandes
- isDisable(); desactive les commandes
- isPause(); fait passer de on<>off
- BPM(); rythme le void bling() 
- process(); must be call all time

## Examples
See examples files
and/or this video :

[![BOF in action #1](https://i.ytimg.com/vi/xCYlpEabitc/mqdefault.jpg)](https://www.youtube.com/embed/xCYlpEabitc)

## Copyright
Read license.txt
