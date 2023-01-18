#include<iostream>
#include<math.h>
#include<string>
using namespace std;

bool IsMember(int a[], int x, int size)
{
	if (!size)
		return -1; 
	if (a[size - 1] == x)
		return 1;
	 IsMember(a, x, size - 1);
}



int Fibonacci(int n)
{
	if (n <= 1)
		return n;
	
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}


int RecursiveSum(int n)
{
	int sum = 0;
	if (n /10 == 0)
		return n ;
	for (n;n != 0; n = n / 10)
	{
		sum += n % 10;
	}
	cout << sum << " ";
	RecursiveSum(sum);

}



void Ways(int x, int n,int num, int& no)
{
	
	if (x == 0)
	{
		no++;
	}
	if (x > 100 || x < 1 || n < 2 || n>10)
		return;
	for (int i = num + 1; i <= pow(x,1.0/n); i++)
	{
		Ways(x - pow(i, n), n, i, no);
	}
}


int main()
{
	int size = 10;
	int arr[10] = { 5, 6, 7, 8, 10, 12, 14, 2, 17, 2 };

	cout << "is member: " << IsMember(arr, 10, size) << endl;
	int n;
	cout << "number for fibonacci: ";
	cin >> n;

	cout << "fibonacci: " << Fibonacci(n) << endl;

	RecursiveSum(795);
	
	int noOfWays = 0;
	int x, n2;
	cout << "NthPower, X, N: ";
	cin >> x >> n2;
	Ways(x, n2, 0, noOfWays);
	cout << endl << "Number of Ways: " << noOfWays << endl;
	return 0;
}
