/*******************************************************
* Free game engine : SNOW
*
* FileName: IComponent.h
* Summary: Component

* Author: maoyanwen
* Date: 2015/06/05 
*******************************************************/
#ifndef Snow_IComponent_h__
#define Snow_IComponent_h__

#include "Interface/IInterface.h"

namespace Snow
{
	class IGameObject;

	class IComponent : public IInterface
	{
	public:
		IComponent(IGameObject* pGameObject){	m_pOwner = pGameObject;		}

		virtual ~IComponent(){};

		IGameObject* GetOwner(){	return m_pOwner;	}

		virtual Result Init() = 0;

		template<typename T>
		Result QueryInterface(T** pInterface);
	private:
		IGameObject* m_pOwner;
	};

	template<typename T>
	Result IComponent::QueryInterface(T** pInterface)
	{
		*pInterface = NULL;
		if (*pInterface = dynamic_cast<T*>(this))
		{
			return R_OK;
		}

		if (m_pOwner)
		{
			return m_pOwner->QueryInterface<T>(pInterface);
		}

		return R_FAIL;
	}
}

#endif // Snow_IComponent_h__