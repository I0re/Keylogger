#include "GetSYSinfo.h"
#include "systeminfo.h"
#include "Winsock2.h"
#include "curl/curl.h"
#include <iostream>
#include <Windows.h> 
#include <iphlpapi.h> 


using namespace std;

void GetSYSinfo::GetHostname() {

		WSADATA WSAData;

		// Initialize winsock dll

		if (::WSAStartup(MAKEWORD(1, 0), &WSAData)) {

			cout << "Failed to find the WinSock DLL\n";

			return;
		}

		char szHostName[128] = "";

		//get the standard host name of the machine

		if (::gethostname(szHostName, sizeof(szHostName))){

			cout << "Failed to get the host name\n";
		}
		else{
			cout << "Host Name: " << szHostName << endl;
		}
		// Cleanup
		WSACleanup();
}

int GetSYSinfo::GetComputerInfo(int argc, char* argv[]) {
	// Main function to get all PC hardware info
	// Existing main() code
	//Main Function to get ALL PC HARDWARE INFO **WORKING**

	//First make a delegate object that handles the cases where the computer has multiple CPUs
	unique_ptr<CPUInfoDelegate> cpuInfo = make_unique<CPUInfoDelegate>();

	//Then extract the separate CPUs into a vector (of CPUInfo objects)
	vector<CPUInfo> cpuInfoVector{ cpuInfo->cpuInfoVector() };

	//Print out the number of CPUs, directory from the delegate object
	cout << "\nThis computer has " << cpuInfo->numberOfCPUInfoItems() << " CPU(s) installed" << endl;

	for (vector<CPUInfo>::const_iterator iter = cpuInfoVector.begin(); iter != cpuInfoVector.end(); iter++) {
		cout << "Information for CPU #" << iter->cpuNumber() + 1 << ": " << endl;
		cout << "CPU Name = " << iter->name() << endl;
		cout << "CPU Manufacturer = " << iter->manufacturer() << endl;
		cout << "Number of CPU Cores = " << iter->numberOfCores() << endl;
		cout << "Current CPU Clock Speed = " << iter->currentClockSpeed() << endl;
		cout << "CPU Architecture = " << iter->architecture() << endl;
		cout << "CPU L2 Cache Size = " << iter->L2CacheSize() << endl;
		cout << "CPU L3 Cache Size = " << iter->L3CacheSize() << endl;
		cout << "Current CPU Temperature = " << iter->currentTemperature() << endl;
		cout << endl;
	}

	unique_ptr<MotherboardInfoDelegate> moboInfo = make_unique<MotherboardInfoDelegate>();
	vector<MotherboardInfo> moboInfoVector = moboInfo->motherboardInfoVector();
	cout << "This computer has " << moboInfo->numberOfMotherboardInfoItems() << " motherboard(s) installed" << endl;

	for (vector<MotherboardInfo>::const_iterator iter = moboInfoVector.begin(); iter != moboInfoVector.end(); iter++) {
		cout << "Information for motherboard #" << iter->motherboardNumber() + 1 << ": " << endl;
		cout << "Motherboard Name = " << iter->name() << endl;
		cout << "Motherboard Manufacturer = " << iter->manufacturer() << endl;
		cout << "Motherboard Chipset = " << iter->chipset() << endl;
		cout << "Motherboard Serial Number = " << iter->serialNumber() << endl;
		cout << "Motherboard Version = " << iter->version() << endl;
		cout << endl;
	}

	unique_ptr<RAMInfoDelegate> ramInfo = make_unique<RAMInfoDelegate>();
	vector<RAMInfo> ramInfoVector = ramInfo->ramInfoVector();
	cout << "This computer has " << ramInfo->numberOfRAMInfoItems() << " RAM stick(s) installed" << endl;

	for (vector<RAMInfo>::const_iterator iter = ramInfoVector.begin(); iter != ramInfoVector.end(); iter++) {
		cout << "Information for RAM stick #" << iter->ramNumber() + 1 << ": " << endl;
		cout << "RAM Name = " << iter->name() << endl;
		cout << "RAM Manufacturer = " << iter->manufacturer() << endl;
		cout << "RAM Capacity = " << iter->capacity() << endl;
		cout << "RAM Serial Number = " << iter->serialNumber() << endl;
		cout << "RAM Form Factor = " << iter->formFactor() << endl;
		cout << "RAM Part Number = " << iter->partNumber() << endl;
		cout << "RAM Memory Type = " << iter->memoryType() << endl;
		cout << "RAM Clock Speed = " << iter->clockSpeed() << endl;
		cout << endl;
	}

	unique_ptr<GPUInfoDelegate> gpuInfo = make_unique<GPUInfoDelegate>();
	vector<GPUInfo> gpuInfoVector = gpuInfo->gpuInfoVector();
	cout << "This computer has " << gpuInfo->numberOfGPUInfoItems() << " GPU(s) installed" << endl;
	for (vector<GPUInfo>::const_iterator iter = gpuInfoVector.begin(); iter != gpuInfoVector.end(); iter++) {
		cout << "Information for GPU #" << iter->gpuNumber() + 1 << ": " << endl;
		cout << "GPU Name = " << iter->name() << endl;
		cout << "GPU Manufacturer = " << iter->manufacturer() << endl;
		cout << "GPU Caption = " << iter->caption() << endl;
		cout << "GPU Adapter RAM = " << iter->adapterRAM() << endl;
		cout << "GPU Refresh Rate = " << iter->refreshRate() << endl;
		cout << "GPU Driver Version = " << iter->driverVersion() << endl;
		cout << "GPU Video Architecture = " << iter->videoArchitecture() << endl;
		cout << "GPU Video Mode Description = " << iter->videoModeDescription() << endl;
		cout << "GPU Video Processor = " << iter->videoProcessor() << endl;
		cout << endl;
	}

	unique_ptr<OSInfoDelegate> osInfo = make_unique<OSInfoDelegate>();
	vector<OSInfo> osInfoVector = osInfo->osInfoVector();
	cout << "This computer has " << osInfo->numberOfOSInfoItems() << " OS(s) installed" << endl;
	for (vector<OSInfo>::const_iterator iter = osInfoVector.begin(); iter != osInfoVector.end(); iter++) {
		cout << "Information for OS #" << iter->osNumber() + 1 << ": " << endl;
		cout << "OS Name = " << iter->name() << endl;
		cout << "OS Manufacturer = " << iter->manufacturer() << endl;
		cout << "OS Caption = " << iter->caption() << endl;
		cout << "OS Version = " << iter->version() << endl;
		cout << "Current User = " << iter->currentUser() << endl;
		cout << "Install Date = " << iter->installDate() << endl;
		cout << "Build Number = " << iter->buildNumber() << endl;
		cout << "Last Boot Up Time = " << iter->lastBootUpTime() << endl;
		cout << "Boot Device = " << iter->bootDevice() << endl;
		cout << "Total Virtual Memory = " << iter->totalVirtualMemory() << endl;
		cout << "Total Visible Memory = " << iter->totalVisibleMemory() << endl;
		cout << "Total Swap Size = " << iter->totalSwapSize() << endl;
		cout << "Serial Number = " << iter->serialNumber() << endl;
		cout << "Free Physical Memory = " << iter->freePhysicalMemory() << endl;
		cout << "Free Virtual Memory = " << iter->freeVirtualMemory() << endl;
		cout << "Free Paging File Space = " << iter->freePagingFileSpace() << endl;
		cout << "Used Paging File Space = " << iter->usedPagingFileSpace() << endl;
		cout << "Current Date Time = " << iter->currentDateTime() << endl;
		cout << endl;
	}

	return 0;
}


