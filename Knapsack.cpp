#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to solve Knapsack and print the selected items
void solveKnapsack(int capacity, const vector<int>& weights, const vector<int>& values, int n) {
    // Create a 2D DP table initialized to 0
    // Rows represent items (0 to n), Columns represent capacities (0 to capacity)
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    // Build the DP table bottom-up
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            // If the weight of the current item is less than or equal to the running capacity
            if (weights[i - 1] <= w) {
                // Find the maximum between including and excluding the item
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                // Exclude the item if it exceeds the running capacity
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The bottom-right corner holds the maximum value
    int maxProfit = dp[n][capacity];
    cout << "\n=========================================" << endl;
    cout << "Maximum Total Value in Knapsack: " << maxProfit << endl;
    cout << "=========================================" << endl;

    // Backtracking to find which items were selected
    cout << "Items included in the Knapsack:" << endl;
    int w = capacity;
    for (int i = n; i > 0 && maxProfit > 0; i--) {
        // If the value comes from the row above, the item was NOT included
        if (dp[i][w] == dp[i - 1][w]) {
            continue; 
        } else {
            // The item was included
            cout << "- Item " << i << " (Weight: " << weights[i - 1] 
                 << ", Value: " << values[i - 1] << ")" << endl;
            
            // Deduct the value and weight of the included item
            maxProfit -= values[i - 1];
            w -= weights[i - 1];
        }
    }
}

int main() {
    int n, capacity;

    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> values(n);
    vector<int> weights(n);

    cout << "\nEnter the values of the " << n << " items:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Value for item " << i + 1 << ": ";
        cin >> values[i];
    }

    cout << "\nEnter the weights of the " << n << " items:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Weight for item " << i + 1 << ": ";
        cin >> weights[i];
    }

    cout << "\nEnter the maximum capacity of the knapsack: ";
    cin >> capacity;

    solveKnapsack(capacity, weights, values, n);

    return 0;
}
