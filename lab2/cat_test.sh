#!/bin/bash


file1=./test/1.txt

echo Testing file $file1

echo TEST cat $file1 / ./my_cat $file1
expect=$( cat $file1 )
res=$( ./my_cat $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./my_cat -b $file1
expect=$( cat -b $file1 )
res=$( ./my_cat -b $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./my_cat -n $file1
expect=$( cat -n $file1)
res=$( ./my_cat -n $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./my_cat --number-nonblank $file1
expect=$( cat -b $file1)
res=$( ./my_cat --number-nonblank $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./my_cat --number $file1
expect=$( cat -n $file1 )
res=$( ./my_cat --number $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -e $file1 / ./my_cat -e $file1
expect=$( cat -e $file1 )
res=$( ./my_cat -e $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./my_cat -s $file1
expect=$( cat -s $file1 )
res=$( ./my_cat -s $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./my_cat --squeeze-blank $file1
expect=$( cat -s $file1 )
res=$( ./my_cat --squeeze-blank $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -t $file1 / ./my_cat -t $file1
expect=$( cat -t $file1 )
res=$( ./my_cat -t $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi

file1=./test/2.txt

echo Testing file $file1

echo TEST cat $file1 / ./my_cat $file1
expect=$( cat $file1 )
res=$( ./my_cat $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./my_cat -b $file1
expect=$( cat -b $file1 )
res=$( ./my_cat -b $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./my_cat -n $file1
expect=$( cat -n $file1)
res=$( ./my_cat -n $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./my_cat --number-nonblank $file1
expect=$( cat -b $file1)
res=$( ./my_cat --number-nonblank $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./my_cat --number $file1
expect=$( cat -n $file1 )
res=$( ./my_cat --number $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -e $file1 / ./my_cat -e $file1
expect=$( cat -e $file1 )
res=$( ./my_cat -e $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./my_cat -s $file1
expect=$( cat -s $file1 )
res=$( ./my_cat -s $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./my_cat --squeeze-blank $file1
expect=$( cat -s $file1 )
res=$( ./my_cat --squeeze-blank $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -t $file1 / ./my_cat -t $file1
expect=$( cat -t $file1 )
res=$( ./my_cat -t $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi

file1=../test/3.txt

echo Testing file $file1

echo TEST cat $file1 / ./my_cat $file1
expect=$( cat $file1 )
res=$( ./my_cat $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./my_cat -b $file1
expect=$( cat -b $file1 )
res=$( ./my_cat -b $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./my_cat -n $file1
expect=$( cat -n $file1)
res=$( ./my_cat -n $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./my_cat --number-nonblank $file1
expect=$( cat -b $file1)
res=$( ./my_cat --number-nonblank $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./my_cat --number $file1
expect=$( cat -n $file1 )
res=$( ./my_cat --number $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -e $file1 / ./my_cat -e $file1
expect=$( cat -e $file1 )
res=$( ./my_cat -e $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./my_cat -s $file1
expect=$( cat -s $file1 )
res=$( ./my_cat -s $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./my_cat --squeeze-blank $file1
expect=$( cat -s $file1 )
res=$( ./my_cat --squeeze-blank $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -t $file1 / ./my_cat -t $file1
expect=$( cat -t $file1 )
res=$( ./my_cat -t $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi

file1=../test/meow.txt

echo Testing file $file1

echo TEST cat $file1 / ./my_cat $file1
expect=$( cat $file1 )
res=$( ./my_cat $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./my_cat -b $file1
expect=$( cat -b $file1 )
res=$( ./my_cat -b $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./my_cat -n $file1
expect=$( cat -n $file1)
res=$( ./my_cat -n $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./my_cat --number-nonblank $file1
expect=$( cat -b $file1)
res=$( ./my_cat --number-nonblank $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./my_cat --number $file1
expect=$( cat -n $file1 )
res=$( ./my_cat --number $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -e $file1 / ./my_cat -e $file1
expect=$( cat -e $file1 )
res=$( ./my_cat -e $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./my_cat -s $file1
expect=$( cat -s $file1 )
res=$( ./my_cat -s $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./my_cat --squeeze-blank $file1
expect=$( cat -s $file1 )
res=$( ./my_cat --squeeze-blank $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -t $file1 / ./my_cat -t $file1
expect=$( cat -t $file1 )
res=$( ./my_cat -t $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi

file1=./test/shablon.txt

echo Testing file $file1

echo TEST cat $file1 / ./my_cat $file1
expect=$( cat $file1 )
res=$( ./my_cat $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./my_cat -b $file1
expect=$( cat -b $file1 )
res=$( ./my_cat -b $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./my_cat -n $file1
expect=$( cat -n $file1)
res=$( ./my_cat -n $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./my_cat --number-nonblank $file1
expect=$( cat -b $file1)
res=$( ./my_cat --number-nonblank $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./my_cat --number $file1
expect=$( cat -n $file1 )
res=$( ./my_cat --number $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -e $file1 / ./my_cat -e $file1
expect=$( cat -e $file1 )
res=$( ./my_cat -e $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./my_cat -s $file1
expect=$( cat -s $file1 )
res=$( ./my_cat -s $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./my_cat --squeeze-blank $file1
expect=$( cat -s $file1 )
res=$( ./my_cat --squeeze-blank $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
echo TEST cat -t $file1 / ./my_cat -t $file1
expect=$( cat -t $file1 )
res=$( ./my_cat -t $file1)
if [ "$expect" == "$res" ]; then
    echo "GOOD"
else
    echo "FAIL"
fi
