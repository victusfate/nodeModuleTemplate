{
  'targets': [  
    {
      'target_name': 'moduleName',
      'sources': ['<!@(ls -1 ./src/*.cc)'],
      'cflags!': [
        '-03',
        '-Wall',
        '-Wno-eof-newline',
        '-msse2',
        '-fno-exceptions'
      ],
      'cflags_cc!': [
        '-03',
        '-Wall',
        '-Wno-eof-newline',
        '-msse2',
        '-fno-exceptions'
      ],      
      'defines': [
        '_FILE_OFFSET_BITS=64',
        '_LARGEFILE_SOURCE',
        '_MODULE_NAME_NODE_MODULE'
      ],
      'include_dirs+': [
        'src/'
      ],
      'link_settings': {
        'conditions' : [
            ['OS=="linux"',
                {
                    'libraries': [
                    ]
                }
            ],
            ['OS=="mac"',
                {
                    'libraries': [
                    ],
                    'xcode_settings': {
                      'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
                    }                    
                }
            ]
        ]
      }  
    }
  ]
}