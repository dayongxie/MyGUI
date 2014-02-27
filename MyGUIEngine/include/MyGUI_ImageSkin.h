#ifndef __MYGUI_IMAGE_SKIN_H__
#define __MYGUI_IMAGE_SKIN_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_SubSkin.h"

namespace MyGUI
{

	class RenderItem;

	class MYGUI_EXPORT ImageSkin :
		public SubSkin
	{
		MYGUI_RTTI_DERIVED( ImageSkin )
	public:
		ImageSkin();
		virtual ~ImageSkin();

		virtual void setAlign(Align _value);
		/*internal:*/
		virtual void _setAlign(const IntSize& _oldsize);

		void setImageSize(const IntSize& s);

	private:
		IntSize mImageSize;
	};

} // namespace MyGUI

#endif // __MYGUI_IMAGE_SKIN_H__
