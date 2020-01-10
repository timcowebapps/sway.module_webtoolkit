#include <sway/webui/control/label.h>
#include <sway/webcore/treeupdater.h>
#include <sway/webcore/css/stylesheet.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webui)
NAMESPACE_BEGIN(control)

void Label::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<Label, emscripten::base<webcore::AVisualComponent>>(classname)
		.constructor<core::containers::HierarchyNodePtr_t, std::string, webcore::TreeNodeElementCreateInfo>()
		.smart_ptr<LabelSmartPtr_t>("LabelSmartPtr_t")
		.class_function("create", &Label::create, emscripten::allow_raw_pointers())
		.function("setFontFamily", &Label::setFontFamily)
		.function("setColor", &Label::setColor)
		.function("getText", &Label::getText)
		.function("setText", &Label::setText);
}

LabelSmartPtr_t Label::create(core::containers::HierarchyNodePtr_t parent, const std::string & nodeId,
	const webcore::TreeNodeElementCreateInfo & createInfo, emscripten::val styleSheet, const std::string & content) {

	auto instance = std::make_shared<Label>(parent, nodeId, createInfo);
	instance->setStyleSheet(styleSheet);
	instance->setHtmlContent(content);
	parent->addChild(instance.get());
	return instance;
}

Label::Label(core::containers::HierarchyNodePtr_t parent,
	const std::string & nodeId, const webcore::TreeNodeElementCreateInfo & createInfo)
	: webcore::AVisualComponent(parent, core::containers::HierarchyNodeIndex(), nodeId, createInfo) {
	// Empty
}

void Label::accept(webcore::ITreeVisitor * visitor) {
	visitor->visitOnEnter(this);

	for (core::containers::HierarchyNodePtr_t node : getChildren())
		static_cast<Label *>(node)->accept(visitor);
}

void Label::setFontFamily(const std::string & fontFamily) {
	_fontFamily = fontFamily;
}

void Label::setColor(const std::string & color) {
	_color = color;
}

std::string Label::getText() const {
	return getHtmlContent();
}

void Label::setText(const std::string & text) {
	if (text == getHtmlContent())
		return;

	setHtmlContent(text);
	for (core::containers::HierarchyListener * listener : getHostTree()->getListeners())
		listener->onNodeUpdated(getNodeIndex());
}

NAMESPACE_END(control)
NAMESPACE_END(webui)
NAMESPACE_END(sway)
