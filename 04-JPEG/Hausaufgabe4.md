### MMSS2021
# 4. Hausaufgabe - JPEG

### Aufgabe
Stellen Sie die Terminalanwendung aus der Live-Veranstaltung zur Kompression eines Bitmap-Bildes fertig, wenn noch nicht geschehen. Damit der Lauflängenkodierer _Honkpacker_ effektiv arbeiten kann, soll das Bild zunächst mit Hilfe der DCT (_Discrete Cosine Transform_) transformiert, anschließend mit einer geeigneten Quantisierungsmatrix quantisiert und schlussendlich ZigZag-codiert werden. Nutzen Sie dazu die [Guideline](guideline.md) aus der Live-Veranstaltung.

Implementieren Sie des Weiteren die Dekompression. Zur Auswahl zwischen Kompression und Dekompression dienen die Kommandozeilenparameter `-c` bzw. `-d` (siehe [main.c](code_01/main.c)).

Außerdem soll über den `-q`-Parameter ein ganzzahliger Prozentwert zwischen 1 und 100 angegeben werden können (Qualitätsparameter α aus der Vorlesung), der bei der Kompression und Dekompression berücksichtigt wird.

Die Hausaufgabe ist in Gruppen (idR. 3 Personen) zu bearbeiten. Die Hausaufgaben-Gruppen sind zugleich die Projektgruppen für die Prüfungsleistung.

Legen Sie Wert auf eine gute Dokumentation Ihres Codes (Kommentare), saubere Formatierung und einheitlichen Stil.

### Bonus
Optimieren Sie Ihren Code in Bezug auf Performance. Implementieren Sie dazu Lookup Tables (LUT), um die Cosinuswerte in der DCT bzw. IDCT vorzuberechnen. Benchmarken Sie Ihre Ergebnisse im Vergleich zur naiven Version, die den Cosinus in jedem Schritt neu berechnet.

### Bonus-Bonus
Parallelisieren Sie Ihr Programm unter Zuhilfenahme von Threads (wir empfehlen `OpenMP`). Bitte achten Sie darauf, Race Conditions zu vermeiden! Dazu bietet es sich an, die jeweiligen Ausgaben zunächst im RAM zu puffern und erst am Schluss in eine Datei zu schreiben.

### Abgabe
Die Hausaufgabe muss bis zum 08.06.2021 23:59 Uhr per Mail an [treumer@tu-freiberg.de]() gesendet werden, wenn sie gewertet werden soll. In den Anhang der Mail kommen ihre .c/.h Datei. Wenn Sie mehrere Quellcode-Dateien senden wollen, packen Sie diese bitte in ein zip-Archiv. Ein Makefile ist gern gesehen ;)

Als Betreff ist folgendes anzugeben:

_MMSS2021 4. Hausaufgabe_

Geben Sie in der Mail unbedingt alle Gruppenmitglieder an. Die Gruppen sollten sich ab der Abgabe der ersten Hausaufgabe nicht mehr ändern.
