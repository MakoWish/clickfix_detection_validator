# MSHTA Levaging cURL Usage

## HTA Modification (REQUIRED!)

Edit the `B.max` file and modify the `fakePdfUrl` value with the location of where you will be hosting the benign "PDF" payload archive and the `B.max` file itself.

_Example:_

```
    fakePdfUrl = https://<mysite.com>/928252966059280400.pdf
```

## Payload Creation

Review the code in `syncovery_sim.c` to ensure for yourself that the payload is 100% benign. You may use the included `Syncovery.exe`, or use `make` to build it yourself.

## Payload Hosting

Copy both `B.max` and `Syncovery.exe` to the URL you specified in the `B.max` HTA file. If you do not place both files in the root of the site, you will need to ensure the `FakePdfUrl` variable in `B.max` reflects this, as well as the "infection" command leveraged on the test endpoint.

## Disclaimer

This repository is provided for educational, research, testing, and defensive security purposes only. The code contained herein is intended to simulate infection techniques observed in real-world environments to assist with security analysis, detection engineering, threat hunting, and incident response activities.

By accessing, downloading, or using any code in this repository, you acknowledge that you do so entirely at your own risk. The repository owner and contributors make no warranties, express or implied, regarding the safety, suitability, reliability, or fitness of the code for any purpose.

Users are solely responsible for ensuring their use of this repository complies with all applicable laws, regulations, policies, and contractual obligations. Any use of the code for unauthorized, malicious, illegal, or unethical activities is strictly prohibited.

The repository owner and contributors assume no responsibility or liability for any direct, indirect, incidental, consequential, or other damages resulting from the use, misuse, modification, distribution, or execution of any code contained in this repository.
