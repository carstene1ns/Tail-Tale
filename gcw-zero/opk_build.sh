#!/bin/sh
rm -rf tailtale.opk
mksquashfs ../tailtale tailtale.png default.gcw0.desktop ../data/* ../README TailTale.opk -all-root -noappend -no-exports -no-xattrs
