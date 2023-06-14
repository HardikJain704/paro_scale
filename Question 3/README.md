 In this example, the parse_top_output function reads the 
 contents of the input file line by line. It uses  regular expressions to extract the PIDs and users from each  line of the top output. The extracted PIDs are stored in a   vector, which is returned by the function.

 This is linux based so 

1. Run the top command in your terminal to see the list of processes and their details.

2. Redirect the output of the top command to a file by using the > symbol and specifying the file name. For example:

``` 
top > top_output.txt
```

3. Make sure the top_output.txt file is in the same directory as the C++ script

4. Open a terminal or command prompt and navigate to the directory where you saved the parse_top.cpp file.

5. Compile the code using a C++ compiler
```
g++ parse_top.cpp -o parse_top

```
This command will compile the parse_top.cpp file and generate an executable binary named parse_top.

6. After successful compilation, run the executable binary using the following command:

``` 
./parse_top

```


After that we will Get all the PIDS which are running. 