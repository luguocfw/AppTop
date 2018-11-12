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
        '<(PRO_ROOT)/app_top/app_top.gyp:apptop',
        '<(PRO_ROOT)/src/src.gyp:libat',
      ], # dependencies
    },
  ], # targets
}