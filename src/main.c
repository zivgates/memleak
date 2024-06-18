#include <Windows.h>
#include <wchar.h>

INT wmain(INT argc, WCHAR* argv[]){
    if(argc < 3){
        wprintf(L"usage: memleak [kilobytes] [paged or not]\n");
        return -1;
    }
    INT size = _wtoi(argv[1]);
    BOOL isPaged;
    if(wcscmp(argv[2], L"nonpaged") == 0) isPaged = TRUE;
    else isPaged = FALSE;
    if(!size){
        wprintf(L"MUST BE A NUMBER\n");
        return -1;
    }
    size *= 1024;
    ULONG totalAllocated = 0;
    BOOL result = SetProcessWorkingSetSize(GetCurrentProcess(), 1024 * 1024, 1024 * 1024 * 1000);
    if(!result){
        wprintf(L"Couldn't Set The Process Working Size\n");
        return -1;
    }
    while(1){
        totalAllocated+=size;
        LPVOID ptr = HeapAlloc(GetProcessHeap(), 0, size);
        if(!ptr){
            wprintf(L"[-] Error Allocating Memory\n");
            return -1;
        }
        if(isPaged == TRUE){
            BOOL result = VirtualLock(ptr, size);
            if(!result){
                wprintf(L"[-] Failed Locking Memory into RAM, Error Code %d\n", GetLastError());
            }
        }
        wprintf(L"[+] Succsessfully Created %p with size of %d Kilobytes, Leaked %d Kilobytes\n", ptr, size / 1024, totalAllocated / 1024);
        Sleep(1);
    }
    return 0;
}