#include <windows.h>
#include <shlobj.h>
#include <stdio.h>

int main(void) {
    char docs[MAX_PATH];
    char workdir[MAX_PATH];
    char marker[MAX_PATH];

    if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, docs) != S_OK) {
        return 1;
    }

    snprintf(workdir, sizeof(workdir), "%s\\928252966059280400", docs);
    CreateDirectoryA(workdir, NULL);

    snprintf(marker, sizeof(marker), "%s\\clickfix-sim-payload.txt", workdir);

    FILE *f = fopen(marker, "a");
    if (!f) return 1;

    fprintf(f, "Benign ClickFix validation payload executed.\n");
    fprintf(f, "Payload type=native Win32 EXE\n");
    fclose(f);

    return 0;
}
