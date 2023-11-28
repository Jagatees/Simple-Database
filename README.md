# Linked List Simple Database

## Overview
The Linked List Simple Database is a basic database management system implemented in C. It uses a linked list structure to store and manage key-value pairs, and the data is persisted in a text file. This project provides a simple command-line interface for users to interact with the database, allowing operations such as insert, update, delete, query, and show all.

## Project Structure
- **database.h**: Header file containing function declarations for database operations.
- **databaseNode.h**: Header file defining the structure of a linked list node for key-value pairs.
- **main.c**: Main program file containing the entry point and the main loop for user interaction.
- **utility.h**: Header file for storing general variables and utility functions.

## Compilation and Execution
To compile the project, use a C compiler. For example:
```bash
gcc main.c database.c databaseNode.c -o linked-list-database
```

## User Commands

- **SHOW ALL:** Display all records in the database.
- **INSERT:** Add a new record to the database.
- **QUERY:** Retrieve and display specific data based on user-defined criteria.
- **UPDATE:** Modify an existing record in the database.
- **SAVE:** Save the current database state to a text file.
- **OPEN:** Load a database from a text file.
- **DELETE:** Remove a record from the database.
- **EXIT:** Exit the database.

## Project Usage

1. Upon running the program, you will be prompted to enter commands.
2. Enter one of the commands mentioned above along with any required parameters.
3. Follow the on-screen instructions to complete the specified operation.
4. The database state is maintained in memory and can be saved to/loaded from a text file.

## Contributing

Contributions to the project are welcome! If you'd like to contribute, fork the repository, create a new branch for your feature or bug fix, make your changes, and submit a pull request.



<table>
  <tr>
        <td align="center"><a href="https://github.com/Jagatees"><img src="https://avatars.githubusercontent.com/u/140966272?s=400&u=4366692093a55d4fda2ba7b4a0b5aa221f8ac0b3&v=4" width="100px;" alt=""/><br /><sub><b>Jagatees</b></sub></a><br />
    </td>
    <td align="center"><a href="https://github.com/Stars1999"><img src="https://avatars.githubusercontent.com/u/25857617?v=4" width="100px;" alt=""/><br /><sub><b>Stars1999</b></sub></a><br />
    </td>  
    <td align="center"><a href="https://github.com/Hexqne
"><img src="https://avatars.githubusercontent.com/u/53991762?v=4" width="100px;" alt=""/><br /><sub><b>Hexqne
</b></sub></a><br />
    </td> 
    <td align="center"><a href="https://github.com/
Jongohzh"><img src="https://avatars.githubusercontent.com/u/44186596?v=4" width="100px;" alt=""/><br /><sub><b>
Jongohzh</b></sub></a><br />
    </td> 
    <td align="center"><a href="https://github.com/yechenkhoo"><img src="https://avatars.githubusercontent.com/u/144420206?v=4" width="100px;" alt=""/><br /><sub><b>yechenkhoo</b></sub></a><br />
    </td> 
  </tr>
</table>
