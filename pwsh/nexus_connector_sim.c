#include <windows.h>
#include <stdio.h>

int main(void) {
    char temp[MAX_PATH];
    char marker[MAX_PATH];

    if (!GetEnvironmentVariableA("TEMP", temp, sizeof(temp))) {
        return 1;
    }

    snprintf(marker, sizeof(marker), "%s\\nexusconnector-validation.log", temp);

    FILE *f = fopen(marker, "a");
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
