#include <sway/webui/control/label.h>
#include <sway/webcore/base/treeupdater.h>
#include <sway/webui/emscriptenutil.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webui)
NAMESPACE_BEGIN(control)

void Label::registerEmscriptenClass(lpcstr_t classname) {
	emscripten::class_<Label, emscripten::base<webcore::base::TreeNodeElement>>(classname)
		.constructor<core::containers::HierarchyNodePtr_t, std::string, webcore::base::TreeNodeElementCreateInfo>()
		.smart_ptr<LabelSmartPtr_t>("LabelSmartPtr_t")
		.class_function("create", &Label::create, emscripten::allow_raw_pointers())
		.function("setStyleSheet", &Label::setStyleSheet)
		.function("setFontFamily", &Label::setFontFamily)
		.function("setColor", &Label::setColor)
		.function("getText", &Label::getText)
		.function("setText", &Label::setText);
}

LabelSmartPtr_t Label::create(core::containers::HierarchyNodePtr_t parent, const std::string & nodeId,
	const webcore::base::TreeNodeElementCreateInfo & createInfo, emscripten::val styleSheet, const std::string & content) {

	auto instance = std::make_shared<Label>(parent, nodeId, createInfo);
	instance->setStyleSheet(styleSheet);
	instance->setHtmlContent(content);
	parent->addChild(instance.get());
	return instance;
}

Label::Label(core::containers::HierarchyNodePtr_t parent,
	const std::string & nodeId, const webcore::base::TreeNodeElementCreateInfo & createInfo)
	: webcore::base::TreeNodeElement(parent, core::containers::HierarchyNodeIndex(), nodeId, createInfo) {
	// Empty
}

void Label::accept(webcore::base::ITreeVisitor * visitor) {
	visitor->visitOnEnter(this);

	for (core::containers::HierarchyNodePtr_t node : getChildren())
		static_cast<Label *>(node)->accept(visitor);
}

void Label::setStyleSheet(emscripten::val styleSheet) {
	if (EmscriptenUtil::isNone(styleSheet) || EmscriptenUtil::isNone(styleSheet["label"]))
		return;

	_styleSheet.insert(std::make_pair("label", styleSheet["label"].as<std::string>()));
	setHtmlElementClasses(_styleSheet["label"]);
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
