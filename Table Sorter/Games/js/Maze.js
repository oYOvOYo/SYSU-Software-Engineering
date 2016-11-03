// 当全部加载好以后
window.onload = function () {
    // 记录是否开始游戏和是否作弊
    var playedGame = false;
    var isCheated = false; 
    // 绑定结果节点，方便后续更改
    var ans = document.getElementById("ans");
    // 对wall类中所有成员绑定鼠标覆盖会触发的结束游戏函数
    var walls = document.getElementsByClassName('wall');
    for (var i = 0; i < walls.length; i++) {
        walls[i].addEventListener("mouseover", loseGame);
    }
    // 当鼠标覆盖S，会开始游戏
    var S = document.getElementById("S");
    S.addEventListener("mouseover", startGame);
    // 当鼠标覆盖E，会结束游戏
    var E = document.getElementById("E");
    E.addEventListener("mouseover", endGame);
    // 设置的特殊判断透明砖检查是否作弊
    var judge = document.getElementById("judge");
    judge.addEventListener("mouseover", haveCheated);
    // 输掉游戏
    function loseGame() {
        if (playedGame) {
            // 改变颜色更新状态
            this.style.backgroundColor = "red";
            ans.innerHTML = "You lose";
            ans.style.opacity = "1";
            playedGame = false
        }
    }
    // 开始游戏
    function startGame() {
        // 恢复初值
        playedGame = true;
        isCheated = false;
        for (var i = 0; i < walls.length; i++) {
            walls[i].style.backgroundColor = "black";
            ans.style.opacity = "0";
        }

    }

    function endGame() {
        // 结束游戏检查是否作弊
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
    // 右边过来就是作弊w
    function haveCheated() {
        isCheated = true;
    }
}