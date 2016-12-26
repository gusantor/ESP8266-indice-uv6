String formularioConfiguracion(){

  String tex = "";
  int n = WiFi.scanNetworks();
  
  tex += "<p><a href=\"/configuracion/estado\">Estado</a> | <a href=\"/login?DISCONNECT=YES\">Logout</a></p>";
  tex += "<fieldset class=\"configuracion\"><legend>Local</legend>";
  if (WiFi.status() == WL_CONNECTED) {
    String currAP = WiFi.SSID();
    tex += "<h2>Conectado a " + currAP + "</h2>";
  }else{
    tex += "<h2>No conectado</h2>";
  }
  if (n == 0) {
    tex += "</p>No se encontraron redes inal&aacute;mbricas</p>";
  } else  {
    
    tex += "<p>Redes inal&aacute;mbricas encontradas</p>";
    tex += "<form action=\"/configuracion/coneccion-ap\" method=\"post\">";
    int anotadas = 0;
    for (int i = 0; i < n; ++i)// 10=n
    {
      //if((WiFi.RSSI(i)>-70)&&(i<7)){
      if((WiFi.RSSI(i)>-80)&&(anotadas<7)){
        // Print SSID and RSSI for each network found
        tex += "<p>" + String(i + 1);
        tex += ": ";
        tex += WiFi.SSID(i)+" ";
        tex += "<label>Ssid</label> <input type=\"radio\" name=\"ssid-selected[]\" value=\"" + String(WiFi.SSID(i)) + "\">";
        tex += "<label>Pass</label> <input type=\"password\" name=\"ssid-pass[]\" value=\"\">";
        tex += " (";
        tex += WiFi.RSSI(i);
        tex += ")";
        tex += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
        tex += "</p>";
        anotadas++;
        delay(10);
      }
    }
    
    
    tex += "<input type=\"submit\" value=\"Enviar\">";
    tex += "</form>";

    /*tex += "<form action=\"/configuracion/set-puerto\" method=\"post\">";
    tex += "<p><label>Puerto</label> <input type=\"text\" name=\"puerto\" value=\"\"></p> ";
    tex += "<input type=\"submit\" value=\"Enviar\">";
    tex += "</form>";*/
    
    tex += "<form action=\"/configuracion/reset-pass\" method=\"post\">";
    tex += "<p><label>Clave</label> <input type=\"password\" name=\"new-pass\" value=\"\"></p> ";
    tex += "<p><label>Confirma clave</label> <input type=\"password\" name=\"confirm-new-pass\" value=\"\"></p>";
    tex += "<input type=\"submit\" value=\"Enviar\">";
    tex += "</form>";
    
    tex += "<form action=\"/configuracion/set-ubicacion\" method=\"post\">";
    tex += "<p class=\"form-comment\">La direcci&oacute;n guardada es : ";

    tex += estaVacio(stored_location.addr)?"sin datos":stored_location.addr;
    
    tex += "</p>";
    tex += "<p><label>Direcci&oacute;n</label> <input type=\"text\" name=\"ubicacion-direccion\" value=\"\"></p> ";
    tex += "<input type=\"submit\" value=\"Enviar\">";
    tex += "<p class=\"form-comment advertencia\">Mapa disponible solo con conecci&oacute;n a internet</p>";
    tex += "</form>";
    tex += "</fieldset>";
    
    tex += "<fieldset class=\"configuracion\"><legend>Remoto</legend>";
    tex += "<form action=\"/configuracion/set-estacion\" method=\"post\">";
    tex += "<p class=\"form-comment\">La estaci&oacute;n guardada es : ";
    
    tex += estaVacio(stored_estacion.id)?"sin datos":stored_estacion.id;
    
    tex += ", ";
    
    tex += estaVacio(stored_estacion.nombre)?"sin datos":stored_estacion.nombre;
    
    tex += "</p>";
    tex += "<div id=\"estaciones\">ninguna estaci&oacute;n</div>";
    tex += "<input type=\"submit\" value=\"Enviar\">";
    tex += "<p class=\"form-comment advertencia\">Remoto solo disponible con conecci&oacute;n a internet</p>";
    tex += "</form>";
    tex += "</fieldset>";

    tex += "<fieldset class=\"configuracion\"><legend>Display</legend>";
    tex += "<form action=\"/configuracion/set-display\" method=\"post\">";
    tex += "<p class=\"form-comment\">La configuraci&oacute;n guardada es : modo > ";
    
    tex += estaVacio(stored_display.dmode)?"sin datos":stored_display.dmode;
    
    tex += ", prioridad > ";
    
    tex += estaVacio(stored_display.dpriority)?"sin datos":stored_display.dpriority;
    
    tex += "</p>";

    tex += "<p>Modo: <label><input type=\"radio\" value=\"mostrar-solo-principal\" name=\"display-mode\">Mostrar solo principal</label> ";
    //tex += "<label><input type=\"radio\" value=\"Mostrar solo remoto\" name=\"display-mode\">Mostrar solo remoto</label> ";
    tex += "<label><input type=\"radio\" value=\"mostrar-ambos\" name=\"display-mode\">Mostrar ambos</label></p>";
    tex += "<p>Prioridad: <label><input type=\"radio\" value=\"Principal local - secundario remoto\" name=\"display-priority\">Principal local - secundario remoto</label> ";
    tex += "<label><input type=\"radio\" value=\"Principal remoto - secundario local\" name=\"display-priority\">Principal remoto - secundario local</label></p>";
    tex += "<input type=\"submit\" value=\"Enviar\">";
    tex += "<p class=\"form-comment advertencia\">Remoto solo disponible con conecci&oacute;n a internet</p>";
    tex += "</form>";
    tex += "</fieldset>";

    tex += "";
    
    tex += "</form>";
    
    tex += "</fieldset>";

  }

  return tex;

}
