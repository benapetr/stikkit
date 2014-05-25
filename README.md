stikkit
=======

command line tool to upload paste to [stikked](https://github.com/claudehohl/Stikked) based pastebins

Features
========

* Super easy to use
* Remembers stikked URL
* Automatically url encodes all data
* Automatically figure out author name if not provided explicitly

Installing on debian or ubuntu
==============================

Just add ppa:
```
sudo add-apt-repository ppa:benapetr/misc
sudo apt-get update
sudo apt-get install stikkit
```

That's all

Building on linux
=================

Checkout this repository
```
cd stikkit
cmake .
make
make install
```

NOTE: you need to have libcurl-dev installed in your system

Usage
=====

```
stikkit -b url
# now type text and hit ctrl+d to exit
cat file | stikkit -b url
echo "Hello world" | stikkit
```

url is an url to stikked server for example, if your server is http://something.blah/stikked and your api is http://something.blah/stikked/api then use http://something.blah/stikked as parameter to -b

The url parameter can be stored to configuration file (stikkit will ask you in case there is none in config file)

Tips
=====

Do you have a server and want to setup default pastebin site for all users in system?

Create /etc/stikkit/url which contains the url of default pastebin site. Users will be able to override it, but by default everyone on system will use this
