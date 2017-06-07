My todo app has all the required capabilities, including listing by priority and error handling. 

This version contains the following bug fixes: 
-remove task option - priorities and checks are also removed now
-read from file works perfectly (reads till the end of the line)

Additional feature:
Priorities can be added two ways. 
1. To a new task: -p "Feed the monkey" 2
2. To an already existing task, giving the task id: 
	'-p "3" 2' will give task 3 the priority of 2.

Printing usage info:
Originally, the usage info was always read in from the file and printed. Now the text is
read into a character array which is printed out when necessary.
