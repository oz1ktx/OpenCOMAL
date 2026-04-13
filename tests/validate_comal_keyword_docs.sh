#!/bin/bash
# validate_comal_keyword_docs.sh
# Validate tab-separated external keyword help docs.

set -euo pipefail

FILE_PATH="${1:-}"
if [[ -z "$FILE_PATH" ]]; then
  echo "Usage: $0 <path-to-comal-keyword-docs.tsv>"
  exit 2
fi

if [[ ! -f "$FILE_PATH" ]]; then
  echo "ERROR: File not found: $FILE_PATH"
  exit 2
fi

awk -F '\t' '
function trim(s) {
  gsub(/^[ \t\r\n]+/, "", s)
  gsub(/[ \t\r\n]+$/, "", s)
  return s
}
BEGIN {
  status = 0
}
{
  line = $0
  if (line ~ /^[ \t]*#/ || line ~ /^[ \t]*$/) {
    next
  }

  if (NF < 3) {
    printf("ERROR:%d: expected 3 tab-separated fields (keyword, category, description)\n", NR)
    status = 1
    next
  }

  keyword = trim($1)
  category = trim($2)

  desc = $3
  for (i = 4; i <= NF; ++i) {
    desc = desc "\t" $i
  }
  desc = trim(desc)

  if (keyword == "") {
    printf("ERROR:%d: keyword field is empty\n", NR)
    status = 1
  }
  if (category == "") {
    printf("ERROR:%d: category field is empty\n", NR)
    status = 1
  }
  if (desc == "") {
    printf("ERROR:%d: description field is empty\n", NR)
    status = 1
  }

  key_upper = toupper(keyword)
  if (seen[key_upper] > 0) {
    printf("ERROR:%d: duplicate keyword '%s' (first seen at line %d)\n", NR, keyword, seen[key_upper])
    status = 1
  } else {
    seen[key_upper] = NR
  }
}
END {
  if (status == 0) {
    print "Keyword docs format OK"
  }
  exit status
}
' "$FILE_PATH"
