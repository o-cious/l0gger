#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>

class ClickLogger {
public:
    void logClick(int x, int y) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        
        std::string timestamp = std::ctime(&time);
        timestamp.erase(timestamp.length() - 1); // Remove newline character

        std::string logEntry = "Clicked at (" + std::to_string(x) + ", " + std::to_string(y) + ") on " + timestamp;
        logs.push_back(logEntry);
    }

    void showLogs() const {
        if (logs.empty()) {
            std::cout << "No logs available.\n";
            return;
        }
        std::cout << "Click Logs:\n";
        for (const auto& log : logs) {
            std::cout << log << "\n";
        }
    }

    void clearLogs() {
        logs.clear();
        std::cout << "Logs cleared.\n";
    }

    void filterLogs(const std::string& filter) const {
        std::cout << "Filtered Logs:\n";
        bool found = false;
        for (const auto& log : logs) {
            if (log.find(filter) != std::string::npos) {
                std::cout << log << "\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "No logs match the filter.\n";
        }
    }

private:
    std::vector<std::string> logs;
};

int main() {
    ClickLogger logger;
    int x, y;
    char option;
    std::string filter;

    while (true) {
        std::cout << "\nClick Logger Menu:\n";
        std::cout << "1. Log a Click\n";
        std::cout << "2. Show Logs\n";
        std::cout << "3. Clear Logs\n";
        std::cout << "4. Filter Logs\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option (1-5): ";
        std::cin >> option;

        switch (option) {
            case '1':
                std::cout << "Enter X coordinate: ";
                std::cin >> x;
                std::cout << "Enter Y coordinate: ";
                std::cin >> y;
                logger.logClick(x, y);
                break;
            case '2':
                logger.showLogs();
                break;
            case '3':
                logger.clearLogs();
                break;
            case '4':
                std::cout << "Enter filter string: ";
                std::cin >> filter;
                logger.filterLogs(filter);
                break;
            case '5':
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Advanced Click Logger</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <header>
        <h1>Advanced Click Logger</h1>
    </header>
    <main>
        <button id="logButton">Click Me!</button>
        <button id="clearLogs">Clear Logs</button>
        <input type="text" id="filterInput" placeholder="Filter logs...">
        <ul id="logList"></ul>
    </main>
    <footer>
        <p>Click logger application for demo purposes.</p>
    </footer>

    <script src="script.js"></script>
</body>
</html>
body {
    font-family: Arial, sans-serif;
    margin: 20px;
    background-color: #f4f4f4;
}

header {
    text-align: center;
    margin-bottom: 20px;
}

button {
    padding: 10px 15px;
    font-size: 16px;
    margin-right: 10px;
    cursor: pointer;
    background-color: #007bff;
    color: white;
    border: none;
    border-radius: 5px;
    transition: background-color 0.3s;
}

button:hover {
    background-color: #0056b3;
}

input {
    padding: 10px;
    font-size: 16px;
    margin-left: 10px;
}

ul {
    margin-top: 20px;
    list-style-type: none;
    padding: 0;
    max-width: 600px;
    margin: 0 auto;
    background-color: white;
    border-radius: 5px;
    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
}

li {
    margin: 5px;
    padding: 10px;
    border-bottom: 1px solid #ddd;
}

li:last-child {
    border-bottom: none;
}

footer {
    text-align: center;
    margin-top: 20px;
    font-size: 14px;
    color: #666;
}document.addEventListener('DOMContentLoaded', () => {
    const logButton = document.getElementById('logButton');
    const clearLogsButton = document.getElementById('clearLogs');
    const filterInput = document.getElementById('filterInput');
    const logList = document.getElementById('logList');

    let logs = [];

    logButton.addEventListener('click', function(event) {
        const time = new Date().toLocaleString();
        const x = event.clientX;
        const y = event.clientY;

        const logEntry = `Clicked at (${x}, ${y}) on ${time}`;
        logs.push(logEntry);
        updateLogList();
    });

    clearLogsButton.addEventListener('click', function() {
        logs = [];
        updateLogList();
    });

    filterInput.addEventListener('input', function() {
        updateLogList();
    });

    function updateLogList() {
        logList.innerHTML = '';
        const filterText = filterInput.value.toLowerCase();

        const filteredLogs = logs.filter(log => log.toLowerCase().includes(filterText));
        filteredLogs.forEach(log => {
            const logItem = document.createElement('li');
            logItem.textContent = log;
            logList.appendChild(logItem);
        });
    }
});
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>

class ClickLogger {
public:
    ClickLogger(const std::string& filename) : filename(filename) {
        loadLogs();
    }

    void logClick(int x, int y) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        
        std::string timestamp = std::ctime(&time);
        timestamp.erase(timestamp.length() - 1); // Remove newline character

        std::string logEntry = "Clicked at (" + std::to_string(x) + ", " + std::to_string(y) + ") on " + timestamp;
        logs.push_back(logEntry);
        saveLog(logEntry);
    }

    void showLogs() const {
        if (logs.empty()) {
            std::cout << "No logs available.\n";
            return;
        }
        std::cout << "Click Logs:\n";
        for (const auto& log : logs) {
            std::cout << log << "\n";
        }
    }

    void clearLogs() {
        logs.clear();
        std::ofstream outFile(filename, std::ios::trunc);
        if (outFile) {
            std::cout << "Logs cleared and file truncated.\n";
        }
        outFile.close();
    }

    void filterLogs(const std::string& filter) const {
        std::cout << "Filtered Logs:\n";
        bool found = false;
        for (const auto& log : logs) {
            if (log.find(filter) != std::string::npos) {
                std::cout << log << "\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "No logs match the filter.\n";
        }
    }

private:
    std::vector<std::string> logs;
    std::string filename;

    void saveLog(const std::string& logEntry) const {
        std::ofstream outFile(filename, std::ios::app);
        if (outFile) {
            outFile << logEntry << "\n";
        }
        outFile.close();
    }

    void loadLogs() {
        std::ifstream inFile(filename);
        if (!inFile) return;

        std::string line;
        while (std::getline(inFile, line)) {
            logs.push_back(line);
        }
        inFile.close();
    }
};

int main() {
    ClickLogger logger("click_logs.txt");
    int x, y;
    char option;
    std::string filter;

    while (true) {
        std::cout << "\nClick Logger Menu:\n";
        std::cout << "1. Log a Click\n";
        std::cout << "2. Show Logs\n";
        std::cout << "3. Clear Logs\n";
        std::cout << "4. Filter Logs\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option (1-5): ";
        std::cin >> option;

        switch (option) {
            case '1':
                std::cout << "Enter X coordinate: ";
                std::cin >> x;
                std::cout << "Enter Y coordinate: ";
                std::cin >> y;
                logger.logClick(x, y);
                break;
            case '2':
                logger.showLogs();
                break;
            case '3':
                logger.clearLogs();
                break;
            case '4':
                std::cout << "Enter filter string: ";
                std::cin.ignore();  // Ignore leftover newline
                std::getline(std::cin, filter);
                logger.filterLogs(filter);
                break;
            case '5':
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
