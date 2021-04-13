#1. Hausaufgabe - Bitmap-Manipulation

###Aufgabe

Erstellen Sie eine Terminalanwendung, die eine Bitmap-Datei einliest, die Helligkeit des Bildes verändert (Aufhellen oder Abdunkeln) und das manipulierte Bild mit neuem Namen speichert.

Nutzen Sie dazu die in der Vorlesung vorgestellte Bitmap-Bibliothek. Die Bibliothek können Sie hier finden: [https://github.com/EndoplasmaticReticulum/bitmap](https://github.com/EndoplasmaticReticulum/bitmap)

Die Hausaufgabe ist in Gruppen (idR 3 Personen) zu bearbeiten. Die Hausaufgaben-Gruppen sind zugleich die Projektgruppen für die Prüfungsleistung.

Legen Sie Wert auf eine gute Dokumentation Ihres Codes (Kommentare), saubere Formatierung und einheitlichen Stil.

###Bonus
Erlauben Sie dem Nutzer folgende Angaben als Kommandozeilenparameter an Ihr Programm zu übergeben:

- die zu manipulierende Bitmap-Datei
- einen Parameter, der dem Programm sagt, dass eine Helligkeitsveränderung stattfinden soll
- gefolgt von einem Wert zwischen -100 (Abdunkeln) und +100 (Aufhellen), der angibt, wie stark und in welcher Richtung die Änderung vorgenommen werden soll.

Ein vollständiger Aufruf könnte dann etwa so aussehen (b steht für Brightness):

```
$ ./bitmap /home/user/pictures/myfancypic.bmp b +50
$ ./bitmap /home/user/another.bmp b -35
```

Passen Sie den Namen des manipulierten Bildes an, sodass man ihm ansieht, welche Manipulation durchgeführt wurde. zB.:

_myfancypic\_darker\_25.bmp_

_another\_lighter\_10.bmp_

________

###Bonus-Bonus
Erstellen Sie eine Terminalanwendung, die 2 Bitmap-Dateien und einen Zahlenwert (Alphablending-Faktor) als Kommandozeilenparameter übergeben bekommt. Die beiden Bilder sollen mit Hilfe von Alphablending übereinandergelegt werden. Das Ergebnis soll als neue Bitmap abgespeichert werden.

###Abgabe
Die Hausaufgabe muss bis zum 06.05.2020 23:59 Uhr per Mail an [treumer@tu-freiberg.de]() gesendet werden, wenn sie gewertet werden soll. In den Anhang der Mail kommen ihre .c/.h-Dateien und ggf. ein Makefile. Wenn Sie mehrere Quellcode-Dateien senden wollen, packen Sie diese in ein zip-Archiv. Sie können natürlich auch die Versionsverwaltung ihrer Wahl verwenden und einen Link senden. Bitte versenden Sie keine ausführbaren Dateien, da diese vom Email-Filter verworfen werden.

Als Betreff ist folgendes anzugeben:

_MMSS2021 1. Hausaufgabe_

Geben Sie in der Mail unbedingt **alle Gruppenmitglieder und Matrikelnummern** an. Die Gruppen sollten sich ab der Abgabe der ersten Hausaufgabe nicht mehr ändern.