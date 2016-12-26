void handleSta() {
  if (!is_authentified()){
    String header;
    header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }
  
  char titulo[100] = {"Connect Station - pezGordo\n"};

  String currAP;
  if (WiFi.status() == WL_CONNECTED) {
  }else{
    mientrasConecta();
  }
  
  String contenido = "<div class=\"content\"><h1>Conecci&oacute;n AP</h1>";  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected");
    Serial.print("heap mem: ");Serial.println(ESP.getFreeHeap());
    Serial.print("IP "); Serial.println(WiFi.localIP());
    IPAddress ip;
    ip = WiFi.localIP();
    String strIP = ip.toString();
    
    currAP = WiFi.SSID();
    
    contenido += "<h2>Conectado a " + currAP + "</h2>";
    contenido += "<div><p>IP <a href=\"http://" + strIP + ":" + port + "\"><span id=\"new-ip\">" + strIP + ":" + port + "</span></a></p>";
    contenido += "<p>SSID " + currAP + " </p>";
    contenido += "<p><span id=\"kill-sta-result\">here next</span></p></div>";
    
  } else {
    contenido += "<h2>No conectado</h2>";
    contenido += "<div>";
    contenido += "<p>No est&aacute;s conectado <span id=\"kill-sta-result\"></span></p></div>";
  }
  
  contenido += "</div>";//fin content
  
  server.send(200, "text/html", doc_start() + doc_header(titulo,'\0') + "\n<body>" + header_html() + contenido + doc_end());
}


void handleRoot(){
  char titulo[100] = {"Inicio - pezGordo\n"};
  String contenido;
  /*contenido += "<div class=\"content\">";
  contenido += "<h1>Home</h1>";
  contenido += "<div>Welcome</div>";
  contenido += "</div>";*/

  contenido = "<div class=\"content inicio\">\n";
  contenido += "<div id=\"contenedor-principal\">\n";
  contenido += "<h1>&Iacute;ndice Ultra Violeta</h1>\n";
  contenido += "<div id=\"principal-indice\" class=\"indice\">&nbsp;</div>\n";
  contenido += "<div id=\"principal-estacion\" class=\"\">&nbsp;</div>\n";
  contenido += "<div id=\"principal-fecha\">&nbsp;</div>\n";
  contenido += "</div>\n";
  contenido += "<div id=\"contenedor-secundario\">\n";
  contenido += "<div id=\"secundario-indice\" class=\"indice\">&nbsp;</div>\n";
  contenido += "<div id=\"secundario-estacion\" class=\"\">&nbsp;</div>\n";
  contenido += "<div id=\"secundario-fecha\" class=\"\">&nbsp</div>\n";
  contenido += "</div>\n";
  contenido += "</div>\n";
  
  //contenido += resp1;
  server.send(200, "text/html", doc_start() + doc_header(titulo,'i') + "\n<body onload=\"javascript:consulta_uvi();\">" + header_html() + contenido + doc_end());
}


void handleAcercaDeIndiceUV() {
  char titulo[100] = {"Acerca del &Iacute;ndice Ultra Violeta"};
  
  String contenido = "<div class=\"content\"><h1>Acerca del &Iacute;ndice Ultra Violeta</h1><p>El &iacute;ndice ultra violeta (iUV) es una medida de la cantidad de radiaci&oacute;n ultra violeta, en el rango de los 240-370nm (UVB, UVA), que est&aacute; afectando un lugar</p>";
  contenido += "<p>Por favor inf&oacute;rmese respecto de los riesgos impl&iacute;citos en la exposici&oacute;n prolongada a la radiaci&oacute;n UV</p>";
  contenido += "</div>";
  
  server.send(200, "text/html", doc_start() + doc_header(titulo,'\0') + "\n<body>" + header_html() + contenido + doc_end());
}


