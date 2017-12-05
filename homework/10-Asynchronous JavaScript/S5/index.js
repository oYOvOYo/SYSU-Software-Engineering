$(function() {

    "use strict";

    var isButtonHover = false;
    var isControlRingClick = false;

    const indexConfig = {
        blue: "#303F9F",
        gray: "#7E7E7E"
    }


    // 模拟自动执行从A~E点击按钮，获取随机数，然后点击大气泡求和的过程
    var orderClick = function() {
        var index = shuffle([0, 1, 2, 3, 4]);
        addSequence(index);

        var liArray = $("#control-ring > li");
        liArray[index[1]].onclick = clickControlRing();
        liArray[index[0]].onclick = clickControlRing(0, liArray[index[1]].click);

        liArray[index[0]].click();

        // clickControlRing(0, function() {}).bind(liArray[index[0]]);
        // var timer = setInterval(function() {
        //     if ($("#info-bar")[0].canBeClick) {
        //         setTimeout($("#info-bar")[0].click(), 500);
        //         clearInterval(timer);
        //     }
        //     for (var i = 1; i < liArray.length; i++) {
        //         liArray[index[i]].click();
        //     }
        // }, 1200);


    }

    var addSequence = function(index) {
        var sequence = document.createElement("span");
        sequence.className = "sequence";
        // 计算A~E随机数的和，显示在大气泡内
        for (var i = 0; i < index.length; i++) {
            sequence.innerHTML += String.fromCharCode('A'.charCodeAt(0) + index[i]);
        }
        $("#info-bar")[0].append(sequence);
    }

    var shuffle = function(array) {
        var currentIndex = array.length, temporaryValue, randomIndex;

        // While there remain elements to shuffle...
        while (0 !== currentIndex) {

            // Pick a remaining element...
            randomIndex = Math.floor(Math.random() * currentIndex);
            currentIndex -= 1;

            // And swap it with the current element.
            temporaryValue = array[currentIndex];
            array[currentIndex] = array[randomIndex];
            array[randomIndex] = temporaryValue;
        }

        return array;
    }

    var deleteOldContent = function() {
        // empty the big buttum
        $("#info-bar").empty();
        // make all small buttum background none
        $("#control-ring > li").each(function() {
            $(this).css("background", "none");
        })
        // remove the message's unread
        $(".unread").remove();
    }

    var addNewContent = function() {
        isControlRingClick = false
        var liArray = $("#control-ring > li");
        for (var i = 0; i < liArray.length; i++) {
            liArray[i].innerHTML = String.fromCharCode('A'.charCodeAt(0) + i);
            liArray[i].haveBeenClicked = false;
        }
        liArray.css("background-color", indexConfig.blue)
    }

    var addElementEvent = function() {
        // 按钮覆盖事件
        $("#button").hover(buttonHoverIn, buttonHoverOut);

        // 气泡点击事件
        $("#info-bar")[0].onclick = clickInfo;
        // 点击@+按钮，将执行这段机器人程序
        $(".apb")[0].onclick = orderClick;
    }

    var buttonHoverIn = function() {
        isButtonHover = true;
        // 鼠标再次指向@+，可以开始新一轮的计算操做
        addNewContent();
    }

    var buttonHoverOut = function() {
        isButtonHover = false;
        // 任何时候，鼠标离开@+区域，将重置整个计算器，清除所有A~E按钮的随机数和大气泡内的和
        deleteOldContent();
    }

    var aHandler = function (err, ans, callback) {
      addNumberElement;

    }

    var clickControlRing = function(ans, callback) {
        if (isButtonHover && !isControlRingClick && !this.haveBeenClicked) {
            addNumberElement.call(this);
            getNumber.call(this, [ans, callback]);
        }
    }

    // 在得到结果前
    var addNumberElement = function() {
        var numberElement = document.createElement("span");
        numberElement.className = "unread";
        // 红色圆圈内显示 。。。，表示正在等待随机数
        numberElement.innerHTML = "...";
        $(this).append(numberElement);
        // 灭活（disable）其它按钮，变为灰色，用户不能够点击（点击没有响应，也不会发送新的请求到服务器）
        disableOthers.call(this);
    }

    var getNumber = function(ans, callback) {
        // 得到服务器发回的随机数后，
        $.get('/api/', num => {
            if ($(this).find(".unread")[0]) {
                // 显示在当前按钮右上角红色圆圈内
                $(this).find(".unread")[0].innerHTML = num;
                // 灭活当前按钮，变为灰色，用户不能够点击
                this.haveBeenClicked = true;
                $(this).css("background-color", indexConfig.gray)
                // 激活（enable）其余按钮，呈现为蓝色，用户可以点击，从服务器获取随机数
                enableOthers.call(this);
                checkInfoCanClick();
                if (err) {
                  handelErr(err);
                } else {
                  callback(ans + parseInt(num));
                }
            }
        })
    }

    // 灭活（disable）其它按钮，变为灰色，用户不能够点击（点击没有响应，也不会发送新的请求到服务器）
    var disableOthers = function() {
        isControlRingClick = true;
        $("#control-ring > li").each(function() {
            if (!$(this)[0].haveBeenClicked) {
                $(this).css("background-color", indexConfig.gray);
            }
        })
    }

    // 激活（enable）其余按钮，呈现为蓝色，用户可以点击，从服务器获取随机数
    var enableOthers = function() {
        isControlRingClick = false;
        $("#control-ring > li").each(function() {
            if (!$(this)[0].haveBeenClicked) {
                $(this).css("background-color", indexConfig.blue);
            }
        })
    }

    // 当A~E按钮全部获得了自己的随机数时，激活大气泡
    var checkInfoCanClick = function() {
        var allHaveNum = true;
        $("#control-ring > li").each(function() {
            if (!$(this)[0].haveBeenClicked) {
                allHaveNum = false;
            }
        })
        if (allHaveNum) {
            $("#info-bar")[0].canBeClick = true;
            $("#info-bar").css("background", indexConfig.blue);
        }
    }

    var clickInfo = function() {
        if (this.canBeClick) {
            var answer = document.createElement("span");
            answer.className = "answer";
            // 计算A~E随机数的和，显示在大气泡内
            answer.innerHTML = getAnswer();
            $(this).append(answer);
            // 灭活大气泡
            $("#info-bar").css("background", indexConfig.gray);
            this.canBeClick = false;
        }
    }

    // 计算A~E随机数的和
    var getAnswer = function() {
        var answer = 0;
        $("#control-ring > li").each(function() {
            answer += parseInt($(this).find(".unread")[0].innerHTML);
        })
        return answer;
    }

    var mainFunc = function() {
        deleteOldContent();
        addElementEvent();
    }

    mainFunc();
})

// 至此 S2部分完成