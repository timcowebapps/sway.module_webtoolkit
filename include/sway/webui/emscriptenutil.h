#ifndef _SWAY_WEBUI_EMSCRIPTENUTIL_H
#define _SWAY_WEBUI_EMSCRIPTENUTIL_H

#include <sway/core.h>
#include <emscripten/val.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(webui)

class EmscriptenUtil {
public:
	static bool isNone(emscripten::val const & val) {
		return val.isNull() || val.isUndefined();
	}
};

NAMESPACE_END(webui)
NAMESPACE_END(sway)

#endif // _SWAY_WEBUI_EMSCRIPTENUTIL_H
