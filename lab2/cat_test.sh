#!/bin/bash


file1=../test/1.txt

echo Testing file $file1

echo TEST cat $file1 / ./s21_cat $file1
expect=$( cat $file1 )
res=$( ./s21_cat $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./s21_cat -b $file1
expect=$( cat -b $file1 )
res=$( ./s21_cat -b $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./s21_cat -n $file1
expect=$( cat -n $file1)
res=$( ./s21_cat -n $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./s21_cat --number-nonblank $file1
expect=$( cat -b $file1)
res=$( ./s21_cat --number-nonblank $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./s21_cat --number $file1
expect=$( cat -n $file1 )
res=$( ./s21_cat --number $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -e $file1 / ./s21_cat -e $file1
expect=$( cat -e $file1 )
res=$( ./s21_cat -e $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./s21_cat -s $file1
expect=$( cat -s $file1 )
res=$( ./s21_cat -s $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./s21_cat --squeeze-blank $file1
expect=$( cat -s $file1 )
res=$( ./s21_cat --squeeze-blank $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -t $file1 / ./s21_cat -t $file1
expect=$( cat -t $file1 )
res=$( ./s21_cat -t $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi

file1=../test/2.txt

echo Testing file $file1

echo TEST cat $file1 / ./s21_cat $file1
expect=$( cat $file1 )
res=$( ./s21_cat $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./s21_cat -b $file1
expect=$( cat -b $file1 )
res=$( ./s21_cat -b $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./s21_cat -n $file1
expect=$( cat -n $file1)
res=$( ./s21_cat -n $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./s21_cat --number-nonblank $file1
expect=$( cat -b $file1)
res=$( ./s21_cat --number-nonblank $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./s21_cat --number $file1
expect=$( cat -n $file1 )
res=$( ./s21_cat --number $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -e $file1 / ./s21_cat -e $file1
expect=$( cat -e $file1 )
res=$( ./s21_cat -e $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./s21_cat -s $file1
expect=$( cat -s $file1 )
res=$( ./s21_cat -s $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./s21_cat --squeeze-blank $file1
expect=$( cat -s $file1 )
res=$( ./s21_cat --squeeze-blank $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -t $file1 / ./s21_cat -t $file1
expect=$( cat -t $file1 )
res=$( ./s21_cat -t $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi

file1=../test/3.txt

echo Testing file $file1

echo TEST cat $file1 / ./s21_cat $file1
expect=$( cat $file1 )
res=$( ./s21_cat $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./s21_cat -b $file1
expect=$( cat -b $file1 )
res=$( ./s21_cat -b $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./s21_cat -n $file1
expect=$( cat -n $file1)
res=$( ./s21_cat -n $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./s21_cat --number-nonblank $file1
expect=$( cat -b $file1)
res=$( ./s21_cat --number-nonblank $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./s21_cat --number $file1
expect=$( cat -n $file1 )
res=$( ./s21_cat --number $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -e $file1 / ./s21_cat -e $file1
expect=$( cat -e $file1 )
res=$( ./s21_cat -e $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./s21_cat -s $file1
expect=$( cat -s $file1 )
res=$( ./s21_cat -s $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./s21_cat --squeeze-blank $file1
expect=$( cat -s $file1 )
res=$( ./s21_cat --squeeze-blank $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -t $file1 / ./s21_cat -t $file1
expect=$( cat -t $file1 )
res=$( ./s21_cat -t $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi

file1=../test/meow.txt

echo Testing file $file1

echo TEST cat $file1 / ./s21_cat $file1
expect=$( cat $file1 )
res=$( ./s21_cat $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./s21_cat -b $file1
expect=$( cat -b $file1 )
res=$( ./s21_cat -b $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./s21_cat -n $file1
expect=$( cat -n $file1)
res=$( ./s21_cat -n $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./s21_cat --number-nonblank $file1
expect=$( cat -b $file1)
res=$( ./s21_cat --number-nonblank $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./s21_cat --number $file1
expect=$( cat -n $file1 )
res=$( ./s21_cat --number $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -e $file1 / ./s21_cat -e $file1
expect=$( cat -e $file1 )
res=$( ./s21_cat -e $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./s21_cat -s $file1
expect=$( cat -s $file1 )
res=$( ./s21_cat -s $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./s21_cat --squeeze-blank $file1
expect=$( cat -s $file1 )
res=$( ./s21_cat --squeeze-blank $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -t $file1 / ./s21_cat -t $file1
expect=$( cat -t $file1 )
res=$( ./s21_cat -t $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi

file1=../test/shablon.txt

echo Testing file $file1

echo TEST cat $file1 / ./s21_cat $file1
expect=$( cat $file1 )
res=$( ./s21_cat $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./s21_cat -b $file1
expect=$( cat -b $file1 )
res=$( ./s21_cat -b $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./s21_cat -n $file1
expect=$( cat -n $file1)
res=$( ./s21_cat -n $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -b $file1 / ./s21_cat --number-nonblank $file1
expect=$( cat -b $file1)
res=$( ./s21_cat --number-nonblank $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -n $file1 / ./s21_cat --number $file1
expect=$( cat -n $file1 )
res=$( ./s21_cat --number $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -e $file1 / ./s21_cat -e $file1
expect=$( cat -e $file1 )
res=$( ./s21_cat -e $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./s21_cat -s $file1
expect=$( cat -s $file1 )
res=$( ./s21_cat -s $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -s $file1 / ./s21_cat --squeeze-blank $file1
expect=$( cat -s $file1 )
res=$( ./s21_cat --squeeze-blank $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
echo TEST cat -t $file1 / ./s21_cat -t $file1
expect=$( cat -t $file1 )
res=$( ./s21_cat -t $file1)
if [ "$expect" == "$res" ]; then
    echo "_"
else
    echo "FAIL"
fi
