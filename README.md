stikkit
=======

command line tool to upload things to stikked

Building on linux
=================

Checkout this repository
```
cd stikkit
make
```

NOTE: you need to have libcurl-dev installed in your system

Usage
=====

./stikkit -b <url>
# now type text and hit ctrl+d to exit

cat <file> | stikkit -b <url>

<url> is an url to stikked server for example, if your server is http://something.blah/stikked and your api is http://something.blah/stikked/api then use http://something.blah/stikked as parameter to -b

The url parameter can be stored to configuration file (stikkit will ask you in case there is none in config file)
