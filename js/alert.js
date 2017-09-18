(function (win, doc, ALERT) {
  'use strict';
  win[ALERT] = function bootstrap_alert() { 
    this.alert = (type, strong, message) => {
      $('#alert_box').append('\
      <div class="alert alert-'+ type + ' alert-dismissible fade show" role="alert">\
        <button type="button" class="close" data-dismiss="alert" aria-label="Close">\
          <span aria-hidden="true">&times;</span></button>\
        <strong>'+ strong + '</strong>' + message + '</div>');
    }

    // add many types
    var alert_types = ["primary", "secondary", "success", "danger", 
                       "warning", "info", "light", "dark"];

    alert_types.forEach(function(type) {
      this[type] = (strong, message) => {
        this.alert(type, strong, message);
      };
    }, this);
  }
})(window, document, 'Alert');