#include <sway/webui/control/layout.h>
#include <sway/webcore/base/treeupdater.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webui)
NAMESPACE_BEGIN(control)

void Layout::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<Layout, emscripten::base<webcore::base::TreeNodeElement>>(classname)
		.constructor<core::containers::HierarchyNodePtr_t, std::string, webcore::base::TreeNodeElementCreateInfo>();
}

Layout::Layout(core::containers::HierarchyNodePtr_t parent,
	const std::string & nodeId, const webcore::base::TreeNodeElementCreateInfo & createInfo)
	: webcore::base::TreeNodeElement(parent, core::containers::HierarchyNodeIndex(), nodeId, createInfo) {
	// Empty
}

NAMESPACE_END(control)
NAMESPACE_END(webui)
NAMESPACE_END(sway)
