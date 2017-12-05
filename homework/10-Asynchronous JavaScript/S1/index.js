$(function () {

  "use strict";

  var isButtonHover = false;
  var isControlRingClick = false;

  const indexConfig = {
    blue: "#303F9F",
    gray: "#7E7E7E"
  }

  var deleteOldContent = function () {
    // empty the big buttum
    $("#info-bar").empty();
    // make all small buttum background none
    $("#control-ring > li").each(function () {
      $(this).css("background", "none");
    })
    // remove the message's unread
    $(".unread").remove();
  }

  var addNewContent = function () {
    isControlRingClick = false
    var liArray = $("#control-ring > li");
    for (var i = 0; i < liArray.length; i++) {
      liArray[i].innerHTML = String.fromCharCode('A'.charCodeAt(0) + i);
      liArray[i].haveBeenClicked = false;
    }
    liArray.css("background-color", indexConfig.blue)
  }

  var addElementEvent = function () {
    // 按钮覆盖事件
    $("#button").hover(buttonHoverIn, buttonHoverOut);
    // 环形按钮点击事件
    $("#control-ring > li").each(function () {
      $(this)[0].onclick = clickControlRing;
    })
    // 气泡点击事件
    $("#info-bar")[0].onclick = clickInfo;
  }

  var buttonHoverIn = function () {
    isButtonHover = true;
    // 鼠标再次指向@+，可以开始新一轮的计算操做
    addNewContent();
  }

  var buttonHoverOut = function () {
    isButtonHover = false;
    // 任何时候，鼠标离开@+区域，将重置整个计算器，清除所有A~E按钮的随机数和大气泡内的和
    deleteOldContent();
  }

  var clickControlRing = function () {
    if (isButtonHover && !isControlRingClick && !this.haveBeenClicked) {
      addNumberElement.call(this);
      getNumber.call(this);
    }
  }

  // 在得到结果前
  var addNumberElement = function () {
    var numberElement = document.createElement("span");
    numberElement.className = "unread";
    // 红色圆圈内显示 。。。，表示正在等待随机数
    numberElement.innerHTML = "...";
    $(this).append(numberElement);
    // 灭活（disable）其它按钮，变为灰色，用户不能够点击（点击没有响应，也不会发送新的请求到服务器）
    disableOthers.call(this);
  }

  var getNumber = function () {
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
      }
    })
  }

  // 灭活（disable）其它按钮，变为灰色，用户不能够点击（点击没有响应，也不会发送新的请求到服务器）
  var disableOthers = function () {
    isControlRingClick = true;
    $("#control-ring > li").each(function () {
      if (!$(this)[0].haveBeenClicked) {
        $(this).css("background-color", indexConfig.gray);
      }
    })
  }

  // 激活（enable）其余按钮，呈现为蓝色，用户可以点击，从服务器获取随机数
  var enableOthers = function () {
    isControlRingClick = false;
    $("#control-ring > li").each(function () {
      if (!$(this)[0].haveBeenClicked) {
        $(this).css("background-color", indexConfig.blue);
      }
    })
  }

  // 当A~E按钮全部获得了自己的随机数时，激活大气泡
  var checkInfoCanClick = function () {
    var allHaveNum = true;
    $("#control-ring > li").each(function () {
      if (!$(this)[0].haveBeenClicked) {
        allHaveNum = false;
      }
    })
    if (allHaveNum) {
      $("#info-bar")[0].canBeClick = true;
      $("#info-bar").css("background", indexConfig.blue);
    }
  }

  var clickInfo = function () {
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
  var getAnswer = function () {
    var answer = 0;
    $("#control-ring > li").each(function () {
      answer += parseInt($(this).find(".unread")[0].innerHTML);
    })
    return answer;
  }

  var mainFunc = function () {
    deleteOldContent();
    addElementEvent();
  }

  mainFunc();
})

// 至此 S1部分完成