# Transazioni finanziarie
Financial Transactions Management System
A C++ application for managing checking account transactions with file-based persistence.

> [!WARNING]\
> This project uses the latest GTest for Unit testing, please use:
>```
> git clone --recurse-submodules https://github.com/SamueleACarradori/TransazioniFinanziarie.git
>```

## 🏗️ Project Architecture
+ `User`    Represents a bank account user with personal information and account management capabilities
+ `CheckingAccount`     Manages the checking account balance and provides deposit/withdrawal functionality
+ `Transaction` 	Represents individual financial transactions between account holders with amounts and timestamp
+ `Date`	Utility class for handling date operations and formatting across the application
+ `FileManager`     Handles file input/output operations for reading and writing data 
+ `IFileConfig`  Interface created for the explicit purpose of giving a common implementation for classes that want to save/loading from file. 


> [!NOTE]\
> This project is made for didactical purposes only.
