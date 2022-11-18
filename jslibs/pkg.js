//pkg.js
mergeInto(LibraryManager.library, {
    jsAdd: function (a, b) {
        console.log("jsAdd");
        return a + b;
    },
    jsConsoleLogInt: function (param) {
        console.log("jsConsoleLogInt:" + param);
    },
    showMeTheAnswer: function () {
        return jsShowMeTheAnswer();
    },
    jsPrintFib: function (ptr, count) {
        var str = 'jsPrintFib: ';
        for (var i = 0; i < count; i++) {
            str += Module.HEAP32[(ptr >> 2) + i];
            str += ' ';
        }
        console.log(str);
    }
})