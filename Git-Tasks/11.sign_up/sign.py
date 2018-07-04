import urllib
import urllib2
from sys import argv


class Sign(object):
    """A auto sign up class"""

    def __init__(self):
        """Initial"""
        self.url_file = None
        self.config = {
            "URL": "http://owtotwo.top:8080/",
            "register": "register"
        }
        self.user_info = {
            "username": "",
            "password": ""
        }

    def set_user_info(self, user_name, user_password):
        """Set the infomation"""
        self.user_info["username"] = user_name
        self.user_info["password"] = user_password
        self.user_info["confirm"] = user_password

    def sign_up(self):
        """Try to sign"""
        url_data = urllib.urlencode(self.user_info) if self.user_info[
            "username"] and self.user_info["password"] else None
        print url_data
        url = self.config["URL"] + self.config["register"] if self.user_info[
            "username"] and self.user_info["password"] else self.config["URL"]
        req = urllib2.Request(url, data=url_data)
        self.url_file = urllib2.urlopen(req)

    def show_data(self):
        """show """
        print self.url_file.read()

    def set_config(self, title, data):
        """set the self.config"""
        self.config[title] = data


if __name__ == "__main__":
    USER_NAME, USER_PASSWORD = "", ""
    if len(argv) == 5 and argv[1] == "-u" and argv[3] == '-p':
        USER_NAME, USER_PASSWORD = argv[2], argv[4]
    if len(argv) == 5 and argv[1] == "-p" and argv[3] == "-u":
        USER_NAME, USER_PASSWORD = argv[4], argv[2]

    SIGN = Sign()
    if USER_NAME and USER_PASSWORD:
        SIGN.set_user_info(USER_NAME, USER_PASSWORD)
    SIGN.sign_up()
    # SIGN.show_data()
