static const char PROGMEM style[] = {
    "html {margin:0px;}\n"
    ".clearfix {clear:both;visibility: hidden;}\n"
    "body {margin:0px;padding:0px;font-family:Arial,Verdana;background-color:yellowgreen/*8fbe00brown*/;}\n"
    ".content {min-height:350px;padding:15px 30px 15px 30px;background-color:white;position:relative;}\n"
    ".content.inicio{text-align:center;}\n"
    ".content a:link,.content a:visited {color:dimgray;text-decoration:none;}\n"
    ".content a:hover,.content a:active {color:dimgray;text-decoration:underline;}\n"
    "ul.nav li {display:inline-block;padding-right:10px;font-weight:bold;}\n"
    "h1,h2,h3 {color:yellowgreen/*8fbe00brown*/;} .powered-by {font-size:0.7em;text-align:right}\n"
    ".footer {background-color:yellowgreen/*8fbe00brown*/;color:white;padding:10px;min-height:50px;position:relative;bottom:0px;}\n"
    ".programacion{color:dimgray;background-color:lightgray;margin:0px;padding:10px;border:1px solid gray;}\n"
    ".page {margin:0 auto;}\n"
    ".header {color:white;min-height:80px;position:relative;}\n"
    ".header a:link,\n"
    ".header a:visited,\n"
    ".header a:hover,.header a:active {color:white;}\n"
    "img#logo {/*float:right;clear:left;*/max-width:100%;height:auto;/*margin-right:15px*/;position:absolute;right:15px;top:15px;z-index:10;}\n"
    "#contenedor-principal {text-align:center;/*width:100%;*/display:inline-block;}\n"
    "#contenedor-principal h1 {text-align:center;/*width:100%*/;color:yellowgreen/*8fbe00brown*/;}\n"
    "#principal-indice {font-size:21em;/*color:yellowgreen*//*8fbe00brown*/;}\n"
    "#principal-estacion {font-size:0.9em;color:yellowgreen/*8fbe00brown*/;}\n"
    "#principal-fecha {font-size:0.9em;color:yellowgreen/*8fbe00brown*/;}\n"
    "#contenedor-secundario {text-align:center;position:absolute;bottom:15px;right:10px;display:inline-block;}\n"
    "#secundario-indice {font-size:2em;color:yellowgreen/*8fbe00brown*/;}\n"
    "#secundario-estacion {font-size:0.9em;color:yellowgreen/*8fbe00brown*/;}\n"
    "#secundario-fecha {font-size:0.9em;color:yellowgreen/*8fbe00brown*/;}\n"
    "form {position:relative;border:1px solid lightgray;padding:10px;margin-bottom:10px;}\n"
    "iframe {width:100%;}\n"
    "fieldset.configuracion {width:auto;display:inline-block;vertical-align:top;}\n"
    "fieldset.configuracion p.seleccion-estacion {margin:0px;text-transform:capitalize;}\n"
    "form p.form-comment, form span.form-comment {color:gray;font-size:0.85em;}\n"
    "form p.advertencia, form span.advertencia {text-align:right;display:inline-block;position:absolute;right:10px;}\n"
    ".verde {color:#8fbe00;}\n"
    ".amarillo {color:#f7e908;}\n"
    ".naranja {color:#fe7b00;}\n"
    ".rojo {color:#e40720;}\n"
    ".morado {color:#a75690;}\n"
};


static const char PROGMEM javaScript_General[] = {
  "var xmlHttp=createXmlHttpObject();\n"
  "function createXmlHttpObject(){\n"
  " if(window.XMLHttpRequest){\n"
  "    xmlHttp=new XMLHttpRequest();\n"
  " }else{\n"
  "    xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');\n"
  " }\n"
  " return xmlHttp;\n"
  "}\n"
};


/*static const char PROGMEM javaScript_KillSta[] = {
  "console.log('Kill STA!');\n"
  "function kill_sta(){\n"
  " if(xmlHttp.readyState==0 || xmlHttp.readyState==4){\n"
  "   xmlHttp.open('GET','/configuracion/kill-sta',true);\n"
  "   xmlHttp.onreadystatechange=askKillSta;\n"
  "   xmlHttp.send(null);\n"
  " }\n"
  "}\n"

  "function askKillSta(){\n"
  " if(xmlHttp.readyState==4 && xmlHttp.status==200){\n"
  "   response=xmlHttp.responseText;\n"
  "   document.getElementById('kill-sta-result').innerHTML=response;\n"
  " }\n"
  "}\n"

  " setTimeout(kill_sta,5000);\n"
};*/

/*static const char PROGMEM menu[] = {
  "<nav class=\"navbar navbar-inverse navbar-fixed-top\">\n"
  "<ul class=\"nav\">\n"
  "<li><a href=\"/\">Inicio</a></li>\n"
  "<li><a href=\"/change-to-sta\">Give credentials</a></li>\n"
  "<li><a href=\"/kill-sta\">Forget SSID</a></li>\n"
  "<li><a href=\"/configuracion\">Configuraci&oacute;n</a></li>\n"
  "<li><a href=\"/login\">Login</a></li>\n"
  "</ul></nav>\n"
};*/

const char PROGMEM resp1[] = {0};
