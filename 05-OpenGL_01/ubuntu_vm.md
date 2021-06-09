# *Hello Triangle* per Ubuntu-VM

Mit der folgenden Anleitung solltet Ihr in der Lage sein, das *Hello-triangle*-Projekt in einer Ubuntu-VM zum Laufen zu bringen. Vielen Dank an Christina :)

## Betriebssystem

- Wechsel von *Oracle VM Virtual Box* auf *VMware Workstation Player*
- Ubuntu Version: *19.10*
- Installieren der *Mesa-20*-Treiber ermöglicht OpenGL *v3.3* (vorher nur *v1.4*):
  - `sudo add-apt-repository ppa:oibaf/graphics-drivers`
  - `sudo apt-get update`
  - `sudo apt-get dist-upgrade`
  - Erfolg testen: `glxinfo | grep "OpenGL version"` sollte ungefähr Folgendes ausgeben:

`OpenGL version string: 3.3 (Compatibility Profile) Mesa 20.2.0-devel (git-04f7759 2020-06-20 eoan-oibaf-ppa)`

## Projekt

- OpenGL *v3.3* statt *v4.1* in `main.c`:

```c
// We want at least OpenGL 3.3 :)
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
```

- GLSL *v3.30* in beiden Shadern:

```glsl
#version 330
```

- Linkeroptionen: `LDFLAGS=-lglfw -ldl`
- `glReleaseShaderCompiler()` auskommentiert, weil erst ab *v4.1* unterstützt:

```c
//glReleaseShaderCompiler()
//gl_check_error("glReleaseShaderCompiler");
```

- [Download der *glad*-Biblothek für *v3.3*](https://glad.dav1d.de/#profile=core&specification=gl&api=gl%3D3.3&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&language=c&loader=on)
- Diverse Pfadanpassungen für header files und shader files in den Projektpfad kopiert
