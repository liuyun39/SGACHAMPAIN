#pragma once

// ==============================
// 1. Target Windows Version (Game Standard)
// ==============================
#define _WIN32_WINNT 0x0A00     // Targeting Windows 10 and above
#define WINVER       0x0A00     // Same as _WIN32_WINNT
#define NTDDI_VERSION NTDDI_WIN10 // Detailed Windows 10 version

#include <SDKDDKVer.h>

// ==============================
// 2. Disable Unnecessary Windows Features (Critical for Games)
// ==============================
#define NOGDICAPMASKS           // Disable old GDI font/device capability masks
#define NOMETAFILE              // Disable ancient Windows Metafile graphics support
#define NOSYSMETRICS            // Disable legacy system UI metrics
#define NOFONT                  // Disable GDI font APIs
#define NODRAWTEXT              // Disable GDI text drawing functions
#define NOBITMAP                // Disable GDI bitmap support

#define NOMINMAX                // MOST IMPORTANT! Disable Windows min/max macros to avoid conflict with std::min/max
#define NOCOMM                  // Disable serial comms support
#define NOKANJI                 // Disable Kanji support for legacy systems
#define NOHELP                  // Disable Windows Help system
#define NOPROFILER              // Disable system profiler support
#define NODEFERWINDOWPOS        // Disable legacy window positioning functionss
#define NOMCX                   // Disable modem and device control

// ==============================
// 3. Safety & Encoding Settings
// ==============================
#define STRICT                  // Enable strict type-checking for HWND/HDC handles

// ==============================
// 4. Include Main Windows Header
// ==============================
#include <Windows.h>

// ==============================
// 5. Game Utility Safe Release Macros
// ==============================
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) if(p){p->Release(); p=nullptr;}
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) if(p){delete p; p=nullptr;}
#endif