void handleUbicacion(){
  char titulo[100] = "Ubicaci&oacute;n";
  String contenido = "<div class=\"content\"><h1>Ubicaci&oacute;n</h1> ";
  String addr = "";
  if(!estaVacio(stored_location.addr)){
    //Serial.print("Ubicacion guardada ");Serial.println(String(strlen(stored_location.addr)));
    for(int i=0;i<strlen(stored_location.addr);i++){
      addr += stored_location.addr[i];
    }
    //addr.replace(" ","+");
    contenido += "<p>"+addr+"</p>";
  }else{
    contenido += "<p>Sin ubicaci&oacute;n definida</p>";
  }
  if(WiFi.status() == WL_CONNECTED) {
    contenido += "<iframe width=\"600\" height=\"450\" id=\"mapa-ubicacion\" frameborder=\"0\" style=\"border:0\" ";
    contenido += "src=\"https://www.google.com/maps/embed/v1/place?key=AIzaSyBucNT6Q6x-bxPvscv2qVi2VBw5FTCXvP4&q="+addr+"\" allowfullscreen>";
    contenido += "</iframe>";
  }else{
    contenido += "<p>Mapa solo disponible con conecci&oacute;n a internet</p>";
  }
  contenido += "</div>";
  server.send(200, "text/html", doc_start() + doc_header(titulo,'\0') + "\n<body>" + header_html() + contenido + doc_end());
}




//login page, also called for disconnect
void handleLogin(){
  
  char titulo[100] = "Login";
  String contenido = "<div class=\"content\"><h1>Login</h1>";
  
  if (server.hasHeader("Cookie")){
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
    if(cookie=="ESPSESSIONID=1"){
      contenido += "<p>Ya logeado</p>";
      contenido += "<p><a href=\"/login?DISCONNECT=YES\">Logout</a></p>";
    }else{
      contenido += "<form action='/login' method='POST'>";
      contenido += "User:<input type='text' name='USERNAME' placeholder='user name'><br>";
      contenido += "Password:<input type='password' name='PASSWORD' placeholder='password'><br>";
      contenido += "<input type='submit' name='SUBMIT' value='Submit'></form>";
    }
  }else{
    contenido += "<form action='/login' method='POST'>";
    contenido += "User:<input type='text' name='USERNAME' placeholder='user name'><br>";
    contenido += "Password:<input type='password' name='PASSWORD' placeholder='password'><br>";
    contenido += "<input type='submit' name='SUBMIT' value='Submit'></form>";
  }
  if (server.hasArg("DISCONNECT")){
    Serial.println("Disconnection");
    String header = "HTTP/1.1 301 OK\r\nSet-Cookie: ESPSESSIONID=0\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }
  if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")){
    
    Serial.print(String(stored_credential.uname)+" ?");
    Serial.println(String(stored_credential.upass)+" ?");
    
    if(stored_credential.uname>0&&stored_credential.upass>0){
      
      if (server.arg("USERNAME") == String(stored_credential.uname) &&  server.arg("PASSWORD") == String(stored_credential.upass) ){
        String header = "HTTP/1.1 301 OK\r\nSet-Cookie: ESPSESSIONID=1\r\nLocation: /configuracion\r\nCache-Control: no-cache\r\n\r\n";
        server.sendContent(header);
        Serial.println("Log in Successful");
        return;
      }
    }
    contenido += "<p>Error en username/password!.</p>";
    Serial.println("Log in Failed");
  }

  contenido += "</div>";
  server.send(200, "text/html", doc_start() + doc_header(titulo,'\0') + "\n<body>" + header_html() + contenido + doc_end());
  
}

void handleAppStatus() {
  if (!is_authentified()){
    String header;
    header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }

  char titulo[100] = "Configuraci&oacute;n del sistema - Estado";
  String contenido = "<div class=\"content\"><h1>Configuraci&oacute;n del sistema</h1>";
  contenido += "<a href=\"/configuracion\">Modificar</a> | <a href=\"/login?DISCONNECT=YES\">Logout</a></p>";
  Location sloc;
  EEPROM.get(sizeof(Credential),sloc);
  Estacion sest;
  EEPROM.get(sizeof(Credential)+sizeof(Location),sest);
  Display sdis;
  EEPROM.get(sizeof(Credential)+sizeof(Location)+sizeof(Estacion),sdis);

  contenido += "<p>Conecci&oacute;n wifi :" + ((WiFi.status() == WL_CONNECTED)?"conectado a "+WiFi.SSID():"no conectado" ) + "</p>";
  contenido += "<p>Direcci&oacute;n : "+(estaVacio(sloc.addr)?"sin datos":String(sloc.addr))+"</p>";
  contenido += "<p>Estaci&oacute;n : "+(estaVacio(sest.id)?"sin datos":String(sest.id))+", "+(estaVacio(sest.nombre)?"sin datos":String(sest.nombre))+"</p>";
  contenido += "<p>Display : modo > "+(estaVacio(sdis.dmode)?"sin datos":String(sdis.dmode))+", prioridad > "+(estaVacio(sdis.dpriority)?"sin datos":String(sdis.dpriority))+"</p>";
  contenido += "</div>";
  server.send(200, "text/html", doc_start() + doc_header(titulo,'\0') + "\n<body>" + header_html() + contenido + doc_end());
}

