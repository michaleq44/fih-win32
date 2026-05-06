#ifndef FIH_WIN32_MAIN_H
#define FIH_WIN32_MAIN_H

#include "util.h"
#include "graphics.h"

#include <stdio.h>
#include <windows.h>
#include <shellapi.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void OnSize(HWND, UINT);
void AttachParentConsole(void);

#endif