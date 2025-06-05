#include <Wifi_creds.h>

void Wifi_creds::cleanup() {
    if (ssid_ch != nullptr) {
        delete[] ssid_ch;
        ssid_ch = nullptr;
    }
    if (pass_ch != nullptr) {
        delete[] pass_ch;
        pass_ch = nullptr;
    }
}

Wifi_creds::~Wifi_creds() {
    cleanup();
}

Wifi_creds::Wifi_creds()
{
    ssid = "";
    pass = "";
    ssid_ch = new char[ssid.length() + 1];
    pass_ch = new char[pass.length() + 1];
    strcpy(ssid_ch, ssid.c_str());
    strcpy(pass_ch, pass.c_str());
}

Wifi_creds::Wifi_creds(const String ssid, const String pass)
{
    Wifi_creds::ssid = ssid;
    Wifi_creds::pass = pass;
    ssid_ch = new char[ssid.length() + 1];
    pass_ch = new char[pass.length() + 1];
    strcpy(ssid_ch, ssid.c_str());
    strcpy(pass_ch, pass.c_str());
}

void Wifi_creds::set(const String ssid, const String pass)
{
    cleanup();  // Clean up existing memory before allocating new
    Wifi_creds::ssid = ssid;
    Wifi_creds::pass = pass;
    ssid_ch = new char[ssid.length() + 1];
    pass_ch = new char[pass.length() + 1];
    strcpy(ssid_ch, ssid.c_str());
    strcpy(pass_ch, pass.c_str());
}