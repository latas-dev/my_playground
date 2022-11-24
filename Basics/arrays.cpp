#include <iostream>
using namespace std;

int main() {

    int n;

    cout << "Enter array size: ";
    cin >> n;

    int A[n];

    for(int i = 0; i < sizeof(A)/sizeof(int); i++) {
        cout << "Enter integer for index " << i << ": ";
        cin >> A[i];
    }

    cout << "A = { ";
    for(int x: A) {
        cout << x << " ";
    }
    cout << "}" << endl;

    return 0;
}