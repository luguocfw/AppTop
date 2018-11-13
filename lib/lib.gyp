#
#
# author: ChenFawang
# lib.gyp
# 2018-11-12
# mail: cfwang_9984@163.com
#
{
  'includes': [
    './../common.gypi',
  ],
  'targets':[
    {
      'target_name': 'libtt',
      'type': 'static_library',
      'sources':[
        'tt_utils.cc',
        'tt_utils.h',
        'tt_global.cc',
        'tt_global.h',
        'tt_hander.cc',
        'tt_hander.h',
      ],
      'dependencies': [
        '<(PRO_ROOT)/base/base.gyp:libttbase',
      ], # dependencies
      'include_dirs': [
        '<(PRO_ROOT)/lib',
      ],
      'direct_dependent_settings': {
        'include_dirs': [
          '<(PRO_ROOT)/lib',
        ],
      },
    },
  ], # targets
}