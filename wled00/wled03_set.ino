/*
 * Receives client input
 */

void _setRandomColor(bool _sec)
{
  lastRandomIndex = strip.get_random_wheel_index(lastRandomIndex);
  uint32_t _color = strip.color_wheel(lastRandomIndex);
  if (_sec){
    whiteSec = ((_color >> 24) & 0xFF);
    colSec[0] = ((_color >> 16) & 0xFF);
    colSec[1] = ((_color >> 8) & 0xFF);
    colSec[2] = (_color & 0xFF);
  } else {
    white = ((_color >> 24) & 0xFF);
    col[0] = ((_color >> 16) & 0xFF);
    col[1] = ((_color >> 8) & 0xFF);
    col[2] = (_color & 0xFF);
  }
}

void handleSettingsSet(byte subPage)
{
  //0: menu 1: wifi 2: leds 3: ui 4: sync 5: time 6: sec
  if (subPage <1 || subPage >6) return;
  
  //WIFI SETTINGS
  if (subPage == 1)
  {
    if (server.hasArg("CSSID")) clientSSID = server.arg("CSSID");
    if (server.hasArg("CPASS"))
    {
      if (!server.arg("CPASS").indexOf('*') == 0)
      {
        DEBUG_PRINTLN("Setting pass");
        clientPass = server.arg("CPASS");
      }
    }
    if (server.hasArg("CMDNS")) cmDNS = server.arg("CMDNS");
    if (server.hasArg("APWTM"))
    {
        int i = server.arg("APWTM").toInt();
        if (i >= 0 && i <= 255) apWaitTimeSecs = i;
    }
    if (server.hasArg("APSSID")) apSSID = server.arg("APSSID");
    apHide = server.hasArg("APHSSID");
    if (server.hasArg("APPASS"))
    {
      if (!server.arg("APPASS").indexOf('*') == 0) apPass = server.arg("APPASS");
    }
    if (server.hasArg("APCHAN"))
    {
      int chan = server.arg("APCHAN").toInt();
      if (chan > 0 && chan < 14) apChannel = chan;
    }
    if (server.hasArg("CSIP0"))
    {
      int i = server.arg("CSIP0").toInt();
      if (i >= 0 && i <= 255) staticIP[0] = i;
    }
    if (server.hasArg("CSIP1"))
    {
      int i = server.arg("CSIP1").toInt();
      if (i >= 0 && i <= 255) staticIP[1] = i;
    }
    if (server.hasArg("CSIP2"))
    {
      int i = server.arg("CSIP2").toInt();
      if (i >= 0 && i <= 255) staticIP[2] = i;
    }
    if (server.hasArg("CSIP3"))
    {
      int i = server.arg("CSIP3").toInt();
      if (i >= 0 && i <= 255) staticIP[3] = i;
    }
    if (server.hasArg("CSGW0"))
    {
      int i = server.arg("CSGW0").toInt();
      if (i >= 0 && i <= 255) staticGateway[0] = i;
    }
    if (server.hasArg("CSGW1"))
    {
      int i = server.arg("CSGW1").toInt();
      if (i >= 0 && i <= 255) staticGateway[1] = i;
    }
    if (server.hasArg("CSGW2"))
    {
      int i = server.arg("CSGW2").toInt();
      if (i >= 0 && i <= 255) staticGateway[2] = i;
    }
    if (server.hasArg("CSGW3"))
    {
      int i = server.arg("CSGW3").toInt();
      if (i >= 0 && i <= 255) staticGateway[3] = i;
    }
    if (server.hasArg("CSSN0"))
    {
      int i = server.arg("CSSN0").toInt();
      if (i >= 0 && i <= 255) staticSubnet[0] = i;
    }
    if (server.hasArg("CSSN1"))
    {
      int i = server.arg("CSSN1").toInt();
      if (i >= 0 && i <= 255) staticSubnet[1] = i;
    }
    if (server.hasArg("CSSN2"))
    {
      int i = server.arg("CSSN2").toInt();
      if (i >= 0 && i <= 255) staticSubnet[2] = i;
    }
    if (server.hasArg("CSSN3"))
    {
      int i = server.arg("CSSN3").toInt();
      if (i >= 0 && i <= 255) staticSubnet[3] = i;
    }
  }

  //LED SETTINGS
  if (subPage == 2)
  {
    if (server.hasArg("LEDCN"))
    {
      int i = server.arg("LEDCN").toInt();
      if (i >= 0 && i <= LEDCOUNT) ledCount = i;
      strip.setLedCount(ledCount);
    }
    if (server.hasArg("CBEOR")) //ignore settings and save current brightness, colors and fx as default
    {
      colS[0] = col[0];
      colS[1] = col[1];
      colS[2] = col[2];
      if (useRGBW) whiteS = white;
      briS = bri;
      effectDefault = effectCurrent;
      effectSpeedDefault = effectSpeed;
    } else {
      if (server.hasArg("CLDFR"))
      {
        int i = server.arg("CLDFR").toInt();
        if (i >= 0 && i <= 255) colS[0] = i;
      }
      if (server.hasArg("CLDFG"))
      {
        int i = server.arg("CLDFG").toInt();
        if (i >= 0 && i <= 255) colS[1] = i;
      }
      if (server.hasArg("CLDFB"))
      {
        int i = server.arg("CLDFB").toInt();
        if (i >= 0 && i <= 255) colS[2] = i;
      }
      if (server.hasArg("CSECR"))
      {
        int i = server.arg("CSECR").toInt();
        if (i >= 0 && i <= 255) colSecS[0] = i;
      }
      if (server.hasArg("CSECG"))
      {
        int i = server.arg("CSECG").toInt();
        if (i >= 0 && i <= 255) colSecS[1] = i;
      }
      if (server.hasArg("CSECB"))
      {
        int i = server.arg("CSECB").toInt();
        if (i >= 0 && i <= 255) colSecS[2] = i;
      }
      if (server.hasArg("CSECW"))
      {
        int i = server.arg("CSECW").toInt();
        if (i >= 0 && i <= 255) whiteSecS = i;
      }
      if (server.hasArg("CLDFW"))
      {
        int i = server.arg("CLDFW").toInt();
        if (i >= 0 && i <= 255)
        {
          useRGBW = true;
          whiteS = i;
        } else {
          useRGBW = false;
          whiteS = 0;
        }
      }
      if (server.hasArg("CLDFA"))
      {
        int i = server.arg("CLDFA").toInt();
        if (i >= 0 && i <= 255) briS = i;
      }
      if (server.hasArg("FXDEF"))
      {
        int i = server.arg("FXDEF").toInt();
        if (i >= 0 && i <= 255) effectDefault = i;
      }
      if (server.hasArg("SXDEF"))
      {
        int i = server.arg("SXDEF").toInt();
        if (i >= 0 && i <= 255) effectSpeedDefault = i;
      }
      if (server.hasArg("IXDEF"))
      {
        int i = server.arg("IXDEF").toInt();
        if (i >= 0 && i <= 255) effectIntensityDefault = i;
      }
    }
    turnOnAtBoot = server.hasArg("BOOTN");
    if (server.hasArg("BOOTP"))
    {
      int i = server.arg("BOOTP").toInt();
      if (i >= 0 && i <= 25) bootPreset = i;
    }
    useGammaCorrectionBri = server.hasArg("GCBRI");
    useGammaCorrectionRGB = server.hasArg("GCRGB");
    fadeTransition = server.hasArg("TFADE");
    sweepTransition = server.hasArg("TSWEE");
    sweepDirection = !server.hasArg("TSDIR");
    if (server.hasArg("TDLAY"))
    {
      int i = server.arg("TDLAY").toInt();
      if (i > 0){
        transitionDelay = i;
      }
    }
    if (server.hasArg("TLBRI"))
    {
      nightlightTargetBri = server.arg("TLBRI").toInt();
    }
    if (server.hasArg("TLDUR"))
    {
      int i = server.arg("TLDUR").toInt();
      if (i > 0) nightlightDelayMins = i;
    }
    nightlightFade = server.hasArg("TLFDE");
    reverseMode = server.hasArg("LEDRV");
    strip.setReverseMode(reverseMode);
    if (server.hasArg("WOFFS"))
    {
      int i = server.arg("WOFFS").toInt();
      if (i >= -255  && i <= 255) arlsOffset = i;
    }
    if (server.hasArg("NRBRI"))
    {
      int i = server.arg("NRBRI").toInt();
      if (i > 0) briMultiplier = i;
    }
  }

  //UI
  if (subPage == 3)
  {
    if (server.hasArg("DESC")) serverDescription = server.arg("DESC");
    useHSBDefault = server.hasArg("COLMD");
    useHSB = useHSBDefault;
    if (server.hasArg("THEME")) currentTheme = server.arg("THEME").toInt();
    for(int i=0;i<6;i++)
    {
      if (server.hasArg("CCOL"+String(i))) cssCol[i] = server.arg("CCOL"+String(i));
    }
    if (server.hasArg("CFONT")) cssFont = server.arg("CFONT");
    buildCssColorString();
  }

  //SYNC
  if (subPage == 4)
  {
    buttonEnabled = server.hasArg("BTNON");
    if (server.hasArg("NUDPP"))
    {
      udpPort = server.arg("NUDPP").toInt();
    }
    receiveNotificationBrightness = server.hasArg("NRCBR");
    receiveNotificationColor = server.hasArg("NRCCL");
    receiveNotificationEffects = server.hasArg("NRCFX");
    receiveNotifications = (receiveNotificationBrightness || receiveNotificationColor || receiveNotificationEffects);
    notifyDirectDefault = server.hasArg("NSDIR");
    notifyDirect = notifyDirectDefault;
    notifyButton = server.hasArg("NSBTN");
    notifyTwice = server.hasArg("NS2XS");
    alexaEnabled = server.hasArg("ALEXA");
    if (server.hasArg("AINVN")) alexaInvocationName = server.arg("AINVN");
    alexaNotify = server.hasArg("NSALX");
    notifyHue = server.hasArg("NSHUE");
    for (int i=0;i<4;i++){
      String a = "HUIP"+String(i);
      if (server.hasArg(a))
        hueIP[i] = server.arg(a).toInt();
    }
    if (server.hasArg("HUELI"))
    {
      int i = server.arg("HUELI").toInt();
      if (i > 0) huePollLightId = i;
    }
    if (server.hasArg("HUEPI"))
    {
      int i = server.arg("HUEPI").toInt();
      if (i > 50) huePollIntervalMs = i;
    }
    hueApplyOnOff = server.hasArg("HURIO");
    hueApplyBri = server.hasArg("HURBR");
    hueApplyColor = server.hasArg("HURCL");
    if (server.hasArg("HUEPL"))
    {
      if (!huePollingEnabled) hueAttempt = true;
      if (!setupHue()) hueAttempt = true;
    } else
    {
      huePollingEnabled = false;
      hueError = "Inactive";
    }
  }

  //TIME
  if (subPage == 5)
  {
    ntpEnabled = server.hasArg("NTPON");
    useAMPM = !server.hasArg("CL24H");
    if (server.hasArg("TZONE")) currentTimezone = server.arg("TZONE").toInt();
    if (server.hasArg("UTCOS")) utcOffsetSecs = server.arg("UTCOS").toInt();
    if (ntpEnabled && WiFi.status() == WL_CONNECTED && !ntpConnected) ntpConnected = ntpUdp.begin(ntpLocalPort); //start if not already connected
    
    if (server.hasArg("OLMDE")){
      overlayDefault = server.arg("OLMDE").toInt();
      overlayCurrent = overlayDefault;
      strip.unlockAll();
    }
    if (server.hasArg("OLIN1")) overlayMin = server.arg("OLIN1").toInt();
    if (server.hasArg("OLIN2")) overlayMax = server.arg("OLIN2").toInt();
    if (server.hasArg("OLINM")) analogClock12pixel = server.arg("OLINM").toInt();
    analogClock5MinuteMarks = server.hasArg("OL5MI");
    analogClockSecondsTrail = server.hasArg("OLSTR");
    
    if (server.hasArg("CRONX")) cronixieDisplay = server.arg("CRONX");
    bool cbOld = cronixieBacklight;
    cronixieBacklight = server.hasArg("CROBL");
    if (cbOld != cronixieBacklight && overlayCurrent == 4)
    {
      strip.setCronixieBacklight(cronixieBacklight); overlayRefreshedTime = 0;
    }
    countdownMode = server.hasArg("CLCND");
    if (server.hasArg("CDGYR")) countdownYear = server.arg("CDGYR").toInt();
    if (server.hasArg("CDGMN")) countdownMonth = server.arg("CDGMN").toInt();
    if (server.hasArg("CDGDY")) countdownDay = server.arg("CDGDY").toInt();
    if (server.hasArg("CDGHR")) countdownHour = server.arg("CDGHR").toInt();
    if (server.hasArg("CDGMI")) countdownMin = server.arg("CDGMI").toInt();
    if (server.hasArg("CDGSC")) countdownSec = server.arg("CDGSC").toInt();
    
    for (int i=1;i<17;i++)
    {
      String a = "MC"+String(i);
      if (server.hasArg(a)) saveMacro(i,server.arg(a),false);
    }
    if (server.hasArg("MCRBT")) macroBoot = server.arg("MCRBT").toInt();
    if (server.hasArg("MCA0I")) macroAlexaOn = server.arg("MCA0I").toInt();
    if (server.hasArg("MCA0O")) macroAlexaOff = server.arg("MCA0O").toInt();
    if (server.hasArg("MCB0D")) macroButton = server.arg("MCB0D").toInt();
    if (server.hasArg("MCB0L")) macroLongPress = server.arg("MCB0L").toInt();
    if (server.hasArg("MCNTD")) macroCountdown = server.arg("MCNTD").toInt();
    if (server.hasArg("MCNLO")) macroNl = server.arg("MCNLO").toInt();
  }

  //SECURITY
  if (subPage == 6)
  {
    if (server.hasArg("RESET"))
    {
      clearEEPROM();
      serveMessage(200, "All Settings erased.", "Connect to WLED-AP to setup again...",255);
      reset();
    }

    bool pwdCorrect = !otaLock; //always allow access if ota not locked
    if (server.hasArg("OPASS"))
    {
      if (otaLock && otaPass.equals(server.arg("OPASS")))
      {
        pwdCorrect = true;
      }
      if (!otaLock && server.arg("OPASS").length() > 0)
      {
        otaPass = server.arg("OPASS");
      }
    }
    
    if (pwdCorrect) //allow changes if correct pwd or no ota active
    {
      otaLock = server.hasArg("NOOTA");
      wifiLock = server.hasArg("OWIFI");
      recoveryAPDisabled = server.hasArg("NORAP");
      aOtaEnabled = server.hasArg("AROTA");
    }
  }

  saveSettingsToEEPROM();
}

