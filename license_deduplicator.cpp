#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <map>
using namespace std;

// Struct to hold license record
struct LicenseRecord {
    int licenseNumber;
    string info;

    bool operator<(const LicenseRecord& other) const {
        return licenseNumber < other.licenseNumber;
    }
};

// Class to hold sorted list of unique license numbers
class SortedList {
private:
    set<int> licenseNumbers;
    vector<LicenseRecord> records;

public:
    bool insert(const LicenseRecord& record) {
        if (licenseNumbers.find(record.licenseNumber) != licenseNumbers.end()) {
            return false; // Duplicate found
        }
        licenseNumbers.insert(record.licenseNumber);
        records.push_back(record);
        return true;
    }

    const vector<LicenseRecord>& getRecords() const {
        return records;
    }
};

int main() {
    SortedList sortedList;
    map<int, LicenseRecord> firstOccurrences;
    ofstream duplicatesFile("duplicates.dat");

    if (!duplicatesFile.is_open()) {
        cerr << "Could not open duplicates.dat for writing.\n";
        return 1;
    }

    cout << "Enter license records (8-digit number followed by name and address).\n";
    cout << "Type END to finish input.\n";

    string line;
    while (getline(cin, line)) {
        if (line == "END") break;
        if (line.length() < 8) continue;

        string licensePart = line.substr(0, 8);
        int licenseNumber;

        try {
            licenseNumber = stoi(licensePart);
        } catch (...) {
            continue; // skip invalid line
        }

        string info = line.substr(9); // after license number
        LicenseRecord record{licenseNumber, info};

        if (!sortedList.insert(record)) {
            if (firstOccurrences.find(licenseNumber) == firstOccurrences.end()) {
                for (const auto& rec : sortedList.getRecords()) {
                    if (rec.licenseNumber == licenseNumber) {
                        duplicatesFile << rec.licenseNumber << " " << rec.info << "\n";
                        firstOccurrences[licenseNumber] = rec;
                        break;
                    }
                }
            }
            duplicatesFile << record.licenseNumber << " " << record.info << "\n";
        }
    }

    duplicatesFile.close();
    cout << "Duplicates written to duplicates.dat\n";
    return 0;
}