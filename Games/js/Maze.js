window.onload = function(){
    var gameTime = false;
    var isCheat = true;

    var ans = document.getElementById("ans");

	var walls = document.getElementsByClassName('wall');
    for (var i = 0; i < walls.length; i++) {
        walls[i].addEventListener("mouseover", lose);
    }

    var S = document.getElementById("S");
    S.addEventListener("mouseover", startGame);

    var E = document.getElementById("E");
    E.addEventListener("mouseover", judgeGame);

    var judge = document.getElementById("judge");
    judge.addEventListener("mouseover", cheatFlag);

    function lose(){
    	if (gameTime) {
            this.style.backgroundColor = "red";
            ans.style.opacity = "1";
            ans.innerHTML = "You Lose";
            gameTime = false
        }
    }


    function startGame(){
        gameTime = true;
        isCheat = true;
        for (var i = 0; i < walls.length; i++) {
            walls[i].style.backgroundColor = "black";
            ans.style.opacity = "0";
         }

    }

    function judgeGame(){
        if (gameTime && !isCheat) {
            ans.style.opacity = "1";
            ans.innerHTML = "You Win";
            gameTime =false;
        } else if (gameTime && isCheat) {
            ans.style.opacity = "1";
            ans.innerHTML = "Don't cheat, you should start form the 'S' and move to the 'E' inside the maze!";
            gameTime =false;
        }
    }

    function cheatFlag(){
            isCheat = false;
    }
}