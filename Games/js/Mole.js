// 当加载完成
window.onload = function () {
    var time;
    var timer;
    var score; // 记录得分
    var beginGame = false; // 开始游戏
    var choice;

    var game = document.getElementById('game');
    // 修改game本体，增加子元素
    for (var i = 0; i < 6; i++) {
        for (var j = 0; j < 10; j++) {
            var box = document.createElement("hole");
            box.className = "hole";
            // 子元素绑定click
            box.addEventListener("click", click);
            game.appendChild(box);
        }
    }

    // 保存需要更新的元素节点，方便后续
    var boxes = document.getElementById('game').getElementsByTagName('hole');
    var scoreInput = document.getElementById('score').getElementsByTagName('input');
    var timeInput = document.getElementById('time').getElementsByTagName('input');
    var state = document.getElementById('state');

    var startStop = document.getElementById('star_or_stop');
    startStop.addEventListener("click", startOrStop);

    // 随机一个hole改变属性为mole
    function randomMole() {
        boxes[Math.floor(Math.random() * 60)].className = "mole";
    }

    // 开始或结束时，改变当前游戏状态，更新对应状态
    function startOrStop() {
        if (beginGame) {
            beginGame = false;
            for (var i = 0; i < 60; i++) {
                boxes[i].className = "hole";
            }
            state.value = "Game Over"
            clearInterval(timer);
        }
        // 开始游戏，改变当前游戏状态，更新对应状态
        else {
            randomMole();
            beginGame = true;
            time = 30; // 初始化时间
            score = 0; // 初始化得分
            scoreInput[0].value = score;
            timeInput[0].value = time;
            // 开始记录时间
            timer = setInterval(Timer, 1000);
            state.value = "Playing";
        }
    }


    function Timer() {
        // 时间减少并跟新展示
        time--;
        timeInput[0].value = time;
        // 时间结束，弹出得分
        if (time <= 0) {
            clearInterval(timer);
            alert("Game Over.\nYour score is : " + score);
            boxes[choice].className = "hole";
            beginGame = false;
            state.value = "Game Over";
            return;
        }

    }

    // 点击函数
    function click() {
        // 开始游戏后
        if (beginGame) {
            if (this.className === "mole") {
                // 点击正确
                score++;
                this.className = "hole";
                randomMole();
            } else if (this.className === "hole") {
                // 点击错误
                score--;
            }
            // 更新得分
            scoreInput[0].value = score;
        }
    }
}