////////////////////////////////////////////////////////////////////////
// Copyright(c) 1999-2099, TQ Digital Entertainment, All Rights Reserved
// Author��  zhu
// Created�� 2017/10/25
// Describe��Э����,��������������ݰ�
////////////////////////////////////////////////////////////////////////
#ifndef _CODE_H
#define _CODE_H

#include <google/protobuf/message.h>
#include <BaseMsg.pb.h>

#define HEADER_SIZE 4

typedef std::shared_ptr<google::protobuf::Message> MessagePtr;

class ProtocolCode {

public:
	// ����ö��
	enum ErrorCode
	{
		SUCCESS = 0,
		INVALID_NAME_LEN,
		UNKNOWN_MESSAGE_TYPE,
		PARSE_ERROR,
	};

public:
	
	// ����
	static const char * encode(const google::protobuf::Message & message, int & iBuffSize);

	// ����
	static google::protobuf::Message * decode(char * pBuf);

	// ��ȡͷ��
	static unsigned int readHdr(char * pBuf);

	// ������Ϣ
	static google::protobuf::Message * createMessage(const std::string & strTypeName);

	// ����Message���������õ����ݰ�
	static MessagePtr parseInnerMsg(std::shared_ptr<zhu::SelfDescribingMessage> pOutterMsg, ErrorCode& error);
};

#endif // !_CODE_H
