FILE="example.txt"
echo "Hello, system calls!" > "$FILE"
echo "Data written to $FILE"
echo "Reading from $FILE:"
cat "$FILE"
echo "Content of $FILE:"
while IFS= read -r line; do
  echo "$line"
done < "$FILE"
rm "$FILE"
echo "$FILE has been removed."
echo "Script execution completed."

