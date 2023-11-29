"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Has = void 0;
var utils_1 = require("./utils");
var Has = /** @class */ (function () {
    function Has(parent) {
        this.parent = parent;
        (0, utils_1.print)('Has constructor');
    }
    return Has;
}());
exports.Has = Has;
// const has = new Has(new Base());
