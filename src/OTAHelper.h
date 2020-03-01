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
 * code@kleinmantara.de
 * https://github.com/kleinmantara/
 */

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266httpUpdate.h>
#include <Esp.h>

class OTAHelper {
    public:
        typedef enum UpdateStatus {
        failed,
        levelInfo,
        levelDebug
        } UpdateStatus_t;

        OTAHelper(char* hostName, char* password, unsigned long normalWaitTime = 2000, unsigned long errorWaitTime = 6000);
        void setStatusCallback(void (*callback)(String ip, boolean error, String resetInfo));
        
        // https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266httpUpdate/src/ESP8266httpUpdate.h#L60
        t_httpUpdate_return updateFirmwareIfNeeded(String url);
        
        void setup();
        void loop();
    private:
        char* _hostName;
        char* _password;
        unsigned long _normalWaitTime;
        unsigned long _errorWaitTime;
        void (*_callback)(String ip, boolean error, String resetInfo);
        boolean isErrorReason();
};
