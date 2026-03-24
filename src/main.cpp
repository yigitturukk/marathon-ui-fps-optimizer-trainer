#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <shlobj.h>

namespace fs = std::filesystem;

void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void PrintBanner() {
    SetColor(11);
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║           MARATHON UI + FPS OPTIMIZER v2.0               ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n";
    SetColor(7);
    std::cout << "                      March 2026\n\n";
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

std::string GetMarathonConfigPath() {
    char localAppData[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, localAppData))) {
        fs::path configPath = fs::path(localAppData) / "Marathon" / "Saved" / "Config" / "WindowsNoEditor";
        return configPath.string();
    }
    return "";
}

bool BackupFile(const std::string& filePath) {
    if (!fs::exists(filePath)) return false;
    std::string backup = filePath + ".backup";
    try {
        fs::copy_file(filePath, backup, fs::copy_options::overwrite_existing);
        return true;
    } catch (...) {
        return false;
    }
}

void ApplyUIFix() {
    std::cout << "\n[*] Applying UI fixes...\n";
    std::string configPath = GetMarathonConfigPath();
    if (configPath.empty()) {
        SetColor(12);
        std::cout << "[-] Could not find Marathon config folder.\n";
        SetColor(7);
        return;
    }
    fs::create_directories(configPath);
    std::string engineIni = configPath + "\\Engine.ini";
    BackupFile(engineIni);

    std::ofstream out(engineIni, std::ios::app);
    if (out.is_open()) {
        out << "\n[SystemSettings]\n";
        out << "r.UIScale=1.2\n";
        out << "r.UIScale.UI.MenuScale=1.15\n";
        out << "r.UIScale.HUD.Scale=1.1\n";
        out << "r.UIScale.NotificationScale=1.2\n";
        out.close();
        SetColor(10);
        std::cout << "[✓] UI scaling applied (Engine.ini modified).\n";
        SetColor(7);
    } else {
        SetColor(12);
        std::cout << "[-] Failed to write Engine.ini.\n";
        SetColor(7);
    }
}

void ApplyFPSBoost() {
    std::cout << "\n[*] Applying FPS boost tweaks...\n";
    std::string configPath = GetMarathonConfigPath();
    if (configPath.empty()) {
        SetColor(12);
        std::cout << "[-] Could not find Marathon config folder.\n";
        SetColor(7);
        return;
    }
    fs::create_directories(configPath);
    std::string engineIni = configPath + "\\Engine.ini";
    BackupFile(engineIni);

    std::ofstream out(engineIni, std::ios::app);
    if (out.is_open()) {
        out << "\n[SystemSettings]\n";
        out << "r.ScreenPercentage=85\n";
        out << "r.ShadowQuality=1\n";
        out << "r.VolumetricFog=0\n";
        out << "r.MotionBlurQuality=0\n";
        out << "r.DepthOfFieldQuality=0\n";
        out << "r.PostProcessAAQuality=1\n";
        out.close();
        SetColor(10);
        std::cout << "[✓] FPS boost settings applied.\n";
        SetColor(7);
    } else {
        SetColor(12);
        std::cout << "[-] Failed to write Engine.ini.\n";
        SetColor(7);
    }
}

void ApplyProConfig(const std::string& profileName) {
    std::cout << "\n[*] Applying " << profileName << " config...\n";
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    fs::path exeDir = fs::path(exePath).parent_path();
    fs::path profilePath = exeDir / "profiles" / (profileName + ".ini");

    if (!fs::exists(profilePath)) {
        SetColor(12);
        std::cout << "[-] Profile " << profileName << ".ini not found.\n";
        SetColor(7);
        return;
    }

    std::string configPath = GetMarathonConfigPath();
    if (configPath.empty()) {
        SetColor(12);
        std::cout << "[-] Could not find Marathon config folder.\n";
        SetColor(7);
        return;
    }
    fs::create_directories(configPath);
    std::string dest = configPath + "\\GameUserSettings.ini";
    BackupFile(dest);

    try {
        fs::copy_file(profilePath, dest, fs::copy_options::overwrite_existing);
        SetColor(10);
        std::cout << "[✓] " << profileName << " config applied. Restart game to see changes.\n";
        SetColor(7);
    } catch (const std::exception& e) {
        SetColor(12);
        std::cout << "[-] Failed to copy config: " << e.what() << "\n";
        SetColor(7);
    }
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
        default: break;
    }
    std::cout << "\n[+] Your recommended Marathon sensitivity: " << marathonSens << "\n";
    std::cout << "Apply this in game settings -> Mouse.\n";
}

