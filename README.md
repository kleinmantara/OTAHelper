# OTAHelper

## Introduction

Enables you to do OTA Updates, even if you build exceptions inside your loop code.

## Usage

```c++
OTAHelper ota = new OTAHelper("HOSTNAME", "PASSWORD");

void setup() {

    // setup wifi first

    ota.setStatusCallback(handleOTAStatus);
    /**
     * Checks the last reboot reason.
     * On an error the setup functions waits n seconds to run a OTA Update
     */
    ota.setup(); 

    // other setup stuff
}

void handleOTAStatus(String ip, boolean error, String reason) {
    //e.g. send message via pushover
    if(error) {
        //Pushover po = Pushover("XXX", "XXX");
        //po.setTitle("OTA Update");
        //po.setMessage("OTA Update failed: " + ip + ", reason: " + reason);
        //po.setSound(F("none"));
        //po.send();
    }
}

void loop() {

    // your stuff

    /**
     * Enables you to run a OTA update during normal operation
     */
    ota.loop();
}
```
