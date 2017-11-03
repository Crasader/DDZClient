#pragma once
#ifndef _MODULE_MANAGER_H
#define _MODULE_MANAGER_H

#include "IModule.h"
#include <map>
#include <BaseMsg.pb.h>
#include <Singleton.h>
#include "DataCenter.h"

typedef std::map<std::string, IModule*> MODULE_MAP;
typedef std::map<std::string, IModule*>::iterator MODULE_ITER;
typedef std::shared_ptr<google::protobuf::Message> MSG_PTR;

class CModuleManager
	: public CSingleTon<CModuleManager>
{
	friend class CSingleTon<CModuleManager>;
public:
	// ���ģ��
	void addModule(std::string strModuleName, IModule * pModule) {
		m_moduleMap[strModuleName] = pModule;
	}

	// �Ƴ�ģ��
	void removeModule(MODULE_ITER it) {
		m_moduleMap.erase(it);
	}

	// �Ƴ�����ģ��
	void removeAllModule() {
		while (!m_moduleMap.empty())
		{
			MODULE_ITER it = m_moduleMap.begin();
			removeModule(it);
		}
	}

	// ��ȡָ��ģ��
	IModule * getModule(const char * strModuleName) {
		return m_moduleMap[strModuleName];
	}

	// ��ģ������������ ģ������ʽ "xxx.xx.xx" ���һ������ģ����
	std::string getModuleName(std::string strTypeName) {
		int index = strTypeName.find_last_of(".");
		std::string moduleName = strTypeName;
		if (index != std::string::npos)
		{
			moduleName = strTypeName.substr(0, index);
		}

		return moduleName;
	}

	// ��ʼ��ģ��
	virtual bool init() {
		auto pDataCenter = CDataCenter::getInstance();
		pDataCenter->init();
		addModule("data", pDataCenter);

		return true;
	}

	// ����Ϣ�ַ�������ģ��
	void dispatchMsg(MSG_PTR pMsg) {
		std::shared_ptr<zhu::SelfDescribingMessage> pTmpMsg = std::dynamic_pointer_cast<zhu::SelfDescribingMessage>(pMsg);
		if (NULL == pTmpMsg.get())
		{
			//log("dynamic_cast msg failed");
			return;
		}

		auto it = m_moduleMap.begin();

		while (it != m_moduleMap.end()) {
			it->second->handle(pTmpMsg);
			it++;
		}
	}

private:
	CModuleManager() {}

private:
	MODULE_MAP m_moduleMap;
};

#define ModuleManagerIns CModuleManager::getInstance()
#endif