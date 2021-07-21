### Guideline - Softwareprojekt Multimedia SS2021


1. Programmierung
  * Programmiersprache offen (C, C++, C#, Java, Swift, Kotlin, Python...)
  * Vorzugsweise _"bare metal"_
  * Multimediabezug!
  * Rücksprache mit uns bei Bibliotheks/Frameworknutzung (glut, glew, glfw zulässig)
  * Betriebssystem nicht vorgeschrieben (vorzugsweise unixioid)
  * bei Problemen: Rücksprache mit uns halten!
  * Abgabe als Sourcecode inkl. _"Bauanleitung"_ (README, Abhängigkeiten, makefile, cmake, ...), bereinigt von Build-Artefakten und unnötigen Binärdateien (.o-Dateien etc)
  * gut strukturierter und kommentierter Quellcode ist wichtig!
  * Speicherfehler vermeiden (bei Sprachen ohne garbage collector); gcc/clang mit -fsanitize=address; -fsanitize=leak; -fsanitize=undefined hilfreich (nur debug, nicht release builds); valgrind
 
> Hoffentlich unnötig zu erwähnen: Kopiert nicht einfach ein bestehendes Projekt aus dem Netz und ändert 2-3 Zeilen Code / Variablen / Funktionsnamen - das bekommen wir mit. Wir hatte schon solche Fälle in der Vergangenheit, die dann mit 5.0 benotet werden mussten. Das wäre sehr schade. Wenn ihr euch an einem bestehenden Projekt orientiert, kennzeichnet das sehr deutlich! Wir wollen Eigenleistung sehen. Wenn ihr ein bestehendes Projekt nehmt und erweitert, dann sind die Anforderungen höher, als wenn ihr _from scratch_ eine eigene Anwendung entwickelt. Beides kann sehr gut werden.
  
2. Ausarbeitung/Dokumentation
  * Zitation!!!
  * Umfang: 8-15 Seiten (normaler Zeilenabstand, nicht 1.5fach, skaliert mit Gruppengröße)
  * Abgabe als PDF (kein docx, doc etc.)

  - Codedokumentation
     * Grobstruktur des Projekts erläutern (ggf. Klassendiagramm)
     * ausgewählte, kritische Codeteile erläutern
     * ggf. Speichermanagement? Design Pattern? ...
  - Projektdokumentation
     * Dokumentation der Arbeitsweise
     * Aufteilung der Arbeit auf Gruppenmitglieder
     * genutzte Tools, Entwicklungsumgebung
     * ggf. mathematische/theoretische Grundlagen zum Projekt
  - Benutzerhandbuch
     * kleine Anleitung aus Benutzersicht (ggf. Use Cases)
     * ggf. Anwendungsbeispiel

3. Abgabe Ausarbeitung
  * Anfang Vorlesungszeit __WS2021/2022__ (Gruppen, die ihre Note dieses Semester (SS2021) benötigen, bitte noch einmal separat einen Termin per Mail mit uns vereinbaren!)
  * Code und Ausarbeitung an _treumer@tu-freiberg.de_
  * Betreff: __MMSS2021 Projekt__
  * Angabe der Gruppenmitglieder + Matrikelnummern

4. Präsentation
  * Zitation!!!
  * Anfang Vorlesungszeit __WS2021/2022__ (1-2 Wochen nach Abgabe der Ausarbeitung)
  * 1. oder 2. Vorlesungswoche (Gruppen, die ihre Note dieses Semester (SS2021) benötigen, bitte noch einmal separat einen Termin per Mail mit uns vereinbaren!)
  * vor allen Kursteilnehmern
  * 20-30 min
  * _"jeder soll etwas sagen"_
  * Demonstration der Software
  * Grobstruktur Code
  * Erläuterung kritischer Codeteile
  * Probleme während der Entwicklung
  * im Grunde kurze Zusammenfassung der Ausarbeitung
  * Grafiken!
