"use strict";

import * as _ from "underscore";

export class Label {
	public wasm_module: any = null;

	/**
	 * Конструктор представления.
	 * 
	 * @method constructor
	 * @param {any} wasm_context Контекст.
	 * @param {any} parent Родительский узел.
	 * @param {any} nodeId Уникальный идентификатор узла.
	 * @param {any} nodeCreateInfo Свойства представления.
	 * @param {any} stylesheet Стили.
	 * @param {String} text Текст.
	 */
	constructor(public wasm_context: any = null, parent: any,
		nodeId: string, nodeCreateInfo: any, stylesheet: any, text?: String) {

		this.wasm_module = wasm_context.module.Label.create(parent, nodeId,
			_.defaults(nodeCreateInfo, {
				tagname: "label"
			}), stylesheet, text);
	}
};