void handleConfiguracion() {
  if (!is_authentified()){
    String header;
    header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }

  Serial.printf("settings heap size: %u\n", ESP.getFreeHeap());


  char titulo[100] = "Configuraci&oacute;n del sistema";
  String contenido;
  contenido += "<div class=\"content\"><h1>Configuraci&oacute;n del sistema</h1><div id=\"admin-config-form-container\">formulario ...</div></div>";

  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send(200, "text/html", doc_start() + doc_header(titulo,'a') + "\n<body onload=\"javascript:trae_formulario_admin();\">" + header_html() + contenido + doc_end());
}


void handleAdminForm(){
  if (!is_authentified()){
    String header;
    header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }
  
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  String form = formularioConfiguracion();
  server.send(200, "text/html", form);
}


void handleSetLocation(){
  if (!is_authentified()){
    String header;
    header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }
  
  Serial.println("handle loc");
  if (server.arg("ubicacion-direccion").length()>0&&server.arg("ubicacion-direccion").length()<=100) {
    char charAddr[100];
    String direccion = server.arg("ubicacion-direccion");
    Serial.println(direccion);
    direccion.toCharArray(charAddr,sizeof(charAddr));
    for(int i=0;i<sizeof(charAddr);i++){
      stored_location.addr[i]=charAddr[i];
    }
    EEPROM.put(sizeof(Credential), stored_location);
    EEPROM.commit();
  }
  String header = "HTTP/1.1 301 OK\r\nLocation: /ubicacion\r\nCache-Control: no-cache\r\n\r\n";
  server.sendContent(header);
  return;
}

void handleSetEstacion(){
  if (!is_authentified()){
    String header;
    header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }
  
  //Serial.println("handle estacion");
  if (server.arg("estacion-id").length()>0) {
    char formvalue[120];
    //char charId[20];
    //char charNom[100];
    char *p, *q;

    String estacionId = escapeParameter(server.arg("estacion-id"));
    estacionId.toCharArray(formvalue,sizeof(formvalue));
    
    p = strtok_r(formvalue,"|",&q);
    for(int i=0;i<20;i++){
      stored_estacion.id[i]=p[i];
    }
    p = strtok_r(NULL,"|",&q);
    for(int i=0;i<100;i++){
      stored_estacion.nombre[i]=p[i];
    }

    //Serial.print("stored estacion id:");Serial.println(stored_estacion.id);
    //Serial.print("stored estacion name:");Serial.println(stored_estacion.nombre);
    EEPROM.put(sizeof(Credential)+sizeof(Location), stored_estacion);
    EEPROM.commit();
  }
  String header = "HTTP/1.1 301 OK\r\nLocation: /configuracion\r\nCache-Control: no-cache\r\n\r\n";
  server.sendContent(header);
  return;
}


void handleSetDisplay(){
  if (!is_authentified()){
    String header;
    header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }
  
  Serial.println("handle set dislay");
  boolean noData = true;
  if (server.arg("display-mode").length()>0) {
    char cdmode[50];
    String sdmode = server.arg("display-mode");
    Serial.println(sdmode);
    sdmode.toCharArray(cdmode,sizeof(cdmode));
    for(int i=0;i<sizeof(cdmode);i++){
      stored_display.dmode[i]=cdmode[i];
      //stored_estacion.id[i]=charId[i];
    }
    noData=false;
  }
  if (server.arg("display-priority").length()>0) {
    char cdpriority[50];
    String sdpriority = server.arg("display-priority");
    Serial.println(sdpriority);
    sdpriority.toCharArray(cdpriority,sizeof(cdpriority));
    for(int i=0;i<sizeof(cdpriority);i++){
      stored_display.dpriority[i]=cdpriority[i];
    }
    noData=false;
  }
  if(!noData){
    EEPROM.put(sizeof(Credential)+sizeof(Location)+sizeof(Estacion), stored_display);
    EEPROM.commit();
  }
  String header = "HTTP/1.1 301 OK\r\nLocation: /configuracion\r\nCache-Control: no-cache\r\n\r\n";
  server.sendContent(header);
  return;
}


