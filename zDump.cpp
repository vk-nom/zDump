#include "DirectOverlay.h"
//#include <iostream>
//#include <Windows.h>
#include "utils.h"
//#include <sstream>
//#include <string>
//#include <algorithm>
//#include <list>
#include "xor.hpp"
//not required but is useful for dx9 (possibly adding an overlay later on) math.
#define PI 3.14159265358979323846264338327950288419716939937510

//we need this for dumping the sdk and reading/writing memory.
#define UWORLD_STRUCTURE 0x9476FE0


//All of our data structures for hooking, and r/w (adding kernel sometime soon)
HWND hwnd = NULL;
DWORD processID;
HANDLE DriverHandle;
uint64_t base_address;

int main()
{
    //pretty much stole the entire hook from 4u4 so big thanks to them!
    DriverHandle = CreateFileW(L"\\\\.\\matchdriver123", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);  // this needs to match your driver

    if (DriverHandle == INVALID_HANDLE_VALUE)
    {
        printf("You Must Load The Driver First.\n");
        Sleep(2000);
        exit(0);
    }
    SetConsoleTitleA("zDump - Beta");
    printf("Hi, Welcome to zDump.\n");
    Sleep(2000);
    system("CLS");
    //Find Fortnites Process and Get The ProcessId
    while (hwnd == NULL)
    {
        hwnd = FindWindowA(0, "Fortnite  ");
        printf("Please Open Fortnite\n");
        Sleep(400);
        system("CLS");
    }
    GetWindowThreadProcessId(hwnd, &processID);


   printf("Getting Started, This May Take a While.\n");
    Sleep(10000);
    system("CLS");

    //Dumping game pointers and Addresses can be useful for cheating (I dont endorse this)
    printf("Dumping Pointers/Addresses, Please Wait.");
    Sleep(800);

    //currently only dumping UWORLD bc im lazy :)
    UworldAddress = read<DWORD_PTR>(DriverHandle, processID, base_address + UWORLD_STRUCTURE);
    printf(_xor_("Uworld: %p.\n").c_str(), UworldAddress);

}
