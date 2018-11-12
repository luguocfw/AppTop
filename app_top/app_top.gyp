#
#
# author: ChenFawang
# app_top.gyp
# 2018-11-12
# mail: cfwang_9984@163.com
#
{
  'includes': [
    './../common.gypi',
  ],
  'targets':[
    {
      'target_name': 'apptop',
      'type': 'executable',
      'sources':[
        'main.c',
      ],
      'include_dirs': [
        '<(PRO_ROOT)/include',
      ],
      'dependencies': [
        '<(PRO_ROOT)/src/src.gyp:libat',
      ], # dependencies
    },
  ], # targets
}