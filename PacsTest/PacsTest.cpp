#include <iostream>
#include "../DicomScu/DicomStoreClient.h"

const string serverHost = "localhost";
const int serverPort = 104;
const string serverAeTitle = "SERVER";
const string clientAeTitle = "CLIENT";

int main(int argc, const char* argv[])
{
	DicomStoreClient client(serverHost, serverPort, serverAeTitle, clientAeTitle);
	if (client.Verify())
	{
		cout << serverAeTitle << " is running" << endl;

		list<string> filePaths;
		for (int i = 1; i < argc; ++i)
		{
			filePaths.push_back(argv[i]);
		}
		if (filePaths.size() > 0)
		{
			client.Store(filePaths);
		}
	}
	else
	{
		cout << "Cannot connect to " << serverAeTitle << endl;
	}
	return 0;
}