bool handleSet(String req)
{
   bool effectUpdated = false;
   if (!(req.indexOf("win") >= 0)) {
        return false;
   }
   int pos = 0;
   DEBUG_PRINT("API req: ");
   DEBUG_PRINTLN(req);
   
   //save macro, requires &MS=<slot>(<macro>) format
   pos = req.indexOf("&MS=");
   if (pos > 0) {
      int i = req.substring(pos + 4).toInt();
      pos = req.indexOf('(') +1;
      if (pos > 0) { 
        int en = req.indexOf(')');
        String mc = req.substring(pos);
        if (en > 0) mc = req.substring(pos, en);
        saveMacro(i, mc); 
      }
      
      pos = req.indexOf("IN");
      if (pos < 1) XML_response();
      return true;
      //if you save a macro in one request, other commands in that request are ignored due to unwanted behavior otherwise
   }
   
   //set brigthness
   pos = req.indexOf("&A=");
   if (pos > 0) {
      bri = req.substring(pos + 3).toInt();
   }

   //set hue
   pos = req.indexOf("HU=");
   if (pos > 0) {
      uint16_t temphue = req.substring(pos + 3).toInt();
      byte tempsat = 255;
      pos = req.indexOf("SA=");
      if (pos > 0) {
        tempsat = req.substring(pos + 3).toInt();
      }
      colorHStoRGB(temphue,tempsat,(req.indexOf("H2")>0)? colSec:col);
   }
   
   //set red value
   pos = req.indexOf("&R=");
   if (pos > 0) {
      col[0] = req.substring(pos + 3).toInt();
   }
   //set green value
   pos = req.indexOf("&G=");
   if (pos > 0) {
      col[1] = req.substring(pos + 3).toInt();
   }
   //set blue value
   pos = req.indexOf("&B=");
   if (pos > 0) {
      col[2] = req.substring(pos + 3).toInt();
   }
   //set white value
   pos = req.indexOf("&W=");
   if (pos > 0) {
      white = req.substring(pos + 3).toInt();
   }
   
   //set 2nd red value
   pos = req.indexOf("R2=");
   if (pos > 0) {
      colSec[0] = req.substring(pos + 3).toInt();
   }
   //set 2nd green value
   pos = req.indexOf("G2=");
   if (pos > 0) {
      colSec[1] = req.substring(pos + 3).toInt();
   }
   //set 2nd blue value
   pos = req.indexOf("B2=");
   if (pos > 0) {
      colSec[2] = req.substring(pos + 3).toInt();
   }
   //set 2nd white value
   pos = req.indexOf("W2=");
   if (pos > 0) {
      whiteSec = req.substring(pos + 3).toInt();
   }
   
   //set 2nd to white
   pos = req.indexOf("SW");
   if (pos > 0) {
      if(useRGBW) {
        whiteSec = 255;
        colSec[0] = 0;
        colSec[1] = 0;
        colSec[2] = 0;
      } else {
        colSec[0] = 255;
        colSec[1] = 255;
        colSec[2] = 255;
      }
   }
   //set 2nd to black
   pos = req.indexOf("SB");
   if (pos > 0) {
      whiteSec = 0;
      colSec[0] = 0;
      colSec[1] = 0;
      colSec[2] = 0;
   }
   //set to random hue SR=0->1st SR=1->2nd
   pos = req.indexOf("SR");
   if (pos > 0) {
      _setRandomColor(req.substring(pos + 3).toInt());
   }
   //set 2nd to 1st
   pos = req.indexOf("SP");
   if (pos > 0) {
      colSec[0] = col[0];
      colSec[1] = col[1];
      colSec[2] = col[2];
      whiteSec = white;
   }
   //swap 2nd & 1st
   pos = req.indexOf("SC");
   if (pos > 0) {
      byte _temp[4];
      for (int i = 0; i<3; i++)
      {
        _temp[i] = col[i];
        col[i] = colSec[i];
        colSec[i] = _temp[i];
      }
      _temp[3] = white;
      white = whiteSec;
      whiteSec = _temp[3];
   }
   
   //set current effect index
   pos = req.indexOf("FX=");
   if (pos > 0) {
      if (effectCurrent != req.substring(pos + 3).toInt())
      {
        effectCurrent = req.substring(pos + 3).toInt();
        strip.setMode(effectCurrent);
        effectUpdated = true;
      }
   }
   //set effect speed
   pos = req.indexOf("SX=");
   if (pos > 0) {
      if (effectSpeed != req.substring(pos + 3).toInt())
      {
        effectSpeed = req.substring(pos + 3).toInt();
        strip.setSpeed(effectSpeed);
        effectUpdated = true;
      }
   }
   //set effect intensity
   pos = req.indexOf("IX=");
   if (pos > 0) {
      if (effectIntensity != req.substring(pos + 3).toInt())
      {
        effectIntensity = req.substring(pos + 3).toInt();
        strip.setIntensity(effectIntensity);
        effectUpdated = true;
      }
   }

   //set hue polling light: 0 -off
   pos = req.indexOf("HP=");
   if (pos > 0) {
      int id = req.substring(pos + 3).toInt();
      if (id > 0)
      {
        if (id < 100) huePollLightId = id;
        setupHue();
      } else {
        huePollingEnabled = false;
      }
   }
   
   //set default control mode (0 - RGB, 1 - HSB)
   pos = req.indexOf("MD=");
   if (pos > 0) {
      useHSB = req.substring(pos + 3).toInt();
   }
   //set advanced overlay
   pos = req.indexOf("OL=");
   if (pos > 0) {
        overlayCurrent = req.substring(pos + 3).toInt();
        strip.unlockAll();
   }
   //set individual pixel (range) to current color
   pos = req.indexOf("&I=");
   if (pos > 0){
      int index = req.substring(pos + 3).toInt();
      pos = req.indexOf("I2=");
      if (pos > 0){
        int index2 = req.substring(pos + 3).toInt();
        strip.setRange(index, index2);
      } else
      {
        strip.setIndividual(index);
      }
   }
   //(un)lock pixel (ranges)
   pos = req.indexOf("&L=");
   if (pos > 0){
      int index = req.substring(pos + 3).toInt();
      pos = req.indexOf("L2=");
      if (pos > 0){
        int index2 = req.substring(pos + 3).toInt();
        if (req.indexOf("UL") > 0)
        {
          strip.unlockRange(index, index2);
        } else
        {
          strip.lockRange(index, index2);
        }
      } else
      {
        if (req.indexOf("UL") > 0)
        {
          strip.unlock(index);
        } else
        {
          strip.lock(index);
        }
      }
   }
   //apply macro
   pos = req.indexOf("&M=");
   if (pos > 0) {
      applyMacro(req.substring(pos + 3).toInt());
   }
   //toggle send UDP direct notifications
   if (req.indexOf("SN=") > 0)
   {
      notifyDirect = true;
      if (req.indexOf("SN=0") > 0)
      {
        notifyDirect = false;
      }
   }
   //toggle receive UDP direct notifications
   if (req.indexOf("RN=") > 0)
   {
      receiveNotifications = true;
      if (req.indexOf("RN=0") > 0)
      {
        receiveNotifications = false;
      }
   }
   //toggle nightlight mode
   pos = req.indexOf("NL=");
   if (pos > 0)
   {
      if (req.indexOf("NL=0") > 0)
      {
        nightlightActive = false;
        bri = briT;
      } else {
        nightlightActive = true;
        nightlightDelayMins = req.substring(pos + 3).toInt();
        nightlightStartTime = millis();
      }
   }
   //set nightlight target brightness
   pos = req.indexOf("NT=");
   if (pos > 0) {
      nightlightTargetBri = req.substring(pos + 3).toInt();
      nightlightActiveOld = false; //re-init
   }
   //toggle nightlight fade
   if (req.indexOf("NF=") > 0)
   {
      if (req.indexOf("NF=0") > 0)
      {
        nightlightFade = false;
      } else {
        nightlightFade = true;
      }
      nightlightActiveOld = false; //re-init
   }
   //toggle general purpose output
   pos = req.indexOf("AX=");
   if (pos > 0) {
      auxTime = req.substring(pos + 3).toInt();
      auxActive = true;
      if (auxTime == 0) auxActive = false;
   }
   //main toggle on/off
   pos = req.indexOf("&T=");
   if (pos > 0) {
      switch (req.substring(pos + 3).toInt())
      {
        case 0: if (bri != 0){briLast = bri; bri = 0;} break; //off
        case 1: bri = briLast; break; //on
        default: if (bri == 0) //toggle
        {
          bri = briLast;
        } else
        {
          briLast = bri;
          bri = 0;
        }
      }
   }
   //set time (unix timestamp)
   pos = req.indexOf("ST=");
   if (pos > 0) {
      setTime(req.substring(pos+3).toInt());
   }
   //set countdown goal (unix timestamp)
   pos = req.indexOf("CT=");
   if (pos > 0) {
      countdownTime = req.substring(pos+3).toInt();
      if (countdownTime - now() > 0) countdownOverTriggered = false;
   }
   
   //set custom chase data
   bool _cc_updated = false;
   pos = req.indexOf("C0="); if (pos > 0) {ccStart =  (req.substring(pos + 3).toInt()); _cc_updated = true;}
   pos = req.indexOf("C1="); if (pos > 0) {ccIndex1 = (req.substring(pos + 3).toInt()); _cc_updated = true;}
   pos = req.indexOf("C2="); if (pos > 0) {ccIndex2 = (req.substring(pos + 3).toInt()); _cc_updated = true;}
   pos = req.indexOf("CP="); if (pos > 0) {ccNumPrimary = (req.substring(pos + 3).toInt()); _cc_updated = true;}
   pos = req.indexOf("CS="); if (pos > 0) {ccNumSecondary = (req.substring(pos + 3).toInt()); _cc_updated = true;}
   pos = req.indexOf("CM="); if (pos > 0) {ccStep = (req.substring(pos + 3).toInt()); _cc_updated = true;}
   pos = req.indexOf("CF="); if (pos > 0) {ccFromStart = (req.substring(pos + 3).toInt()); _cc_updated = true;}
   pos = req.indexOf("CE="); if (pos > 0) {ccFromEnd = (req.substring(pos + 3).toInt()); _cc_updated = true;}
   if (_cc_updated) strip.setCustomChase(ccIndex1, ccIndex2, ccStart, ccNumPrimary, ccNumSecondary, ccStep, ccFromStart, ccFromEnd);
   
   //set presets
   pos = req.indexOf("PS="); //saves current in preset
   if (pos > 0) {
      savePreset(req.substring(pos + 3).toInt());
   }
   pos = req.indexOf("PL="); //applies entire preset
   if (pos > 0) {
      applyPreset(req.substring(pos + 3).toInt(), true, true, true);
      effectUpdated = true;
   }
   pos = req.indexOf("PA="); //applies brightness from preset
   if (pos > 0) {
      applyPreset(req.substring(pos + 3).toInt(), true, false, false);
   }
   pos = req.indexOf("PC="); //applies color from preset
   if (pos > 0) {
      applyPreset(req.substring(pos + 3).toInt(), false, true, false);
   }
   pos = req.indexOf("PX="); //applies effects from preset
   if (pos > 0) {
      applyPreset(req.substring(pos + 3).toInt(), false, false, true);
      effectUpdated = true;
   }

   //cronixie
   pos = req.indexOf("NX="); //sets digits to code
   if (pos > 0) {
      cronixieDisplay = req.substring(pos + 3, pos + 9);
      setCronixie();
   }
   pos = req.indexOf("NM="); //mode, 1 countdown
   if (pos > 0) {
      countdownMode = true;
      if (req.indexOf("NM=0") > 0)
      {
        countdownMode = false;
      }
   }
   if (req.indexOf("NB=") > 0) //sets backlight
   {
      cronixieBacklight = true;
      if (req.indexOf("NB=0") > 0)
      {
        cronixieBacklight = false;
      }
      if (overlayCurrent == 4) strip.setCronixieBacklight(cronixieBacklight);
      overlayRefreshedTime = 0;
   }

   //internal call, does not send XML response
   pos = req.indexOf("IN");
   if (pos < 1) XML_response();
   //do not send UDP notifications this time
   pos = req.indexOf("NN");
   if (pos > 0)
   {
      colorUpdated(5);
      return true;
   }
   if (effectUpdated)
   {
      colorUpdated(6);
   } else
   {
      colorUpdated(1);
   }
   return true;
}
