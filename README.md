stupidunixtricks
================

This repository contains various little things that I've hacked up either for fun, or just the pure blooded mindedness of it.

read.c
======

Ever find yourself wishing you could use 'cat' on a directory to list the contents of that directory? Well now you can!

read.c can be shimed in between 'cat' and Glibc using LD_PRELOAD, and makes read() calls on a file descriptor for a directory return a list of the directory contents.

Build with:

    $ gcc read.c -shared -fPIC -o read.so 

then just add read.so to LD_PRELOAD:

    $ export LD_PRELOAD=$(pwd)/read.so

now you can use 'cat' on directories to your hearts content:

    $ cat /usr/local/bin/
    git-flow git-flow-init git-flow-release git-flow-feature git-flow-hotfix gitflow-shFlags git-flow-version gitflow-common git-flo

WARNING: It doesn't actually work very well. May cause nasal deamons.
