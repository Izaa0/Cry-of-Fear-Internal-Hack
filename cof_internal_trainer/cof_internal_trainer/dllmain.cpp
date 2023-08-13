// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "mem.h"
#include "proc.h"
#include <mmsystem.h>
#include <userenv.h>





DWORD WINAPI HackThread(HMODULE hModule)
{
    
    AllocConsole();
    FILE* f;
    char* buffer{};
    freopen_s(&f, "CONOUT$", "w", stdout);
    
    //change the path to the sound file
    PlaySound(L"C:\\Users\\Your Name\\source\\repos\\cof_internal_trainer\\Release\\Sound\\injectSound.wav", NULL, SND_SYNC);

    bool enable_stamina{ false }, enable_health{ false }, enable_ammo{ false }, checkstate{true};
    uintptr_t module_base = (uintptr_t)GetModuleHandle(L"hw.dll");
    uintptr_t local_player_ptr{ *(uintptr_t*)(module_base + 0x80E07C) };

    std::cout << "Press END to eject" << std::endl;
    std::cout << "[F1] Health" << std::endl;
    std::cout << "[F2] Stamina" << std::endl;
    std::cout << "[F3] Ammo" << std::endl;
    std::cout << "[F4] Disable Hack" << std::endl;


    
    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }

        if (GetAsyncKeyState(VK_F1) & 1)
        {
            
            enable_health = !enable_health;

            if (enable_health == true)
            {
                std::cout << "Health Hack Activated!" << std::endl;
            }
            else
            {
                std::cout << "Health Hack Deactivated!" << std::endl;
            }
        }

        if (GetAsyncKeyState(VK_F2) & 1)
        {
            

            enable_stamina = !enable_stamina;

            if (enable_stamina == true)
            {
                std::cout << "Stamina Hack Activated!" << std::endl;
            }
            else
            {
                std::cout << "Stamina Hack Deactivated!" << std::endl;
            }
        }

        if (GetAsyncKeyState(VK_F3) & 1)
        {
            enable_ammo = !enable_ammo;

            if (enable_ammo == true)
            {
                std::cout << "Ammo Hack Activated" << std::endl;
                
            }
            else
            {
                std::cout << "Ammo Hack Deactivated" << std::endl;
            }
        }

        if (GetAsyncKeyState(VK_F4) & 1)
        {
            checkstate = !checkstate;

            if (checkstate == true)
            {
                std::cout << "Hack Activated" << std::endl;

            }
            else
            {
                std::cout << "Deactivated" << std::endl;
            }
        }

        if (checkstate)
        {
            if (enable_health)
            {
                *(float*)mem::FindMyAAddy(module_base + 0x80E07C, { 0x7C, 0x4, 0x164 }) = 1337.f;
            }

            if (enable_ammo)
            {
                *(int*)mem::FindMyAAddy(module_base + 0x80E07C, { 0x7C, 0x2530, 0x4, 0x20C, 0x7C, 0x1E4 }) = 1337;
            }

            if (enable_stamina)
            {
                *(float*)mem::FindMyAAddy(module_base + 0x80E07C, { 0x7C , 0x21F0 }) = 1337.f;
            }
        }

        Sleep(5);

    }


    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;

}






BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));

    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

