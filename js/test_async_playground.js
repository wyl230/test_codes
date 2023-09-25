// Modern JavaScript added a way to handle callbacks in an
// elegant way by adding a Promise based API which has special
// syntax that lets you treat asynchronous code as though it
// acts synchronously.
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __generator = (this && this.__generator) || function (thisArg, body) {
    var _ = { label: 0, sent: function() { if (t[0] & 1) throw t[1]; return t[1]; }, trys: [], ops: [] }, f, y, t, g;
    return g = { next: verb(0), "throw": verb(1), "return": verb(2) }, typeof Symbol === "function" && (g[Symbol.iterator] = function() { return this; }), g;
    function verb(n) { return function (v) { return step([n, v]); }; }
    function step(op) {
        if (f) throw new TypeError("Generator is already executing.");
        while (g && (g = 0, op[0] && (_ = 0)), _) try {
            if (f = 1, y && (t = op[0] & 2 ? y["return"] : op[0] ? y["throw"] || ((t = y["return"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;
            if (y = 0, t) op = [op[0] & 2, t.value];
            switch (op[0]) {
                case 0: case 1: t = op; break;
                case 4: _.label++; return { value: op[1], done: false };
                case 5: _.label++; y = op[1]; op = [0]; continue;
                case 7: op = _.ops.pop(); _.trys.pop(); continue;
                default:
                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) { _ = 0; continue; }
                    if (op[0] === 3 && (!t || (op[1] > t[0] && op[1] < t[3]))) { _.label = op[1]; break; }
                    if (op[0] === 6 && _.label < t[1]) { _.label = t[1]; t = op; break; }
                    if (t && _.label < t[2]) { _.label = t[2]; _.ops.push(op); break; }
                    if (t[2]) _.ops.pop();
                    _.trys.pop(); continue;
            }
            op = body.call(thisArg, _);
        } catch (e) { op = [6, e]; y = 0; } finally { f = t = 0; }
        if (op[0] & 5) throw op[1]; return { value: op[0] ? op[1] : void 0, done: true };
    }
};
var _this = this;
// Like all language features, this is a trade-off in
// complexity: making a function async means your return
// values are wrapped in Promises. What used to return a
// string, now returns a Promise<string>.
var func = function () { return ":wave:"; };
var asyncFunc = function () { return __awaiter(_this, void 0, void 0, function () { return __generator(this, function (_a) {
    return [2 /*return*/, ":wave:"];
}); }); };
var myString = func();
var myPromiseString = asyncFunc();
myString.length;
// myPromiseString is a Promise, not the string:
// myPromiseString.length;
// You can use the await keyword to convert a promise
// into its value. Today, these only work inside an async
// function.
var myWrapperFunction = function () { return __awaiter(_this, void 0, void 0, function () {
    var myString, myResolvedPromiseString;
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0:
                myString = func();
                return [4 /*yield*/, asyncFunc()];
            case 1:
                myResolvedPromiseString = _a.sent();
                // Via the await keyword, now myResolvedPromiseString
                // is a string
                myString.length;
                myResolvedPromiseString.length;
                return [2 /*return*/];
        }
    });
}); };
// Code which is running via an await can throw errors,
// and it's important to catch those errors somewhere.
var myThrowingFunction = function () { return __awaiter(_this, void 0, void 0, function () {
    return __generator(this, function (_a) {
        throw new Error("Do not call this");
    });
}); };
// We can wrap calling an async function in a try catch to
// handle cases where the function acts unexpectedly.
var asyncFunctionCatching = function () { return __awaiter(_this, void 0, void 0, function () {
    var myReturnValue, error_1;
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0:
                myReturnValue = "Hello world";
                _a.label = 1;
            case 1:
                _a.trys.push([1, 3, , 4]);
                return [4 /*yield*/, myThrowingFunction()];
            case 2:
                _a.sent();
                return [3 /*break*/, 4];
            case 3:
                error_1 = _a.sent();
                console.error("myThrowingFunction failed", error_1);
                return [3 /*break*/, 4];
            case 4: return [2 /*return*/, myReturnValue];
        }
    });
}); };
// Due to the ergonomics of this API being either returning
// a single value, or throwing, you should consider offering
// information about the result inside the returned value and
// use throw only when something truly exceptional has
// occurred.
var exampleSquareRootFunction = function (input) { return __awaiter(_this, void 0, void 0, function () {
    return __generator(this, function (_a) {
        if (isNaN(input)) {
            throw new Error("Only numbers are accepted");
        }
        if (input < 0) {
            return [2 /*return*/, { success: false, message: "Cannot square root negative number" }];
        }
        else {
            return [2 /*return*/, { success: true, value: Math.sqrt(input) }];
        }
        return [2 /*return*/];
    });
}); };
// Then the function consumers can check in the response and
// figure out what to do with your return value. While this
// is a trivial example, once you have started working with
// networking code these APIs become worth the extra syntax.
var checkSquareRoot = function (value) { return __awaiter(_this, void 0, void 0, function () {
    var response;
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0: return [4 /*yield*/, exampleSquareRootFunction(value)];
            case 1:
                response = _a.sent();
                if (response.success) {
                    response.value;
                }
                return [2 /*return*/];
        }
    });
}); };
// Async/Await took code which looked like this:
// getResponse(url, (response) => {
//   getResponse(response.url, (secondResponse) => {
//     const responseData = secondResponse.data
//     getResponse(responseData.url, (thirdResponse) => {
//       ...
//     })
//   })
// })
// And let it become linear like:
// const response = await getResponse(url)
// const secondResponse = await getResponse(response.url)
// const responseData = secondResponse.data
// const thirdResponse = await getResponse(responseData.url)
// ...
// Which can make the code sit closer to left edge, and
// be read with a consistent rhythm.
