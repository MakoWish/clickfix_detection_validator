#include <windows.h>
#include <stdio.h>

int main(void) {
    FILE *f = fopen("C:\\Windows\\Temp\\nexusconnector-validation.log", "a");
    if (!f) return 1;

    SYSTEMTIME st;
    GetSystemTime(&st);

    fprintf(f, "PowerShell chain loader infection validation succeeded.\n");
    fprintf(f, "Simulated app path: %%LOCALAPPDATA%%\\NexusConnector\\NexusConnector.exe\n");
    fprintf(f, "UTC=%04u-%02u-%02uT%02u:%02u:%02uZ\n\n",
        st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

    fclose(f);
    return 0;
}
