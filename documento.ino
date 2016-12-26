String doc_start(){
  String doc_start = "<!DOCTYPE HTML><html lang=\"es\">"
  "<meta charset=\"utf-8\">\n";
  return doc_start;
}

String doc_header(char titulo[100], char tipo){
  String doc_header = "<head>" + favicon() +"\n" + scripts(tipo) +"\n" + "<title>" + String(titulo) + "</title>\n";
  doc_header += "<link rel=\"stylesheet\" type=\"text/css\" href=\"/css/esp8266-pezGordo.css\">\n";
  doc_header += "</head>\n";
  return doc_header;
}

String doc_end(){
  String doc_end = "<div class=\"clearfix\"></div>\n<div class=\"powered-by footer\">powered by<br>pezGordo &#169; 2016</div>\n";
  
  if (WiFi.status() == WL_CONNECTED) {
    doc_end += ""
    "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>"
    "<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js\" "
    "integrity=\"sha384-0mSbJDEHialfmuBBQP6A4Qrprq5OVfW37PRR3j5ELqxss1yVqOtnepnHVP9aJ7xS\" crossorigin=\"anonymous\"></script>"
    "<script type=\"text/javascript\" src=\"http://www.pezgordo.cl/sites/all/themes/pezgordo/scripts/esp8266-uvi-pezGordo2.js\"></script>\n";
    "";
  }
  doc_end +="</body>\n</html>";
  return doc_end;
}

String menu(){
  String menu = "<nav class=\"navbar navbar-inverse navbar-fixed-top\">\n"
  "<ul class=\"nav\">\n"
  "<li><a href=\"/\">Inicio</a></li>\n"
  "<li><a href=\"/indice-uv\">&Iacute;ndice Ultra Violeta</a></li>\n"
  "<li><a href=\"/ubicacion\">Ubicaci&oacute;n</a></li><!--<li><a href=\"/aplicacion/control\">Aplicaci&oacute;n</a></li>//-->\n"
  "<li><a href=\"/change-to-sta\">Give credentials</a></li>\n"
  "<li><a href=\"/kill-sta\">Forget SSID</a></li>\n"
  "<li><a href=\"/configuracion\">Configuraci&oacute;n</a></li>\n"
  "<li><a href=\"/login\">Login</a></li>\n"
  "</ul></nav>\n";
  return menu;
}

String header_html(){
  String header_html = "";
  header_html += "<div class=\"header\">\n";
  header_html += menu() + "</div>";//String(menu)
  return header_html;
}


String scripts(char tipo){
  String scripts;
  scripts = "<script type=\"text/javascript\" src=\"/scripts/general.js\"></script>\n";
  switch (tipo){
  case 'g':
    break;
  case 'i':
    if (WiFi.status() == WL_CONNECTED) {
      scripts += "<script type=\"text/javascript\" src=\"/scripts/inicio.js\"></script>\n";
    }
    break;
  case 'a':
    scripts += "<script type=\"text/javascript\" src=\"/scripts/admin.js\"></script>\n";
    break;
  case 'r':
    scripts += "<script type=\"text/javascript\" src=\"/scripts/kill-sta.js\"></script>\n";
    break;
  case 'k':
    scripts += "<script type=\"text/javascript\" src=\"/scripts/kill-sta2.js\"></script>\n";
    break;
  default:
    scripts += "";
    break;
  }
  return scripts;
}

String favicon(){
  String favicon = "<link rel=\"icon\" href=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAABmJLR0QA/wD/AP+gvaeTAAAACXBIWXMAAAsTAAALEwEAmpwYAAAAB3RJTUUH4AQIEgANi7c0rgAAABl0RVh0Q29tbWVudABDcmVhdGVkIHdpdGggR0lNUFeBDhcAAAFfSURBVDjLxdMxa1RBEAfw3z4fGlBSBEESkHRithDMF4jYp7PyWdhqqXbaWSg2ClYiIST4PoFWChaGtNFqOoOoSAoRDBqU3N2zcE+OI8IVggPL7szs/Gf2P7P8b0nQ5pw6TiQu4Bg2mojNSQCqsp9PbOMh7mCjzXllogqe5DyV+IDjGJRV4yeuNBGrbc6p2Cp06DcRfagSZ0eC13GzgB/CUjmfwQv8wA7utTlPK6hT5VKHd7hb9AE+tjnP4iVmsI9pXMMpLFcHcNKVTG/xGBdL8C5u41G5u9jmvFSPAfTwwG9O1vAds8X3bcD9ipO4isOYr8da2msirg8Nbc41too6VxF4elDJwzd3o84motfxDM+xhyOFgz9S4yteoY/3432+FLHbLiwsS+ky5go/w4R7dRPxeqRdf5mWpJD6GTeK9Qu26glH/ihu4VzRP2G9idieFGAfb3B62N4mYu2f/MZfylZkaKXS38IAAAAASUVORK5CYII=\" type=\"image/x-png\" />";
  return favicon;
}

