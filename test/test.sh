echo cleaning old asserts
rm asserts
echo compiling asserts
g++ fixed_container.cpp -std=c++20 -Wall -Wextra -Wpedantic -Werror -o asserts
echo running asserts
./asserts
echo test done
