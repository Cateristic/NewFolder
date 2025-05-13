#include<stdio.h>

int binarySearch(int arr[], int n , int target)
{
    int low = 0;
    int high = n-1;

    while(low<=high)
    {
        int mid = low + (high-low)/2;

        if(arr[mid] == target)
        {
            return mid;
        }
        else if(arr[mid]<target)
        {
            low = mid+1;
        }
        else
        {
            high = mid-1;
        }
    }

    return -1;
}

int main() {
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 5;

    int result = binarySearch(arr, n, target);

    if (result != -1)
        printf("Element found at index %d\n", result);
    else
        printf("Element not found\n");

    return 0;
}