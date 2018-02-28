#!/bin/bash 
# Gramatically better way of attaching search refinements (filters) to
# programs, such as, "wn" (vwhichisnew), or "ww" (vwhichiswatched).

if (( $# == 0 )) || [[ "$1" == "-?" ]]; then
  cat <<BANNER
Usage: <wn|ww> | re <filename fragment(s) -- or subject / topic>...

e.g. vwhatisnew | re space starship
May produce these results (if files exist, in the current dir):
 Clip-of-Starship-Troopers.mp4
 Space-x The Hoax.mp4
 ...
BANNER
  exit 1
elif (( $# > 1 )); then
  # We know we have some gaps...
  qry=$( sed <<<"$@" -rn 's/ +/\|/gp' )
else
  # sed above fails, if no spaces in $@
  qry=$1
fi

# Remember file, if exactly one
nfiles=$( grep -iE "$qry" <.gnotes/re | wc --lines )
if (( $nfiles == 1 )); then
  echo "lastvideo='$( grep -iE "$qry" <.gnotes/re )'" >.gnotes/memory
fi

# Re-grep and hilight query, for user
grep --color=auto -iE "$qry" <.gnotes/re
