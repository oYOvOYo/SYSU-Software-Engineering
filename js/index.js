$(function () {

    var objList = [
        ["Coding", "https://github.com/jskyzero"],
        ["PlayStation", "http://psnine.com/psnid/sujiner"],
        ["Creating", "http://space.bilibili.com/2213467/#!/index"]
    ];

    var clickUrl = function clickUrl(objList) {
        for (var i = 0; i < objList.length; i++) {
            bindClickUrl(objList[i]);
        }

        function bindClickUrl(obj) {
            var ID = obj[0]; 
            var Url = obj[1];
            $("#" + ID).bind("click", function() {
                window.open(Url, "_self");
            })
        }  
    }
    
    clickUrl(objList);
})