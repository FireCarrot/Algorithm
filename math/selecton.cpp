#include <vector>
#include <iostream>

using namespace std;

/* 3
 * 7 3 1 */

int main() {
    int g;
    cin >> g;

    vector<int> groups;
    for (int i = 0; i < g; i++) {
        int tmp;
        cin >> tmp;

        groups.push_back(tmp);
    }

    /* The solution would be :
     * In 3 groups which are 7, 3, 1,
     * if 2 are selected from different 2 groups
     * what is the number of the possible cases to be selected?
     * 7*3 + 3*1 + 1*7
     * if 4 groups are 7, 5, 4, 3 : selected cases = 4C2 = 6 => O(g*g)*/

    int sum = 0;
    for (int i = 0; i < g; i++) {
        for (int j = i+1; j < g; j++) {
            sum += (groups[i] * groups[j]);
            cout << sum << "+=" << groups[i] << "*" << groups[j] << endl;
        }
    }

    cout << sum << endl;
}
