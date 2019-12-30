#ifndef _SWAY_WEBUI_LAYOUT_H
#define _SWAY_WEBUI_LAYOUT_H

#include <sway/webcore/base/treenodeelement.h>
#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webui)

class Layout
	: public webcore::base::TreeNodeElement {

public:

#pragma region "Static methods"

	static void registerEmscriptenClass(lpcstr_t classname);

#pragma endregion // Static methods

#pragma region "Constructor / Destructor"

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	Layout(core::containers::HierarchyNodePtr_t parent,
		const std::string & nodeId, const webcore::base::TreeNodeElementCreateInfo & createInfo);

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~Layout() = default;

#pragma endregion // Constructor / Destructor

private:
};

NAMESPACE_END(webui)
NAMESPACE_END(sway)

#endif // _SWAY_WEBUI_LAYOUT_H
