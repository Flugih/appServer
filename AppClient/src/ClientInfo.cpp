#include "../include/ClientInfo.h"

void ClientInfo::collectUserInfo(){
	getOSversion();
}

void ClientInfo::getOSversion(){
	HMODULE hMod = ::GetModuleHandle(TEXT("ntdll.dll"));
	if (hMod) {
		RtlGetVersionPtr pRtlGetVersion = (RtlGetVersionPtr)::GetProcAddress(hMod, "RtlGetVersion");
		if (pRtlGetVersion != nullptr) {
			OSVERSIONINFOEX osvi;
			ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
			osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

			if (pRtlGetVersion(&osvi) == 0) {
				ostringstream oss;
				oss << osvi.dwMajorVersion << "." << osvi.dwMinorVersion;
				OSversion = oss.str();

			}
		}
	}

	getRegion();
}

void ClientInfo::getRegion(){
	wchar_t localeName[LOCALE_NAME_MAX_LENGTH] = { 0 };
	int ret = GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH);
	if (ret != 0) {

		wchar_t wxCountry[COUNTRY_NAME_MAX_LEN];
		if (GetLocaleInfoEx(localeName, LOCALE_SENGLISHCOUNTRYNAME, wxCountry, COUNTRY_NAME_MAX_LEN)) {
			wstring_convert<codecvt_utf8<wchar_t>> converter;
			string country = converter.to_bytes(wxCountry);

			region = country;
		}
	}
}

ClientInfo::ClientInfo() : appVersion("1.0.0") {
}

void ClientInfo::getUserInfo(){
	collectUserInfo();
	clInfo.push_back({ OSversion, region, appVersion, userID });
}
