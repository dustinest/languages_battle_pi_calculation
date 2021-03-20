# Battle of languages

Recently I found fellow developers asking what is the best language for development and showing their "hello world" example.

Sure, every language has its perks and syntax but when it comes to implementing the business logic, maintenance and community support then the question is hard to answer.

## So I gave myself a goal.

Make easy application which is a CPU heavy to showcase what the language can do.
Use vanilla language - no external dependencies to exclude the community bias
The application must not use any external I/O to remove the slow down bias.
Single thread implementation as otherwise some languages have huge advantages!

## Why I chose those languages

C++ is a good reference to start with as it is closest to the speed as possible. Other languages listed below are popular among developers.

- C#;
- Java;
- JavaScript (Node.js);
- Go Lang;
- Python.

## Why PI calculation?

The PI calculation is the oldest problem to solve in software engineering. It is a CPU heavy and can easily showcase what language can do.

## What does it demonstrate

The syntax is quite similar, there are some perks and problems based on the language but overall the code length is almost the same but results do differ!
When C++, Java and C# are quick to solve the problem (in my test machine C++ and Java are fighting for the first place)
then Node.js is decent, Go Lang and Python came last with Python even so painfully it did not finish 10000 iterations in 24h in my test machine.

## What if I know more optimisation tricks.

Go ahead, do PR! 😍
