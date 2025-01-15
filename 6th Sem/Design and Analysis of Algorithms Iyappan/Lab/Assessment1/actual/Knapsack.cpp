#include <iostream>
#include <iomanip>
using namespace std;

double FractionalKnapsack(double P[], double W[], double X[], double R[], int M, int n) {
    int rem_cap = M;
    for (int i = 0; i < n; i++) {
        R[i] = 0;
    }

    double profit = 0;
    for (int i = 0; i < n; i++) {
        if (W[i] <= rem_cap) {
            R[i] = 1;
            rem_cap = rem_cap - W[i];
        } else {
            R[i] = double(rem_cap) / W[i];
            rem_cap = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        profit += R[i] * P[i];
    }
    return profit;
}

void DescSort(double arr[], double P[], double W[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                double temp = arr[j + 1];
                double val1 = P[j + 1];
                double val2 = W[j + 1];

                arr[j + 1] = arr[j];
                P[j + 1] = P[j];
                W[j + 1] = W[j];

                arr[j] = temp;
                P[j] = val1;
                W[j] = val2;
            }
        }
    }
}

int main() {
    int n = 5;
    int max = 60;
    double P[] = {30, 40, 45, 77, 90};
    double W[] = {5, 10, 15, 22, 25};
    double R[n];
    double X[n];

    cout << "Total weight capacity of knapsack: " << max << " kg" << endl;
    cout << "List of weights and corresponding profits:" << endl;

    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " - Weight: " << W[i] << " kg, Profit: " << P[i] << endl;
    }

    for (int i = 0; i < n; i++) {
        X[i] = (P[i] / W[i]);
    }

    cout << "\nWeight-to-Profit Ratios before sorting:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " - Ratio: " << fixed << setprecision(2) << X[i] << endl;
    }

    DescSort(X, P, W, n);

    cout << "\nWeight-to-Profit Ratios after sorting:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " - Weight: " << W[i] << " kg, Profit: " << P[i] << ", Ratio: " << fixed << setprecision(2) << X[i] << endl;
    }

    double profit = FractionalKnapsack(P, W, X, R, max, n);
    cout << "\nThe total profit is: " << fixed << setprecision(2) << profit << endl;

    cout << "\nOptimal solution:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " - Weight taken: " << R[i] * W[i] << " kg, Profit: " << R[i] * P[i] << endl;
    }

    return 0;
}
