#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;

const int numProcesses = 5; // P0 to P4
const int numResources = 3; // A, B, and C

bool safeState(int processes[], int available_resources[], int max_required[][numResources], int allocation[][numResources]);

int main() {
    int i, j, looping;

    int alloc[5][3]; // Allocation Matrix P0 to P4
    int max[5][3]; // Max Matrix 
    int available[3] = {3, 3, 2}; // Available Resources

    int f[numProcesses], ans[numProcesses], index = 0;

    std::ifstream file;
    file.open("data.txt");

    for (int m = 0; m < numProcesses; ++m) {
        for (int l = 0; l < numResources; ++l) {
            
        
            if (file.is_open()) {
                std::string line;

                std::getline(file, line, ' ');
            
                std::stringstream ss;
                ss << line;
                int output;
                ss >> output;
                
                alloc[m][l] = output;
                
            }
        }
    }

    for (int m = 0; m < numProcesses; ++m) {
        for (int l = 0; l < numResources; ++l) {
            
        
            if (file.is_open()) {
                std::string line;

                std::getline(file, line, ' ');
            
                std::stringstream ss;
                ss << line;
                int output;
                ss >> output;
               
                max[m][l] = output;
                
            }
        }
    }

    for (int m = 0; m < numResources; ++m) {
        
        if (file.is_open()) {
           std::string line;

            std::getline(file, line, ' ');
            
            std::stringstream ss;
            ss << line;
            int output;
            ss >> output;
            
            available[m] = output;
            
        }
    }

    int processes[] = {0, 1, 2, 3, 4}; // P0 to p4
    safeState(processes, available, max, alloc);
   
}

bool safeState(int processes[], int available_resources[], int max_required[][numResources], int allocation[][numResources]) {

    int need[numProcesses][numResources];



    // Calculates the need of all processes and assigns it to the matrix "need"

    for (int i = 0 ; i < numProcesses ; i++) {

        for (int j = 0 ; j < numResources ; j++) {

            need[i][j] = max_required[i][j] - allocation[i][j];

        }

    }

    bool finish[numProcesses] = {0};
    int safe_sequence[numProcesses];

    // Copy current available resources

    int currently_available[numResources];
    for (int i = 0; i < numResources ; i++) currently_available[i] = available_resources[i];

    int index = 0;

    while (index < numProcesses) {

        bool found = false;

        //  A nested for loop to determine if work (available) is less less than or equal to need

        for (int p = 0; p < numProcesses; p++) {

            if (finish[p] == 0) {

                int j;
                for (j = 0; j < numResources; j++) {

                    if (need[p][j] > currently_available[j]) break;

                }

                if (j == numResources) {

                   // If the process is less than equal to work the following loop is ran to update work.
                    for (int k = 0 ; k < numResources ; k++) {

                        currently_available[k] += allocation[p][k];

                    }

                    safe_sequence[index] = p;
                    ++index;
                    finish[p] = 1;

                    // The process id is stored within the safe_sequence array, and the process is marked assigned true
                    found = true;

                }

            }

        }

        // If the system is not in a safe state, print out that result
        if (found == false) {

            cout << "No safe state\nNo safe sequence!";

            return false;

        }

    }

    // Safe state, so printing the safe sequence

      cout << "Safe state\n";
      cout << "Safe sequence is:\n <";

    for (int i = 0; i < numProcesses ; i++) 
    
    cout << " P" << safe_sequence[i] << " ";
    cout << ">\n";

    return true;

}