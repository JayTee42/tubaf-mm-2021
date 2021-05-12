### MMSS2020
# 3. Hausaufgabe - Kompression

### Aufgabe

Erstellen Sie eine Terminalanwendung, die in der Lage ist, das in der Vorlesung / Übung vorgestellte *honk*-Format zu packen und zu entpacken. Als Parameter ist eine Option (Kompression vs. Dekompression) zu übergeben. Die Ein- und Ausgabe soll über *stdin* / *stdout* erfolgen.

Kurze Dokumentation des Formats:

 - Die gepackte Datei setzt sich aus heterogenen und homogenen Gruppen zusammen.
 - Jede Gruppe beginnt mit einem Statusbyte:
   - Das höchstwertige Bit bestimmt, ob es sich um eine heterogene (0) oder homogene (1) Gruppe handelt.
   - Die unteren sieben Bit geben die Anzahl *l* der Bytes in der Gruppe an. Sie sollte zwischen 1 und 127 liegen.
 - Für heterogene Gruppen folgen nun *l* Bytes, die nicht weiter komprimiert sind und direkt in die Ausgabe geschrieben werden können. In ihnen sollten keine benachbarten gleichen Bytes auftreten (sie ließen sich sonst durch eine homogene Gruppe ersetzen).
 - Für homogene Gruppen folgt ein einzelnes Musterbyte. Es muss *l*-mal in die Ausgabe geschrieben werden.

Beispiel:

    0x03 0xAB 0xAC 0xAD | 0x86 0x2A | 0x01 0x00

- Zunächst tritt eine heterogene Gruppe mit drei Bytes auf. In die Ausgabe wird geschrieben:

        0xAB 0xAC 0xAD

- Nun folgt eine homogene Gruppe. Das Byte 0x2A wird sechsmal in die Ausgabe geschrieben:

        0x2A 0x2A 0x2A 0x2A 0x2A 0x2A

- Am Schluss steht eine weitere heterogene Gruppe, die ein Byte umfasst. Es wird ausgegeben:

        0x00

Insgesamt folgt also:

    0xAB 0xAC 0xAD 0x2A 0x2A 0x2A 0x2A 0x2A 0x2A 0x00

Um Ihr Programm zu testen, finden Sie im Downloadbereich einige Beispieldateien und ihre gepackten Pendants. Stellen Sie sicher, dass Ihr Programm die gleichen Ausgaben liefert. Dies lässt sich komfortabel per Hashing verifizieren:

    openssl md5 <testfile>
    bzw.
    md5sum <testfile>
    ...

Die Hausaufgabe ist in Gruppen (idR. 3 Personen) zu bearbeiten. Die Hausaufgaben-Gruppen sind zugleich die Projektgruppen für die Prüfungsleistung.

Legen Sie Wert auf eine gute Dokumentation Ihres Codes (Kommentare), saubere Formatierung und einheitlichen Stil.

### Bonus

Erweitern Sie Ihr Programm um eine Fortschrittsanzeige (in Prozent) für die Kompression und die Dekompression. Dafür könnte das *honk*-Format um einen Header erweitert werden.

### Abgabe

Die Hausaufgabe muss bis zum 25.05.2020 23:59 Uhr per Mail an [treumer@tu-freiberg.de]() gesendet werden, wenn sie gewertet werden soll. In den Anhang der Mail kommt ihre .c/.h Datei. Wenn Sie mehrere Quellcode-Dateien senden wollen, packen Sie diese bitte in ein zip-Archiv. Ein Makefile ist gern gesehen ;) ...

Als Betreff ist folgendes anzugeben:

_MMSS2021 3. Hausaufgabe_

Geben Sie in der Mail unbedingt alle Gruppenmitglieder an. Die Gruppen sollten sich ab der Abgabe der ersten Hausaufgabe nicht mehr ändern.
