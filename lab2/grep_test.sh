#!/bin/bash

solo_pattern=When
EEE=e
FFF=f
file1=./test/1.txt
file2=./test/2.txt
file3=./test/3.txt

echo "----------------------------------------------------------------------------"
echo "TESTS WITH ONE FILE"
echo "----------------------------------------------------------------------------"



echo TEST grep $solo_pattern $file1 / ./my_grep $solo_pattern $file1
expect=$( grep $solo_pattern $file1 )
res=$( ./my_grep $solo_pattern $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi



echo TEST grep -e $solo_pattern $file1 / ./my_grep -e $solo_pattern $file1
expect=$( grep -e $solo_pattern $file1)
res=$( ./my_grep -e $solo_pattern $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi



echo TEST grep -f $file3 $file1 / ./my_grep -f $file3 $file1
expect=$( grep -f $file3 $file1)
res=$( ./my_grep -f $file3 $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi



for flag in  i v c l n h s o
do
for var in i v c l n h s o
do
if [ "$var" == "$flag" ]; then
    echo TEST grep -$var $solo_pattern $file1 / ./my_grep -$var $solo_pattern $file1
    expect=$( grep -$var $solo_pattern $file1)
    res=$( ./my_grep -$var $solo_pattern $file1)
    if [ "$expect" == "$res" ]; then
        echo "GOOD"
    else
        echo "FAIL"
    fi
else
    echo TEST grep -$flag$var $solo_pattern $file1 / ./my_grep -$flag$var $solo_pattern $file1
    expect=$( grep -$flag$var $solo_pattern $file1)
    res=$( ./my_grep -$flag$var $solo_pattern $file1)
    if [ "$expect" == "$res" ]; then
        echo "GOOD"
    else
        echo "FAIL"
    fi
fi
done
done



for var in  i v c l n h s o
do
echo TEST grep -$var$EEE $solo_pattern  $file1 / ./my_grep -$var$EEE $solo_pattern $file1
expect=$( grep -$var$EEE $solo_pattern $file1 )
res=$( ./my_grep -$var$EEE $solo_pattern $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
done



for var in  i v c l n h s o
do
echo TEST grep -$var$FFF $file3 $file1 / ./my_grep -$var$FFF $file3 $file1
expect=$( grep -$var$FFF $file3 $file1)
res=$( ./my_grep -$var$FFF $file3 $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
done



echo "----------------------------------------------------------------------------"
echo "TESTS WITH TWO FILES"
echo "----------------------------------------------------------------------------"



echo TEST grep -e $solo_pattern $file1 $file2 / ./my_grep -e $solo_pattern $file1 $file2
expect=$( grep -e $solo_pattern $file1 $file2)
res=$( ./my_grep -e $solo_pattern $file1 $file2)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi



echo TEST grep -f $file3 $file1 $file2 / ./my_grep -f $file3 $file1 $file2
expect=$( grep -f $file3 $file1 $file2)
res=$( ./my_grep -f $file3 $file1 $file2)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi



for flag in  i v c l n h s o
do
for var in i v c l n h s o
do
if [ "$var" == "$flag" ]; then
    echo TEST grep -$var $solo_pattern $file1 $file2 / ./my_grep -$var $solo_pattern $file1 $file2
    expect=$( grep -$var $solo_pattern $file1 $file2)
    res=$( ./my_grep -$var $solo_pattern $file1 $file2)
    if [ "$expect" == "$res" ]; then
        echo "GOOD"
    else
        echo "FAIL"
    fi
else
    echo TEST grep -$flag$var $solo_pattern $file1 $file2 / ./my_grep -$flag$var $solo_pattern $file1 $file2
    expect=$( grep -$flag$var $solo_pattern $file1 $file2)
    res=$( ./my_grep -$flag$var $solo_pattern $file1 $file2)
    if [ "$expect" == "$res" ]; then
        echo "GOOD"
    else
        echo "FAIL"
    fi
fi
done
done



for var in  i v c l n h s o
do
echo TEST grep -$var$EEE $solo_pattern  $file1 $file2 / ./my_grep -$var$EEE $solo_pattern $file1 $file2
expect=$( grep -$var$EEE $solo_pattern $file1 $file2)
res=$( ./my_grep -$var$EEE $solo_pattern $file1 $file2)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
done



for var in  i v c l n h s o
do
echo TEST grep -$var$FFF $file3  $file1 $file2/ ./my_grep -$var$FFF $file3  $file1 $file2
expect=$( grep -$var$FFF $file3  $file1 $file2)
res=$( ./my_grep -$var$FFF $file3  $file1 $file2)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
done
