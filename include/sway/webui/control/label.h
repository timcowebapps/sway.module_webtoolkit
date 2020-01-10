#ifndef _SWAY_WEBUI_CONTROL_LABEL_H
#define _SWAY_WEBUI_CONTROL_LABEL_H

#include <sway/webcore/visualcomponent.h>
#include <sway/webcore/treenodeelement.h>
#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webui)
NAMESPACE_BEGIN(control)

typedef std::shared_ptr<class Label> LabelSmartPtr_t;

class Label
	: public webcore::AVisualComponent {

public:

#pragma region Static methods

	static void registerEmscriptenClass(lpcstr_t classname);

	static LabelSmartPtr_t create(core::containers::HierarchyNodePtr_t parent, const std::string & nodeId,
		const webcore::TreeNodeElementCreateInfo & createInfo, emscripten::val styleSheet, const std::string & content);

#pragma endregion

#pragma region "Constructor / Destructor"

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	Label(core::containers::HierarchyNodePtr_t parent,
		const std::string & nodeId, const webcore::TreeNodeElementCreateInfo & createInfo);

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~Label() = default;

#pragma endregion

#pragma region "IVisitable > HierarchyNode > TreeNodeElement implementation"

	virtual void accept(webcore::ITreeVisitor * visitor);

#pragma endregion

#pragma region "Getters / Setters"

	void setFontFamily(const std::string & fontFamily);

	void setColor(const std::string & color);

	std::string getText() const;

	void setText(const std::string & text);

#pragma endregion

private:
	std::string _fontFamily;
	std::string _color;
};

NAMESPACE_END(control)
NAMESPACE_END(webui)
NAMESPACE_END(sway)

#endif // _SWAY_WEBUI_CONTROL_LABEL_H
