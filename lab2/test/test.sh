echo TEST 1 - cat 1.txt / ../cat/s21_cat 1.txt
expect=$( cat 1.txt )
res=$( ../cat/s21_cat 1.txt)
if [ "$expect" == "$res" ]; then
    echo "OK"
else
    echo "FAIL"
fi
echo TEST 2 - cat -v 1.txt / ../cat/s21_cat -v 1.txt 
expect=$( cat -v 1.txt  )
res=$( ../cat/s21_cat -v 1.txt )
if [ "$expect" == "$res" ]; then
    echo "OK"
else
    echo "FAIL"
fi
echo TEST 3 - cat -b meow.txt / ../cat/s21_cat -b meow.txt
expect=$( cat -b meow.txt )
res=$( ../cat/s21_cat -b meow.txt)
if [ "$expect" == "$res" ]; then
    echo "OK"
else
    echo "FAIL"
fi
echo TEST 4 - cat -n meow.txt / ../cat/s21_cat -n meow.txt
expect=$( cat -n meow.txt)
res=$( ../cat/s21_cat -n meow.txt)
if [ "$expect" == "$res" ]; then
    echo "OK"
else
    echo "FAIL"
fi
echo TEST 5 - cat -b meow.txt / ../cat/s21_cat --number-nonblank meow.txt
expect=$( cat -b meow.txt)
res=$( ../cat/s21_cat --number-nonblank meow.txt)
if [ "$expect" == "$res" ]; then
    echo "OK"
else
    echo "FAIL"
fi
echo TEST 6 - cat -n meow.txt / ../cat/s21_cat --number meow.txt
expect=$( cat -n meow.txt )
res=$( ../cat/s21_cat --number meow.txt)
if [ "$expect" == "$res" ]; then
    echo "OK"
else
    echo "FAIL"
fi  
echo TEST 7 - cat -e w.txt / ../cat/s21_cat -e w.txt
expect=$( cat -e w.txt )
res=$( ../cat/s21_cat -e w.txt)
if [ "$expect" == "$res" ]; then
    echo "OK"
else
    echo "FAIL"
fi
echo TEST 8 - cat -s meow.txt / ../cat/s21_cat -s meow.txt
expect=$( cat -s meow.txt )
res=$( ../cat/s21_cat -s meow.txt)
if [ "$expect" == "$res" ]; then
    echo "OK"
else
    echo "FAIL"
fi
echo TEST 9 - cat -s meow.txt / ../cat/s21_cat --squeeze-blank meow.txt
expect=$( cat -s meow.txt )
res=$( ../cat/s21_cat --squeeze-blank meow.txt)
if [ "$expect" == "$res" ]; then
    echo "OK"
else
    echo "FAIL"
fi
echo TEST 10 - cat -t 1.txt / ../cat/s21_cat -t 1.txt
expect=$( cat -t 1.txt )
res=$( ../cat/s21_cat -t 1.txt)
if [ "$expect" == "$res" ]; then
    echo "OK"
else
    echo "FAIL"
fi


echo TEST 1 - grep test.txt / ../grep/s21_grep -e 'hello' test.txt
TEST_GREP_e=`grep -e 'hello' test.txt`
TEST_S21GREP_e=`../grep/s21_grep -e 'hello' test.txt`

if [[ $TEST_GREP_e == $TEST_S21GREP_e  ]]
then
    echo "OK"
else
    echo "FAIL"
fi

echo TEST 2 - grep test.txt / ../grep/s21_grep -i 'hello' test.txt
TEST_GREP_i=`grep -i 'hello' test.txt`
TEST_S21GREP_i=`../grep/s21_grep -i 'hello' test.txt`

if [[ $TEST_GREP_i == $TEST_S21GREP_i  ]]
then
    echo "OK"
else
    echo "FAIL"
fi

echo TEST 3 - grep test.txt / ../grep/s21_grep -v 'hello' test.txt
TEST_GREP_v=`grep -v 'hello' test.txt`
TEST_S21GREP_v=`../grep/s21_grep -v 'hello' test.txt`

if [[ $TEST_GREP_v == $TEST_S21GREP_v  ]]
then
    echo "OK"
else
    echo "FAIL"
fi

echo TEST 4 - grep test.txt / ../grep/s21_grep -c 'hello' test.txt
TEST_GREP_c=`grep -c 'hello' test.txt`
TEST_S21GREP_c=`../grep/s21_grep -c 'hello' test.txt`

if [[ $TEST_GREP_c == $TEST_S21GREP_c  ]]
then
    echo "OK"
else
    echo "FAIL"
fi

echo TEST 5 - grep test.txt / ../grep/s21_grep -l 'hello' test.txt
TEST_GREP_l=`grep -l 'hello' test.txt`
TEST_S21GREP_l=`../grep/s21_grep -l 'hello' test.txt`

if [[ $TEST_GREP_l == $TEST_S21GREP_l  ]]
then
    echo "OK"
else
    echo "FAIL"
fi

echo TEST 6 - grep test.txt / ../grep/s21_grep -n 'hello' test.txt
TEST_GREP_n=`grep -n 'hello' test.txt`
TEST_S21GREP_n=`../grep/s21_grep -n 'hello' test.txt`

if [[ $TEST_GREP_n == $TEST_S21GREP_n  ]]
then
    echo "OK"
else
    echo "FAIL"
fi

echo TEST 7 - grep test.txt / ../grep/s21_grep -h 'hello' test.txt
TEST_GREP_h=`grep -h 'hello' test.txt`
TEST_S21GREP_h=`../grep/s21_grep -h 'hello' test.txt`

if [[ $TEST_GREP_h == $TEST_S21GREP_h  ]]
then
    echo "OK"
else
    echo "FAIL"
fi

echo TEST 8 - grep test.txt / ../grep/s21_grep -s 'hello' test.txt
TEST_GREP_s=`grep -s 'hello' test.txt`
TEST_S21GREP_s=`../grep/s21_grep -s 'hello' test.txt`

if [[ $TEST_GREP_s == $TEST_S21GREP_s  ]]
then
    echo "OK"
else
    echo "FAIL"
fi

echo TEST 9 - grep test.txt / ../grep/s21_grep -f shablon.txt test.txt
TEST_GREP_f=`grep -f shablon.txt test.txt`
TEST_S21GREP_f=`../grep/s21_grep -f shablon.txt test.txt`

if [[ $TEST_GREP_f == $TEST_S21GREP_f  ]]
then
    echo "OK"
else
    echo "FAIL"
fi

echo TEST 10 - grep test.txt / ../grep/s21_grep -o 'hello' test.txt
TEST_GREP_o=`grep -o 'hello' test.txt`
TEST_S21GREP_o=`../grep/s21_grep -o 'hello' test.txt`

if [[ $TEST_GREP_o == $TEST_S21GREP_o  ]]
then
    echo "OK"
else
    echo "FAIL"
fi
