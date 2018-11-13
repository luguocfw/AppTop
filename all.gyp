#
#
# author: ChenFawang
# all.gyp
# 2018-11-12
# mail: cfwang_9984@163.com
#
{
  'includes': [
    'common.gypi',
  ],
  'targets':[
    {
      'target_name': 'pro_all',
      'type': 'none',
      'dependencies': [
        '<(PRO_ROOT)/app/app.gyp:tasktop',
        '<(PRO_ROOT)/lib/lib.gyp:libtt',
        '<(PRO_ROOT)/base/base.gyp:libttbase',
      ], # dependencies
    },
  ], # targets
}