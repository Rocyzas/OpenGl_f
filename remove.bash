#!/bin/bash

# Set the filename
# Create an empty file
touch $filename
# Check the file is exists or not
if [ -f $filename ]; then
   rm moc_* *.o Makefile
   echo "Files removed"
fi
