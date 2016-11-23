#!/bin/sh -e
sed -i "s@\(export BUILD_ABS=\"\)\(.*\)\(\"\)@\1$PWD\3@
        s@\(export HYPER_ABS=\"\)\(.*\)\(\"\)@\1$PWD\3@
        s@\(export module_file=\"\)\(.*\)\(\/bfm/bin/native/vmm.modules\"\)@\1$PWD\3@" env.sh

