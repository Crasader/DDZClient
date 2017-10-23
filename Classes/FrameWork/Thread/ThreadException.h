//////////////////////////////////////////////////////////
//// Author:	Zhu 
//// Date:		2017/10/23
//// Describe:	�߳��쳣��
/////////////////////////////////////////////////////////
#pragma once
#ifndef _THREAD_EXCEPTION_H
#define _THREAD_EXCEPTION_H

#include <exception>

// ============================================================================
//  Include Files for the threading libraries
// ============================================================================
#ifdef WIN32                // windows95 and above
#include <windows.h>
#else                       // linux
#include <pthread.h>
#endif

namespace ThreadLib {
	enum Error
	{
		Unspecified,                // δ˵���Ĵ���
		InitFailure,                // δ��ʼ��
		CreationFailure             // ��������
	};

	class Exception
		: public std::exception
	{
	public:
		// ====================================================================
		// Description: �����쳣
		// ====================================================================
		Exception(Error p_error = Unspecified)
		{
			m_error = p_error;
		}

		// ====================================================================
		// Description: ��ȡ��������
		// ====================================================================
		Error GetError() const
		{
			return m_error;
		}

	protected:
		Error m_error;
	};
}

#endif // !_THREAD_EXCEPTION_H
