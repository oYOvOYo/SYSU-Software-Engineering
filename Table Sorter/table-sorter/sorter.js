// 插入jQUery 与 lodash
document.write('<script type="text/javascript" src="../jQuery.js"></script>\
                <script type="text/javascript" src="../lodash.js"></script>');
// 避免污染
(function () {
    // 排序函数
    var sortTable = function (table) {
        // 构造table对象函数
        var createTable = function (table) {
            // 存一些局部属性方便使用
            var tableHead = table.find("thead");
            var tableBody = table.find("tbody");
            var trList = tableBody.find("tr");
            var haveBeenSord; // 检查是否已经排序过
            // 排序方法
            this.sort = function (index) {
                // 所在的列,方便比较
                var index = $(this).index();
                // 自定义比较对应字段的函数
                var sortAscend = function (tr1, tr2) {
                    var str1 = tr1.children[index].textContent;
                    var str2 = tr2.children[index].textContent;
                    return str1.localeCompare(str2);
                }
                var sortDescend = function (tr1, tr2) {
                    return - sortAscend(tr1, tr2);
                }
                // 清除之前带有的属性
                tableHead.find("th").removeClass("click descend ascend");
                if (haveBeenSord) { //判断是否已经排序
                    $(this).addClass("click").addClass("descend");
                    haveBeenSord = false;
                    trList.sort(sortDescend);
                } else {
                    $(this).addClass("click").addClass("ascend");
                    haveBeenSord = true;
                    trList.sort(sortAscend);
                }
                // 更新显示
                tableBody.append(trList);
            }
            // 绑定排序方法
            tableHead.find("th").bind("click", this.sort);
        }
        // 构造对象
        var tableObj = new createTable(table);
    };

    // 对每一个table使用排序函数
    window.onload = function () {
        $("table").each(function () {
            sortTable($(this));
        });
    }
})();