void ShowTrainerMenu() {
    std::cout << "\n=== TRAINER MODULE ===\n";
    std::cout << "Hotkeys (while in game):\n";
    std::cout << "  F1 - God Mode\n";
    std::cout << "  F2 - Infinite Ammo\n";
    std::cout << "  F3 - No Reload\n";
    std::cout << "  F4 - Speed Hack\n";
    std::cout << "  F5 - One-Hit Kill\n";
    std::cout << "\n[!] Use at your own risk. Trainer may trigger bans in multiplayer.\n";
}

void RestoreBackup() {
    std::cout << "\n[*] Restoring backups...\n";
    std::string configPath = GetMarathonConfigPath();
    if (configPath.empty()) {
        SetColor(12);
        std::cout << "[-] Could not find Marathon config folder.\n";
        SetColor(7);
        return;
    }
    std::vector<std::string> files = {"Engine.ini", "GameUserSettings.ini"};
    for (const auto& file : files) {
        std::string original = configPath + "\\" + file;
        std::string backup = original + ".backup";
        if (fs::exists(backup)) {
            try {
                fs::copy_file(backup, original, fs::copy_options::overwrite_existing);
                SetColor(10);
                std::cout << "[✓] Restored " << file << "\n";
                SetColor(7);
            } catch (...) {
                SetColor(12);
                std::cout << "[-] Failed to restore " << file << "\n";
                SetColor(7);
            }
        } else {
            std::cout << "[!] No backup found for " << file << "\n";
        }
    }
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
        std::cout << "\n╔════════════════════════════════════════════╗\n";
        std::cout << "║              MAIN MENU                      ║\n";
        std::cout << "╠════════════════════════════════════════════╣\n";
        std::cout << "║  1. Apply UI Fix                           ║\n";
        std::cout << "║  2. Apply FPS Boost                        ║\n";
        std::cout << "║  3. Apply Pro Config                       ║\n";
        std::cout << "║  4. Sensitivity Converter                  ║\n";
        std::cout << "║  5. Trainer Module (Experimental)          ║\n";
        std::cout << "║  6. Restore Backups                        ║\n";
        std::cout << "║  0. Exit                                   ║\n";
        std::cout << "╚════════════════════════════════════════════╝\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                ApplyUIFix();
                break;
            case 2:
                ApplyFPSBoost();
                break;
            case 3: {
                std::cout << "\nSelect profile:\n";
                std::cout << "  1. Aztecross\n";
                std::cout << "  2. LuluLuvely\n";
                std::cout << "  3. FalloutPlays\n";
                std::cout << "Choice: ";
                int prof;
                std::cin >> prof;
                std::cin.ignore();
                std::string profile;
                if (prof == 1) profile = "Aztecross";
                else if (prof == 2) profile = "LuluLuvely";
                else if (prof == 3) profile = "FalloutPlays";
                else profile = "";
                if (!profile.empty()) ApplyProConfig(profile);
                else std::cout << "Invalid choice.\n";
                break;
            }
            case 4:
                ConvertSensitivity();
                break;
            case 5:
                ShowTrainerMenu();
                break;
            case 6:
                RestoreBackup();
                break;
            case 0:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
        if (choice != 0) {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    } while (choice != 0);

    return 0;
}