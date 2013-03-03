/********************************************************************
	filename: 	package_if.h
	author:		billowqiu
	
	purpose:	package����java�а�(jar)�ĸ��һ������ʾwindows��dll����linux�����so
				package�����߱����ϸ��սӿڵķ�ʽ���б��룬��c++�м�����Ϊvirtual���������ṩ����
				ÿһ��package�����ṩ�ķ�������ӿ��ļ����ж��壬������������packageʱ�����Ԥ����ĵ�������
				����μ�common_define.h�ļ��е�PACKAGE_LOAD��PACKAGE_UNLOAD����ԭ��
				����ͨ����PACKAGE_DEFINE���嵼������
*********************************************************************/

#ifndef IPACKAGE_H_
#define IPACKAGE_H_

#include "common_define.h"

namespace packagemgr
{

enum EPackageNotify
{
	NOTIFY_PACKAGE_LOAD,
	NOTIFY_PACKAGE_UNLOAD,
	NOTIFY_PACKAGE_UPDATE
};

interface IPackage
{
	friend class PackageManager;
	
	struct PackageInfo
	{
		PackageInfo(){}
		PackageInfo(package_handler handle, PACKAGE_LOAD load_fun, PACKAGE_UNLOAD unload_fun):
		m_handle(handle),
		m_packageLoad(load_fun), 
		m_packageUnload(unload_fun)
		{
		}
		//����Ӧ��ƽ̨��صľ��
		package_handler m_handle;
		//������ʱ�ɹ��������õļ��غ���
		PACKAGE_LOAD m_packageLoad;
		//��ж��ʱ�ɹ��������õ�ж�غ���
		PACKAGE_UNLOAD m_packageUnload;
	};
	
public:
	virtual ~IPackage()
    {
    }
	
	/** 
	 *  ���İ汾
	 *  @return float.
	*/
	virtual float Version() = 0;

    /** 
     *  ������/ֹͣ
     *  @return bool.
    */
    virtual bool Startup() = 0;
    virtual bool Shutdown() = 0;
    
	/** 
	 *  ��������
	 *  @return std::string.
	*/
	virtual std::string Name() = 0;
	
	/** 
	 *  ֪ͨ�¼���ʵ���߸���type����static_cast
	 *  @param[in] type.
	 *  @param[in] data.
	 *  @return void.
	*/
	virtual void Notify(EPackageNotify type, const void* data) = 0;

	//ֻ�������������
private:
	void set_info(const PackageInfo& info)
	{
		m_info = info;
	}
	PackageInfo get_info()const
	{
		return m_info;
	}
	
private:
	PackageInfo m_info;
};

}

#endif // IPACKAGE_H_
