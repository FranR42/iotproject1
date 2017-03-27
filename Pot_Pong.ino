

/* 
The same TembooAccount.h file settings can be used for all Temboo SDK sketches.  
Keeping your account information in a separate file means you can share the 
main .ino file without worrying that you forgot to delete your credentials.
*/
void setup() {
  pinMode(0,INPUT);     // Set pin 0 to be an input
  Serial.begin(9600);   // Start up serial communication at 9600 speed
}

void loop() {
  int reading = analogRead(0);    // Read the current value of the potentiometer
  Serial.println(reading);        // Send the value just read down the serial cable
  delay(50);                      // Wait for a short time, just to slow things a little
  #include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 10;   // Maximum number of times the Choreo should be executed

void loop() {
  Serial.begin(9600);
  
  // For debugging, wait until the serial console is connected
  delay(4000);
  while(!Serial);
  Bridge.begin();
}

void loop() {
  if (calls <= maxCalls) {
    Serial.println("Running SendEmail - Run #" + String(calls++));
    
    TembooChoreo SendEmailChoreo;

    // Invoke the Temboo client
    SendEmailChoreo.begin();

    // Set Temboo account credentials
    SendEmailChoreo.setAccountName(TEMBOO_ACCOUNT);
    SendEmailChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    SendEmailChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // Set Choreo inputs
    SendEmailChoreo.addInput("FromAddress", "francis.m.rouse@gmail.com");
    SendEmailChoreo.addInput("Username", "francis.m.rouse@gmail.com");
    SendEmailChoreo.addInput("ToAddress", "s00173325@mail.itsligo.ie");
    SendEmailChoreo.addInput("Subject", "Pont pong");
    SendEmailChoreo.addInput("MessageBody", "thanks for playing!");
    SendEmailChoreo.addInput("Password", "rouse2016");
    
    // Identify the Choreo to run
    SendEmailChoreo.setChoreo("/Library/Google/Gmail/SendEmail");
    
    // Run the Choreo; when results are available, print them to serial
    SendEmailChoreo.run();
    
    while(SendEmailChoreo.available()) {
      char c = SendEmailChoreo.read();
      Serial.print(c);
    }
    SendEmailChoreo.close();
  }

  Serial.println("Waiting...");
  delay(30000); // wait 30 seconds between SendEmail calls
}
}

