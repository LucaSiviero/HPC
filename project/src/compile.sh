#! /bin/sh

echo "Which file do you want to compile?"
read file
echo "What is the output file name? Empty for default."
read output

echo "Compiling" $file

syclcc --hipsycl-targets="cuda:sm_86" $file $output

echo "Compilation finished"