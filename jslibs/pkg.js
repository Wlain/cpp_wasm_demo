//pkg.js
mergeInto(LibraryManager.library, {
    jsAdd: function (a, b) {
        console.log("jsAdd");
        return a + b;
    },

    jsConsoleLogInt: function (param) {
        console.log("jsConsoleLogInt:" + param);
    }
})