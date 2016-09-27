/*******************************************************
* Free game engine : SNOW
*
* FileName: ISocket.h
* Summary: ISocket

* Author: maoyanwen
* Date: 2015/08/14 
*******************************************************/
#ifndef Snow_ISocket_h__
#define Snow_ISocket_h__

#include "Interface/IInterface.h"

namespace Snow
{
	typedef sint32 socket_t;
	class ISocket : public IInterface
	{
	public:
		virtual bool Init() = 0;

		virtual void Close() = 0;

		virtual void OnCennect() = 0;

		virtual void OnClose() = 0;

	private:
		socket_t	m_nID;
	};
}

#endif // Snow_ISocket_h__