# *Hello Triangle* per Cygwin

Mit der folgenden Anleitung solltet Ihr in der Lage sein, das *Hello-triangle*-Projekt unter Windows mit Cygwin zum Laufen zu bringen.

## Betriebssystem

- [Cygwin](https://www.cygwin.com/) in der *x86_64*-Version installieren
- Folgende Pakete in der jeweils neuesten Version hinzufügen (wenn nicht schon geschehen):
  - *gcc*
  - *make*
  - *libX11_6*

## Projekt

- Die **aktuelle** Version des Projekts pullen
- Die [*x86_64*-Version von GLFW für Windows](https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.bin.WIN64.zip) herunterladen und entpacken
- Das Verzeichnis *include/GLFW* in das *include*-Verzeichnis des Projekts kopieren
- Alle drei Binaries aus *lib-mingw-w64* in ein neues Verzeichnis namens *lib* auf derselben Ebene wie *include* und *src* kopieren
- Euer Projektverzeichnis sollte jetzt so aussehen:

```tree
.
├── include
│   ├── glad
│   │   └── glad.h
│   ├── gl_calls.h
│   ├── GLFW
│   │   ├── glfw3.h
│   │   └── glfw3native.h
│   └── KHR
│       └── khrplatform.h
├── lib
│   ├── glfw3.dll
│   ├── libglfw3.a
│   └── libglfw3dll.a
├── Makefile
├── shader
│   ├── fragment.glsl
│   └── vertex.glsl
└── src
    ├── glad.c
    ├── gl_calls.c
    └── main.c
```

- Außerdem müssen die Linkerflags angepasst werden. **Das habe ich im aktuellen Makefile bereits erledigt!** Dort gibt es eine Linux-/Windows-Fallunterscheidung, sodass unter Windows die Zeile `LDFLAGS=-Llib -lglfw3 -ldl -lopengl32 -lgdi32` zum Einsatz kommt.
- Da die Binaries für MinGW statt für Cygwin vorgesehen sind, wird die MinGW-Funktion `__ms_vsnprintf()` vorausgesetzt, die unter Cygwin fehlt. Das erzeugt einen Linkerfehler. Ich habe länger recherchiert, wie man den beheben kann, aber keine schöne Möglichkeit gefunden. Deshalb die hässliche Variante (siehe `main.c`, **ebenfalls schon im Repo**):

```c
#ifdef __CYGWIN__
	#include <stdarg.h>

	void __ms_vsnprintf(char * s, size_t n, const char * format, va_list arg)
	{
		vsnprintf(s, n, format, arg);
	}
#endif
```
