#ifndef __MYGUI_COCOS2D_VERTEXBUFFER_H__
#define __MYGUI_COCOS2D_VERTEXBUFFER_H__

#include "MyGUI_IVertexBuffer.h"

namespace MyGUI
{
	class Cocos2dVertexBuffer :
		public IVertexBuffer
	{
	public:
		Cocos2dVertexBuffer();
		virtual ~Cocos2dVertexBuffer();


		virtual void setVertexCount(size_t _count);
		virtual size_t getVertexCount();

		virtual Vertex* lock();
		virtual void unlock();

		/*internal:*/
		void destroy();
		void create();

		void releaseVBO();
		unsigned int genVBO();
		unsigned int getBufferID();

	private:
		unsigned int mBufferID;
		Vertex *mVertexBuffer;
		size_t mVertexCount;
		size_t mNeedVertexCount;
		size_t mSizeInBytes;
	};
}

#endif // __MYGUI_COCOS2D_VERTEXBUFFER_H__