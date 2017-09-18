(function (win, doc, DB) {
  'use strict';
  win[DB] = function bootstrap_alert() {
    var DB_URL = "https://couchdb.jskyzero.top/color-of-mood/"

    this.initialAjax = () => {
      $.ajaxSetup({
        headers: {
          "Authorization": "Basic " + btoa("color-of-mood-player" + ":" + "color-of-mood")
        }, xhrFields: {
          withCredentials: true
        }
      })
    }

    this.test_connection = (errorHandler, successHandler) => {
      $.ajax({
        method: "GET",
        url: DB_URL + "aa",
        error: (jqXHR, textStatus, errorThrown) => {
          console.log(jqXHR.responseText);
          errorHandler();
        }
      }).done(function (meg) {
        // console.log(meg);
        successHandler();
      });
    }
  }
})(window, document, 'CouchDB');