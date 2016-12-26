String jsAdmin(){
  String javaScript;
  javaScript="";

  javaScript+="function trae_formulario_admin(){\n";
  javaScript+=" if(xmlHttp.readyState==0 || xmlHttp.readyState==4){\n";
  javaScript+="   xmlHttp.open('GET','/configuracion/formulario-admin',true);\n";
  javaScript+="   xmlHttp.onreadystatechange=actualizaAdminForm;\n"; // no brackets?????
  javaScript+="   xmlHttp.send(null);\n";
  javaScript+=" }\n";
  javaScript+="}\n";

  javaScript+="function actualizaAdminForm(){\n";
  javaScript+=" if(xmlHttp.readyState==4 && xmlHttp.status==200){\n";
  javaScript+="   response=xmlHttp.responseText;\n";
  javaScript+="   document.getElementById('admin-config-form-container').innerHTML=response;\n";
  if (WiFi.status() == WL_CONNECTED) {
    javaScript+="   obtiene_estaciones();\n";
  }
  javaScript+=" }\n";
  javaScript+="}\n";
  
  return javaScript;
}

String jsInicio(){
  String javaScript;

  javaScript+="function consulta_uvi(){\n";
  javaScript+=" if(xmlHttp.readyState==0 || xmlHttp.readyState==4){\n";
  javaScript+="   xmlHttp.open('GET','obtiene-uvi',true);\n";
  javaScript+="   xmlHttp.onreadystatechange=actualizaUvi;\n"; // no brackets?????
  javaScript+="   xmlHttp.send(null);\n";
  javaScript+=" }\n";
  javaScript+=" setTimeout('consulta_uvi()',10000);//300000\n";
  javaScript+="}\n";

  javaScript+="function actualizaUvi(){\n";
  javaScript+=" if(xmlHttp.readyState==4 && xmlHttp.status==200){\n";
  javaScript+="   jsonResponse=xmlHttp.responseText;\n";
  javaScript+="   var resp=JSON.parse(jsonResponse);\n";
  javaScript+="   var mostrar;\n";
  javaScript+="   var principal={};\n";
  javaScript+="   var secundario={};\n";
  javaScript+="   principal.maximo={};\n";
  javaScript+="   principal.ultimo={};\n";
  javaScript+="   principal.estacion={};\n";
  javaScript+="   secundario.maximo={};\n";
  javaScript+="   secundario.ultimo={};\n";
  javaScript+="   secundario.estacion={};\n";
  
  javaScript+="   mostrar = resp[2].modo;\n";
  javaScript+="   principal.estacion.nombre = resp[0].nombre;\n";
  javaScript+="   principal.maximo.fecha = resp[0].data.maximo.fecha;\n";
  javaScript+="   principal.maximo.uvi = resp[0].data.maximo.uvi;\n";
  javaScript+="   principal.ultimo.fecha = resp[0].data.ultimo.fecha;\n";
  javaScript+="   principal.ultimo.uvi = resp[0].data.ultimo.uvi;\n";
  javaScript+="   var uvi=parseInt(principal.ultimo.uvi);\n";

  javaScript+="   secundario.estacion.nombre = resp[1].nombre;\n";
  javaScript+="   secundario.maximo.fecha = resp[1].data.maximo.fecha;\n";
  javaScript+="   secundario.maximo.uvi = resp[1].data.maximo.uvi;\n";
  javaScript+="   secundario.ultimo.fecha = resp[1].data.ultimo.fecha;\n";
  javaScript+="   secundario.ultimo.uvi = resp[1].data.ultimo.uvi;\n";

  javaScript+="   var icolor='verde';\n";
  //javaScript+="   console.log(uvi);\n";
  javaScript+="   switch(true){\n";
  javaScript+="   case(uvi>2 && uvi<=5):\n";
  javaScript+="     icolor='amarillo';\n";
  javaScript+="     break;\n";
  javaScript+="   case(uvi>5 && uvi<=7):\n";
  javaScript+="     icolor='naranja';\n";
  javaScript+="     break;\n";
  javaScript+="   case(uvi>7 && uvi<=10):\n";
  javaScript+="     icolor='rojo';\n";
  javaScript+="     break;\n";
  javaScript+="   case(uvi>=11):\n";
  javaScript+="     icolor='morado';\n";
  javaScript+="     break;\n";
  javaScript+="   }\n";
  
  javaScript+="   document.getElementById('principal-indice').innerHTML='<div class=\"'+icolor+'\">'+principal.ultimo.uvi+'</div>';\n";
  javaScript+="   document.getElementById('principal-estacion').innerHTML=principal.estacion.nombre;\n";
  javaScript+="   document.getElementById('principal-fecha').innerHTML=principal.ultimo.fecha;\n";

  javaScript+="   document.getElementById('secundario-indice').innerHTML=(mostrar=='mostrar-ambos'?secundario.ultimo.uvi:'');\n";
  javaScript+="   document.getElementById('secundario-estacion').innerHTML=(mostrar=='mostrar-ambos'?secundario.estacion.nombre:'');\n";
  javaScript+="   document.getElementById('secundario-fecha').innerHTML=(mostrar=='mostrar-ambos'?secundario.ultimo.fecha:'');\n";
  
  javaScript+=" }\n";
  javaScript+="}\n";
  
  return javaScript;
}

