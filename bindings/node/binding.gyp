{
  "targets": [
    {
      "target_name": "gaotp",
      "sources": [ "gaotp_node.c" ],
      "libraries":  [ "-lgaotp", "-lmycrypto" ]
    },{
         "target_name": "copy_binary",
         "type":"none",
         "dependencies" : [ "gatop" ],
         "copies":
         [
            {
               'destination': '<(module_root_dir)',
               'files': ['<(module_root_dir)/build/Release/gaotp.node']
            }
         ]
      }
  ]
}