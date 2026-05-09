#include "main.h"

WNDCLASSEX wc;
MSG msg;
int winwidth, winheight, imgwidth, imgheight;
void* img;
ULONG_PTR gdiToken;
ULONGLONG lastRedrawTime;
LPWSTR wintitle = NULL;

int APIENTRY wWinMain(HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPWSTR lpCmdLine,
                    int nShowCmd)
{
    AttachParentConsole();

    int argc;
    LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argv == NULL) {
        fprintf(stderr, "Error parsing command line\n");
        return 1;
    }
    if (argc < 2) {
        printf("%s", HELP_STRING);
        LocalFree(argv);
        return 1;
    }

    InitGDIPlus(&gdiToken);
    img = LoadGDIImage(argv[1]);

    if (img == NULL) {
        fprintf(stderr, "Image loading failed\n");
        ShutdownGDIPlus(gdiToken);
        return 1;
    }

    POINT imgsize = GetImageSize(img);
    imgwidth = imgsize.x;
    imgheight = imgsize.y;

    wc.lpfnWndProc = WndProc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hInstance = hInstance;
    wc.lpszClassName = WCLASS_NAME;
    wc.hbrBackground = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

    RegisterClassEx(&wc);

    LPCWSTR last_slash = wcsrchr(argv[1], L'\\');
    LPCWSTR last_fslash = wcsrchr(argv[1], L'/');

    LPCWSTR last = (last_slash > last_fslash) ? last_slash : last_fslash;

    if (last == NULL) {
        wintitle = malloc((lstrlenW(argv[1]) + 7) * sizeof(WCHAR));
        wsprintf(wintitle, L"fih - %ls", argv[1]);
    } else {
        wintitle = malloc((lstrlenW(last + 1) + 7) * sizeof(WCHAR));
        wsprintf(wintitle, L"fih - %ls", last + 1);
    }

    LocalFree(argv);

    HWND hwnd = CreateWindowEx(
        0,
        WCLASS_NAME,
        wintitle,
        WS_OVERLAPPEDWINDOW | CS_OWNDC,

        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,
        NULL,
        hInstance,
        NULL
        );

    if (hwnd == NULL) {
        fprintf(stderr, "Window creation failed\n");
        free(wintitle);
        ShutdownGDIPlus(gdiToken);
        return 1;
    }
    ShowWindow(hwnd, nShowCmd);
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_WINDOWPOSCHANGED: {
            RECT rect;
            GetClientRect(hwnd, &rect);
            int twidth = rect.right;
            int theight = rect.bottom;
            if (twidth != winwidth || theight != winheight) {
                winwidth = twidth;
                winheight = theight;
                OnSize(hwnd, 0);
            }
        } break;

        case WM_KEYDOWN: {
            if (wParam == VK_ESCAPE) {
                PostQuitMessage(0);
            }
        } break;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            if (imgwidth >= winwidth || imgheight >= winheight) {
                int twidth, theight;
                if (imgwidth * winheight > winwidth * imgheight) {
                    twidth = winwidth;
                    theight = (imgheight * winwidth) / imgwidth;
                } else {
                    theight = winheight;
                    twidth = (imgwidth * winheight) / imgheight;
                }

                int xpos = (winwidth - twidth) / 2;
                int ypos = (winheight - theight) / 2;
                DrawGDIImage(hdc, img, xpos, ypos, twidth, theight);
            } else {
                int xpos = (winwidth - imgwidth) / 2;
                int ypos = (winheight - imgheight) / 2;
                DrawGDIImage(hdc, img, xpos, ypos, imgwidth, imgheight);
            }

            EndPaint(hwnd, &ps);
        } break;

        case WM_ERASEBKGND: {
            return 1;
        }

        case WM_CLOSE: {
            DestroyWindow(hwnd);
            return 0;
        }

        case WM_DESTROY: {
            if (img != NULL) {
                DestroyGDIImage(img);
                img = NULL;
            }

            ShutdownGDIPlus(gdiToken);
            free(wintitle);
            PostQuitMessage(0);
            return 0;
        }

        default:
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void OnSize(HWND hwnd, UINT flag) {
    //fprintf(stderr, "%dx%d\n", winwidth, winheight);
    ULONGLONG currentTime = GetTickCount64();

    if (currentTime - lastRedrawTime > REDRAW_THRESHOLD) {
        ResizeBackBuffer(winwidth, winheight);
        InvalidateRect(hwnd, NULL, FALSE);
        lastRedrawTime = currentTime;
    }
}

void AttachParentConsole(void) {
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        FILE *fdummy;
        freopen_s(&fdummy, "CONOUT$", "w", stdout);
        freopen_s(&fdummy, "CONOUT$", "w", stderr);
        freopen_s(&fdummy, "CONIN$", "r", stdin);
    }
}