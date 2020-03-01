# OTAHelper

## Introduction

Enables you to do OTA Updates, even if you build exceptions inside your loop code.

## Usage

```c++
OTAHelper ota = new OTAHelper("HOSTNAME", "PASSWORD");

void setup() {

    // setup wifi first

    /**
     * Checks the last reboot reason.
     * On an error the setup functions waits n seconds to run a OTA Update
     */
    ota.setup(); 

    // other setup stuff
}

void loop() {

    // your stuff

    /**
     * Enables you to run a OTA update during normal operation
     */
    ota.loop();
}
```
