"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Base = void 0;
var utils_1 = require("./utils");
var has_parent_1 = require("./has_parent");
var Base = /** @class */ (function () {
    function Base() {
        (0, utils_1.print)('Base constructor');
        this.has = new has_parent_1.Has(this);
    }
    return Base;
}());
exports.Base = Base;
