#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <boost/noncopyable.hpp>

#include "common_define.h"
#include "package_if.h"
#include "util.h"
#include "package_error.h"

namespace packagemgr
{

class PackageManager : public boost::noncopyable
{
public:
    PackageManager();
	~PackageManager();
	
	/** 
	 *  ������/ֹͣ
	 *  @return bool.
	*/
    PackageError::ErrorType Startup();
	PackageError::ErrorType Shutdown();	
	
    /** 
     *  �����û��Զ������ݣ������ʽ�û��Լ�cast
     *  @param[in] data.
     *  @return void.
    */
    void set_user_data(const void* data);
    const void* user_data()const;
    
	/** 
	 *  ��������·�������ص�������
	 *  @param[in] file.
	 *  @param[in/out] package_name.
	 *  @return bool.
	*/
    PackageError::ErrorType AddPackage(const std::string& file, std::string& package_name);
	
	/** 
	 *  ������ɾ��
	 *  @param[in] package_name.
	 *  @return bool.
	*/
	PackageError::ErrorType DelPackage(const std::string& package_name);
	
	/** 
	 *  ��������ȡ��Ӧ�İ��ӿ�
	 *  @param[in] package_name.
	 *  @param[in/out] package.
	 *  @return bool.
	*/
	template <typename T>
	PackageError::ErrorType GetPackage(const std::string& package_name, T* &package)
	{
		package_map::iterator it = m_packages_map.find(package_name);
		if (it == m_packages_map.end())
		{
            return PackageError::PACKAGE_ERR_PACKAGE_NOT_FOUND;
		}
        
		package = dynamic_cast<T*>(it->second);
		if( package == NULL )
        {
            return PackageError::PACKAGE_ERR_CAST_INTERFACE_FAIL;
        }
        
        return PackageError::PACKAGE_SUCCESS;
	}
	
private:
	
	/** �ڱ�׼80�е���Ļ����������͹ر���Ϣ.
	 *
	 * �ڰ������͹ر�ʱ���������еĽ����ӡ����Ӧ����Ϣ.
	 *
	 *	@param[in] sname ��������.
	 *	@param[in] proc  ������رչ���.
	 *	@param[in] isSuccessed ִ�н��.
	 */
	static void PrintMsg( const std::string &sname, const std::string &proc, bool result );
	
private:
	typedef std::unordered_map<std::string, IPackage*> package_map;
	package_map m_packages_map;
    
	//�����ڹرճ���ʱ���հ�����˳���������ж�أ�ʹ��reverse_iterator
	typedef std::vector<IPackage*> package_vec;
	package_vec m_packages_vec;

    //�û��Զ������ݣ�Ŀǰ����Ϊconst����
    const void* m_user_data;
};

typedef Singleton<PackageManager> packagemgr_instance;

}

#endif // PACKAGEMANAGER_H
