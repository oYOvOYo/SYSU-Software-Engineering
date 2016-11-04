(function () {
    var createPuzzle = function () {
        var puzzle = document.getElementById("puzzle");
        var blank_index = Math.floor(Math.random() * 15);
        // 文件碎片
        var frag = document.createDocumentFragment();
        for (var i = 0; i < 15; i++) {
            var piece = document.createElement("img");
            piece.className = "piece";
            frag.appendChild(piece)
        }
        // 写入文件碎片
        puzzle.appendChild(frag);
    }

    window.onload = function () {
        var puzzle_obj = new createPuzzle();
}
})();

