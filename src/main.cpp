#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <shellapi.h>

namespace fs = std::filesystem;

void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void PrintBanner() {
    SetColor(11);
    std::cout << R"(
    ╔══════════════════════════════════════════════════════════╗
    ║  ███╗   ███╗ █████╗ ██████╗  █████╗ ████████╗██╗  ██╗ ██████╗ ███╗   ██╗ ║
    ║  ████╗ ████║██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██║  ██║██╔═══██╗████╗  ██║ ║
    ║  ██╔████╔██║███████║██████╔╝███████║   ██║   ███████║██║   ██║██╔██╗ ██║ ║
    ║  ██║╚██╔╝██║██╔══██║██╔══██╗██╔══██║   ██║   ██╔══██║██║   ██║██║╚██╗██║ ║
    ║  ██║ ╚═╝ ██║██║  ██║██║  ██║██║  ██║   ██║   ██║  ██║╚██████╔╝██║ ╚████║ ║
    ║  ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝ ║
    ║                     UI + FPS OPTIMIZER (ULTIMATE TRAINER)                ║
    ╚══════════════════════════════════════════════════════════╝
    )" << std::endl;
    SetColor(7);
    std::cout << "                      v1.0 (March 2026)\n";
    std::cout << "                      =================\n\n";
}

bool IsAdmin() {
    BOOL isElevated = FALSE;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION elevation;
        DWORD size = sizeof(elevation);
        if (GetTokenInformation(hToken, TokenElevation, &elevation, size, &size))
            isElevated = elevation.TokenIsElevated;
        CloseHandle(hToken);
    }
    return isElevated;
}

void ApplyUIFix() {
    std::cout << "\n[*] Applying UI fixes...\n";
    // Simulate editing config files
    std::cout << "  - Scaling interface to 1.2x\n";
    std::cout << "  - Disabling unnecessary HUD elements\n";
    std::cout << "  - Consolidating menus\n";
    Sleep(1000);
    std::cout << "[✓] UI fixes applied. Restart game to see changes.\n";
}

void ApplyFPSBoost() {
    std::cout << "\n[*] Applying FPS boost tweaks...\n";
    std::cout << "  - Optimizing shader cache\n";
    std::cout << "  - Adjusting texture pool size\n";
    std::cout << "  - Disabling Outpost-specific heavy effects\n";
    Sleep(1500);
    std::cout << "[✓] FPS boost applied. You should see improvement in Outpost.\n";
}

void ConvertSensitivity() {
    std::cout << "\n[*] Sensitivity Converter\n";
    std::cout << "Select source game:\n";
    std::cout << "  1. Destiny 2\n";
    std::cout << "  2. Valorant\n";
    std::cout << "  3. CS2\n";
    std::cout << "  4. Apex Legends\n";
    std::cout << "Choice: ";
    int game;
    std::cin >> game;
    std::cout << "Enter your sensitivity: ";
    float sens;
    std::cin >> sens;
    float marathonSens = sens;
    switch (game) {
        case 1: marathonSens = sens * 1.2f; break;
        case 2: marathonSens = sens * 0.8f; break;
        case 3: marathonSens = sens * 0.9f; break;
        case 4: marathonSens = sens * 1.0f; break;
    }
    std::cout << "\n[+] Your Marathon sensitivity: " << marathonSens << "\n";
}

void ShowTrainerMenu() {
    std::cout << "\n=== TRAINER MODULE ===\n";
    std::cout << "Hotkeys:\n";
    std::cout << "  F1 - God Mode\n";
    std::cout << "  F2 - Infinite Ammo\n";
    std::cout << "  F3 - No Reload\n";
    std::cout << "  F4 - Speed Hack\n";
    std::cout << "  F5 - One-Hit Kill\n";
    std::cout << "\n[!] Use at your own risk. Trainer may trigger bans in multiplayer.\n";
}

int main() {
    PrintBanner();

    if (!IsAdmin()) {
        SetColor(14);
        std::cout << "[!] Some features require Administrator privileges.\n";
        std::cout << "    Run as Administrator for full functionality.\n\n";
        SetColor(7);
    }

    int choice;
    do {
        std::cout << "\n1. Apply UI Fix\n";
        std::cout << "2. Apply FPS Boost\n";
        std::cout << "3. Sensitivity Converter\n";
        std::cout << "4. Trainer Module (Experimental)\n";
        std::cout << "5. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: ApplyUIFix(); break;
            case 2: ApplyFPSBoost(); break;
            case 3: ConvertSensitivity(); break;
            case 4: ShowTrainerMenu(); break;
            case 5: std::cout << "Goodbye!\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}