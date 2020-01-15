#include <sway/webui/control/list.h>
#include <sway/webcore/treeupdater.h>
#include <sway/webcore/css/stylesheet.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webui)
NAMESPACE_BEGIN(control)

void List::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<List, emscripten::base<webcore::mvc::AView>>(classname)
		.constructor<core::containers::HierarchyNodePtr_t, std::string, webcore::TreeNodeElementCreateInfo>()
		//.smart_ptr<ListSmartPtr_t>("ListSmartPtr_t")
		.class_function("create", &List::create, emscripten::allow_raw_pointers())
		.function("makeItem", &List::makeItem, emscripten::allow_raw_pointers());
}

ListSmartPtr_t List::create(core::containers::HierarchyNodePtr_t parent, const std::string & nodeId,
	const webcore::TreeNodeElementCreateInfo & createInfo, emscripten::val styleSheet) {

	//auto instance = std::make_shared<List>(parent, nodeId, createInfo);
	auto instance = new List(parent, nodeId, createInfo);
	instance->setStyleSheet(styleSheet);
	//parent->addChild(instance.get());
	parent->addChild(instance);
	return instance;
}

List::List(core::containers::HierarchyNodePtr_t parent,
	const std::string & nodeId, const webcore::TreeNodeElementCreateInfo & createInfo)
	: webcore::mvc::AView(parent, core::containers::HierarchyNodeIndex(), nodeId, createInfo) {
	// Empty
}

void List::accept(webcore::ITreeVisitor * visitor) {
	visitor->visitOnEnter(this);

	for (core::containers::HierarchyNodePtr_t node : getChildren())
		static_cast<List *>(node)->accept(visitor);
}

void List::update() {
	// Empty
}

void List::makeItem(u32_t index, webcore::mvc::AView * item) {
	//auto collection = static_cast<webcore::ACollectionModel *>(getModel());
	item->setNodeId(core::misc::format("%s_%i", item->getNodeId().c_str(), index));
	//item->setModel(collection->getItem(index));
	item->initialize();
	addChild(item);
}

NAMESPACE_END(control)
NAMESPACE_END(webui)
NAMESPACE_END(sway)
