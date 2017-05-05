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
sudo make install
```

NOTE: you need to have `libcurl-dev` installed in your system

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

Configuration
=====

The default configuration pulls the URL from `/etc/stikkit/url` - however, the better approach is to create your own config directory.

The stikkit software will look for `.stikkit` in your home directory. Within this directory, there are a few key files worth creating.

 - *url* - Contains your base installation URL for stikked
 - *apikey* - If your stikked installation requires an API key, save it in here
 - *expiry* - The default expiry time (in minutes) for a paste, if needed
 - *author* - The default author name if you wish to use one
 - *private* - If you want to mark the paste as private (not visible in recent pastes), create this empty file

Tips
=====

Do you have a server and want to setup default pastebin site for all users in system?

Create `/etc/stikkit/url` which contains the url of default pastebin site. Users will be able to override it, but by default everyone on system will use this
