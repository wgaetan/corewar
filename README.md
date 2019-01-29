# corewar

Project based around the famous exercise Corewar, we worked in a group of 3 students.

The project is splitted in 2 parts, one programm calles "asm" and one called "corewar".

The "corewar" part is the Virtual Machine that read bytecode from a ".cor" binary file and manage the game.

The "asm" part take ".s" files, written in a kind of asm language (specific to this project), parse them and translate them into bytecode understandable by the VM.

I wrote the full code of the "asm" programm, while my mates did the VM.

Synopsis:
	`$ ./asm [options] file_name`

Options:
* -h: Show this usage. (override any other options)
* -v: Detailed errors message if there is errors in file.
* -d: Display a visual representation of how the compiler parse the file.


The -v and -d were bonuses.

The "asm" is basically splitted into 3 parts:
* A lexer that split ".asm" file's content into tokens.
* A checking part, that validate each tokens based on rules depending of the token's type.
* An evaluation part that translate each tokens into bytecode.
* The last part write the bytecode previously translated into the output file (a ".cor" file).

(a ".s" file can be found at the root of the repository, in order to test the "asm").
  
  
