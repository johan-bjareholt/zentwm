zentwm
======

A wayland tiling window manager based on the swc library written in C++

It is still in heavy development, so please report bugs if you find any! :)

Special thanks to [Michael Forney](https://github.com/michaelforney/) for his awesome work on swc, wld and velox.
When i started writing zentwm i had no idea how wayland or compositors works, and i wouldn't have been able to code this without swc and wld as a base and velox as a reference.

#### Installation

The requirements is the latest git version of [swc](https://github.com/michaelforney/swc).
After that, simply make the project.
There's currently no make install in the Makefile however.

#### Usage

Simply run "swc-launch $PATH_TO_ZENTWM"


#### General ToDo

- Decide whether to use camelcase or _
- Add support for hooks at specific events
- Replacing some pointer arguments to references for stability
- Fully implement WINDOW_FLOATING and WINDOW_STATIC, since STATIC doesn't work properly and FLOATING isn't implemented yet

#### Wont Fix
- Multiscreen (until either nvidia starts supporting wayland or i buy an amd card)

### FAQ

##### How do i change keyboard layout?

You change the keyboard layout with setxkbmap

##### How do i change keybindings?

It's currently only possible by modifying the config.cpp file and recompiling.

I know, a parsed configfile would be nice but it's boring work to code.
