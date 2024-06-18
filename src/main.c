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

    while(1){
        totalAllocated+=size;
        LPVOID ptr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
        if(!ptr){
            wprintf(L"[-] Error Allocating Memory\n");
            return -1;
        }
        if(isPaged == TRUE){
            BOOL result = VirtualLock(ptr, size);
            if(!result){
                wprintf(L"[-] Failed Locking Memory into RAM\n");
            }
        }
        wprintf(L"[+] Succsessfully Created %p with size of %d Kilobytes, Leaked %d Kilobytes\n", ptr, size / 1024, totalAllocated / 1024);
        Sleep(1);
    }
    return 0;
}