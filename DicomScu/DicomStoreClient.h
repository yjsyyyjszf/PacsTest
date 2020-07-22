#pragma once

#include <string>
#include <list>
#include "dcmtk/dcmnet/dstorscu.h"

using namespace std;

class DicomStoreClient : DcmStorageSCU
{
public:
	DicomStoreClient(string serverHost, int serverPort, string serverAeTitle, string clientAeTitle);
	bool Store(const list<string>& filePaths);
	bool Verify();
};
