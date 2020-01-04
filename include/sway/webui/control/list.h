#ifndef _SWAY_WEBUI_CONTROL_LIST_H
#define _SWAY_WEBUI_CONTROL_LIST_H

#include <sway/webcore/visualcomponent.h>
// #include <sway/webcore/model/abstractitemmodel.h>
#include <sway/webcore/base/treenodeelement.h>
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
		const webcore::base::TreeNodeElementCreateInfo & createInfo, emscripten::val styleSheet);

#pragma endregion // Static methods

#pragma region "Constructor / Destructor"

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	List(core::containers::HierarchyNodePtr_t parent,
		const std::string & nodeId, const webcore::base::TreeNodeElementCreateInfo & createInfo);

	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~List() = default;

#pragma endregion // Constructor / Destructor

#pragma region "IVisitable > HierarchyNode > TreeNodeElement > AVisualComponent implementation"

	virtual void accept(webcore::base::ITreeVisitor * visitor);

#pragma endregion // IVisitable > HierarchyNode > TreeNodeElement > AVisualComponent implementation

#pragma region "IObserver > AVisualComponent implementation"

	/*!
	 * \brief
	 *    Обновляет состояние наблюдателя.
	 */
	virtual void update() override;

#pragma endregion // IObserver > AVisualComponent implementation

	void makeItem(u32_t index, webcore::AVisualComponent * item);

#pragma region "Getters / Setters"

	void setStyleSheet(emscripten::val styleSheet);

#pragma endregion // Getters / Setters

private:
	std::map<std::string, std::string> _styleSheet;
};

NAMESPACE_END(control)
NAMESPACE_END(webui)
NAMESPACE_END(sway)

#endif // _SWAY_WEBUI_CONTROL_LIST_H
