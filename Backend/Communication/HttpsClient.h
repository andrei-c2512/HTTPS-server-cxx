#pragma once
#include "SecureClient.h"
#include "HttpsClientConnection.h"

class HttpsClient : public SecureClient<HttpResponse, HttpRequest, HttpsClientConnection> {
public:
	HttpsClient(const std::string& certificateFile , std::vector<std::string> approvedList)
		:SecureClient<HttpResponse, HttpRequest, HttpsClientConnection>(certificateFile , std::move(approvedList))
	{}
protected:
	//using SecureClient<HttpResponse, HttpRequest, HttpsClientConnection>::onNewMessage;
};