#!/bin/bash
# bash array index
# ref. https://unix.stackexchange.com/questions/278502/accessing-array-index-variable-from-bash-shell-script-loop

AR=('foo' 'bar' 'baz' 'bat')
for i in "${!AR[@]}"; do
  printf '${AR[%s]}=%s\n' "$i" "${AR[i]}"
done

