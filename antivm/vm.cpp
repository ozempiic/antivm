#include <iostream>
#include <windows.h>

using namespace std;

BOOL FileExists(LPCTSTR szPath)
{
    DWORD dwAttrib = GetFileAttributes(szPath);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES) && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

BOOL CheckFilePattern(LPCTSTR szPath, LPCTSTR pattern)
{
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(pattern, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }
    else
    {
        FindClose(hFind);
        return TRUE;
    }
}

int CheckFile()
{
    LPCSTR fname[] = {
        "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\StartUp\\agent.pyw",
        "C:\\WINDOWS\\system32\\drivers\\vmmouse.sys",
        "C:\\WINDOWS\\system32\\drivers\\vmhgfs.sys",
        "C:\\WINDOWS\\system32\\drivers\\VBoxMouse.sys",
        "C:\\WINDOWS\\system32\\drivers\\VBoxGuest.sys",
        "C:\\WINDOWS\\system32\\drivers\\VBoxSF.sys",
        "C:\\WINDOWS\\system32\\drivers\\VBoxVideo.sys",
        "C:\\WINDOWS\\system32\\vboxdisp.dll",
        "C:\\WINDOWS\\system32\\vboxhook.dll",
        "C:\\WINDOWS\\system32\\vboxmrxnp.dll",
        "C:\\WINDOWS\\system32\\vboxogl.dll",
        "C:\\WINDOWS\\system32\\vboxoglarrayspu.dll",
        "C:\\WINDOWS\\system32\\vboxoglcrutil.dll",
        "C:\\WINDOWS\\system32\\vboxoglerrorspu.dll",
        "C:\\WINDOWS\\system32\\vboxoglfeedbackspu.dll",
        "C:\\WINDOWS\\system32\\vboxoglpackspu.dll",
        "C:\\WINDOWS\\system32\\vboxoglpassthroughspu.dll",
        "C:\\WINDOWS\\system32\\vboxservice.exe",
        "C:\\WINDOWS\\system32\\vboxtray.exe",
        "C:\\WINDOWS\\system32\\VBoxControl.exe",
    };

    LPCSTR patterns[] = {
        "C:\\*.vmx",
        "C:\\*.vmxf",
        "C:\\*.vmdk",
        "C:\\*-flat.vmdk",
        "C:\\*.nvram",
        "C:\\*.vmem",
        "C:\\*.vmsd",
        "C:\\*.vmsn",
        "C:\\*.vswp",
        "C:\\*.vmss",
        "C:\\*.log",
        "C:\\*-#.log"
    };

    for (int i = 0; i < (sizeof(fname) / sizeof(LPCSTR)); i++)
    {
        cout << "Checking file: " << fname[i] << endl;
        if (FileExists(fname[i]))
        {
            cout << "[+] File exists: " << fname[i] << endl;
            MessageBox(NULL, "This program can't run in a virtual machine.", "Error", MB_OK | MB_ICONERROR);
            exit(1);
        }
    }

    for (int i = 0; i < (sizeof(patterns) / sizeof(LPCSTR)); i++)
    {
        cout << "Checking pattern: " << patterns[i] << endl;
        if (CheckFilePattern("C:\\", patterns[i]))
        {
            cout << "[+] File pattern matched: " << patterns[i] << endl;
            MessageBox(NULL, "This program can't run in a virtual machine.", "Error", MB_OK | MB_ICONERROR);
            exit(1);
        }
    }

    MessageBox(NULL, "Not a VM.", "Success", MB_OK | MB_ICONEXCLAMATION);

    return 0;
}

extern "C" BOOL WINAPI Wow64DisableWow64FsRedirection(PVOID* OldValue);
extern "C" BOOL WINAPI Wow64RevertWow64FsRedirection(PVOID OldValue);

int main()
{
    PVOID OldValue;
    if (Wow64DisableWow64FsRedirection(&OldValue))
    {
        CheckFile();
        Wow64RevertWow64FsRedirection(OldValue);
    }
    else
    {
        cout << "Failed to disable WOW64 file system redirection." << endl;
    }
    return 0;
}
