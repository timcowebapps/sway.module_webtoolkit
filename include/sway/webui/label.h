#ifndef _SWAY_WEBUI_LABEL_H
#define _SWAY_WEBUI_LABEL_H

#include <sway/webcore/base/treenodeelement.h>
#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webui)

class Label;
typedef std::shared_ptr<Label> LabelSmartPtr_t;

class Label
	: public base::TreeNodeElement {

public:

	#pragma region Static methods

	static void registerEmscriptenClass(lpcstr_t classname);

	static LabelSmartPtr_t createControl(core::containers::HierarchyNodePtr_t parent, const std::string & nodeId,
		const base::TreeNodeElementCreateInfo & createInfo, emscripten::val styleSheet, const std::string & content);

	#pragma endregion // Static methods

	#pragma region "Constructor / Destructor"

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	Label(core::containers::HierarchyNodePtr_t parent,
		const std::string & nodeId, const base::TreeNodeElementCreateInfo & createInfo);

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~Label() = default;

	#pragma endregion // Constructor / Destructor

	virtual void accept(base::ITreeVisitor * visitor);

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

NAMESPACE_END(webui)
NAMESPACE_END(sway)

#endif // _SWAY_WEBUI_LABEL_H
