# Bank System (C++) 🏦  

A secure banking system developed in C++ using Object-Oriented Programming (OOP) principles.  

## ✨ Features  
- User registration & login  
- Deposit/withdraw money  
- Check account balance  
- View transaction history  

## 🚀 Quick Start  

### 🔑 Default Admin Credentials  
For full system access, use:  
Username: fouad@200  
Password: 1111  

### ⚙️ Installation  
# 1. Clone repository
git clone https://github.com/FouadSabbouh/Bank_system.git

# 2. Compile (requires OpenSSL)
g++ -std=c++17 *.cpp -o bank_system -lssl -lcrypto

# 3. Run
./bank_system
## 🏗️ System Structure  
Bank_system/
├── main.cpp        # Main program
├── user.[cpp|h]    # User management
├── bank.[cpp|h]    # Banking operations
└── users.txt       # User database
## 💻 Usage Guide  
1. Login with admin credentials  
2. Main Menu:  
   - [1] Create account  
   - [2] Deposit funds  
   - [3] Withdraw funds  
   - [4] Check balance  
   - [5] View all users (admin)  

## 🛠️ Dependencies  
- C++17 compiler  


