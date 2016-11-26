# Read from the file file.txt and output the tenth line to stdout.
cat file.txt | tail -n+10 | head -1