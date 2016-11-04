(function () {
    var moleGame = function () {
        var notGame, timer, time, score; //不再游戏, 计时器
         // 初始化函数
        var moleInitial = function () {
            var frag = document.createDocumentFragment();
            for (var i = 0; i < 6 * 10; i++)
                frag.appendChild(document.createElement("img"));
            $("#game").append(frag);
            $("img").addClass("hole");
            $("#start_or_stop").bind("click", startOrStop);
        }
        // 改变游戏状态
        var startOrStop = function () {
            if (notGame) {
                endGame();
                notGame = false;
            } else {
                startGame();
                notGame = true;
            }
        }
        //开始游戏
        var startGame = function () {
            time = 30, score = 0;
            // 每一秒更新显示
            var oneSecond = function () {
                $("#time").find("input")[0].value = --time;
                if (time < 0) {
                    alert("Game Over, Your scores is " + score);
                    endGame();
                }
                    
            }
            // 点击函数
            var clickHole = function () {
                if (notGame) {
                    if ($(this).hasClass("mole")) {
                        score++;
                        $(this).removeClass("mole").addClass("hole");
                        randomMole();
                    }
                    $("#score").find("input")[0].value = score;
                    console.log(score);
                    console.log($("#score").find("input")[0].value);
                }
            }
            // 随机改变一个
            var randomMole = function () {
                $(".hole")[Math.floor(Math.random() * 60)].className = "mole";
            }
            //开始游戏后的属性设置
            $("#state")[0].value = "Playing";
            $("img").bind("click", clickHole);
            $("#time").find("input")[0].value = time;
            $("#score").find("input")[0].value = score;
            timer = setInterval(oneSecond, 1000)
            randomMole();
        }
        // 结束游戏
        var endGame = function () {
            clearInterval(timer);
            $("img").removeClass("mole").addClass("hole");
            $("#state")[0].value = "Game Over";
            $("#time").find("input")[0].value = 0;
        }
        // 初始化
        moleInitial();
    }
    // 构造一个mole对象
    window.onload = function () {
        var Mole = new moleGame();
    }
})();
