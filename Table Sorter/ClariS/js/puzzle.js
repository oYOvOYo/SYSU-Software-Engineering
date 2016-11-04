(function () {

    var createPuzzle = function () {
        var winGame = function () {
            for (var i = 0; i < 16; i++) {
                if (imgList[i].style.backgroundPositionX != - i % 4 * 100 + "px" ||
                    imgList[i].style.backgroundPositionY != - Math.floor(i / 4) * 100 + "px")
                    return;
            }
            if (haveInitialed)
                document.getElementById("win").style.opacity = "1";
        }

        var canMove = function () {
            var position = this.style.backgroundPosition;
            var moveFrom = 0, moveTo = 0; 
            for (var i = 0; i < 16; i ++) {
                if (imgList[i].style.backgroundImage == "none")
                    moveTo = i;
                if (imgList[i].style.backgroundPosition == position)
                    moveFrom = i;
            }
            if (Math.abs(moveFrom - moveTo) == 1 || Math.floor(moveFrom - moveTo) % 4 == 0) {
                imgList[moveFrom].style.backgroundPosition = imgList[moveTo].style.backgroundPosition;
                imgList[moveTo].style.backgroundPosition = position;
                imgList[moveTo].style.backgroundImage = imgList[moveFrom].style.backgroundImage;
                imgList[moveFrom].style.backgroundImage = "none";
            }
            winGame();
        }

        var initialGame = function () {
            for (var i = 0; i < 1000; i++) {
                canMove.call(imgList[Math.floor(Math.random() * 15)]);
            }
            document.getElementById("win").style.opacity = "0";
            haveInitialed = true;
        }

        var createPiece = function (i) {
            var piece = document.createElement("img");
            piece.className = "piece";
            piece.onclick = canMove;
            piece.style.backgroundPositionX = - i % 4 * 100 + "px";
            piece.style.backgroundPositionY = - Math.floor(i / 4) * 100 + "px";
            return piece;
        }

        var puzzle = document.getElementById("puzzle");
        var frag = document.createDocumentFragment();
        var haveInitialed;
        for (var i = 0; i < 16; i++) frag.appendChild(createPiece(i))
        puzzle.appendChild(frag);
        var imgList = document.getElementsByClassName("piece");
        imgList[15].style.backgroundImage = "none";
        document.getElementById("reset").onclick = initialGame;
    }

    window.onload = function () {
        var puzzle_obj = new createPuzzle();
    }
})();