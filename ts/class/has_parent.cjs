"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var base_1 = require("./base");
var utils_1 = require("./utils");
var Has = /** @class */ (function () {
    function Has(parent) {
        this.parent = parent;
        (0, utils_1.print)('Has constructor');
    }
    return Has;
}());
var has = new Has(new base_1.Base());
