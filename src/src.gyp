#
#
# author: ChenFawang
# src.gyp
# 2018-11-12
# mail: cfwang_9984@163.com
#
{
  'includes': [
    './../common.gypi',
  ],
  'targets':[
    {
      'target_name': 'libat',
      'type': 'static_library',
      'sources':[
        'at_utils.c',
        'at_global.c',
        'at_hander.c',
      ],
      'include_dirs': [
        '<(PRO_ROOT)/include',
      ],
    },
  ], # targets
}