void handleSetStation() {
  if (!is_authentified()){
    String header;
    header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }
  
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i).startsWith("ssid-selected") && server.arg(i).length() > 0) {
      server.arg(i).toCharArray(bufssid, server.arg(i).length() + 1);
      //Serial.print("ssid: "); Serial.println(bufssid);
    }
    if (server.argName(i).startsWith("ssid-pass") && server.arg(i).length() > 0) {
      server.arg(i).toCharArray(bufsspass, server.arg(i).length() + 1);
      //Serial.print("pass: "); Serial.println(bufsspass);
    }
  }

  char titulo[100] = "Conecci&oacute;n AP";
  String contenido = "<div class=\"content\"><h1>Configuraci&oacute;n del sistema - Conecci&oacute;n AP</h1>";

  contenido += "<div id=\"kill-sta-result\">Esperando ...</div>";
  
  contenido += "</div>";
  
  server.send(200, "text/html", doc_start() + doc_header(titulo,'r') + "\n<body>" + header_html() + contenido + doc_end());
}

void handleKillSta(){
  char titulo[100] = {"Kill Station - pezGordo\n"};

  //ESP.reset();
  String contenido = "<div class=\"content\"><h1>Configuraci&oacute;n de acceso a redes</h1>";
  contenido += "<p>Esperando... <span id=\"killing-ap-result\"></span></p>";
  contenido += "</div>";
  server.send(200, "text/html", doc_start() + doc_header(titulo,'k') + "\n<body>" + header_html() + contenido + doc_end());
  //WiFi.disconnect(true);
  //WiFi.mode(WIFI_AP);
}


void handleKillSta2(){
  if (!is_authentified()){
    String header;
    header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }

  mientrasConecta();
  
  String currAP;
  String contenido;

  if(WiFi.status() == WL_CONNECTED) {
    currAP = WiFi.SSID();
    yield();

    IPAddress ip;
    ip = WiFi.localIP();
    yield();
    String strIP = ip.toString();
    yield();
    
    contenido += "<h2>Conectado a " + currAP + "</h2>";
    contenido += "<div><p>Con IP y puerto <a href=\"http://" + strIP + ":" + port + "\"><span id=\"new-ip\">" + strIP + ":" + port + "</span></a></p>";
    contenido += "<p>Con&eacute;ctate a la red " + currAP + " y navega a esta IP para acceder a tu UVi</p>";
    contenido += "<p>La red " + AP_NameString + " ser&aacute desconectada</p></div>";
    contenido += "<p id=\"kill-ap-result\">&nbsp;</p></div>";
  }else{
    contenido += "<h2>No conectado</h2>";
    contenido += "A&uacute;n no est&aacute;s conectado a ninguna red.";
  }

  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");

  //ESP8266WebServer server(port);
  //yield();
  server.send(200, "text/html", contenido);
  //yield();

  //delay(2000);
  //if(WiFi.status() == WL_CONNECTED) {
    //WiFi.mode(WIFI_STA);
    //yield();
  //else{
    //WiFi.disconnect(true);
    //yield();
    //WiFi.mode(WIFI_AP);
    //yield();
    //configureAP();
    //Serial.println("CONFIGURACION AP LISTA");
  //}

}


void handleKillSta3(){
  if (!is_authentified()){
    String header;
    header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }

  String currAP;
  if(WiFi.status() == WL_CONNECTED) {
    currAP = WiFi.SSID();
    yield();
    //WiFi.mode(WIFI_AP_STA);
    //yield();
  }

  String contenido = ""+(currAP.length()>0?"Se ha desconectado de la red "+currAP:"No est&aacute; conectado a ninguna red")+"";

  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");

  server.send(200, "text/html", contenido);

  WiFi.disconnect(true);
  yield();
  WiFi.mode(WIFI_AP);
  yield();

}

void handleKillAP(){
  if (!is_authentified()){
    String header;
    header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }

  String contenido = "ok, AP killed";
  
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");

  server.send(200, "text/html", contenido);

  if(WiFi.status() == WL_CONNECTED) {
    WiFi.mode(WIFI_STA);
    yield();
  }

}


