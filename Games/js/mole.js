window.onload = function(){

	var time;
	var timer;
	var score;
	var gameTime = false;
	var choice;

	var game = document.getElementById('game');
    for (var i = 0; i < 6; i++) {
        for (var j = 0; j < 10; j++) {
            var box = document.createElement("hole");
            box.className = "hole";
            box.addEventListener("click", hit);
            game.appendChild(box);
        }
    }	

    var boxes = document.getElementById('game').getElementsByTagName('hole');
    var scoreInput = document.getElementById('score').getElementsByTagName('input');
    var timeInput = document.getElementById('time').getElementsByTagName('input');
    var stage = document.getElementById('stage');

    var startStop = document.getElementById('start_stop');
    startStop.addEventListener("click", startOrStop);

    function randomMole() {
        choice = Math.floor(Math.random() * 60);
        boxes[choice].className = "mole";
    }

    function startOrStop(){
    	if (gameTime) {
    		gameTime = false;
    		boxes[choice].className = "hole";
    		stage.value = "Game Over";
    		clearInterval(timer);
    	}
    	else {
    		randomMole();
    		gameTime = true;
    		time = 30;
            score = 0;
            scoreInput[0].value = score;
            timeInput[0].value = time;
            timer = setInterval(Timer, 1000);
            stage.value = "Playing";
    	}
    }

    function Timer(){
    	time--;
        timeInput[0].value = time;
        if (time <= 0) {
            clearInterval(timer);
            alert("Game Over.\nYour score is : " + score);
            boxes[choice].className = "hole";
            gameTime = false;
            stage.value = "Game Over";
            return;
        }
        
    }

    function hit() {
    	if (gameTime) {
    		if (this.className === "mole") {
    			score++;
    			this.className = "hole";
    			randomMole();
    		} else if (this.className === "hole") {
    			score--;
    		}
    		  	scoreInput[0].value = score;
    	}
    }
}