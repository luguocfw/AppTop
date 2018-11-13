#
#
# author: ChenFawang
# common.gypi
# 2018-11-12
# mail: cfwang_9984@163.com
#
{
  'target_defaults': {
    'libraries': [
      '-lpthread',
      '-lrt',
      '-lm',
      '-ldl',
    ],
    'cflags':[
      '-fPIC',
      '-std=c++11',
    ],
    'conditions': [
      ['build_type=="debug"',{
        'defines': ['BUILD_DEBUG'],
        'cflags':[
          '-g',
        ],
      }],
      ['build_type=="release"',{
        'defines': ['BUILD_RELEASE'],
      }],
    ], # conditions
  },
}
