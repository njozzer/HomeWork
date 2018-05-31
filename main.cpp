#include <iostream>
#include <math.h>

int arr[] = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

int is_simple(int a) {
    for (int i:arr) {
        if (i == a) {
            return 1;
        }
    }
    return 0;
}

int getCountsOfDigits(int number) {
    return (int) (log10(number) + 1);
}

void getDigits(int *arr, int number) {
    int k = 0;
    while (number) {
        arr[k] = number % 10;
        number /= 10;
        k++;
    }
}

int number(int n) {
    int numb = 0;
    for (int i = pow(10, n - 1); i < pow(10, n); i++) {
        int k = getCountsOfDigits(i);
        int *arr = (int *) malloc(k * sizeof(int));
        getDigits(arr, i);
        int t = 1;
        for (int j = k - 1; j > 0; j--) {
            if (is_simple(arr[j] * 10 + arr[j - 1])) {
            } else {
                t = 0;
                break;
            }
        }

        if (t) {
            numb++;
        }
        free(arr);
    }
    return numb;
}

long long *array(long long a, int *len) {
    int k = 0;
    for (int i = 0; i < 21; ++i) {
        if (arr[i] / 10 == a % 10) {
            k++;
        }
    }
    long long *arra = (long long*) malloc(k * sizeof(long long));
    for (int i = 0; i < 21; ++i) {
        if (arr[i] / 10 == a % 10) {
            arra[i] = arr[i] / 10;
        }
    }
}

int n1(long long num,long long *arr1, int len, int k, int n) {
    if (k == n) {
        return 1;
    }
    int e = 0;
    for (int i = 0; i < len; ++i) {
        long long d = num*10 + arr1[i];
        int len = 0;
        long long *arr2 = array(d, &len);
        e += n1(d, arr2, len, k + 1, n);
    }
    return e;
}



int main() {
    int n;
    std::cin >> n;
    int k = 0;
    for (int i:arr) {
        int len = 0;
        long long *arr1 = array(i, &len);
        k += n1(i, arr1, len, 2, n);
    }
    printf("\n%d", number(n));
    return 0;
}