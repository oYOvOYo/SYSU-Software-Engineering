// $(function () {



//     console.log($.get('/api/', data => {
//         console.log(data);
//     }))

//     var deleteOldContent = function () {
//         // empty the big buttum
//         $(".info").empty();
//         // make all small buttum background black
//         $("#control-ring > li").each(
//             function () {
//                 $(this).css("background", "#7E7E7E");
//             }
//         )
//         // remove the message's unread
//         $(".unread").remove();
//     }

//     var addNewContent = function () {
//         $(".message")[0].innerText = 'C';
//     }

//     var addElementEvent = function () {
//         $(".message")[0].click(function () {
//             alert($(this));
//         });
//     }

//     var mainFunc = function () {
//         deleteOldContent();
//         addNewContent();
//         addElementEvent();
//     }

//     mainFunc();
// })