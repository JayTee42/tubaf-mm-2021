# Modul "Multimedia" 2021 (TUBAF)

## Inhalte

| Woche               | Thema                     | Material                                                                  |
| :------------------ | :------------------------ | :------------------------------------------------------------------------ |
| 05. - 09. April     | Einführung, Terminplanung | [Folien](https://github.com/JayTee42/tubaf-mm-2021/blob/main/00-Einfuehrung/Formal.pdf) |
| 12. - 16. April     | Farbräume, Bildverarbeitung| [Vorlesung](https://youtu.be/kBZoBG6i1Vc), [Mitschnitt](https://teach.informatik.tu-freiberg.de/playback/presentation/2.0/playback.html?meetingId=582e5bc54d5449187b47904734197edf2dffad4b-1618401121075), [Folien](https://github.com/JayTee42/tubaf-mm-2021/blob/main/01-Farbmodelle/vl01.pdf), [Code (Dithering)](https://github.com/JayTee42/tubaf-mm-2021/tree/main/01-Farbmodelle/code_01), [Bitmap-Bibliothek](https://github.com/JayTee42/bitmap), [Hausaufgabe](https://github.com/JayTee42/tubaf-mm-2021/blob/main/01-Farbmodelle/Hausaufgabe1.md)|
| 26. - 30. April     | SIMD                       | [Vorlesung](https://www.youtube.com/watch?v=2AjGdW9XGAQ), [Mitschnitt](https://teach.informatik.tu-freiberg.de/playback/presentation/2.0/playback.html?meetingId=582e5bc54d5449187b47904734197edf2dffad4b-1619611035082), [Folien](https://github.com/JayTee42/tubaf-mm-2021/blob/main/02-SIMD/vl02.pdf), [Hausaufgabe](https://github.com/JayTee42/tubaf-mm-2021/blob/main/02-SIMD/Hausaufgabe2.md) |

> Die nächte Veranstaltung findet am 12.05.2021 ab 14 Uhr statt (Programmierübung zu Kompression)

## Ablauf

Liebe MM-Teilnehmer/-innen,

aufgrund der Corona-Pandemie findet Multimedia in diesem Semester in digitaler Form statt. Dazu treffen wir uns stets [in diesem BBB-Raum](https://teach.informatik.tu-freiberg.de/b/jon-9z6-k3j). Nähere Details zum Ablauf und zur Terminplanung sprechen wir in der ersten Veranstaltung (Dienstag, 06. April, 09:30 Uhr) mit Euch ab.

Für Ankündigungen, Terminänderungen etc. werden wir grundsätzlich dieses GitHub-Repo sowie (in dringenden Fällen) eine Mailingliste nutzen, die in der Einführungsveranstaltung initiiert wird. Der OPAL-Kurs wird nicht weiter aktualisiert werden.

Und noch eine Bitte von unserem Administrator: Wenn Ihr Euch im BBB registriert (kein Zwang), verwendet bitte Eure Unimail-Adresse, damit Ihr nicht fälschlicherweise als Spam eingeordnet werdet.

## Stundenplan

Nach ausführlicher [Terminabsprache](https://doodle.com/poll/h2nvrv6kan2qk34h) mit Euch haben wir uns auf den folgenden zeitlichen Ablauf geeinigt:

 - **Montag (ungerade Woche)**: Ben und ich veröffentlichen hier im Repo (und per Mailingliste) ein Video, das den theoretischen Vorlesungsstoff für die jeweilige Woche beinhaltet. Ihr habt bis zum Mittwochstermin Zeit, Euch mit den Inhalten vertraut zu machen.
 - **Mittwoch, 14:00 Uhr bis (maximal) 17:30 Uhr (ungerade Woche)**: Wir treffen uns zum praktischen Teil im [BBB](https://teach.informatik.tu-freiberg.de/b/jon-9z6-k3j) und programmieren zusammen. Diese Veranstaltungen werden aufgezeichnet und ebenfalls hier verlinkt. Anschließend bekommt Ihr eine Hausaufgabe, die ca. 14 Tage Bearbeitungszeit hat.
 - **Donnerstag, 11:30 Uhr (ungerade Woche)**: Für diejenigen TeilnehmerInnen, die am Mittwoch nicht durchweg Zeit haben, bieten wir hier einen weiteren Termin zur Konsultation im [BBB](https://teach.informatik.tu-freiberg.de/b/jon-9z6-k3j) an. Dort können z.B. Fragen zum Theorieteil oder zur Programmierung beantwortet werden.

Der 09:30-Uhr-Termin am Dienstag fällt zukünftig weg. Vielen Dank für Eure Kompromissbereitschaft bei der Terminplanung :)

## Entwicklungsumgebung

Für die C-Übung und etwaige Hausaufgaben benötigt Ihr einen C-Kompiler und einen Texteditor.
Im Idealfall verwendet Ihr eine native unixoide Umgebung. 

Außerdem von Vorteil: git, cmake, später auch Bibliotheken (OpenGL, glfw, glad)

### Texteditoren
- Sublime Text 3 (Win, Mac, Linux)
- Visual Studio Code
- Atom (Win, Mac, Linux)
- Notepad++ (Win)
- vim, emacs, geany...

### Kompiler
- gcc, clang

#### Linux
- Debian(-basierte, Ubuntu, Mint...): <tt>sudo apt-get install build-essentials</tt>
- Arch Linux(-basierte, Manjaro...): <tt>sudo pacman -S base-devel</tt>

#### Mac
- XCode aus dem AppStore installieren
- Terminal: <tt>xcode-select --install</tt>

#### Windows

##### Videos zur Einrichtung von Entwicklungsumgebungen unter Windows
- [Subsystem](https://youtu.be/6xWLpVFxI_Y)
- [Cygwin](https://youtu.be/VDPGdi4nYPE)
- [Ubuntu in der VM](https://youtu.be/vqNA219bj4I)

##### Linux Subsystem
Seit 2016 bietet Windows 10 die Möglichkeit ein Linux-Subsystem zu verwenden. [Hier](https://msdn.microsoft.com/en-us/commandline/wsl/install-win10) finden Sie eine Anleitung dazu. Anschließend können Sie gcc, wie unter "Linux" beschrieben, installieren.

##### Cygwin
- [Cygwin installieren](https://warwick.ac.uk/fac/sci/moac/people/students/peter_cock/cygwin/part1)
- [gcc für Cygwin installieren](https://warwick.ac.uk/fac/sci/moac/people/students/peter_cock/cygwin/part2)

##### MinGW
- [MinGW inkl. gcc installieren](http://www.mingw.org/wiki/howto_install_the_mingw_gcc_compiler_suite)

##### Integrierte Entwicklungsumgebung (IDE)
- Pelles C
- Visual Studio
