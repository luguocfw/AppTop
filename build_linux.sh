#! /bin/bash





ROOT=`pwd`
CROSS_COMPILE=
GYP_TOOLS=${ROOT}/tools/GYP-Tools
ROOT_GYP=${ROOT}/all.gyp
export CC=${CROSS_COMPILE}gcc
export CXX=${CROSS_COMPILE}g++
export AR=${CROSS_COMPILE}ar
export STRIP=${CROSS_COMPILE}strip

function env_base()
{
  export GYP_DEFINES="PRO_ROOT=${ROOT} "
}

function build()
{
  cd $ROOT/tools
  ./get_gyptools.sh
  cd $ROOT
  ${GYP_TOOLS}/gyp --depth=. -f make ${ROOT_GYP}
  make V=1 
}

function build_release()
{
  env_base
  export GYP_DEFINES=$GYP_DEFINES"build_type=release "
  build
}

function build_debug()
{
  env_base
  export GYP_DEFINES=$GYP_DEFINES"build_type=debug "
  build
}
