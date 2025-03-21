#include <iostream>
#include <unordered_map>
#include <vector>


using namespace std;

//Global Variables
int count = 0;
int maxAmount = INT_MIN; // Start with the smallest possible integer

// Function to add a money amount for a user ID
void addMoney(unordered_map<int, vector<int>>& userMoneyMap, int userId, int amount) {
    // Check if the user ID is already in the hashmap
    if (userMoneyMap.find(userId) != userMoneyMap.end()) {
        // If user ID exists, append the new money amount to the vector
        userMoneyMap[userId].push_back(amount);
    } else {
        // If user ID doesn't exist, create a new vector with the amount
        userMoneyMap[userId] = {amount};
    }
}

// This will find the largest and displays them for each bid - bid may start again.
void findLargestAmount(const unordered_map<int, vector<int>>& userMoneyMap) {

    vector<int> usersWithMaxAmount; // To store user IDs with the largest amount

    // Traverse through the hashmap
    for (const auto& entry : userMoneyMap) {
        int userId = entry.first;
        const vector<int>& amounts = entry.second;

        // Find the largest amount for this user
        for (int amount : amounts) {
            if (amount > maxAmount) {
                maxAmount = amount;
                // Start a new list with this user
                usersWithMaxAmount = {userId};
            } else if (amount == maxAmount) {
                // Add this user to the list
                usersWithMaxAmount.push_back(userId);
            }
        }
    }

    // Print the result
    cout << "Largest amount in CDN: $" << maxAmount << endl;
    cout << "User(s) with the largest amount by ID: ";
    for (int userId : usersWithMaxAmount) {
        // Display user ID(s) and increase counter to find if we have to bid again
        cout << userId << " ";
        count++;
    }
    cout << endl << endl;
}

[[noreturn]] int main() {

    unordered_map<int, vector<int>> userMoneyMap;
    bool result = true;

    // Sample inputs
    addMoney(userMoneyMap, 1, 100);  // User 1 has 100
    addMoney(userMoneyMap, 2, 200);  // User 2 has 200
    addMoney(userMoneyMap, 1, 150);  // User 1 now has 100 and 150

    // Random selection for bids over $35
    for (int i = 0; i < 2000; i++) {
        int randomID = rand() % 30 + 1;
        int randomMoney = rand() % 300 + 1;

        if (randomMoney > 35)
            addMoney(userMoneyMap, randomID, randomMoney);
    }

    // Print the hashmap to verify
    for (const auto& entry : userMoneyMap) {
        cout << "User " << entry.first << " has amounts: ";
        for (int amount : entry.second) {
            cout << amount << " ";
        }
        cout << endl << endl;
    }

    // Find largest bidder(s) and checks how many biggest bidders there are and resets counter
    findLargestAmount(userMoneyMap);
    cout << "Count = " << count << endl;
    if (count ==  1) {
        result = false;
    }
    count = 0;

    // It will continue to bid under the rules until one winner is found
    while(result == true){
        // Random selection for bids over highest bid
        for (int i = 0; i < 2000; i++) {
            int randomID = rand() % 30 + 1;
            int randomMoney = rand() % maxAmount+300 + maxAmount;

            if (randomMoney > (maxAmount+1))
                addMoney(userMoneyMap, randomID, randomMoney);
        }
        findLargestAmount(userMoneyMap);

        // Check if there is one winner or not - then resents counter if it does not exit while loop
        if (count ==  1) {
            break;
        }
        count = 0;
    }

    return 0;
}