## Unix Shell 
This project creates a unix shell that supports 10 commands.

# What the project does not support
The project does not support
* Tabs and auto completion 
* Whitespace normalization & collapsing 
* Options and arguments of the commands, e.g. -r, -ls

# What the project supports
* Home paths : ~/folder/file.txt
* Relative paths : ./folder/   folder/folder2/file.txt
* Absolute paths : /home/user/folder
* Parent paths : ../folder/folder2/file.txt

## Supported commands
The project supports the following 10 commands

# cd
cd command can take the following parameters
* Goes to the parent directory : cd ..
* Goes to what path is given : cd /home/user/folder/  OR cd ~/folder/  cd folder/  cd ../folder/ cd ./folder/
* Goes to home directory : cd 
The function does not support:
* Error checking, it will not give error if give an invalid path 

# pwd
pwd command does not take any arguments it just prints the current path

# ls
ls command does not take any arguments it just prints the contents of the folder and not the contents of all directories included

# echo
echo commad prints anything typed after it, does not need " " marks

# whoami
whoami command does not take any arguments or options it just prints the home directory

# touch
touch command creates multiple files for any kind of path given. A valid example that creaets 5 files is the following:
* touch ~/folder/file1.txt /home/user/file2.txt  ../folder/file3.txt ./folder/file4.txt folder/file5.txt  

touch command gives an error if an invalid path is given

# rm
rm command deletes multiple files for any kind of path given. A valid example that deletes 5 files is the following:
* rm ~/folder/file1.txt /home/user/file2.txt  ../folder/file3.txt ./folder/file4.txt folder/file5.txt  
rm command gives an error if an invalid path is given
rm command does not support any options

# mkdir_m
mkdir_m command creates multiple folders for any kind of path given. A valid example that creates 6 folders is the following:
* mkdir_m ~/folder/folder1 /home/user/folder2  ../folder/folder3 ./folder/folder4 folder/file5 or folder6  
mkdir_m command gives an error if an invalid path is given
mkdir_m command does not support any options
In order to create the command i used mkdir function so i renamed mine as mkdir_m

# cp
cp command copies only one file from one destination to another and if the destination name is not given it will use the name of the source file.
Valid examples of cp command are:
* cp ~/folder/file.txt what/ever/path/    or  ~/folder/file.txt what/ever/path/file_name.txt
* cp this_folder/file.pdf  ~/what/ever/path or this_folder/file.pdf  ~/what/ever/path/file_name.txt
* cp file.txt ./folder/   and ./folder/new_name.txt
* cp ../file.txt  ~/folder/whatever_name.txt 
So it typically supports any type of path and any type of name (given or not) for the copied file.


# wc
wc command prints the number of lines, words and the path of the given file.
it can take any valid path to the desired file.
Wc support line and word counting for only .txt files and not other files e.g pdf
In cases of .pdf files it prints correctly only the size of bytes of the file and gives a message claiming that lines and words numbers are invalid beacause the file provided is a .pdf file.


