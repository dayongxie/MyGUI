/*!
	@file
	@author		Albert Semenov
	@date		10/2008
*/
#include "Precompiled.h"
#include "EditorWindow.h"

namespace demo
{

	EditorWindow::EditorWindow() :
		BaseLayout("EditorWindow.layout")
	{
		MyGUI::FontManager& fontmanager = MyGUI::FontManager::getInstance();

		MyGUI::IFont* font = fontmanager.getByName(fontmanager.getDefaultFont());

		MyGUI::ITexture* texture = font->getTextureFont();

		MyGUI::ImageBox *imgBox;
		assignWidget(imgBox, "ImageBox");

		imgBox->setImageTexture(texture->getName());
	}

	void EditorWindow::clearView()
	{
		MyGUI::WidgetManager::getInstance().destroyWidgets(mMainWidget->getEnumerator());
	}

	MyGUI::Widget* EditorWindow::getView()
	{
		return mMainWidget;
	}

} // namespace demo
