#!/bin/bash

libfile="./Libfile"

arduino-cli lib update-index

while IFS= read -r line
do
   arduino-cli lib install "$line"
done < "$libfile"
