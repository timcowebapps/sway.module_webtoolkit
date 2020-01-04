#include <sway/webui/control/list.h>
#include <sway/webcore/base/treeupdater.h>
// #include <sway/webcore/model/abstractitemcollection.h>
// #include <sway/webcore/model/abstractitemmodel.h>
#include <sway/webui/emscriptenutil.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webui)
NAMESPACE_BEGIN(control)

void List::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<List, emscripten::base<webcore::AVisualComponent>>(classname)
		.constructor<core::containers::HierarchyNodePtr_t, std::string, webcore::base::TreeNodeElementCreateInfo>()
		//.smart_ptr<ListSmartPtr_t>("ListSmartPtr_t")
		.class_function("create", &List::create, emscripten::allow_raw_pointers())
		.function("makeItem", &List::makeItem, emscripten::allow_raw_pointers())
		.function("setStyleSheet", &List::setStyleSheet);
}

ListSmartPtr_t List::create(core::containers::HierarchyNodePtr_t parent, const std::string & nodeId,
	const webcore::base::TreeNodeElementCreateInfo & createInfo, emscripten::val styleSheet) {

	//auto instance = std::make_shared<List>(parent, nodeId, createInfo);
	auto instance = new List(parent, nodeId, createInfo);
	instance->setStyleSheet(styleSheet);
	//parent->addChild(instance.get());
	parent->addChild(instance);
	return instance;
}

List::List(core::containers::HierarchyNodePtr_t parent,
	const std::string & nodeId, const webcore::base::TreeNodeElementCreateInfo & createInfo)
	: webcore::AVisualComponent(parent, core::containers::HierarchyNodeIndex(), nodeId, createInfo) {
	// Empty
}

void List::accept(webcore::base::ITreeVisitor * visitor) {
	visitor->visitOnEnter(this);

	for (core::containers::HierarchyNodePtr_t node : getChildren())
		static_cast<List *>(node)->accept(visitor);
}

void List::update() {
	// Empty
}

void List::makeItem(u32_t index, webcore::AVisualComponent * item) {
	//auto collection = static_cast<webcore::model::AbstractItemCollection *>(getModel());
	item->setNodeId(core::misc::format("%s_%i", item->getNodeId().c_str(), index));
	//item->setModel(collection->getItem(index));
	item->initialize();
	addChild(item);
}

void List::setStyleSheet(emscripten::val styleSheet) {
	if (EmscriptenUtil::isNone(styleSheet) || EmscriptenUtil::isNone(styleSheet["list"]))
		return;

	_styleSheet.insert(std::make_pair("list", styleSheet["list"].as<std::string>()));
	setHtmlElementClasses(_styleSheet["list"]);
}

NAMESPACE_END(control)
NAMESPACE_END(webui)
NAMESPACE_END(sway)
