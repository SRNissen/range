
echo
echo iterator test init
    rm bin/iterator
    g++ -o ./bin/iterator iterator.cpp -std=c++20 -Wall -Wextra -Wpedantic -Werror -fmax-errors=3
    ./bin/iterator
echo iterator test done

echo
echo fixed_container test init
    rm bin/fixed_container
    g++ -o ./bin/fixed_container fixed_container.cpp -std=c++20 -Wall -Wextra -Wpedantic -Werror -fmax-errors=3
    ./bin/fixed_container
echo fixed_container test done

echo
echo rangemakers test init
    rm bin/rangemakers
    g++ -o ./bin/rangemakers rangemakers.cpp -std=c++20 -Wall -Wextra -Wpedantic -Werror -fmax-errors=3
    ./bin/rangemakers
echo rangemakers test done