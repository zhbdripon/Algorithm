#include <bits/stdc++.h>
using namespace std;

/*
    Universal Binary Search Template
    --------------------------------
    Finds the FIRST index where condition(mid) becomes true.

    Pattern:
        F F F F T T T T
                ^
            answer

    Search Space:
        [lo, hi)

    Loop:
        while (lo < hi)

    Updates:
        true  -> hi = mid
        false -> lo = mid + 1
*/

int binarySearch(int lo, int hi) {
    // search range: [lo, hi)

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        if (condition(mid)) {
            hi = mid;          // keep mid
        } else {
            lo = mid + 1;      // discard mid
        }
    }

    return lo;
}
