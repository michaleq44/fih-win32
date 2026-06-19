# fih-win32
* **Autor:** Michał Kulas<br>
<br>

[English](README.md) | [Polski](README.pl.md)
<br>
Bardzo prosta przeglądarka grafiki dla systemu Microsoft Windows ([wersja Linux](https://github.com/michaleq44/fih))<br>
Jedyne co robi to ładuje zdjęcia i je wyświetla.<br>
**UWAGA:** nazwy programów używanych do kompilacji są podane w języku angielskim
#### Skalowanie
Program skaluje obraz aby zmieścił się w okno, ale nie rozciąga go powyżej oryginalnego rozmiaru.
#### Sposób użycia
Wykonaj: `fih.exe [twoj/ścieżka/do_obrazu.png]`<br>
Wspierna formaty obrazków to te wspierane przez bibliotekę systemu Windows GDI+:
- BMP (.bmp)
- PNG (.png)
- JPEG (.jpg/.jpeg)
- GIF (.gif) __POKAZUJE TYLKO PIERWSZĄ KLATKĘ__
- TIFF (.tif/.tiff)
- WMF/EMF (.wmf/.emf)
- ICO (.ico)

### Zależności czasu uruchomienia
- system operacyjny **Microsoft Windows** 10/11 (może działać na starszych, ale nie było to testowane)
- **Microsoft Visual C++ Redistributable for Visual Studio 2015-2022**
  - Większość użytkowniku już to ma, ale jest wymagane do uruchomienia pliku `.exe`

## Kompilacja
wymagania na Linux:
- **Windows SDK** w `~/opt/winsdk`<br>
(można też zdefiniować `winsdk/sdk` parametrem CMake `-DWIN_SDK_DIR=/ścieżka/do/sdk`
oraz `winsdk/crt` parametrem `-DWIN_CRT_DIR=/ścieżka/do/crt`)
- **GNU Make** lub **Ninja** (Ninja jest preferowane, ale z rozmiarem programu nie powinno robić to dużej różnicy)
- **CMake** (wersja 3.15 lub wyższa)

wymagania na Windows:
- **Visual Studio 2022** (Community, Professional lub Enterprise)
  - Workload: "Desktop development with C++"
  - Individual Component: "C++ Clang-cl for v143 build tools"
- **CMake** (wersja 3.15 lub wyższa)

### Jak skompilować:
Windows:
- otwórz folder projektu w **Developer Command Prompt for VS 2022**
- wykonaj `prepare.bat {parametry}`
  - parametrami mogą być: `-r` aby zbudować wersję Release (redystrybucyjną) zamiast Debug (testową) lub wszelakie parametry CMake
- powstanie plik wyjściowy `fih.exe` w podfolderze `Debug` lub `Release`, zależnie od użycia parametru `-r`

Linux:
- w folderze projektu wykonaj `./prepare.sh {parametry}`
    - parametrami mogą być: `-r` aby zbudować wersję Release (redystrybucyjną) zamiast Debug (testową) lub wszelakie parametry CMake
    - **WAŻNE:** ostatnia linia wyjścia skryptu `prepare.sh` to twoje narzędzie kompilacji. Zapamiętaj ją.
- wejdź do folderu kompilacji: `cd build`
- wykonaj komendę swojego narzędzia kompilacji: `make` lub `ninja`
- powinien powstać plik wyjściowy `fih.exe`

### Dystrybucja
Możesz budować archiwa redystrybucyjne narzędziem `cpack` dołączonym do programu CMake.<br>
Gotowe archiwa są dostępne w zakładce `Releases` na platformie GitHub.
