zentwm
======

A wayland tiling window manager based on the swc library written in C++

It is still in heavy development, so please report bugs if you find any! :)

#### Installation

In it's current state, it is not possible to compile swc with C++, because there is a variable named class.
there is a patch in this folder named class_to_appid.patch which you will have to apply to swc to make it work
To automate the process, i have added the swcinstall.sh script in the misc folder which downloads, checks out the compatible swc commit and patches it.
After that is run, simply cd into swc_patched and make install

#### Usage

Simply run "swc-launch $PATH_TO_ZENTWM"


#### General ToDo

- Decide whether to use camelcase or _
- Move code from Screen to Workspace
- Fix dirty hideAll workspace function
- Change window.link to a C++ alternative, and fix all layout&hideAll functions to use the new one
