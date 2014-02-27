#include "MyGUI_Precompiled.h"
#include "MyGUI_ImageSkin.h"
#include "MyGUI_RenderItem.h"
#include "MyGUI_LayerManager.h"
#include "MyGUI_CommonStateInfo.h"

namespace MyGUI
{

	ImageSkin::ImageSkin() :
		SubSkin()
	{
	}

	ImageSkin::~ImageSkin()
	{
	}

	void ImageSkin::_setAlign(const IntSize& _oldsize)
	{
		Base::_setAlign(_oldsize);
	}

	void ImageSkin::setImageSize( const IntSize& s )
	{
		mImageSize = s;

		if (!mAlign.isHStretch())
		{
			if (mAlign.isLeft())
				mCoord.left = 0;
			else if (mAlign.isRight())
				mCoord.left = mCoord.right() - mImageSize.width;
			else if (mAlign.isHCenter())
				mCoord.left = (mCroppedParent->getWidth() - mImageSize.width) / 2;
			mCoord.width = mImageSize.width;
		}

		if (!mAlign.isVStretch())
		{
			if (mAlign.isTop())
				mCoord.top = 0;
			else if (mAlign.isBottom())
				mCoord.top = mCoord.bottom() - mImageSize.height;
			else if (mAlign.isVCenter())
				mCoord.top = (mCroppedParent->getHeight() - mImageSize.height) / 2;

			mCoord.height = mImageSize.height;
		}

		mCurrentCoord = mCoord;

		_updateView();
	}

	void ImageSkin::setAlign( Align _value )
	{
		Base::setAlign(_value);

		if (!mAlign.isHStretch())
		{
			if (mAlign.isLeft())
				mCoord.left = 0;
			else if (mAlign.isRight())
				mCoord.left = mCroppedParent->getWidth() - mImageSize.width;
			else if (mAlign.isHCenter())
				mCoord.left = (mCroppedParent->getWidth() - mImageSize.width) / 2;
			mCoord.width = mImageSize.width;
		}
		else
		{
			mCoord.left = 0;
			mCoord.width = mCroppedParent->getWidth();
		}

		if (!mAlign.isVStretch())
		{
			if (mAlign.isTop())
				mCoord.top = 0;
			else if (mAlign.isBottom())
				mCoord.top = mCroppedParent->getHeight() - mImageSize.height;
			else if (mAlign.isVCenter())
				mCoord.top = (mCroppedParent->getHeight() - mImageSize.height) / 2;

			mCoord.height = mImageSize.height;
		}
		else
		{
			mCoord.top = 0;
			mCoord.height = mCroppedParent->getHeight();
		}

		mCurrentCoord = mCoord;

		_updateView();
	}

} // namespace MyGUI
