#!/bin/sh
find ./ -iname *.h -o -iname *.cc | xargs clang-format -i