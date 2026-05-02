#include <windows.h>
#include <gdiplus.h>

using namespace Gdiplus;

Bitmap *gbackbuffer = nullptr;

extern "C" {
    void InitGDIPlus(ULONG_PTR *token) {
        GdiplusStartupInput gdiplusStartupInput;
        GdiplusStartup(token, &gdiplusStartupInput, nullptr);
    }

    void ShutdownGDIPlus(ULONG_PTR token) {
        GdiplusShutdown(token);
    }

    void ResizeBackBuffer(int w, int h) {
        if (gbackbuffer) delete gbackbuffer;
        gbackbuffer = new Bitmap(w, h);
    }

    POINT GetImageSize(void *imgptr) {
        int w = static_cast<Image*>(imgptr)->GetWidth();
        int h = static_cast<Image*>(imgptr)->GetHeight();

        return {w, h};
    }

    void* LoadGDIImage(const wchar_t* filename) {
        Image *img = new Image(filename);

        if (img->GetLastStatus() != Ok) {
            delete img;
            return NULL;
        }

        return img;
    }

    void DestroyGDIImage(void *imgptr) {
        if (imgptr != nullptr) {
            Image* img = static_cast<Image*>(imgptr);
            delete img;
        }
    }

    void DrawGDIImage(HDC hdc, void* imgptr, int x, int y, int width, int height) {
        if (!gbackbuffer) return;

        Graphics screenGraphics(hdc);

        Graphics tempGraphics(gbackbuffer);

        tempGraphics.Clear(Color::Black);
        Image *img = static_cast<Image*>(imgptr);
        tempGraphics.DrawImage(img, x, y, width, height);

        screenGraphics.DrawImage(gbackbuffer, 0, 0);
    }
}