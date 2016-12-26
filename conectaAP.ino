void mientrasConecta() {
  actCycle = 0;
  //WiFi.begin(ssid, password);
  //Serial.print("login: ");Serial.println(bufssid);
  //Serial.print("pass: ");Serial.println(bufsspass);
  WiFi.begin(bufssid, bufsspass);
  yield();
  while (WiFi.status() != WL_CONNECTED && actCycle < maxCycle) {
    delay(500);
    Serial.print(".");
    actCycle++;
  }
  Serial.print("Wifi status ");Serial.println(WiFi.status());
  return;
}


