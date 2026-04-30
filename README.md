🏦 ATM System Project (C++ Console Application)
📌 Overview

This project is a fully functional ATM Simulation System built using C++ (Console Application).
It simulates real-world banking operations such as login authentication, balance inquiry, deposits, withdrawals, and quick cash operations with secure validation and file-based data persistence.

The system is designed with a modular structure, clean separation of logic, and focuses on real banking workflows and user experience in a console environment.

🚀 Features
🔐 Authentication System
Secure login using Account Number + PIN Code
Maximum of 3 login attempts
Account lock simulation after failed attempts
User session handling
💰 Banking Operations
💵 Deposit money
💸 Normal withdrawal (multiples of 5 validation)
⚡ Quick withdrawal (preset amounts)
📊 Check account balance
🚪 Logout system
🧠 Smart Validations
Prevent overdraft (no negative balance)
Input validation (numbers, strings, doubles)
Transaction confirmation before execution
Balance consistency across file system
📂 File Handling System
Load clients data from file (MyClients.txt)
Save updated balances automatically
Convert structured data ↔ file records
Persistent storage simulation
🏗️ System Architecture

The project is built with a clean layered structure:

Struct Layer
Client data model (stClient)
Enums Layer
Main menu options
Quick withdraw options
Core Logic Layer
Login system
Transaction processing
Balance management
Utility Layer
Input handling (int, double, string)
Console styling (colors, loading effects)
Screen control (clear, pause)
File System Layer
Read/write operations
Data persistence
🧾 Data Model

Each client contains:

struct stClient {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};

Stored in file format:

AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance
🧮 Business Logic
💳 Quick Withdraw Options
20, 50, 100, 200, 400, 600, 800, 1000
⚠️ Rules
Balance must be sufficient
Amount must be valid
User must confirm transaction
🔐 Security Features
PIN verification system
Limited login attempts (3 tries)
Account lock message
Transaction confirmation step
🛠️ Technologies Used
C++ (OOP + Procedural mix)
File Handling (fstream)
Windows Console API (colors, sleep)
STL (vector, string)
Basic system commands (cls, pause)
📷 Project Flow
User Login
Validate Account
Show Welcome Screen
Main Menu:
Quick Withdraw
Normal Withdraw
Deposit
Check Balance
Logout
File updates automatically
🎯 Key Highlights
Real ATM simulation logic
Clean modular design
Persistent file storage
Professional console UI
Strong input validation system
Beginner → Advanced level C++ structure
📌 Future Improvements
GUI version (Qt / WinForms)
Database integration (MySQL / SQLite)
Multi-user roles (Admin / Customer)
Transaction history log
Encryption for PIN codes
👨‍💻 Author

Tarek Mahmoud
Computer Science Student | ICPC Participant
Passionate about Backend Systems & Problem Solving

⭐ If you like this project

Give it a ⭐ on GitHub and feel free to contribute or suggest improvements.
