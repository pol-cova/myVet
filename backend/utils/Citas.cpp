#pragma once
#include <string>
#include <vector>
#include <unordered_set>

// Global set of booked hours
std::unordered_set<std::string> bookedHours;

class Citas {
public:
    static std::vector<std::string> getAvailableHoursForToday(const std::string& date, const std::unordered_set<std::string>& booked) {
        // Standard clinic hours: 9 AM to 5 PM
        const std::vector<std::string> allHours = {
            "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00"
        };
        std::vector<std::string> available;
        available.reserve(allHours.size());
        for (const auto& hour : allHours) {
            std::string key = date + " " + hour;
            if (!booked.contains(key)) {
                available.push_back(hour);
            }
        }
        return available;
    }
};
