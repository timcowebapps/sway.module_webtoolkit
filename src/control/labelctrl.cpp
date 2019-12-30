#include <sway/webui/control/labelctrl.h>
#include <sway/webcore/base/treeupdater.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webui)
NAMESPACE_BEGIN(control)

void LabelCtrl::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<LabelCtrl, emscripten::base<webcore::base::TreeNodeElement>>(classname)
		.constructor<core::containers::HierarchyNodePtr_t, std::string, webcore::base::TreeNodeElementCreateInfo>()
		.smart_ptr<LabelSmartPtr_t>("LabelSmartPtr_t")
		.class_function("create", &LabelCtrl::create, emscripten::allow_raw_pointers())
		.function("setStyleSheet", &LabelCtrl::setStyleSheet)
		.function("setFontFamily", &LabelCtrl::setFontFamily)
		.function("setColor", &LabelCtrl::setColor)
		.function("getText", &LabelCtrl::getText)
		.function("setText", &LabelCtrl::setText);
}

LabelSmartPtr_t LabelCtrl::create(core::containers::HierarchyNodePtr_t parent, const std::string & nodeId,
	const webcore::base::TreeNodeElementCreateInfo & createInfo, emscripten::val styleSheet, const std::string & content) {

	auto instance = std::make_shared<LabelCtrl>(parent, nodeId, createInfo);
	instance->setStyleSheet(styleSheet);
	instance->setHtmlContent(content);
	parent->addChild(instance.get());
	return instance;
}

LabelCtrl::LabelCtrl(core::containers::HierarchyNodePtr_t parent,
	const std::string & nodeId, const webcore::base::TreeNodeElementCreateInfo & createInfo)
	: webcore::base::TreeNodeElement(parent, core::containers::HierarchyNodeIndex(), nodeId, createInfo) {
	// Empty
}

void LabelCtrl::accept(webcore::base::ITreeVisitor * visitor) {
	visitor->visitOnEnter(this);

	for (core::containers::HierarchyNodePtr_t node : getChildren())
		static_cast<LabelCtrl *>(node)->accept(visitor);
}

namespace Emscripten {
	bool isNone(emscripten::val const& val) {
		return val.isNull() || val.isUndefined();
	}
}

void LabelCtrl::setStyleSheet(emscripten::val styleSheet) {
	if (Emscripten::isNone(styleSheet) || Emscripten::isNone(styleSheet["label"]))
		return;

	_styleSheet.insert(std::make_pair("label", styleSheet["label"].as<std::string>()));
	setHtmlElementClasses(_styleSheet["label"]);
}

void LabelCtrl::setFontFamily(const std::string & fontFamily) {
	_fontFamily = fontFamily;
}

void LabelCtrl::setColor(const std::string & color) {
	_color = color;
}

std::string LabelCtrl::getText() const {
	return getHtmlContent();
}

void LabelCtrl::setText(const std::string & text) {
	if (text == getHtmlContent())
		return;

	setHtmlContent(text);
	for (core::containers::HierarchyListener * listener : getHostTree()->getListeners())
		listener->onNodeUpdated(getNodeIndex());
}

NAMESPACE_END(control)
NAMESPACE_END(webui)
NAMESPACE_END(sway)
