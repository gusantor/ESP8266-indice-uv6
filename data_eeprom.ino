void lee_credenciales(){
  EEPROM.get(0,stored_credential);
  Serial.print(String(stored_credential.uname));Serial.println(String(stored_credential.upass));
  if(String(stored_credential.uname)!=defaultUserName){
    //Serial.println(stored_credential.uname);
    Serial.println("Usuario credencial distinto "+(defaultUserName)+", placa nueva");
    escribe_credential_default();
  }else{
    Serial.println("Usuario credencial existe, user "+String(stored_credential.uname)+", pass "+String(stored_credential.upass)+", placa NO nueva");
  }
}

void escribe_credential_default(){
  Serial.println("Escribe credencial default user: "+String(defaultUserName)+", pass : "+String(defaultUserPass));
  char buffN[20];
  defaultUserName.toCharArray(buffN,sizeof(buffN));
  for(int i=0;i<sizeof(buffN);i++){
    default_credential.uname[i] = buffN[i];
  }
  char buffP[50];
  defaultUserPass.toCharArray(buffP,sizeof(buffP));
  for(int i=0;i<sizeof(buffP);i++){
    default_credential.upass[i] = buffP[i];
  }
  EEPROM.put(0, default_credential);
  EEPROM.commit();
  //Credential stored_credential=default_credential;
  stored_credential=default_credential;
}

void lee_ubicacion(){
  EEPROM.get(sizeof(Credential),stored_location);
  Serial.print("ubicacion leida ");
  Serial.println();
  Serial.print("vacia ubicacion? ");Serial.println(String(estaVacio(stored_location.addr)));
  Serial.println(" ubicacion "+String(estaVacio(stored_location.addr)));
}

void lee_estacion(){
  EEPROM.get(sizeof(Credential)+sizeof(Location),stored_estacion);
  Serial.print("estacion leida ");
  Serial.println();
  Serial.print("vacia estacion id? ");Serial.println(String(estaVacio(stored_estacion.id)));
  Serial.print("vacia estacion nombre? ");Serial.println(String(estaVacio(stored_estacion.nombre)));
  Serial.print(" estacion id "+String(estaVacio(stored_estacion.id)));
  Serial.println(" estacion nombre "+String(estaVacio(stored_estacion.nombre)));
}

void lee_display(){
  EEPROM.get(sizeof(Credential)+sizeof(Location)+sizeof(Estacion),stored_display);
  Serial.print("display leido ");
  Serial.println();
  Serial.print("vacia display modo? ");Serial.println(String(estaVacio(stored_display.dmode)));
  Serial.print("vacia display prioridad? ");Serial.println(String(estaVacio(stored_display.dpriority)));
  Serial.print(" modo "+String(estaVacio(stored_display.dmode)));
  Serial.println(" prioridad "+String(estaVacio(stored_display.dpriority)));
}

void ResetEEPROM(){
  Serial.println("Reset");
  delay(10);
  WiFi.disconnect(true);
  delay(50);
  ESP.reset();
}


/*void lee_puerto(){
  EEPROM.get(sizeof(Credential)+sizeof(Location)+sizeof(Estacion)+sizeof(Display),port);
  Serial.print("puerto leido ");
  Serial.println();
  char portChar[6];
  String portStr=String(port);
  portStr.toCharArray(portChar,6);
  Serial.print("vacia puerto? ");Serial.println(String(estaVacio(portChar)));
  Serial.println(" puerto "+portStr);
  if(!estaVacio(portChar)&&port<=0){
    Serial.println(" sin definicion ");
    escribe_puerto(defaultPort);
  }
}

void escribe_puerto(int customPort){
  EEPROM.put(sizeof(Credential)+sizeof(Location)+sizeof(Estacion)+sizeof(Display), customPort);
  EEPROM.commit();
}*/
