#include "MyGUI_Cocos2dVertexBuffer.h"
#include "MyGUI_VertexData.h"

#include <CCGL.h>

namespace MyGUI
{

	const size_t VERTEX_IN_QUAD = 6;
	const size_t RENDER_ITEM_STEEP_REALLOCK = 5 * VERTEX_IN_QUAD;

	Cocos2dVertexBuffer::Cocos2dVertexBuffer() :
		mVertexBuffer(nullptr),
		mNeedVertexCount(0),
		mVertexCount(RENDER_ITEM_STEEP_REALLOCK),
		mBufferID(0),
		mSizeInBytes(0)
	{
	}

	Cocos2dVertexBuffer::~Cocos2dVertexBuffer()
	{
		destroy();
	}

	void Cocos2dVertexBuffer::setVertexCount(size_t _count)
	{
		if (_count != mNeedVertexCount)
		{
			mNeedVertexCount = _count;
			destroy();
			if (_count > 0)
				create();
		}
	}

	size_t Cocos2dVertexBuffer::getVertexCount()
	{
		return mNeedVertexCount;
	}

	Vertex* Cocos2dVertexBuffer::lock()
	{
		return mVertexBuffer;
	}

	void Cocos2dVertexBuffer::unlock()
	{
		if (mBufferID)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
			glBufferSubData(GL_ARRAY_BUFFER, 0, mSizeInBytes, mVertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}

	void Cocos2dVertexBuffer::destroy()
	{
		if (mVertexBuffer)
		{
			delete[] mVertexBuffer;
			mVertexBuffer = nullptr;
		}

		releaseVBO();
	}

	void Cocos2dVertexBuffer::create()
	{
		destroy();

		mSizeInBytes = mNeedVertexCount * sizeof(MyGUI::Vertex);
		mVertexBuffer = new Vertex[mNeedVertexCount];
		if (!mVertexBuffer)
			return;

		if (!genVBO())
			destroy();
	}

	void Cocos2dVertexBuffer::releaseVBO()
	{
		if (mBufferID)
		{
			glDeleteBuffers(1, &mBufferID);
			mBufferID = 0;
		}
	}

	unsigned int Cocos2dVertexBuffer::genVBO()
	{
		releaseVBO();

		do 
		{
			glGenBuffers(1, &mBufferID);

			if (!mBufferID) break;

			glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
			glBufferData(GL_ARRAY_BUFFER, mSizeInBytes, mVertexBuffer, GL_STATIC_DRAW);

			int bufferSize = 0;
			glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			if (mSizeInBytes != (size_t)bufferSize)
			{
				releaseVBO();
				break;
			}
		} while(0);

		return mBufferID;
	}

	unsigned int Cocos2dVertexBuffer::getBufferID()
	{
		if (!mBufferID) {
			genVBO();
		}

		return mBufferID;
	}
}