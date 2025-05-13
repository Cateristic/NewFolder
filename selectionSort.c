#include <stdio.h>

void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        // Swap the found minimum element with the first element
        if(min_idx != i) {
            temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
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
        printf("\n--- Selection Sort Menu ---\n");
        printf("1. Enter elements\n");
        printf("2. Display elements\n");
        printf("3. Sort using Selection Sort\n");
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
                    printf("Array is empty. Please enter elements first.\n");
                else {
                    selectionSort(arr, n);
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
