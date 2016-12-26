String escapeParameter(String param) {
  param.replace("+", " ");
  param.replace("%21", "!");
  param.replace("%23", "#");
  param.replace("%24", "$");
  param.replace("%26", "&");
  param.replace("%27", "'");
  param.replace("%28", "(");
  param.replace("%29", ")");
  param.replace("%2A", "*");
  param.replace("%2B", "+");
  param.replace("%2C", ",");
  param.replace("%2F", "/");
  param.replace("%3A", ":");
  param.replace("%3B", ";");
  param.replace("%3D", "=");
  param.replace("%3F", "?");
  param.replace("%40", "@");
  param.replace("%5B", "[");
  param.replace("%5D", "]");
  param.replace("á","&aacute;");
  param.replace("é","&eacute;");
  param.replace("í","&iacute;");
  param.replace("ó","&oacute;");
  param.replace("ú","&uacute;");
  param.replace("Á","&Aacute;");
  param.replace("É","&Eacute;");
  param.replace("Í","&Iacute;");
  param.replace("Ó","&Oacute;");
  param.replace("Ú","&Uacute;");

  return param;
}

bool estaVacio(char *test){
  for(int i=0;i<sizeof(test);i++){
    //Serial.print(isAscii(test[i]));Serial.print(" ");
    if(isAscii(test[i])){
      return false;
    }
  }
  return true;
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      parser();
    }
  }
  return;
}

void envia_data(){
  Serial.print("data|");
  //lee_uvi_estacion();
  //if(strlen(stored_display.dmode)>0){
  if(!estaVacio(stored_display.dmode)){
    //Serial.print("dm:");
    Serial.print(stored_display.dmode);
    //Serial.print("|dp:");
    Serial.print("|");
    Serial.print(stored_display.dpriority);
  }else{
    Serial.print("sin-modo|sin-prioridad");
  }
  //if(strlen(stored_estacion.id)>0){
  if(!estaVacio(stored_estacion.id)){
    //Serial.print("|ei:");
    Serial.print("|");
    Serial.print(stored_estacion.id);
    //Serial.print("|en:");
    Serial.print("|");
    Serial.print(stored_estacion.nombre);
  }else{
    Serial.print("|sin-estacion-id|sin-estacion-nombre");
  }
  //Serial.print("|hip:");
  Serial.print("|");
  if(WiFi.status() == WL_CONNECTED) {
    Serial.print(WiFi.localIP());
  }else{
    Serial.print(WiFi.softAPIP());
  }
  //Serial.print("|hpo:");
  //Serial.print("|");
  //Serial.print(port);
  Serial.print(":");
  Serial.print(String(port));
  Serial.print("|");
  Serial.print(remoteUVI);
  Serial.println("");
}

void envia_indice_remoto(){
  Serial.print("iuvr|");
  //if(strlen(stored_display.dmode)>0){
  if(!estaVacio(stored_display.dmode)){
    //Serial.print("dm:");
    //Serial.print("iuvr|");
    Serial.print(stored_display.dmode);
    //Serial.print("|dp:");
    Serial.print("|");
    Serial.print(stored_display.dpriority);
  }else{
    Serial.print("sin-modo|");
    Serial.print("sin-prioridad");
  }
  //if(strlen(stored_estacion.id)>0){
  if(!estaVacio(stored_estacion.id)){
    //Serial.print("|ei:");
    Serial.print("|");
    Serial.print(stored_estacion.id);
    //Serial.print("|en:");
    Serial.print("|");
    Serial.print(stored_estacion.nombre);
  }else{
    Serial.print("|sin-estacion-id|sin-estacion-nombre");
  }
  //Serial.print("|hip:");
  Serial.print("|");
  if(WiFi.status() == WL_CONNECTED) {
    Serial.print(WiFi.localIP());
  }else{
    Serial.print(WiFi.softAPIP());
  }
  //Serial.print("|hpo:");
  //Serial.print("|");
  //Serial.print(port);
  Serial.print(":");
  Serial.print(String(port));
  Serial.print("|");
  Serial.print(remoteUVI);
  Serial.println("");
}

void parser(){
  char formvalue[250];
  char *p, *q;
  inputString.toCharArray(formvalue,sizeof(formvalue));

  p = strtok_r(formvalue,"|",&q);
  tipo = String(p);
  if(tipo=="solIUVR"){
    p = strtok_r(NULL,"|",&q);//indice local1
    localUVI = p;//atoi(p);
    localFechaUlt="";
    if (timeStatus() != timeNotSet) {
      localFechaUlt = printDigits(day()) + "/" + printDigits(month()) + "/" + String(year()) + " " + printDigits(hour()) + ":" + printDigits(minute()); //+ ":" + printDigits(second());
    }
    
    //Serial.print("indice local ");Serial.println(localUVI);
    p = strtok_r(NULL,"|",&q);//indice local 2
    p = strtok_r(NULL,"|",&q);//photo
    p = strtok_r(NULL,"|",&q);//temp
  }
  if(tipo=="solReset"){
    //ResetEEPROM();
  }
  return;
}


String printDigits(int digits) {
  // utility for digital clock display: prints preceding colon and leading 0
  String result = "";
  if (digits < 10)
    result += "0";
  return result + String(digits);
}

void lee_uvi_estacion(){
  if (WiFi.status() == WL_CONNECTED) {
    if(strlen(stored_estacion.id)>0){
      HTTPClient http;
      String url="http://www.pezgordo.cl/indice-uv/json/";
      url += stored_estacion.id;
      http.begin(url); //HTTP
      int httpCode = http.GET();
      if(httpCode > 0) {
        if(httpCode == HTTP_CODE_OK) {
          int commas;
          //String 
          uviPayload = http.getString();
          int firstUVIItem = uviPayload.indexOf("\"uvi\":");
          int firstComma = uviPayload.indexOf(",",firstUVIItem);
          remoteUVIMx = uviPayload.substring(firstUVIItem+6,firstComma);
          int secondUVIItem = uviPayload.indexOf("\"uvi\":", firstUVIItem + 1);
          int secondComma = uviPayload.indexOf(",",secondUVIItem);
          remoteUVI = uviPayload.substring(secondUVIItem+6,secondComma);
          int maxFecha = uviPayload.indexOf("\"fecha\":");
          commas = uviPayload.indexOf(",",maxFecha);
          remoteFechaMax = uviPayload.substring(maxFecha+9,commas-1);

          int ultFecha = uviPayload.indexOf("\"fecha\":",maxFecha+1);
          commas = uviPayload.indexOf(",",ultFecha);
          remoteFechaUlt = uviPayload.substring(ultFecha+9,commas-1);
          
          //Serial.println(uviPayload);
          //Serial.println(String(firstUVIItem)+" "+String(firstComma)+" "+String(secondUVIItem)+" "+String(remoteUVIMx)+" "+String(remoteUVI));
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    }
  }
}
