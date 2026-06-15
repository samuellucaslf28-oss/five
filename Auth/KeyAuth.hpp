#pragma once 
#include <string> 
#include <windows.h> 
#include <wininet.h> 
#include <sstream> 
#include <iomanip> 
#include <vector> 
#include "skStr.h"

#pragma comment(lib, "wininet.lib") 

class Authentication { 
private: 
    std::string api_url; 
    std::string api_key; 
    std::string version; 
    std::string session_id; 
    
    // Helper function to make HTTP requests using WinInet 
    std::string makeHttpRequest(const std::string& path, const std::string& data) { 
        // Encrypted UserAgent
        HINTERNET hInternet = InternetOpenA(skCrypt("UserAgent").decrypt(), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0); 
        if (!hInternet) return ""; 

        // Encrypted URL construction
        std::string decrypted_url = api_url;
        if (decrypted_url.empty()) decrypted_url = skCrypt("undefinedauth.discloud.app").decrypt();

        HINTERNET hConnect = InternetConnectA(hInternet, decrypted_url.c_str(), INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0); 
        if (!hConnect) { 
            InternetCloseHandle(hInternet); 
            return ""; 
        } 

        std::string fullPath = skCrypt("/api").decrypt() + path; 
        HINTERNET hRequest = HttpOpenRequestA(hConnect, skCrypt("POST").decrypt(), fullPath.c_str(), NULL, NULL, NULL, INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD, 0); 
        if (!hRequest) { 
            InternetCloseHandle(hConnect); 
            InternetCloseHandle(hInternet); 
            return ""; 
        } 

        // Headers 
        std::string headers = skCrypt("Content-Type: application/json\r\nX-API-Key: ").decrypt() + api_key + skCrypt("\r\n").decrypt(); 
        HttpAddRequestHeadersA(hRequest, headers.c_str(), -1, HTTP_ADDREQ_FLAG_ADD); 

        // Send request 
        if (!HttpSendRequestA(hRequest, NULL, 0, (LPVOID)data.c_str(), data.length())) { 
            InternetCloseHandle(hRequest); 
            InternetCloseHandle(hConnect); 
            InternetCloseHandle(hInternet); 
            return ""; 
        } 

        // Read response 
        std::string response; 
        char buffer[1024]; 
        DWORD bytesRead; 
        while (InternetReadFile(hRequest, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) { 
            response.append(buffer, bytesRead); 
        } 

        InternetCloseHandle(hRequest); 
        InternetCloseHandle(hConnect); 
        InternetCloseHandle(hInternet); 

        return response; 
    } 

    // Simple JSON value extractor 
    std::string getJsonValue(const std::string& json, const std::string& key) { 
        std::string searchKey = "\"" + key + "\":\""; 
        size_t start = json.find(searchKey); 
        if (start == std::string::npos) { 
            // Try without quotes (for status) 
            searchKey = "\"" + key + "\":"; 
            start = json.find(searchKey); 
            if (start == std::string::npos) return ""; 
            start += searchKey.length(); 
            size_t end = json.find(",", start); 
            if (end == std::string::npos) end = json.find("}", start); 
            if (end == std::string::npos) return ""; 
            return json.substr(start, end - start); 
        } 
        
        start += searchKey.length(); 
        size_t end = json.find("\"", start); 
        if (end == std::string::npos) return ""; 
        
        return json.substr(start, end - start); 
    } 

public: 
    Authentication(const std::string& api_key) : api_key(api_key) {
        api_url = skCrypt("undefinedauth.discloud.app").decrypt();
    } 

    bool init(const std::string& ver) { 
        version = ver; 
        std::string data = skCrypt("{\"version\":\"").decrypt() + version + skCrypt("\"}").decrypt(); 
        std::string response = makeHttpRequest(skCrypt("/init").decrypt(), data); 
        
        if (response.empty()) { 
            throw std::runtime_error(skCrypt("Falha na conexão com o servidor de autenticação").decrypt()); 
        } 

        std::string status = getJsonValue(response, skCrypt("status").decrypt()); 
        if (status != skCrypt("success").decrypt()) { 
            std::string error = getJsonValue(response, skCrypt("message").decrypt()); 
            throw std::runtime_error(!error.empty() ? error : skCrypt("Falha na inicialização").decrypt()); 
        } 

        session_id = getJsonValue(response, skCrypt("session_id").decrypt()); 
        return true; 
    } 

    std::string get_session_id() const { return session_id; }

    bool login(const std::string& username, const std::string& hwid) { 
        std::string data = skCrypt("{\"username\":\"").decrypt() + username + skCrypt("\",\"hwid\":\"").decrypt() + hwid + skCrypt("\",\"session_id\":\"").decrypt() + session_id + skCrypt("\"}").decrypt(); 
        std::string response = makeHttpRequest(skCrypt("/login").decrypt(), data); 
        
        if (response.empty()) { 
            throw std::runtime_error(skCrypt("Falha na conexão com o servidor de autenticação").decrypt()); 
        } 

        std::string status = getJsonValue(response, skCrypt("status").decrypt()); 
        if (status != skCrypt("success").decrypt()) { 
            std::string error = getJsonValue(response, skCrypt("message").decrypt()); 
            throw std::runtime_error(!error.empty() ? error : skCrypt("Falha na autenticação").decrypt()); 
        } 

        return true; 
    } 

    bool register_key(const std::string& key, const std::string& username) { 
        std::string data = skCrypt("{\"key\":\"").decrypt() + key + skCrypt("\",\"username\":\"").decrypt() + username + skCrypt("\",\"session_id\":\"").decrypt() + session_id + skCrypt("\"}").decrypt(); 
        std::string response = makeHttpRequest(skCrypt("/register").decrypt(), data); 

        if (response.empty()) { 
            throw std::runtime_error(skCrypt("Falha na conexão com o servidor de registro").decrypt()); 
        } 

        std::string status = getJsonValue(response, skCrypt("status").decrypt()); 
        if (status != skCrypt("success").decrypt()) { 
            std::string error = getJsonValue(response, skCrypt("message").decrypt()); 
            throw std::runtime_error(!error.empty() ? error : skCrypt("Falha no registro").decrypt()); 
        } 

        return true; 
    } 
}; 

// Function to generate HWID 
inline std::string generate_hwid() { 
    std::string hwid; 
    DWORD volumeSerial; 
    GetVolumeInformationA("C:\\", NULL, 0, &volumeSerial, NULL, NULL, NULL, 0); 
    
    std::stringstream ss; 
    ss << std::hex << std::uppercase << std::setfill('0') << std::setw(8) << volumeSerial; 
    hwid = ss.str(); 
    
    return hwid; 
}