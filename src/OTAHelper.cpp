/**
 * OTAHelper
 * Copyright (C) 2020 kleinMantara <code@kleinmantara.de>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * https://github.com/kleinmantara/
 */
#include "OTAHelper.h"

OTAHelper::OTAHelper(char* hostName, char* password, unsigned long normalWaitTime, unsigned long errorWaitTime) {
    _hostName = hostName;
    _password = password;
    _normalWaitTime = normalWaitTime;
    _errorWaitTime = errorWaitTime;
}

void OTAHelper::setStatusCallback(void (*callback)(String ip, boolean error, String resetInfo)) {
  _callback = callback;
}

void OTAHelper::setup() {
  ArduinoOTA.setHostname(_hostName);
  ArduinoOTA.setPassword(_password);
  ArduinoOTA.begin();


  int waitTimeForOTA = _normalWaitTime;

  if (isErrorReason()) {
    if(_callback) {
      _callback(WiFi.localIP().toString(), true, ESP.getResetInfo());
    }
    waitTimeForOTA = _errorWaitTime;
  } else {
    _callback(WiFi.localIP().toString(), false, ESP.getResetInfo());
  }

  uint32_t beginWait = millis();
  while (millis() - beginWait < waitTimeForOTA) {
    ArduinoOTA.handle();
    yield();
  }
}

t_httpUpdate_return OTAHelper::updateFirmwareIfNeeded(String url) {
    // https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266httpUpdate/src/ESP8266httpUpdate.cpp
    return ESPhttpUpdate.update(url);
}


void OTAHelper::loop() {
    ArduinoOTA.handle();
}

boolean OTAHelper::isErrorReason() {
  //https://github.com/esp8266/Arduino/blob/f1a8287bb380cd1fc09a3e0c5c86c9ac7de65788/cores/esp8266/Esp.cpp#L301-L312
  rst_info* rinfo = ESP.getResetInfoPtr();
  int reason = rinfo->reason;

  /**
     0 DEFAULT
     1 WDT
     2 EXCEPTION
     3 SOFT_WDT
     4 SOFT_RESTART > OTA-Update
     5 DEEP_SLEEP_AWAKE
     6 EXT_SYS_RST
  */
  if (reason == 1 // WDT
      || reason == 2 // EXCEPTION
      || reason == 3 // SOFT_WDT
     ) {
    return true;
  }

  return false;
}