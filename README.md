stikkit
=======

command line tool to upload paste to stikked based pastebins

Features
========

* Super easy to use
* Remembers stikked URL
* Automatically url encodes all data
* Automatically figure out author name if not provided explicitly

Building on linux
=================

Checkout this repository
```
cd stikkit
./configure
make
make install
```

NOTE: you need to have libcurl-dev installed in your system

Usage
=====

```
stikkit -b url
# now type text and hit ctrl+d to exit
```

cat file | stikkit -b url
echo "Hello world" | stikkit

url is an url to stikked server for example, if your server is http://something.blah/stikked and your api is http://something.blah/stikked/api then use http://something.blah/stikked as parameter to -b

The url parameter can be stored to configuration file (stikkit will ask you in case there is none in config file)
