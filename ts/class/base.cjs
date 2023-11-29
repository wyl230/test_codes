"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Base = void 0;
var utils_1 = require("./utils");
var Base = /** @class */ (function () {
    function Base() {
        (0, utils_1.print)('Base constructor');
    }
    Base.prototype.destroy = function () {
        (0, utils_1.print)('Base destroy');
    };
    Base.prototype.destructor = function () {
        (0, utils_1.print)('Base destructor');
    };
    return Base;
}());
exports.Base = Base;
var base = new Base();