String jsRedirect(){
  String javaScript;
  javaScript="";
  javaScript+="console.log('redirect!');\n";
  javaScript+="function actualiza_ip(){\n";
  //javaScript+="\tnewIP=document.getElementById('new-ip').innerHTML;\n";
  //javaScript+="\tsetTimeout(function(){window.location=\"http://\"+newIP+\"\";},10000);\n";
  javaScript+="}\n";
  //javaScript+=" setTimeout(actualiza_ip,3000);\n";
  return javaScript;
}

String jsKillSta(){
  String javaScript;
  javaScript="";
  javaScript+="function kill_sta(){\n";
  javaScript+=" if(xmlHttp.readyState==0 || xmlHttp.readyState==4){\n";
  javaScript+="   xmlHttp.open('GET','/configuracion/kill-sta',true);\n";
  javaScript+="   xmlHttp.onreadystatechange=askKillSta;\n"; // no brackets?????
  javaScript+="   xmlHttp.send(null);\n";
  javaScript+=" }\n";
  javaScript+="}\n";

  javaScript+="function askKillSta(){\n";
  javaScript+="\tif(xmlHttp.readyState==4 && xmlHttp.status==200){\n";
  javaScript+="\t\tresponse=xmlHttp.responseText;\n";
  javaScript+="\t\tdocument.getElementById('kill-sta-result').innerHTML=response;\n";
  javaScript+="\t\task_real_disconnect_ap();\n";
  javaScript+="\t}\n";
  javaScript+="}\n";

  javaScript+="function ask_real_disconnect_ap(){\n";
  javaScript+="\tconsole.log(':p');\n";

  javaScript+="\tif(xmlHttp.readyState==0 || xmlHttp.readyState==4){\n";
  javaScript+="\t\txmlHttp.open('GET','/configuracion/kill-ap',true);\n";
  javaScript+="\t\txmlHttp.onreadystatechange=function(){setTimeout(askKillAP,3000);}\n";
  javaScript+="\t\txmlHttp.send(null);\n";
  javaScript+="\t}\n";
  
  javaScript+="}\n";

  javaScript+="function askKillAP(){\n";
  javaScript+="\tif(xmlHttp.readyState==4 && xmlHttp.status==200){\n";
  javaScript+="\t\tresponse=xmlHttp.responseText;\n";
  javaScript+="\t\tdocument.getElementById('kill-ap-result').innerHTML=response;\n";
  javaScript+="\t}\n";
  javaScript+="}\n";

  javaScript+="setTimeout(kill_sta,5000);\n";

  return javaScript;
}

String jsKillStaFR(){
  String javaScript;
  javaScript="console.log('yay');\n";
  javaScript+="function kill_sta(){\n";
  javaScript+=" if(xmlHttp.readyState==0 || xmlHttp.readyState==4){\n";
  javaScript+="   xmlHttp.open('GET','/configuracion/kill-sta2',true);\n";
  javaScript+="   xmlHttp.onreadystatechange=askKillSta;\n"; // no brackets?????
  javaScript+="   xmlHttp.send(null);\n";
  javaScript+=" }\n";
  javaScript+="}\n";

  javaScript+="function askKillSta(){\n";
  javaScript+=" if(xmlHttp.readyState==4 && xmlHttp.status==200){\n";
  javaScript+="   response=xmlHttp.responseText;\n";
  javaScript+="   document.getElementById('killing-ap-result').innerHTML=response;\n";
  javaScript+=" }\n";
  javaScript+="}\n";

  javaScript+=" setTimeout(kill_sta,5000);\n";

  return javaScript;
}
