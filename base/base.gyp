#
#
# author: ChenFawang
# base.gyp
# 2018-11-13
# mail: cfwang_9984@163.com
#
{
  'includes': [
    './../common.gypi',
  ],
  'targets':[
    {
      'target_name': 'libttbase',
      'type': 'static_library',
      'sources':[
        'tt_log.cc',
        'tt_log.h',
      ],
      'include_dirs': [
        '<(PRO_ROOT)/base',
      ],
      'direct_dependent_settings': {
        'include_dirs': [
          '<(PRO_ROOT)/base',
        ],
      },
    },
  ], # targets
}