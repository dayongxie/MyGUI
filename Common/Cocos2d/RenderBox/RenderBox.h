/*!
@file
@author		Evmenov Georgiy
@date		09/2009
@module
*/

#ifndef __RENDER_BOX_H__
#define __RENDER_BOX_H__

#include <cocos2d.h>
#include <MyGUI.h>
#include <MyGUI_Cocos2dPlatform.h>
#include <MyGUI_Cocos2dRTTexture.h>

namespace wraps
{
	class RenderBox
	{
	public:
		RenderBox();
		~RenderBox();
		void setCanvas(MyGUI::Canvas* _value);
		void destroy();
		void setBackgroundColour(const MyGUI::Colour& _value);

		cocos2d::CCScene* createScene();
		void clearScene();
		cocos2d::CCScene* getRunningScene() { return mScene; }
		
		void frameAdvise(bool _advise);
	protected:
		void eventPreTextureChanges(MyGUI::Canvas* _canvas);
		void requestUpdateCanvas(MyGUI::Canvas* _canvas, MyGUI::Canvas::Event _event);

		void frameEntered(float _time);
	protected:
		MyGUI::Canvas* mCanvas;
		MyGUI::IRenderTarget* mRenderTarget;
		MyGUI::Colour mColour;
		cocos2d::CCScene* mScene;
	};

} // namespace wraps

#endif // __RENDER_BOX_H__
