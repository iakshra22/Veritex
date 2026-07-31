#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include "../include/VritexEngine.h"

// Global Engine Instance & Handles
VritexEngine engine;
HWND hInputText, hStatusLabel, hSuggestionBox, hAutoCompBox, hUserDictInput;

std::wstring toWString(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}

std::string toString(const wchar_t* wstr) {
    std::wstring ws(wstr);
    return std::string(ws.begin(), ws.end());
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
            HINSTANCE hInst = pcs->hInstance;

            CreateWindowW(L"STATIC", L"VRITEX ENGINE - Smart Spell Checker & Auto-Correct", 
                          WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 10, 560, 25, hwnd, NULL, hInst, NULL);

            CreateWindowW(L"STATIC", L"Type Word/Text:", WS_VISIBLE | WS_CHILD, 
                          20, 50, 120, 20, hwnd, NULL, hInst, NULL);
            
            hInputText = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 
                                      140, 48, 250, 25, hwnd, (HMENU)101, hInst, NULL);

            hStatusLabel = CreateWindowW(L"STATIC", L"[READY]", WS_VISIBLE | WS_CHILD, 
                                        400, 50, 150, 20, hwnd, NULL, hInst, NULL);

            CreateWindowW(L"STATIC", L"1. Prefix Auto-Complete Predictions (Trie DFS):", 
                          WS_VISIBLE | WS_CHILD, 20, 90, 350, 20, hwnd, NULL, hInst, NULL);
            
            hAutoCompBox = CreateWindowW(L"LISTBOX", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, 
                                        20, 115, 540, 70, hwnd, (HMENU)102, hInst, NULL);

            CreateWindowW(L"STATIC", L"2. Auto-Correct Suggestions (Edit Distance + Soundex):", 
                          WS_VISIBLE | WS_CHILD, 20, 200, 380, 20, hwnd, NULL, hInst, NULL);

            hSuggestionBox = CreateWindowW(L"LISTBOX", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, 
                                           20, 225, 540, 80, hwnd, (HMENU)103, hInst, NULL);

            CreateWindowW(L"BUTTON", L"Apply Selected Suggestion", WS_VISIBLE | WS_CHILD, 
                          20, 315, 200, 30, hwnd, (HMENU)201, hInst, NULL);

            CreateWindowW(L"STATIC", L"3. Add Custom Word to Dictionary:", WS_VISIBLE | WS_CHILD, 
                          20, 360, 250, 20, hwnd, NULL, hInst, NULL);
            
            hUserDictInput = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 
                                           20, 385, 200, 25, hwnd, NULL, hInst, NULL);

            CreateWindowW(L"BUTTON", L"Add Word", WS_VISIBLE | WS_CHILD, 
                          230, 384, 100, 27, hwnd, (HMENU)202, hInst, NULL);
            break;
        }

        case WM_COMMAND: {
            if (HIWORD(wParam) == EN_CHANGE && LOWORD(wParam) == 101) {
                wchar_t buffer[256];
                GetWindowTextW(hInputText, buffer, 256);
                std::string currentWord = toString(buffer);

                SendMessageW(hAutoCompBox, LB_RESETCONTENT, 0, 0);
                SendMessageW(hSuggestionBox, LB_RESETCONTENT, 0, 0);

                if (!currentWord.empty()) {
                    std::vector<std::string> completions = engine.autoComplete(currentWord);
                    for (const auto& comp : completions) {
                        SendMessageW(hAutoCompBox, LB_ADDSTRING, 0, (LPARAM)toWString(comp).c_str());
                    }

                    bool isValid = engine.isValidWord(currentWord);
                    if (isValid) {
                        SetWindowTextW(hStatusLabel, L"[VALID SPELLING]");
                    } else {
                        SetWindowTextW(hStatusLabel, L"[MISSPELLED!]");

                        std::vector<std::string> suggestions = engine.getSuggestions(currentWord, 5);
                        for (const auto& sugg : suggestions) {
                            SendMessageW(hSuggestionBox, LB_ADDSTRING, 0, (LPARAM)toWString(sugg).c_str());
                        }
                    }
                } else {
                    SetWindowTextW(hStatusLabel, L"[READY]");
                }
            }

            if (LOWORD(wParam) == 201) {
                int selIdx = (int)SendMessageW(hSuggestionBox, LB_GETCURSEL, 0, 0);
                if (selIdx != LB_ERR) {
                    wchar_t selText[256];
                    SendMessageW(hSuggestionBox, LB_GETTEXT, selIdx, (LPARAM)selText);
                    SetWindowTextW(hInputText, selText);
                }
            }

            if (LOWORD(wParam) == 202) {
                wchar_t buffer[64];
                GetWindowTextW(hUserDictInput, buffer, 64);
                std::string newWord = toString(buffer);
                if (!newWord.empty()) {
                    engine.addToUserDictionary(newWord);
                    SetWindowTextW(hUserDictInput, L"");
                    MessageBoxW(hwnd, L"Word added to User Dictionary successfully!", L"Vritex Engine", MB_OK | MB_ICONINFORMATION);
                }
            }
            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    if (!engine.loadDataset("data/dictionary.txt")) {
        MessageBoxW(NULL, L"Could not load data/dictionary.txt dataset!", L"Vritex Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    const wchar_t CLASS_NAME[] = L"VritexWindowClass";
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0, CLASS_NAME, L"Vritex Engine Desktop Application",
        WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 480,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}