void handleJSON(){
  String toDisplayData= "";
  String principal_nombre,principal_uvi,principal_fecha,secundario_nombre,secundario_uvi, secundario_fecha, modo;

  //if(strlen(stored_display.dmode)>0){
  if(!estaVacio(stored_display.dmode)){
    //fi(String(stored_display.dmode).equals("mostrar-ambos")){
    modo=String(stored_display.dmode);
  }else{
    modo = "sin-modo";
  }
    //}
    if(String(stored_display.dpriority).equals("Principal local - secundario remoto")){
      //if(strlen(stored_location.addr)>0){
      if(!estaVacio(stored_location.addr)){
        principal_nombre=stored_location.addr;
      }else{
        principal_nombre="local";
      }
      principal_uvi=localUVI;
      principal_fecha=localFechaUlt;
      //if(strlen(stored_estacion.nombre)>0){
      if(!estaVacio(stored_estacion.nombre)){
        secundario_nombre=stored_estacion.nombre;
      }else{
        secundario_nombre="remoto";
      }
      secundario_uvi=remoteUVI;
      remoteFechaUlt.replace("\/","/");
      secundario_fecha=remoteFechaUlt;
    }
    if(String(stored_display.dpriority).equals("Principal remoto - secundario local")){
      //if(strlen(stored_estacion.nombre)>0){
      if(!estaVacio(stored_estacion.nombre)){
        principal_nombre=stored_estacion.nombre;
      }else{
        principal_nombre="remoto";
      }
      principal_uvi=remoteUVI;
      principal_fecha=remoteFechaUlt;
      //if(strlen(stored_location.addr)>0){
      if(!estaVacio(stored_location.addr)){
        secundario_nombre=stored_location.addr;
      }else{
        secundario_nombre="local";
      }
      secundario_uvi=localUVI;
      secundario_fecha = localFechaUlt;
    }
  //}//fin hay display mode
  
  toDisplayData="[{\"nombre\":\""+principal_nombre+"\",\"data\":{\"maximo\":{\"fecha\":\"08/05/2016 13:20\",\"uvi\":0,\"fecha_f\":{\"date\":\"2016-05-08 13:20:00\",\"timezone_type\":3,\"timezone\":\"America/Santiago\"}},\"ultimo\":{\"fecha\":\""+principal_fecha+"\",\"uvi\":"+principal_uvi+",\"fecha_f\":{\"date\":\"2016-05-08 13:20:00\",\"timezone_type\":3,\"timezone\":\"America/Santiago\"}}}},"
  "{\"nombre\":\""+secundario_nombre+"\",\"data\":{\"maximo\":{\"fecha\":\"08/05/2016 15:33\",\"uvi\":0,\"fecha_f\":{\"date\":\"2016-05-08 13:20:00\",\"timezone_type\":3,\"timezone\":\"America/Santiago\"}},\"ultimo\":{\"fecha\":\""+secundario_fecha+"\",\"uvi\":"+secundario_uvi+",\"fecha_f\":{\"date\":\"2016-05-08 13:20:00\",\"timezone_type\":3,\"timezone\":\"America/Santiago\"}}}},"//]";
  "{\"modo\":\""+modo+"\"}]";
    
  server.send(200,"application/json",toDisplayData);
}



void handleCss(){
  server.send ( 200, "text/css", String(style) );
}


void handleNotFound(){
  char titulo[100] = {"Not found\n"};
  String contenido = "<div class=\"content\"><h1>No encontrado</h1>";
  contenido += "</div>";
  server.send(404, "text/html", doc_start() + doc_header(titulo,'\0') + "\n<body>" + header_html() + contenido + doc_end());
}


void handleJSGeneral(){
  server.send(200, "text/html",String(javaScript_General));
}


void handleJSInicio(){
  server.send(200, "text/html",jsInicio());
}

void handleJSAdmin(){
  server.send(200, "text/html",jsAdmin());
}

void handleJSRedirect(){
  server.send(200, "text/html",jsRedirect());
}

void handleJSKillSta(){
  server.send(200, "text/html",jsKillSta());
}

void handleJSKillSta2(){
  server.send(200, "text/html",jsKillStaFR());
}

