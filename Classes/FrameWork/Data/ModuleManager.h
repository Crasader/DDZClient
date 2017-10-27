#pragma once
#ifndef _MODULE_MANAGER_H
#define _MODULE_MANAGER_H

#include "IModule.h"
#include <map>
#include <BaseMsg.pb.h>
#include <Singleton.h>

typedef std::map<std::string, std::shared_ptr<IModule>> MODULE_MAP;
typedef std::map<std::string, std::shared_ptr<IModule>>::iterator MODULE_ITER;
typedef std::shared_ptr<google::protobuf::Message> MSG_PTR;
typedef std::shared_ptr<IModule> MODULE_PTR;

class CModuleManager
	: public CSingleTon<CModuleManager>
{
	friend class CSingleTon<CModuleManager>;
public:
	// ���ģ��
	void addModule(std::string strModuleName, MODULE_PTR pModule) {
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
	MODULE_PTR getModule(const char * strModuleName) {
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
		return true;
	}

	// ����Ϣ�ַ�������ģ��
	void dispatchMsg() {

	}

private:
	CModuleManager() {}

private:
	MODULE_MAP m_moduleMap;
};

#endif