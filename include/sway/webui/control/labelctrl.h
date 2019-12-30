#ifndef _SWAY_WEBUI_CONTROL_LABELCTRL_H
#define _SWAY_WEBUI_CONTROL_LABELCTRL_H

#include <sway/webcore/base/treenodeelement.h>
#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webui)
NAMESPACE_BEGIN(control)

typedef std::shared_ptr<class LabelCtrl> LabelSmartPtr_t;

class LabelCtrl
	: public webcore::base::TreeNodeElement {

public:

#pragma region Static methods

	static void registerEmscriptenClass(lpcstr_t classname);

	static LabelSmartPtr_t create(core::containers::HierarchyNodePtr_t parent, const std::string & nodeId,
		const webcore::base::TreeNodeElementCreateInfo & createInfo, emscripten::val styleSheet, const std::string & content);

#pragma endregion // Static methods

#pragma region "Constructor / Destructor"

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	LabelCtrl(core::containers::HierarchyNodePtr_t parent,
		const std::string & nodeId, const webcore::base::TreeNodeElementCreateInfo & createInfo);

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~LabelCtrl() = default;

#pragma endregion // Constructor / Destructor

	virtual void accept(webcore::base::ITreeVisitor * visitor);

#pragma region Getters / Setters

	void setStyleSheet(emscripten::val styleSheet);

	void setFontFamily(const std::string & fontFamily);

	void setColor(const std::string & color);

	std::string getText() const;

	void setText(const std::string & text);

#pragma endregion // Getters / Setters

private:
	std::map<std::string, std::string> _styleSheet;
	std::string _fontFamily;
	std::string _color;
};

NAMESPACE_END(control)
NAMESPACE_END(webui)
NAMESPACE_END(sway)

#endif // _SWAY_WEBUI_CONTROL_LABELCTRL_H
