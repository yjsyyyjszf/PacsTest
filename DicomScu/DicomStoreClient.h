#pragma once

#include <string>
#include <list>
#include "dcmtk/dcmnet/dstorscu.h"
#include "dcmtk/dcmjpeg/djdecode.h"
#include "dcmtk/dcmjpls/djdecode.h"
#include "dcmtk/dcmdata/dcrledrg.h"

using namespace std;

class DicomStoreClient : DcmStorageSCU
{
public:
	DicomStoreClient(string serverHost, int serverPort, string serverAeTitle, string clientAeTitle);
	bool Store(const list<string>& filePaths);
	bool Verify();
};
