$(function () {
    var checkInput = () => {
        const Titles = [
            ["#name", /^[a-zA-Z][\w_]{5,17}$/],
            ["#ID", /^[1-9][\d]{7}$/],
            ["#phone", /^[1-9][\d]{10}$/],
            ["#email", /^[a-zA-Z_\-]+@(([a-zA-Z_\-])+\.)+[a-zA-Z]{2,4}$/]
        ];
        for (var i = 0; i < Titles.length; i++) {
            var title = Titles[i];
            if ($(title[0]).val() != "" && !title[1].test($(title[0]).val())) {
                $(title[0]).css("background-color", "red");
            } else {
                $(title[0]).css("background-color", "none");
            }
        }
    }
    setInterval(checkInput, 1000);
}); 