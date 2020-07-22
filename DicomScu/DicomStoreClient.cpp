#include "DicomStoreClient.h"
#include "dcmtk/dcmjpeg/djdecode.h"
#include "dcmtk/dcmjpls/djdecode.h"
#include "dcmtk/dcmdata/dcrledrg.h"

DicomStoreClient::DicomStoreClient(string serverHost, int serverPort, string serverAeTitle, string clientAeTitle)
{
	setPeerHostName(serverHost.c_str());
	setPeerPort(serverPort);
	setPeerAETitle(serverAeTitle.c_str());
	setAETitle(clientAeTitle.c_str());

	DJDecoderRegistration::registerCodecs();
	DJLSDecoderRegistration::registerCodecs();
	DcmRLEDecoderRegistration::registerCodecs();
}

bool DicomStoreClient::Store(const list<string>& filePaths)
{
	for (auto pFilePath = filePaths.begin(); pFilePath != filePaths.end(); ++pFilePath)
	{
		addDicomFile(pFilePath->c_str(), E_FileReadMode::ERM_autoDetect);
	}

	bool ok = true;
	while (addPresentationContexts().good())
	{
		ok = initNetwork().good() && negotiateAssociation().good() && sendSOPInstances().good();
		releaseAssociation();
		if (!ok)
		{
			break;
		}
	}
	clearPresentationContexts();
	return ok;
}

bool DicomStoreClient::Verify()
{
	OFList<OFString> transferSyntaxes;
	transferSyntaxes.push_back(UID_LittleEndianExplicitTransferSyntax);
	transferSyntaxes.push_back(UID_LittleEndianImplicitTransferSyntax);
	addPresentationContext(UID_VerificationSOPClass, transferSyntaxes);

	bool ok = initNetwork().good() && negotiateAssociation().good() && sendECHORequest(0).good();
	releaseAssociation();
	clearPresentationContexts();
	return ok;
}
