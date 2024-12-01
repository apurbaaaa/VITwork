FILE="example.txt"
DIR="."
echo "Hello, world!" > "$FILE"
echo "Parent process ID: $$"
(
  echo "Child process ID: $$"
  ls -l
  exit 0
) &
wait
echo "Child process has finished."
echo "Contents of directory '$DIR':"
for entry in "$DIR"/*; do
  if [ -d "$entry" ]; then
	echo "Directory: $entry"
  elif [ -f "$entry" ]; then
	echo "File: $entry"
  fi
done
echo "Status of file '$FILE':"
stat "$FILE"
rm "$FILE"
echo "Script execution completed."

