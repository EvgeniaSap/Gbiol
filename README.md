# Gbiol
A console game in the format of a short biology test for schoolchildren.

## Using Gbiol
When you start the program, a menu will open that allows you to choose: 
- read the preparatory materials for the test; 
- pass the test; 
- view information about the developer; 
- exit the program.


Before passing the test, you can set the difficulty (from 1 to 5) of the questions that will be in the test. It is also possible to pass the test completely and pass the test with questions sorted by increasing difficulty.

Upon completion of the test, the student is given a total score for the test.

## Classes
Used classes:
- СntrlQuest – abstract base class;
- Test - child class from the base class;
- Test1 - child class from the first derivative;
- Test2 - child class from the first derivative.

See ![Class Diagram](https://github.com/EvgeniaSap/Gbiol/issues/1#issue-1391633224).
## Data organization
Input:
- text file `теория.txt` with theoretical material;
- text file `вопросы.txt` with control questions;
- lines containing answers to questions;
- a positive integer that specifies the maximum complexity of the questions for the user;
- positive integer – menu key.

Output:
- text file `ответы.txt` with test results;
- report on the work of the program;
- list of diagnostic messages.
