#!/bin/bash

# Set the filename
filename='test.txt'
# Create an empty file
touch $filename
# Check the file is exists or not
if [ -f $filename ]; then
   rm *.o moc_*
   echo "$filename is removed"
fi
