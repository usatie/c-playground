#!/Users/shunusami/Desktop/42/c-playground/shell/minishell
# Display a `prompt`
# Have a working `history`
# Search and launch the right executable
history
ls
echo Hello
cat Makefile
wc Makefile
touch .tmp
ls
rm .tmp
ls
mkdir .tmp_dir
ls
rm -f .tmp_dir
ls
history

# Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
echo ';'
echo ;
echo '\'
echo \

# Handle ’ (single quote) which should prevent the shell from interpreting the meta- characters in the quoted sequence.
echo 'Hello\tWorld\n'
echo '$PATH'

# Handle " (double quote) which should prevent the shell from interpreting the meta- characters in the quoted sequence except for $ (dollar sign).
echo "Hello\tWorld\n"
echo "$PATH"

# > redirect output 
echo "hello" > hello.txt
cat hello.txt
echo "world" > hello.txt
cat hello.txt

# < redirect input
cat < hellot.txt
wc < hellot.txt

# pipes
cat Makefile
cat Makefile | grep ".c"
cat Makefile | grep ".c" | wc

# environment variables
env

# Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
echo $?

# Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
## In interactive mode:
### ctrl-C displays a new prompt on a new line.
### ctrl-D exits the shell.
### ctrl-\ does nothing.

# Your shell must implement the following builtins:
## echo with option -n
echo -n "hello"
echo "hello" -n

## cd with only a relative or absolute path
mkdir .tmp_dir
ls
cd .tmp_dir
ls
cd ..
ls
rm -f .tmp_dir

cd /usr
ls

## pwd with no options
pwd

## export with no options
export
export hoge=fuga
export

## unset with no options
unset
unset hoge

## env with no options or arguments
env

## exit with no options
exit
