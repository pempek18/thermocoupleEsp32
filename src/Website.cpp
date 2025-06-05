#include "Website.h"

String Website::readHTMLTemplate()
{
    String templateContent = "";
    File file = SPIFFS.open("/index.html", "r"); // Replace with your HTML file name

    if (!file)
    {
        Serial.println("Failed to open template file");
        return templateContent;
    }

    while (file.available())
    {
        templateContent += (char)file.read();
    }

    file.close();
    return templateContent;
}

void Website::refresh()
{
    server.handleClient();
}

void Website::prepareXML()
{
    strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

    for (int i = 0; i < 11; i++)
    {
        // Add nickname
        sprintf(buf, "<N%i>%s</N%i>\n", i, "Nickname", i);
        strcat(XML, buf);
        // Add Time
        sprintf(buf, "<T%i>%2f</T%i>\n", i, 0, i);
        strcat(XML, buf);
    }

    strcat(XML, "</Data>\n");
}
void Website::xmlHeader(uint16_t record)
{
    strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");
    sprintf(buf, "<R>%i</R>\n", record);
    strcat(XML, buf);
}
void Website::xmlSensorState(String state = "INIT")
{
    if (state == NULL)
        state = "INIT";
    sprintf(buf, "<S>%s</S>\n", state);
    strcat(XML, buf);
}
void Website::xmlRecord(uint16_t number, String recordName, float time)
{
    sprintf(buf, "<N%i>%s</N%i>\n", number, recordName, number);
    strcat(XML, buf);
    // Add Time
    sprintf(buf, "<T%i>%2f</T%i>\n", number, time, number);
    strcat(XML, buf);
}
void Website::xmlTemperature(uint16_t number, String recordName, float value)
{
    sprintf(buf, "<N%i>%s</N%i>\n", number, recordName, number);
    strcat(XML, buf);
    // Add Time
    sprintf(buf, "<T%i>%1f</T%i>\n", number, value, number);
    strcat(XML, buf);
}
// code to send the main web page
// I avoid string data types at all cost hence all the char mainipulation code
void Website::SendXML()
{
    // Serial.println("sending xml");

    // wanna see what the XML code looks like?
    // actually print it to the serial monitor and use some text editor to get the size
    // then pad and adjust char XML[2048]; above
    // Serial.println(XML);

    // you may have to play with this value, big pages need more porcessing time, and hence
    // a longer timeout that 200 ms
    server.send(200, "text/xml", XML);
}
// /*Define in deverative*/
// void Website::handleBtnChange(){
void Website::handleBtnChange()
{
    WEBSITE_DEBUG_PRINT("Button inside website: ");
    WEBSITE_DEBUG_PRINTLN(server.args());
    // WEBSITE_DEBUG_PRINTLN(server.header());
    WEBSITE_DEBUG_PRINTLN(server.pathArg(1));
    String id = server.arg("ID");
    int iButtonId = id.toInt();
    String sNickname = server.arg("VALUE");
    WEBSITE_DEBUG_PRINT("Change Button ");
    WEBSITE_DEBUG_PRINT(iButtonId);
    WEBSITE_DEBUG_PRINT("Was pressed, with textbox value ");
    WEBSITE_DEBUG_PRINTLN(sNickname);
}
void Website::handleBtnDelete()
{
    String id = server.arg("ID");
    int iButtonId = id.toInt();
    WEBSITE_DEBUG_PRINT("Change Button ");
    WEBSITE_DEBUG_PRINT(iButtonId);
    WEBSITE_DEBUG_PRINTLN("Was pressed");
}
void Website::handleButtonReset()
{
    WEBSITE_DEBUG_PRINTLN("Reset Button Was Pressed");
}
void Website::begin()
{
    // Initialize SPIFFS
    if (!SPIFFS.begin())
    {
        WEBSITE_DEBUG_PRINTLN("SPIFFS initialization failed!");
        return;
    }
    // Start the mDNS service with the hostname "server-page"
    if (!MDNS.begin("temperature"))
    {
        WEBSITE_DEBUG_PRINTLN("Error starting mDNS");
        return;
    }
    Serial.println("mDNS responder started");
    // Route to load index.html
    server.serveStatic("/", SPIFFS, "/index.html");
    // Route to load style.css file
    server.serveStatic("/style.css", SPIFFS, "/style.css", "text/css");
    // Route to load script.js file
    server.serveStatic("/script.js", SPIFFS, "/script.js", "text/javascript");
    // Route to load networks.json file
    server.serveStatic("/networks.json", SPIFFS, "/networks.json");
    // Send prepared in runtime }ML base on array of chars
    server.on("/xml", [&]()
              { Website::SendXML(); });
    // Buttons
    server.on("/BUTTON_CHANGE", [&]()
              { handleBtnChange(); });
    server.on("/BUTTON_RESET", [&]()
              { handleButtonReset(); });
    server.on("/BUTTON_DELETE", [&]()
              { handleBtnDelete(); });
    server.begin();
}