window.onload = function () {
    // 当加载好时候
    // 获取puzzle，方便操作
    var puzzle = document.getElementById("puzzle");
    // 计算出拼好的情况，方便后续比对
    var rightAns = [];
    for (var i = 0; i < 16; i++) {
        var position = {
            left: (i % 4) * 100 + "px",
            top: Math.floor(i / 4) * 100 + "px"
        };
        rightAns.push(position)
    }
    puzzleInitial();

    function puzzleInitial() {
        // 深复制
        var cloneAns = JSON.parse(JSON.stringify(rightAns));
        var randomAns = [];
        for (var i = 0, len = cloneAns.length; i < len; i++) {
            var j = Math.floor(Math.random() * cloneAns.length);
            // 打乱顺序
            randomAns[i] = cloneAns[j];
            cloneAns.splice(j, 1);
        }
        // 随机空白
        var blank_index = Math.floor(Math.random() * 15);
        // 文件碎片
        var frag = document.createDocumentFragment();
        for (var i = 0; i < 16; i++) {
            var piece = document.createElement("div");
            piece.className = (i == blank_index ? "blank" : "piece");
            piece.id = "piece" + i;
            piece.style.left = randomAns[i].left;
            piece.style.top = randomAns[i].top;
            frag.appendChild(piece)
        }
        // 写入文件碎片
        puzzle.appendChild(frag);
    }

    // 检查是否获胜
    function puzzleWin() {
        for (var i = 0; i < 16; i++) {
            var piece = document.getElementById("piece" + i);
            if (piece.style.left != rightAns[i].left) return false;
            if (piece.style.top != rightAns[i].top) return false;
        }
        return true;
    }
    // 展示获胜
    function showWin() {
        if (puzzleWin()) {
            $(win).css("opacity", "1");
        };
    }
    // resert按钮
    $("#reset").click(function () {
        location.reload();
    }
    );
    // 检查是否可以移动
    $("div.piece").click(function () {
        var blank = {};
        var piece = {};
        blank.top = parseInt($("div.blank").css("top"));
        blank.left = parseInt($("div.blank").css("left"));
        piece.top = parseInt($(this).css("top"));
        piece.left = parseInt($(this).css("left"));
        // 当边界相接处有空白时候
        if (Math.abs(blank.top - piece.top) +
            Math.abs(blank.left - piece.left) == 100) {
            // 交换空白和图片的位置
            // 使用了jQuery
            $("div.blank").animate({ left: '-=' + (blank.left - piece.left) + 'px' }, "fast");
            $("div.blank").animate({ top: '-=' + (blank.top - piece.top) + 'px' }, "fast");
            $(this).animate({ left: '+=' + (blank.left - piece.left) + 'px' }, "fast");
            $(this).animate({ top: '+=' + (blank.top - piece.top) + 'px' }, "fast");
            window.setTimeout(showWin, 1000);
        }
    });
}