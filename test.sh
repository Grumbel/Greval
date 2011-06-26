#!/bin/bash

function expect_fail {
    if "$1" "$2"; then
        echo "FAILURE:" "$1" "$2"
    else
        echo "OK:" "$1" "$2"
    fi
}

function expect_result {
    RES=$("$2" "$3")
    if [ "$RES" != "$1" ]; then
        echo "FAILURE:" "$2" "$3" "->" "$1" "!=" "$RES"
    else
        echo "OK:" "$2" "$3" "->" "$RES"
    fi
}

# expect_fail "./expr" ".5.6.7"
# expect_fail "./expr" "5 6 7"

expect_result "18" "./expr" "5+6+7"
expect_result "25" "./expr" "(5+6)+7*2"
expect_result "7.75" "./expr" "5+11/12*3"

# EOF #
