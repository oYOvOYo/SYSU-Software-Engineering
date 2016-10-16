window.onload = function () {
    var playedGame = false;
    var isCheated = false;

    var ans = document.getElementById("ans");

    var walls = document.getElementsByClassName('wall');
    for (var i = 0; i < walls.length; i++) {
        walls[i].addEventListener("mouseover", loseGame);
    }

    var S = document.getElementById("S");
    S.addEventListener("mouseover", startGame);

    var E = document.getElementById("E");
    E.addEventListener("mouseover", endGame);

    var judge = document.getElementById("judge");
    judge.addEventListener("mouseover", haveCheated);

    function loseGame() {
        if (playedGame) {
            this.style.backgroundColor = "red";
            ans.innerHTML = "You lose";
            ans.style.opacity = "1";
            playedGame = false
        }
    }


    function startGame() {
        playedGame = true;
        isCheated = false;
        for (var i = 0; i < walls.length; i++) {
            walls[i].style.backgroundColor = "black";
            ans.style.opacity = "0";
        }

    }

    function endGame() {
        if (playedGame && !isCheated) {
            ans.style.opacity = "1";
            ans.innerHTML = "You Win";
            playedGame = false;
        } else if (playedGame && isCheated) {
            ans.style.opacity = "1";
            ans.innerHTML = "Don't cheat, you should start form the 'S' and move to the 'E' inside the maze!";
            playedGame = false;
        }
    }

    function haveCheated() {
        isCheated = true;
    }
}