char* GetSYSinfo::GetMAC(int adapterType) {
	// Get Ethernet MAC address
	//https://learn.microsoft.com/en-us/windows/win32/api/iptypes/ns-iptypes-ip_adapter_info?redirectedfrom=MSDN
	char* pEthernetMac = getMAC(MIB_IF_TYPE_ETHERNET);  // Or Use 6 for Ethernet
	if (pEthernetMac != NULL) {
		printf("Ethernet MAC Address: %s\n", pEthernetMac);
		free(pEthernetMac);
	}
	else {
		printf("Failed to retrieve Ethernet MAC address.\n");
	}

	// Get WiFi MAC address
	//ONLY WORKS IF WIFI NETWORK INTERFACE CARD IS BUILT INTO PC IF ITS AN EXTERNAL WIFI ADDAPTER USE 'MIB_IF_TYPE_OTHER' AND SEARCH FOR THAT WIFI NETWORK INTERFACE ADAPTER
	char* pWifiMac = getMAC(IF_TYPE_IEEE80211);
	if (pWifiMac != NULL) {
		printf("WiFi MAC Address: %s\n", pWifiMac);
		free(pWifiMac);
	}
	else {
		printf("Failed to retrieve WiFi MAC address.\n");
	}

	return 0;
}

char* GetSYSinfo::getMAC(int adapterType) {
	ULONG outBufLen = 0;
	DWORD ret = 0;

	// Initial call to get the required buffer size
	ret = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, NULL, &outBufLen);
	if (ret != ERROR_BUFFER_OVERFLOW) {
		printf("Error getting buffer size\n");
		return NULL;
	}

	PIP_ADAPTER_ADDRESSES pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
	if (pAddresses == NULL) {
		printf("Error allocating memory needed to call GetAdaptersAddresses\n");
		return NULL;
	}

	// Actual call to get adapter addresses
	ret = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, pAddresses, &outBufLen);
	if (ret != NO_ERROR) {
		printf("Error getting adapters addresses\n");
		free(pAddresses);
		return NULL;
	}

	char* mac_addr = NULL;

	for (PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses; pCurrAddresses != NULL; pCurrAddresses = pCurrAddresses->Next) {
		if (pCurrAddresses->PhysicalAddressLength == 6 && pCurrAddresses->IfType == adapterType) {
			mac_addr = (char*)malloc(18);
			if (mac_addr != NULL) {
				sprintf_s(mac_addr, 18, "%02X:%02X:%02X:%02X:%02X:%02X",
					pCurrAddresses->PhysicalAddress[0], pCurrAddresses->PhysicalAddress[1],
					pCurrAddresses->PhysicalAddress[2], pCurrAddresses->PhysicalAddress[3],
					pCurrAddresses->PhysicalAddress[4], pCurrAddresses->PhysicalAddress[5]);
			}
			break;
		}
	}

	free(pAddresses);
	return mac_addr;
}

