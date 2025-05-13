#include <stdio.h>

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Temporary arrays
    int L[n1], R[n2];

    // Copy data to temp arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays
    i = 0; j = 0; k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    // Copy remaining elements
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);       // Sort first half
        mergeSort(arr, m + 1, r);   // Sort second half

        merge(arr, l, m, r);        // Merge the sorted halves
    }
}

void display(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[100], n = 0, choice;

    do {
        printf("\n--- Merge Sort Menu ---\n");
        printf("1. Enter elements\n");
        printf("2. Display elements\n");
        printf("3. Sort using Merge Sort\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter number of elements: ");
                scanf("%d", &n);
                printf("Enter %d elements: ", n);
                for (int i = 0; i < n; i++)
                    scanf("%d", &arr[i]);
                break;

            case 2:
                if (n == 0)
                    printf("Array is empty!\n");
                else {
                    printf("Array elements: ");
                    display(arr, n);
                }
                break;

            case 3:
                if (n == 0)
                    printf("Array is empty. Enter elements first.\n");
                else {
                    mergeSort(arr, 0, n - 1);
                    printf("Array sorted successfully.\n");
                }
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 0);

    return 0;
}
