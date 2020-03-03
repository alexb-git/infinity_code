#!/bin/bash
# A simple script

file_name=$1


if [  -f $file_name.cpp  ];
then echo "file exists"
else

echo  "#include <iostream> /* ostream istream */

int main(int argc, char const *argv[], char const *envp[])
{
    /* code */

    return 0;
}" > $file_name.cpp


#touch $file_name.cpp

atom $file_name.cpp &

echo "hello "$file_name
