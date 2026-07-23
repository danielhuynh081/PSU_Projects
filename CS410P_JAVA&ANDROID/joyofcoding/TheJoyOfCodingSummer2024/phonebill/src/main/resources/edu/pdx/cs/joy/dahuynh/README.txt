This is a README file!

Daniel Huynh CS410P Project 1 July 15th, 2024 Professor Whitlock

This is the phone bill program.
this program allows users to input command line arguments into phonecall objects and display them with a bill

Users must run the program with java -jar target/phonebill-1.0.0.jar *Options* *arguments*
The format for the command line arguments is "Name" "555-555-5555"(caller) "555-555-5555"(callee) "12/25/5555"(begin date) "12:12"(begin time) "12/25/5555"(end date) "12:12"(end time)

**Important Notes**
- When writing both first and last name, there must be quotation marks. ("Steve Jobs")
- Caller and Callee Phone numbers are formatted to be 10 digit numbers with hyphens separating each segment, hyphens have to be manually typed in.
- Begin and End Dates are Month/Day/Year.
- Begin and End Times are based on 24 hour military time.


when there are no arguments given to the command line or if the argument format is incorrect, no phone call gets stored to the bill.

Options:
-print : Print the Phone Bill with the newly entered phone call
-README : Print the README File

