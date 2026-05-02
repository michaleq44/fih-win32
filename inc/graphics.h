#ifndef FIH_WIN32_GRAPHICS_H
#define FIH_WIN32_GRAPHICS_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

    void InitGDIPlus(ULONG_PTR* token);
    void ShutdownGDIPlus(ULONG_PTR token);
    POINT GetImageSize(void *imgptr);
    void* LoadGDIImage(const wchar_t* filename);
    void DestroyGDIImage(void *imgptr);
    void DrawGDIImage(HDC hdc, void* imgptr, int x, int y, int width, int height);
    void ResizeBackBuffer(int w, int h);

#ifdef __cplusplus
}
#endif

#endif