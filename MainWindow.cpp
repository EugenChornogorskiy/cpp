#include <windows.h>
#include <string>
#include <fstream>
#include "World.h"
#include "Sheep.h"
#include "Grass.h"
#include "Wilk.h"
#include "Muchomor.h"
#include "Mlecz.h"

World* g_world = nullptr;
bool autoMode = true;
int cellSize = 60;
string saveFileName = "world.bin";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_CREATE) {
        SetTimer(hwnd, 1, 1500, nullptr);
    }
    
    if (msg == WM_PAINT && g_world) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
         
        std::string grid = g_world->toString();
        int x = 0, y = 0;
        
        for (char c : grid) {
            if (c == '\n') {
                y++;
                x = 0;
                continue;
            }
            
            RECT rect = {
                x * cellSize + 50,
                y * cellSize + 50,
                x * cellSize + 50 + cellSize - 2,
                y * cellSize + 50 + cellSize - 2
            };
             
            HBRUSH brush;
            if (c == 'S') brush = CreateSolidBrush(RGB(255, 220, 100)); 
            else if (c == 'G') brush = CreateSolidBrush(RGB(80, 200, 80)); 
            else if (c == 'W') brush = CreateSolidBrush(RGB(255, 80, 80)); 
            else if (c == 'D') brush = CreateSolidBrush(RGB(250, 250, 250)); 
            else if (c == 'T') brush = CreateSolidBrush(RGB(180, 100, 100));
            else brush = CreateSolidBrush(RGB(60, 60, 70));  
            
            FillRect(hdc, &rect, brush);
            DeleteObject(brush);
             
            FrameRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));
             
            if (c == 'S' || c == 'G' || c == 'W' || c == 'D' || c == 'T') {
                SetBkMode(hdc, TRANSPARENT);
                SetTextColor(hdc, RGB(0, 0, 0));
                char text[2] = {c, 0};
                TextOutA(hdc, rect.left + 20, rect.top + 15, text, 1);
            }
            x++;
        }
         
        char info[512];
        sprintf_s(info, "Turn: %d | SPACE: auto (%s) | RIGHT: next | S: save | L: load | ESC: exit",
                  g_world->getTurn(), autoMode ? "ON" : "OFF");
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(100, 100, 255));
        TextOutA(hdc, 10, 10, info, strlen(info));
        
        EndPaint(hwnd, &ps);
    }
    
    if (msg == WM_TIMER && g_world && autoMode) {
        g_world->makeTurn();
        InvalidateRect(hwnd, nullptr, TRUE);
    }
    
    if (msg == WM_KEYDOWN) {
        if (wParam == VK_SPACE) {
            autoMode = !autoMode;
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        if (wParam == VK_RIGHT && g_world) {
            g_world->makeTurn();
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        if (wParam == 'S' || wParam == 's') {
            g_world->writeWorld(saveFileName);
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        if (wParam == 'L' || wParam == 'l') {
            g_world->readWorld(saveFileName);
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        if (wParam == VK_ESCAPE) {
            DestroyWindow(hwnd);
        }
    }
    
    if (msg == WM_DESTROY) {
        KillTimer(hwnd, 1);
        PostQuitMessage(0);
    }
    
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    srand(GetTickCount());
     
    World world(5, 5);
    g_world = &world;
     
    for (int i = 0; i < 12; i++) {
        world.addOrganism(std::make_unique<Sheep>(Position(rand() % 5, rand() % 5)));
    }
    for (int i = 0; i < 6; i++) {
        world.addOrganism(std::make_unique<Wilk>(Position(rand() % 5, rand() % 5)));
    }
    
    WNDCLASSEXA wc = {};
    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = "SWIAT";
    
    RegisterClassExA(&wc);
     
    int windowWidth = 15 * cellSize + 100;
    int windowHeight = 15 * cellSize + 120;
    
    HWND hwnd = CreateWindowExA(0, "SWIAT", "GDI",
                               WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                               CW_USEDEFAULT, CW_USEDEFAULT,
                               windowWidth, windowHeight,
                               nullptr, nullptr, hInstance, nullptr);
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
     
    MSG msg;
    while (GetMessageA(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    
    return 0;
}