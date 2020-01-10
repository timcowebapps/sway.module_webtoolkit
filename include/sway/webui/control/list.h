#ifndef _SWAY_WEBUI_CONTROL_LIST_H
#define _SWAY_WEBUI_CONTROL_LIST_H

#include <sway/webcore/visualcomponent.h>
#include <sway/webcore/treenodeelement.h>
#include <sway/webcore/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webui)
NAMESPACE_BEGIN(control)

//typedef std::shared_ptr<class List> ListSmartPtr_t;
typedef class List * ListSmartPtr_t;

class List
	: public webcore::AVisualComponent {

public:

#pragma region "Static methods"

	static void registerEmscriptenClass(lpcstr_t classname);

	static ListSmartPtr_t create(core::containers::HierarchyNodePtr_t parent, const std::string & nodeId,
		const webcore::TreeNodeElementCreateInfo & createInfo, emscripten::val styleSheet);

#pragma endregion

#pragma region "Constructor / Destructor"

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	List(core::containers::HierarchyNodePtr_t parent,
		const std::string & nodeId, const webcore::TreeNodeElementCreateInfo & createInfo);

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~List() = default;

#pragma endregion

#pragma region "IVisitable > HierarchyNode > TreeNodeElement > AVisualComponent implementation"

	virtual void accept(webcore::ITreeVisitor * visitor);

#pragma endregion

#pragma region "IObserver > AVisualComponent implementation"

	/*!
	 * \brief
	 *    Обновляет состояние наблюдателя.
	 */
	virtual void update() override;

#pragma endregion

	void makeItem(u32_t index, webcore::AVisualComponent * item);
};

NAMESPACE_END(control)
NAMESPACE_END(webui)
NAMESPACE_END(sway)

#endif // _SWAY_WEBUI_CONTROL_LIST_H