void GetSYSinfo::GetExternalIPAddress() {
	CURL* curlIPv4;
	CURL* curlIPv6;
	CURLcode res;
	std::string readIPV4Buffer;
	std::string readIPV6Buffer;

	// Initialize CURL for IPv4
	curlIPv4 = curl_easy_init();
	if (curlIPv4) {
		curl_easy_setopt(curlIPv4, CURLOPT_URL, "https://api.ipify.org?format=json");
		curl_easy_setopt(curlIPv4, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curlIPv4, CURLOPT_WRITEDATA, &readIPV4Buffer);
		res = curl_easy_perform(curlIPv4);
		curl_easy_cleanup(curlIPv4);

		// Extract the IP address from the JSON string
		size_t start = readIPV4Buffer.find("\"ip\":\"") + 6;
		size_t end = readIPV4Buffer.find("\"", start);
		std::string ipv4Address = readIPV4Buffer.substr(start, end - start);

		std::cout << "\nIPv4 Address: " << ipv4Address << std::endl;
	}

	// Initialize CURL for IPv6
	curlIPv6 = curl_easy_init();
	if (curlIPv6) {
		curl_easy_setopt(curlIPv6, CURLOPT_URL, "https://api64.ipify.org?format=json");
		curl_easy_setopt(curlIPv6, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curlIPv6, CURLOPT_WRITEDATA, &readIPV6Buffer);
		res = curl_easy_perform(curlIPv6);
		curl_easy_cleanup(curlIPv6);

		// Extract the IP address from the JSON string
		size_t start = readIPV6Buffer.find("\"ip\":\"") + 6;
		size_t end = readIPV6Buffer.find("\"", start);
		std::string ipv6Address = readIPV6Buffer.substr(start, end - start);

		std::cout << "IPv6 Address: " << ipv6Address << std::endl;
	}
}

size_t GetSYSinfo::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}