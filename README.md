# fih-win32
* **Author:** Michał Kulas<br>
<br>

[English](README.md) | [Polski](README.pl.md)
<br>
Very simplistic image viewer for Microsoft Windows ([Linux version](https://github.com/michaleq44/fih))<br>
All it does is load images and display them.
#### Scaling
The program scales the image to fit into the window but doesn't stretch it to a bigger size than the original.
#### Usage
Execute: `fih.exe [your/image_path.png]`<br>
The supported image formats are the ones supported by the Windows GDI+ library:
- BMP (.bmp)
- PNG (.png)
- JPEG (.jpg/.jpeg)
- GIF (.gif) __ONLY SHOWS FIRST FRAME__
- TIFF (.tif/.tiff)
- WMF/EMF (.wmf/.emf)
- ICO (.ico)

### Runtime dependencies:
- **Microsoft Windows** 10/11 operating system (might work on older versions but wasn't tested)
- **Microsoft Visual C++ Redistributable for Visual Studio 2015-2022**
  - Most Windows users already have this, but it is required to run the `.exe`.

## Compilation
Linux dependencies:
- the **Windows SDK** in `~/opt/winsdk`<br>
(or define `winsdk/sdk` with `-DWIN_SDK_DIR=/path/to/sdk` and
`winsdk/crt` with `-DWIN_CRT_DIR=/path/to/crt`)
- **GNU Make** or **Ninja** (Ninja is preferred, although with the size of the program there shouldn't be a huge difference)
- **CMake** (3.15 or higher)

Windows dependencies:
- **Visual Studio 2022** (Community, Professional, or Enterprise)
  - Workload: "Desktop development with C++"
  - Individual Component: "C++ Clang-cl for v143 build tools"
- **CMake** (3.15 or higher)

### How to compile:
Windows:
- open the project directory in the **Developer Command Prompt for VS 2022**
- execute `prepare.bat {flags}`
  - the flags can be `-r` to build Release instead of Debug and any CMake flags
  you might want to pass through
- there should be an output file `fih.exe` in the `Debug` or `Release` subdirectory depending on whether you used `-r`

Linux:
- in the project directory execute `./prepare.sh {flags}`
  - the flags can be `-r` to build Release instead of Debug and any CMake flags
  you might want to pass through
  - **IMPORTANT:** the `prepare.sh` script's last line of output is your build tool. Remember it.
- enter the build directory with `cd build`
- execute your build tool: either `make` or `ninja`
- there should be an output file `fih.exe`

### Packaging:
You can build packages using `cpack`, the tool bundled with CMake.<br>
They are also available in the 'Releases' tab on GitHub.
