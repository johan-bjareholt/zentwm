#!/bin/bash

FOLDER=$PWD/swc_patched

git clone git@github.com:michaelforney/swc.git $FOLDER

cd $FOLDER
# I personally have an issue with the latest commit
# If you don't, you can try the newest one, but i can't guarantee that your computer won't blow up
git checkout a33ff2c
git apply --stat ../class_to_appid.patch
