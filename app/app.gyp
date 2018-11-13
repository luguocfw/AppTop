#
#
# author: ChenFawang
# app.gyp
# 2018-11-12
# mail: cfwang_9984@163.com
#
{
  'includes': [
    './../common.gypi',
  ],
  'targets':[
    {
      'target_name': 'tasktop',
      'type': 'executable',
      'sources':[
        'main.cc',
      ],
      'dependencies': [
        '<(PRO_ROOT)/lib/lib.gyp:libtt',
        '<(PRO_ROOT)/base/base.gyp:libttbase',
      ], # dependencies
    },
  ], # targets
}