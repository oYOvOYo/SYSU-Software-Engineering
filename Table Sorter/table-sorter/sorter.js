// 插入jQUery 与 lodash
document.write('<script type="text/javascript" src="../jQuery.js"></script>\
                <script type="text/javascript" src="../lodash.js"></script>');

(function () {

    var sortTable = function (table) {
        var createTable = function (table) {
            var tableHead = table.find("thead");
            var tableBody = table.find("tbody");
            var trList = tableBody.find("tr");
            var haveBeenSord;

            this.sort = function (index) {
                var index = $(this).index();
                var sortAscend = function (tr1, tr2) {
                    var str1 = tr1.children[index].textContent;
                    var str2 = tr2.children[index].textContent;
                    return str1.localeCompare(str2);
                }
                var sortDescend = function (tr1, tr2) {
                    return - sortAscend(tr1, tr2);
                }
                tableHead.find("th").removeClass("click descend ascend");
                if (haveBeenSord) {
                    $(this).addClass("click").addClass("descend");
                    haveBeenSord = false;
                    trList.sort(sortDescend);
                } else {
                    $(this).addClass("click").addClass("ascend");
                    haveBeenSord = true;
                    trList.sort(sortAscend);
                }

                tableBody.append(trList);
            }
            tableHead.find("th").bind("click", this.sort);
        }

        var tableObj = new createTable(table);
        console.log(tableObj);
    };


    window.onload = function () {
        $("table").each(function () {
            console.log(sortTable($(this)));
        });
    }

})();
