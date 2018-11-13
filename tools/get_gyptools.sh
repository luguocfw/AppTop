#! /bin/bash

gyp_url="https://github.com/luguocfw/GYP-Tools"

if [ ! -d GYP-Tools ]
then
  git clone $gyp_url
fi
