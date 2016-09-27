/*******************************************************
* Free game engine : SNOW
*
* FileName: IGameObject.h
* Summary: GameObject

* Author: maoyanwen
* Date: 2015/06/05 
*******************************************************/
#ifndef Snow_IGameObject_h__
#define Snow_IGameObject_h__

#include "Interface/IInterface.h"
#include "Interface/IEventBus.h"

namespace Snow
{
	class IComponent;

	class IGameObject : public IInterface
	{
	public:
		template<typename T>
		Result QueryInterface(T** pInterface);

		Result AddComponent(IComponent* pCom)
		{
			if (!pCom)
			{
				return R_FAIL;
			}
			m_pComponents.push_back(pCom);
			return R_OK;
		}

		virtual Result Init()
		{
			return InitComponents();
		}

		virtual Result InitComponents() = 0;
	private:
		vector<Snow::IComponent*>	m_pComponents;
	};

	template<typename T>
	Result IGameObject::QueryInterface(T** pInterface)
	{
		*pInterface = NULL;
		if (*pInterface = dynamic_cast<T*>(this))
		{
			return R_OK;
		}

		for (size_t i = 0; i < m_pComponents.size(); ++i)
		{
			if (*pInterface = dynamic_cast<T*>(m_pComponents[i]))
			{
				return R_OK;
			}
		}

		return R_FAIL;
	}

}

#endif // Snow_IGameObject_h__