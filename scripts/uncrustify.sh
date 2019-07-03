#!/bin/sh
SRCROOT=`git rev-parse --show-toplevel`
CFG="$SRCROOT/scripts/uncrustify.cfg"
echo "srcroot: $SRCROOT"
pushd "$SRCROOT"
uncrustify -c "$CFG" --no-backup `git ls-tree --name-only -r HEAD | grep fp-.*\\\.[ch]$ | grep -v nbis | grep -v build/`
popd
