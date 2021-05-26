# JPEG-Guideline
## Kompression

- Mit Codegerüst vertraut machen
- Pixel-Buffer der Bitmap einlesen (`create_grayscale_bitmap()`)
- Validieren, dass es sich um eine 8mx8n-Bitmap handelt, sonst Abbruch
- Anzahl der horizontalen / vertikalen Blöcke berechnen: `blocks_x`, `blocks_y`
- Über den Pixel-Buffer iterieren, in Graustufen umwandeln (später mal mit SIMD-Instruktionen ... ?)
- Pixel-Buffer als Graustufen-Bitmap ausgeben (`compress()`, Zwischenergebnis -> noch nicht freigeben)
- Ausgabedatei anlegen und Block-Anzahlen als zwei 4-Byte-unsigned-Integer an den Anfang schreiben (`blocks_x`, `blocks_y`)
- In doppelter `for`-Schleife über die Blöcke iterieren. Aktueller Block jeweils: (`index_x`, `index_y`)
- Den aktuellen Block aus dem Pixel-Buffer in ein 64-`floats`-Array einlesen, Helligkeitswert dabei um 0 zentrieren (`read_block()`).
- Block-Wertebereich nun -128...127
- DCT auf den Block anwenden (`perform_dct()`, Formeln aus Bens Folien besorgen). Tipp: Zerlegung in "innere" und "äußere" Funktion
- Block-Wertebereich nun -1024...1016
- Quantisierung auf den Block anwenden (`quantize()`). In diesem Schritt von `float` nach `int8_t` wechseln
- Block-Wertebereich nun -128...127
- ZigZag-Verfahren auf den Block anwenden (`zig_zag`).
- Den resultierenden Block als 64 signed Bytes in die Ausgabe schreiben
- Ausgabeformat am Ende:
```
[4 Bytes blocks_x] [4 Bytes blocks_y] [n komprimierte Bytes, n = Anzahl der Bitmap-Pixel]
```
