#include "DicomStoreClient.h"

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
	for (list<string>::const_iterator filePath = filePaths.begin(); filePath != filePaths.end(); ++filePath)
	{
		addDicomFile(filePath->c_str(), E_FileReadMode::ERM_autoDetect);
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
