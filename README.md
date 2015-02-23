zentwm
======

A wayland tiling window manager based on the swc library written in C++

This is currently nothing more than a C++ compilable version of the swc example wm, but a fun thing to play around with nontheless!

#### Installation

In it's current state, it is not possible to compile swc with C++, because there is a variable named class.
there is a patch in this folder named class_to_appid.patch which you will have to apply to swc to make it work
To automate the process, i have added the swcinstall.sh script in the misc folder which downloads, checks out the compatible swc commit and patches it.
After that is run, simply cd into swc_patched and make install
