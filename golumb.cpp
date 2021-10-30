#include <bits/stdc++.h>
using namespace std;
#define MAX 100001
#define ull unsigned long long

void printGolombSequence(int N)
{

    // Initialise the array
    int arr[MAX];

    // Initialise the cnt to 0
    int cnt = 0;

    // First and second element
    // of Golomb Sequence is 0, 1
    arr[0] = 0;
    arr[1] = 1;

    // Map to store the count of
    // current element in Golomb
    // Sequence
    map<int, int> M;

    // Store the count of 2
    M[2] = 2;

    // Iterate over 2 to N
    for (int i = 2; i <= N; i++) {

        // If cnt is equals to 0
        // then we have new number
        // for Golomb Sequence
        // which is 1 + previous
        // element
        if (cnt == 0) {
            arr[i] = 1 + arr[i - 1];
            cnt = M[arr[i]];
            cnt--;
        }

        // Else the current element
        // is the previous element
        // in this Sequence
        else {
            arr[i] = arr[i - 1];
            cnt--;
        }

        // Map the current index to
        // current value in arr[]
        M[i] = arr[i];
    }

    // Print the Golomb Sequence
    for (int i = 1; i <= N; i++) {
        cout << arr[i] << ' ';
    }
}


int main()
{
	int T,R,L;
	cin >> T ;

    for(int i=0 ; i < T ; i++)
    {
       cin >> L ;
     printGolombSequence(L);
    }

	return 0;
}
