[![C++ Build and Release Pipeline](https://github.com/realRudraP/DAC/actions/workflows/build.yml/badge.svg)](https://github.com/realRudraP/DAC/actions/workflows/build.yml)
# Discretionary Access Control System

A C++ implementation of a Discretionary Access Control (DAC) system using linked lists. This program allows users to create access policies and check access permissions for various subjects and objects in a system.

## Overview

This application implements a Discretionary Access Control mechanism where:

- Users can create subjects (users, processes, etc.) and objects (files, directories, databases, etc.)
- Access rights can be granted or revoked for specific subject-object pairs
- The system maintains an access control list (ACL) using linked lists
- Users can check if a subject has specific rights to an object

## Features

- **Two-Mode Operation**:
  - Policy Creation Mode: Create subjects, objects, and grant/revoke permissions
  - Access Check Mode: Verify access permissions for subject-object pairs
  
- **Object Types**:
  - File
  - Process
  - Directory
  - Database
  - Device

- **Access Rights**:
  - Read (r)
  - Write (w)
  - Own (o)
  - Execute (x)
  - Run
  - Open
  - Stop
  - Search
  - Access

- **User-Friendly Interface**:
  - Color-coded terminal output
  - Comprehensive help system
  - Clear feedback on operations

## Commands

### Policy Creation Mode

- `Create Subject <Subject name>` - Create a new subject
- `Create <Object Type> <Object Name>` - Create a new object
- `Grant <Subject Name> <Object Name> [Rights]` - Grant permissions
- `Revoke <Subject Name> <Object Name> [Rights]` - Remove permissions
- `Check <Subject Name> <Object Name> <Right>` - Check if a subject has a specific permission
- `Help` - Display help information
- `Done` - Finish creating policies and move to access check mode

### Access Check Mode

- `<Subject Name> <Object Name> <Right>` - Check if a subject has permission to perform an action on an object
- `Exit` - End the program

## Implementation Details

- The system uses a linked list structure to maintain the access control lists
- Case-insensitive subject and object names
- Object-specific valid rights (e.g., Execute is only valid for Process objects)
- Color-coded terminal interface for better user experience

## Building and Running

```bash
# Compile the program
g++ -o dac main.cpp parser.cpp manager.cpp command.cpp utils.cpp -I./include

# Run the program
./dac
```

## Example Usage

### Creating Access Policies

```
Create Subject alice
Create file document.txt
Grant alice document.txt read write
Check alice document.txt read
```

### Checking Access

```
alice document.txt read
```

## Project Structure

- `main.cpp` - Program entry point and main loops
- `parser.cpp/.h` - Command parsing
- `manager.cpp/.h` - Access control functionality
- `command.cpp/.h` - Command representation
- `utils.cpp/.h` - Utility functions
- `colors.h` - ANSI color definitions for terminal output

## Notes

- Subject and object names are case-insensitive
- Multiple rights can be specified in Grant and Revoke commands
- Rights can be specified using full names (read, write) or shortcuts (r, w, o, x) where applicable
