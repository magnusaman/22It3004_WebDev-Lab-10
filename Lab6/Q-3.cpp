#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to check if attribute names exist in both relations
bool check_attribute_names(const vector<string>& attributes1, const vector<string>& attributes2) {
  for (const string& attr1 : attributes1) {
    if (find(attributes2.begin(), attributes2.end(), attr1) == attributes2.end()) {
      return false;
    }
  }
  return true;
}

// Function to perform simplified natural join (assumes unique attribute values)
vector<vector<string>> natural_join(const vector<vector<string>>& R, const vector<vector<string>>& S) {
  vector<vector<string>> result;

  // Check if common attributes exist and have unique values in both relations
  if (!check_attribute_names(R[0], S[0])) {
    cout << "Error: Missing common attributes in relations." << endl;
    return result; // Empty result on error
  }

  for (const vector<string>& row1 : R) {
    for (const vector<string>& row2 : S) {
      // Find matching rows based on common attributes (assuming unique values)
      bool join_condition = true;
      for (size_t i = 0; i < row1.size(); i++) {
        if (R[0][i] != S[0][i] && row1[i] != row2[i]) {
          join_condition = false;
          break;
        }
      }

      // Combine rows if they meet the join condition
      if (join_condition) {
        vector<string> joined_row;
        for (const string& value : row1) {
          joined_row.push_back(value);
        }
        for (const string& value : row2) {
          // Skip duplicate values already added from common attributes
          if (find(R[0].begin(), R[0].end(), value) == R[0].end()) {
            joined_row.push_back(value);
          }
        }
        result.push_back(joined_row);
      }
    }
  }

  return result;
}

// Function to get user input for a relation
vector<vector<string>> get_relation_input(int num_rows, int num_attributes) {
  vector<vector<string>> relation;
  for (int i = 0; i < num_rows; i++) {
    vector<string> row;
    for (int j = 0; j < num_attributes; j++) {
      string value;
      cout << "Enter value for row " << i + 1 << ", attribute " << j + 1 << ": ";
      cin >> value;
      row.push_back(value);
    }
    relation.push_back(row);
  }
  return relation;
}

int main() {
  int num_rows_R, num_attributes_R, num_rows_S, num_attributes_S;

  // Get input for relation R
  cout << "Enter number of rows for relation R: ";
  cin >> num_rows_R;
  cout << "Enter number of attributes for relation R: ";
  cin >> num_attributes_R;

  vector<vector<string>> R = get_relation_input(num_rows_R, num_attributes_R);

  // Get input for relation S
  cout << "\nEnter number of rows for relation S: ";
  cin >> num_rows_S;
  cout << "Enter number of attributes for relation S: ";
  cin >> num_attributes_S;

  vector<vector<string>> S = get_relation_input(num_rows_S, num_attributes_S);

  // Perform simplified natural join
  vector<vector<string>> joined_relation = natural_join(R, S);

  if (!joined_relation.empty()) {
    cout << "\nNatural Join Result:\n";
    for (const vector<string>& row : joined_relation) {
      for (const string& value : row) {
        cout << value << " ";
      }
      cout << endl;
    }
  } else {
    // Handle the case where the join fails (commented out for brevity)
    // cout << "Join not possible." << endl;
  }

  return 0;
}
