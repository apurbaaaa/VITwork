echo "Task a: Creating parent and child process"
(
  echo "In child process (PID $$)"
  echo "Child process ID: $$"
  sleep 5
) &

CHILD_PID=$!
echo "Parent process waiting for child process to finish."
wait $CHILD_PID
echo "Child process has finished."

echo "Task b: Creating a zombie process"
(
  echo "In zombie process (PID $$)"
  sleep 30 & ZOMBIE_PID=$!
  echo "Zombie process ID: $ZOMBIE_PID"
) &
sleep 5

echo "Task c: Creating an orphan process"
(
  echo "In orphan process (PID $$)"
  sleep 60 & ORPHAN_PID=$!
  echo "Orphan process ID: $ORPHAN_PID"
  sleep 60
) &

echo "Task d: Making the process sleep"
sleep 10
echo "Sleep complete."

echo "Task e: Using pipes"
mkfifo mypipe
echo "Message from the parent process" > mypipe & 
cat mypipe
rm mypipe

wait
echo "All tasks completed."

