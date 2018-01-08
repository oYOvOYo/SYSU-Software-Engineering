$(document).ready(function () {
  "use strict";

  const fs = require('fs');
  const exec = require('child_process').exec;
  const color_table = {
    '0': '#eee',
    '1': '#c6e48b',
    '2': '#7bc96f',
    '3': '#239a3b',
    '4': '#196127'
  }

  var grid_value = new Array(365);

  main();

  function main() {
    console.log("hello world!");

    initialTable();
    $("rect").attr('fill', color_table[0]);
    $("#folder_chooser").on("change", choose_folder);
    $("#choose").on("click", click_folder_chooser);
    $("#start").on("click", start_draw);
  }

  function grid_click(event) {
    grid_value[this.id] = (grid_value[this.id] + 1) % 5;
    $(this).attr('fill',  color_table[grid_value[this.id]]);
  }

  function click_folder_chooser(event) {
    $("#folder_chooser").click();
  }

  function choose_folder(event) {
    console.log("choose: ", this.files[0].path);
    var click_innerhtml = $("#choose").html() + " now is " + this.files[0].path;
    $("#choose").html(click_innerhtml)
    $("#start").prop("disabled", false);
  }

  function start_draw(event) {
    var isWin = /^win/.test(process.platform);
    var path = $("#folder_chooser")[0].files[0].path;
    var scripts = "cd " + path + ";\n";
    var today = new Date().getDay();

    for (var i = 0; i < grid_value.length; i++) {
      while (grid_value[i]) {
        scripts += each_day_scripts(364 - i + today, path).repeat(3);
        grid_value[i]--;
      }
    }

    if (isWin) {
      fs.writeFile("run.PS1", scripts, function (err) {
        if (err) {
          return console.log(err);
        }
        run_scripts("powershell.exe -File run.PS1")
      });
    } else {
      fs.writeFile("run.sh", scripts, function (err) {
        if (err) {
          return console.log(err);
        }
        run_scripts("bash run.sh")
      });
    }
  }

  function run_scripts(scripts) {
    const child = exec(scripts,
      (error, stdout, stderr) => {
        // console.log(`stdout: ${stdout}`);
        // console.log(`stderr: ${stderr}`);
        if (error !== null) {
          console.log(`exec error: ${error}`);
        }
      });
  }

  function each_day_scripts(before_date, path) {
    var scripts = `
echo "github drawer" > ${path}/github_drawer;
git add -A;
git commit --date "${before_date} day ago" -m "add github drawer";
rm github_drawer;
git add -A;
git commit --date "${before_date} day ago" -m "delete github drawer";
`;
    return scripts;
  }

  function initialTable() {
    var row_size = 7;
    var col_size = 52;

    for (var j = 0; j < col_size; j++) {
      for (var i = 0; i < row_size; i++) {
        var rect = document.createElementNS("http://www.w3.org/2000/svg", 'rect')
        $(rect).attr("width", 10);
        $(rect).attr("height", 10);
        $(rect).attr("x", j * 13);
        $(rect).attr("y", i * 13);
        $(rect).on("click", grid_click);

        var id = j * row_size + i;
        grid_value[id] = 0;
        rect.id = id;

        $("#drawer").append(rect);
      }
    }
  }
});
